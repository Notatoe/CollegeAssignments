// Noah Morris
// 9/1/2020
// Cosc 140
// Homework 1
// This  program takes command line arguments, lists how many there are, gives each address, gives each string, and gives the length of each string

#include <iostream>
#include <string>

using namespace std;

//this function returns the length of each command line argument which is assigned to temp
int strlen(char* temp)
{
	//temp2 is the length and it starts at 0
	int temp2 = 0;

	//this while loop goes through every char of the command line argument and counts them until the end of the string
	while(*temp != 0)
	{
		temp++;
		temp2++;
	}

	//returns the final count of the command line argument length
	return temp2;
}

int main(int argc, char** argv)
{
	//outputs the amount of arguments
	cout << "Num args = " << argc << '\n';

	//outputs each argument as well as the address and the length of them
	for(int i = 0; i < argc; i++)
	{
		cout << "argv[" << i << "] = " << &argv[i] << " " << argv[i] << " (strlen=" << strlen(argv[i]) << ")\n";
	}
	return 0;
}

