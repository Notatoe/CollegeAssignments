// Noah Morris
// Dunn - Section 3
// 09/02/2019
// Lab 3
// TA: Angel
/* This program takes an inputted number and determines if it belongs to an primary interstate or auxiliary highway and which direction it goes in, if it is an auxiliary highway it also says which
 * interstate it serves*/

#include <iostream>
#include <string>
using namespace std;

int main()
{
	//initializes the interstate number
	int intNum;

	//asks the user for the interstate number
	cout << "Enter an interstate number: ";
	cin >> intNum;
	
	//checks to see if the number falls within the bounds of a primary interstate
	if(intNum >= 1 && intNum <= 99)
	{
		//prints the formatted sentence for primary interstates
		cout << "I-" << intNum << " is a primary interstate, going ";
	}

	//checks for invalid inputs and if it falls within the bounds of being a auxiliary highway
	else if((intNum % 100 != 0) && intNum >= 101 && intNum <= 999)
	{
		//prints the formatted sentence for auxiliary highways including which primary interstate it serves by using modular division on the inputed number
		cout << "I-" << intNum << " is an auxiliary highway, serving I-" << intNum % 100 << ", going ";
	}

	//only used if the input is not a valid number either the interstates or highways and prints a statement saying the input is not valid and terminates the program
	else
	{
		cout << intNum << " is not a valid interstate number." << endl;
		return 3;
	}
	
	//check if the number is even or odd to determine if it goes east/west or north/south
	if(intNum % 2 == 0)
	{
		//the number was even so it goes east/west
		cout << "east/west." << endl;
	}
	else
	{
		//the number was odd so it goes north/south
		cout << "north/south." << endl;
	}		

	return 0;
}
