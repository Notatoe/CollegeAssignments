// Noah Morris
// Dunn - Section 3
// 08/27/2019
// For Lab 2
// TA: Angel
// Ask the user the address of a building and the price of the building from last month and this month, then display a string that shows the price change.

#include <iostream>
#include <string>
using namespace std;

int main()
{
	//initilaize the integers and string for the address and building cost
	int streetNum;
	string streetAddress;
	string streetType;
	int lastMonth;
	int thisMonth;
	
	//ask for street adress
	cout << "Enter the building's street address: ";
	cin >> streetNum >> streetAddress >> streetType;

	//ask for the value of last and this month
	cout << "Enter last month's value: ";
	cin >> lastMonth;
	cout << "Enter this month's value: ";
	cin >> thisMonth;

	//print the statement that says how the value of the address has changed from the two months 
	cout << "The building located at " << streetNum << " " << streetAddress << " " << streetType << endl;
	cout << "was worth $" << lastMonth << " last month,\n";
	cout << "and is now worth $" << thisMonth << " this month.\n";

	return 0;
}
