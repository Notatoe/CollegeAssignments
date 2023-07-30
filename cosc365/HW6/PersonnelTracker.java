// Noah Morris
// nmorri11

import java.io.*;
import java.util.*;

public class PersonnelTracker
{
    // Person class carries values used by everyone
    static class Person
    {
        String name;
        String SSN;
        char gender;
    }

    // Student class that from extends from Person for students
    static class Student extends Person
    {
        float GPA;
        int year;

        Student() {}
    }

    // Employee class that from extends Person for staff and faculty
    static class Employee extends Person
    {
        String position;
        double salary;
    }

    // Staff class that extends from Employee for staff members
    static class Staff extends Employee
    {
        int vacationDays;

        Staff() {}
    }

    // Faculty class that extends from Employee for faculty members
    static class Faculty extends Employee
    {
        String rank;
        
        Faculty() {}
    }

    public static void main(String[] args) throws IOException
    {
        // student values used for Answers.txt
        int studentCount = 0;
        int staffCount = 0;
        int facultyCount = 0;
        int mStudentCount = 0;
        int fStudentCount = 0;
        double fGPA = 0;
        double mGPA = 0;
        int m4 = 0;
        int f4 = 0;

        // Arraylists to hold the students, staff, and faculty seperately
        ArrayList<Student> students = new ArrayList<Student>();
        ArrayList<Staff> staffMembers = new ArrayList<Staff>();
        ArrayList<Faculty> facultyMembers = new ArrayList<Faculty>();

        // Opens up the PersonnelEntries.csv file
        FileReader inputFile = new FileReader("PersonnelEntries.csv");
        BufferedReader reader = new BufferedReader(inputFile);
        String line = reader.readLine();

        // While still reading in lines
        while(line != null)
        {
            // splits the line into an array with each index being sperated from commas in the line
            String[] temp = line.split(",");

            // If the person is a staff member
            if(temp[3].equals("Staff"))
            {
                // increment staff counter
                staffCount++;

                // initialize and assign values to new Staff object
                Staff temp2 = new Staff();
                temp2.name = temp[0];
                temp2.SSN = temp[1];
                temp2.gender = temp[2].charAt(0);
                temp2.position = temp[3];
                temp2.salary = Double.parseDouble(temp[4]);
                temp2.vacationDays = Integer.parseInt(temp[5]);
                
                // add the staff object to the staff arraylist
                staffMembers.add(temp2);
            }
            // if the person is a faculty member
            else if(temp[3].equals("Faculty"))
            {
                // increment faculty counter
                facultyCount++;

                // initialize and assign values the the new faculty object
                Faculty temp2 = new Faculty();
                temp2.name = temp[0];
                temp2.SSN = temp[1];
                temp2.gender = temp[2].charAt(0);
                temp2.position = temp[3];
                temp2.salary = Double.parseDouble(temp[4]);
                temp2.rank = temp[5];
                
                // add the faculty object to the faculty arraylist
                facultyMembers.add(temp2);
            }
            // else the person is a student
            else
            {
                // increment the student counter
                studentCount++;

                // initialize and assign values to the student object
                Student temp2 = new Student();
                temp2.name = temp[0];
                temp2.SSN = temp[1];
                temp2.gender = temp[2].charAt(0);
                temp2.GPA = Float.parseFloat(temp[3]);
                temp2.year = Integer.parseInt(temp[4]);

                // check for gender for other statistics
                // if male
                if(temp2.gender == 'M')
                {
                    // increment male student counter, add GPA to the male GPA, and if the GPA was a 4, increment the male 4 counter
                    mStudentCount++;
                    mGPA += temp2.GPA;
                    if(temp2.GPA == 4)
                        m4++;
                }
                // if female
                else
                {
                    // increment female student counter, add GPA to the female GPA, and if the GPA was a 4, increment the female 4 counter
                    fStudentCount++;
                    fGPA += temp2.GPA;
                    if(temp2.GPA == 4)
                        f4++;
                }
                
                // add the student object to the student
                students.add(temp2);
            }

            // move the reader to the next line in the file
            line = reader.readLine();
        }
        // close the reader
        reader.close();

        // set the culminated male and female GPAs to the average by dividing it by the total of each gender
        mGPA = mGPA / mStudentCount;
        fGPA = fGPA / fStudentCount;

        // creates the Answers.txt document
        PrintWriter answers = new PrintWriter("Answers.txt");

        // print the values to the document in the correct format
        answers.printf("The number of students is : %d%n", studentCount);
        answers.printf("The number of staff is : %d%n", staffCount);
        answers.printf("The number of faculty is : %d%n", facultyCount);
        answers.printf("The number of female students is : %d%n", fStudentCount);
        answers.printf("The average female student's GPA is : %.2f%n", fGPA);
        answers.printf("The number of female students with a 4.0 GPA is : %d%n", f4);
        answers.printf("The number of male students is : %d%n", mStudentCount);
        answers.printf("The average male student's GPA is : %.2f%n", mGPA);
        answers.printf("The number of male students with a 4.0 GPA is : %d%n", m4);

        //close answers.txt
        answers.close();

        // sorts students by their social security number
        Collections.sort(students, new Comparator<Student>()
        {
            public int compare(Student student1, Student student2)
            {
                return student1.SSN.compareTo(student2.SSN);
            }
        });

        // sorts staff by their vacation days or social security number if vacation days are equal
        Collections.sort(staffMembers, new Comparator<Staff>()
        {
            public int compare(Staff staff1, Staff staff2)
            {
                if(staff1.vacationDays > staff2.vacationDays)
                    return 1;
                else if(staff1.vacationDays < staff2.vacationDays)
                    return -1;
                else if(staff1.vacationDays == staff2.vacationDays)
                {
                    return staff1.SSN.compareTo(staff2.SSN);
                }
                else
                    return 0;
            }
        });

        // sorts the faculty members by their salary
        Collections.sort(facultyMembers, new Comparator<Faculty>()
        {
            public int compare(Faculty faculty1, Faculty faculty2)
            {
                if(faculty1.salary > faculty2.salary)
                    return 1;
                else if(faculty1.salary < faculty2.salary)
                    return -1;
                else
                    return 0;
            }
        });

        //creates students.csv
        PrintWriter studentFile = new PrintWriter("Students.csv");
        
        // traverses the students array list
        for(int i = 0; i < students.size(); i++)
        {
            // creates a string of the student values in the correct format
            String temp = students.get(i).name + ',' + students.get(i).SSN + ',' +
            students.get(i).gender + ',' + students.get(i).GPA + ',' + students.get(i).year + '\n';

            // inserts the string to the document
            studentFile.printf(temp);
        }

        //closes Students.csv
        studentFile.close();

        //creates Staff.csv
        PrintWriter staffFile = new PrintWriter("Staff.csv");

        // traverses the staff array list
        for(int i = 0; i < staffMembers.size(); i++)
        {
            // creates a string of the staff values in the correct format
            String temp = staffMembers.get(i).name + ',' + staffMembers.get(i).SSN + ',' + staffMembers.get(i).gender + ',' +
            staffMembers.get(i).position + ',' + staffMembers.get(i).salary + ',' + staffMembers.get(i).vacationDays + '\n';

            // inserts the string to the document
            staffFile.printf(temp);
        }

        // closes Staff.csv
        staffFile.close();

        // creates Faculty.csv
        PrintWriter facultyFile = new PrintWriter("Faculty.csv");

        // traverses the faculty array list
        for(int i = 0; i < facultyMembers.size(); i++)
        {
            // creates a string of the faculty values in the correct format
            String temp = facultyMembers.get(i).name + ',' + facultyMembers.get(i).SSN + ',' + facultyMembers.get(i).gender + ',' + 
            facultyMembers.get(i).position + ',' + facultyMembers.get(i).salary + ',' + facultyMembers.get(i).rank + '\n';
            
            // inserts the string to the document
            facultyFile.printf(temp);
        }

        // closes Faculty.csv
        facultyFile.close();
    }
}