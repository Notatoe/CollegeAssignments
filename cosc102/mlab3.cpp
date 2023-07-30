// Noah Morris
// Dunn - Section 3
// 09/02/2019
// For Lab 3
// TA: Angel
// This program tells you whether an integer is even or odd

#include <iostream>
#include <string>
using namespace std;

int main()
{
	//initilaizes the inputed integer
	int num;
	
	//Asks the user for an integer value
	cout << "Input an integer: ";
	cin >> num;
	
	//Uses modular division of two so that if there is a remainder then it has to be an odd number
	if(num % 2 == 0)
	{
		cout << "The input was even." << endl;
	}
	else
	{
		cout << "The input was odd." << endl;
	}

	return 0;
}
