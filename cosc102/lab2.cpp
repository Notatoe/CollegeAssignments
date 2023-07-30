// Noah Morris
// Dunn - Section 3
// 08/28/2019
// lab2
// TA: Angel
/* This program takes an address and values for this and last month's property value and then tells you the change in value as well as an estimated monthly
 * value */

#include <iostream>// imports iostream
#include <string>// imports string
using namespace std;

int main()
{
	//initilaize the integers and strings for the address and building cost
	int streetNum, lastMonth, thisMonth;
	string streetAddress, streetType;
	
	//ask for street adress
	cout << "Enter the building's street address: ";
	cin >> streetNum >> streetAddress >> streetType;
	
	//ask for the value of last and this month
	cout << "Last month's property value: ";
	cin >> lastMonth;
	cout << "This month's property value: ";
	cin >> thisMonth;
	
	//puts a emplty line in between the inputed values and the final statement
	cout << endl;

	//Give data on the location's change in value and monthly mortgage
	cout << "The building located at " << streetNum << " " << streetAddress << " " << streetType << "." << endl;
	cout << "Its value has changed by $" << thisMonth - lastMonth << " since last month.\n";
	cout << "The estimated monthly mortgage is $" << (thisMonth * 0.045)/12 << ".\n";

	return 0;
}
