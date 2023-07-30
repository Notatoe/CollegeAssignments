// Noah Morris
// Dunn - Section 3
// 09/25/2019
// Lab 6
// TA: Angel
/* This program takes a file that holds information about speeding tickets and creates another file that holds the fine for the speeding tickets
 * in the original file, but only those tickets that fall between dates that the user has given.*/ 

#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

int main()
{
	//ints for the start/end dates as well as ints and a char for temporary variables.
	int startMonth, endMonth, startDay, endDay, startYear, endYear, citationDay, citationMonth, citationYear, clockedSpeed, speedLimit, i;
	string ticket, output, citationNum, line;
	char roadType;

	//vectors used to hold information on the speeding tickets
	vector<string> citNum;
	vector<int> citDay, citMonth, citYear, clockedSpd, spdLimit;
	vector<double> fine;
	vector<char>  type;

	//array that holds abbriviations for the months in a year
	string month[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	//asks user to input the ticket file name
	cout << "Enter a ticket file: ";
	cin >> ticket;

	//creates ifstream and ofstream for the files
	ifstream fin;
	ofstream fout;

	//opens the file that the user gave
	fin.open(ticket);

	//error checks to make sure file exists
	if(!fin)
	{
		cerr << "Unable to open " << ticket << ".\n";
		return 1;
	}

	//records all of the information within each ticket
	do
	{
		fin >> citationNum;
		citNum.push_back(citationNum);
		fin >> citationMonth;
		citMonth.push_back(citationMonth);
		fin >> citationDay;
		citDay.push_back(citationDay);
		fin >> citationYear;
		citYear.push_back(citationYear);
		fin >> clockedSpeed;
		clockedSpd.push_back(clockedSpeed);
		fin >> speedLimit;
		spdLimit.push_back(speedLimit);
		fin >> roadType;
		type.push_back(roadType);
	}
	//deletes last input in each vector because it kept doubling the last ticket's information
	while(getline(fin, line));
	citNum.pop_back();
	citMonth.pop_back();
	citDay.pop_back();
	citYear.pop_back();
	clockedSpd.pop_back();
	spdLimit.pop_back();
	type.pop_back();
	
	//sets the year to be in the 2000s if the year is abbrievated
	for(i = 0; i < citNum.size(); i++)
	{
		if(citYear.at(i) >= 0 && citYear.at(i) < 1000)
		{
			citYear.at(i) += 2000;
		}
	}

	//asks the user for the name of the output file and creates it
	cout << "Enter a report file: ";
	cin >> output;
	fout.open(output);

	/*asks user for the start date to check if the ticket is within bounds. Checks for errors and if the date makes sense. Also checks leap-year
	 * and days in each month.*/
	do
	{
		if(!cin)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cout << "Enter report start date (mm dd yyyy): ";
	}
	while(!(cin >> startMonth >> startDay >> startYear) || startMonth > 12 || startMonth < 1 || startDay < 1 || ((startMonth == 1 || startMonth == 3 || startMonth == 5 || startMonth == 7 || startMonth == 8 || startMonth == 10 || startMonth == 12) && startDay > 31) || ((startMonth == 4 || startMonth == 6 || startMonth == 9 || startMonth == 11) && startDay > 30) || (startYear % 4 != 0 && startMonth == 2 && startDay > 28) || (startYear % 4 == 0 && startMonth == 2 && startDay > 29));

	/*asks user for the end date to check if the ticket is within bounds. Checks for errors and if the date makes sense. Also checks for leap-year
	 * and days in each month.*/
	do
	{
		if(!cin)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cout << "Enter report end date   (mm dd yyyy): ";
	}
	while(!(cin >> endMonth >> endDay >> endYear) || endMonth > 12 || endMonth < 0 || endDay < 0 || ((endMonth == 1 || endMonth == 3 || endMonth == 5 || endMonth == 7 || endMonth == 8 || endMonth == 10 || endMonth == 12) && endDay > 31) || ((endMonth == 4 || endMonth == 6 || endMonth == 9 || endMonth == 11) && endDay > 30) || (endYear % 4 != 0 && endMonth == 2 && endDay > 28) || (endYear % 4 == 0 && endMonth == 2 && endDay > 29));

	//checks to see if the ticket date falls within bounds
	for(i = 0; i < citYear.size(); i++)
	{
		if(startYear < citYear.at(i) && citYear.at(i) < endYear)
		{
			continue;
		}
		else if(citYear.at(i) == startYear)
		{
			if(citMonth.at(i) > startMonth)
			{
				continue;
			}
			else if(citMonth.at(i) == startMonth)
			{
				if(citDay.at(i) >= startDay)
				{
					continue;
				}
				else
				{
					citNum.at(i) = "No";
				}
			}
			else
			{
				citNum.at(i) = "No";
			}
		}
		else if(citYear.at(i) == endYear)
		{
			if(citMonth.at(i) < endMonth)
			{
				continue;
			}
			else if(citMonth.at(i) == endMonth)
			{
				if(citDay.at(i) <= endDay)
				{
					continue;
				}
				else
				{
					citNum.at(i) = "No";
				}
			}
			else
			{
				citNum.at(i) = "No";
			}
		}
		else
		{
			citNum.at(i) = "No";
		}
	}
	
	//calculates fine and puts it into the output file
	for(i = 0; i < citYear.size(); i++)
	{
		//sets fine for every ticket so that the fine lines up with the correct ticket
		fine.push_back(0.00);

		//dosen't calculate or record if the date is out of bounds
		if(citNum.at(i) == "No")
		{
			continue;
		}
		
		//calculates the fine for each ticket based on the type of road
		if(type.at(i) == 'i' || type.at(i) == 'I')
		{
			fine.at(i) = (clockedSpd.at(i) - spdLimit.at(i)) * 5.2252;
		}
		else if(type.at(i) == 'r' || type.at(i) == 'R')
		{
			fine.at(i) = (clockedSpd.at(i) - spdLimit.at(i)) * 17.1525;
		}
		else if(type.at(i) == 'h' || type.at(i) == 'H')
		{
			fine.at(i) = (clockedSpd.at(i) - spdLimit.at(i)) * 9.4412;
		}
		else
		{
			fine.at(i) = (clockedSpd.at(i) - spdLimit.at(i)) * 12.152;
		}
		
		//if the fine is negative it is set to 0
		if(fine.at(i) < 0.00)
		{
			fine.at(i) = 0.00;
		}
		
		//outputs fines and tickets that fall in bounds and puts it in the correct format.
		fout << setfill('0') << setw(2) << right << citDay.at(i);
		fout << setfill('-') << setw(4) << month[citMonth.at(i) - 1];
		fout << setw(1) << '-';
		fout << setw(4) << citYear.at(i);
		fout << setw(1) << ' ';
		fout << left << setfill(' ') << setw(10) << citNum.at(i);
		fout << setw(2) << " $";
		fout << right << setfill(' ') << setw(9) << fixed << setprecision(2) << fine.at(i) << '\n';
	}

	return 0;
}
