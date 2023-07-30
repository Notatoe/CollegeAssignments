// Noah Morris
// COSC 130
// Lab 3.1
// This lab has 7 written functions that aid in the addition and subtraction of a byte.
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

typedef unsigned char byte; 

byte msb(byte temp)
{
	//pushes the furthest index to the right which puts it on the far left of the line of bit since it was on the right end
	temp = temp >> 7;
	return temp;
}
bool overflow(byte temp1, byte temp2, byte temp3)
{
	//sets all bytes that were inputed to be in most significant bit form
	byte msb1 = msb(temp1), msb2 = msb(temp2), msb3 = msb(temp3);

	//if statements that check if msb1 and msb2 are equal while msb3 is not, if it is then there is overflow
	if(msb1 & msb2 & ~msb3)
	{
		return 1;
	}
	else if(~msb1 & ~msb2 & msb3)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
byte twoscomplement(byte temp)
{
	//inverts all of the bits in the byte and adds one to put the byte in twos complement form
	temp = ~temp + 1;
	return temp;
}

byte str2bin(string temp)
{
	//creates a byte that is set at zero and an int that is equal to the length of what the user inputed
	byte temp2 = 0;
	int temp3 = temp.length();
	
	//large for loop that adds to the byte numerically based on where ones were placed within the user inputs
	for(int i = temp3 - 1; i >= 0; i--)
	{
		if(temp.at(i) == '1')
		{
			if(i == temp3 - 1)
			{
				temp2 += 1;
			}
			if(i == temp3 - 2)
			{
				temp2 += 2;
			}
			if(i == temp3 - 3)
			{
				temp2 += 4;
			}
			if(i == temp3 - 4)
			{
				temp2 += 8;
			}
			if(i == temp3 - 5)
			{
				temp2 += 16;
			}
			if(i == temp3 - 6)
			{
				temp2 += 32;
			}
			if(i == temp3 - 7)
			{
				temp2 += 64;
			}
			if(i == temp3 - 8)
			{
				temp2 += 128;
			}
		}
	}

	//returns final byte
	return temp2;
}
string bin2str(byte temp)
{
	//creates an empty string and an int that represents the binary value of a the byte
	string temp2 = "";
	int temp3 = temp;
	
	//eight if/else statements that check if the int is greater than or equal to the corresponding binary bit index where
	//if it is the number is subtracted from the int and a one is added to the string, otherwise the int is left how it is
	//and a zero is added to the string.
	//bit index 0 which represents 128
	if(temp3 >= 128)
	{
		temp3 -= 128;
		temp2 = temp2 + "1";
	}
	else
	{
		temp2 = temp2 + "0";
	}

	//bit index 1 which represents 64
	if(temp3 >= 64)
	{
		temp3 -= 64;
		temp2 = temp2 + "1";
	}
	else
	{
		temp2 = temp2 + "0";
	}
	
	//bit index 2 which represents 32
	if(temp3 >= 32)
	{
		temp3 -= 32;
		temp2 = temp2 + "1";
	}
	else
	{
		temp2 = temp2 + "0";
	}
	
	//bit index 3 which represents 16
	if(temp3 >= 16)
	{
		temp3 -= 16;
		temp2 = temp2 + "1";
	}
	else
	{
		temp2 = temp2 + "0";
	}
	
	//bit index 4 which represents 8
	if(temp3 >= 8)
	{
		temp3 -= 8;
		temp2 = temp2 + "1";
	}
	else
	{
		temp2 = temp2 + "0";
	}
	
	//bit index 5 which represents 4
	if(temp3 >= 4)
	{
		temp3 -= 4;
		temp2 = temp2 + "1";
	}
	else
	{
		temp2 = temp2 + "0";
	}
	
	//bit index 6 which represents 2
	if(temp3 >= 2)
	{
		temp3 -= 2;
		temp2 = temp2 + "1";
	}
	else
	{
		temp2 = temp2 + "0";
	}
	
	////bit index 7 which represents 1
	if(temp3 == 1)
	{
		temp3 -= 1;
		temp2 = temp2 + "1";
	}
	else
	{
		temp2 = temp2 + "0";
	}
	
	//returns a string that represents the byte with 8 bits
	return temp2;
}
string bin2dec(byte); 

bool isBIN8(string temp)
{
	//checks to make sure that the user didn't input over eight digits
	if(temp.length() <= 8)
	{
		//for loop that goes throught the whole inputed string
		for(unsigned int i = 0; i < temp.length(); i++)
		{
			//checks to make sure the user only inputted 1s and 0s
			if(temp.at(i) != '0' && temp.at(i) != '1')
			{
				return 0;
			}
		}
	}
	else
	{
		return 0;
	}

	//returns 1 only if the input was eight or less 1s and 0s
	return 1;
}

bool isVALID(string temp)
{
	//checks to make sure the user put one of the two valid operations which are + and -
	if(temp == "+" || temp == "-")
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int main(int argc, char *argv[]) {
	string sX, sY;
	string op;

	cout << "X>  "; 
	cin >> sX;
	if (cin.eof())
		return 1;

	if (!isBIN8(sX)) {
		cout << "error: not 8-bit binary number\n";
		return 1;
	}

	cout << "Y>  "; 
	cin >> sY;
	if (cin.eof())
		return 1;

	if (!isBIN8(sY)) {
		cout << "error: not 8-bit binary number\n";
		return 1;
	}

	cout << "op> "; 
	cin >> op;
	if (cin.eof())
		return 1;

	if (!isVALID(op)) {
		cout << "error: unknown operation\n";
		return 1;
	}

	// Done reading input, now execute

	byte X = str2bin(sX);
	byte Y = str2bin(sY);

	if (op.compare("-") == 0)
		Y = twoscomplement(Y);

	byte S = X + Y;
	bool V = overflow(X, Y, S);

	cout << "\n";

	cout << "    "
		<< setw(8) << right << bin2str(X)
		<< setw(6) << right << bin2dec(X) << "\n";

	cout << "  " << op << " "
		<< setw(8) << right << bin2str(Y)
		<< setw(6) << right << bin2dec(Y) << "\n";

	cout << "    "
		<< setw(8) << right << bin2str(S)
		<< setw(6) << right << bin2dec(S) << "\n";

	if (V)
		cout << "\n** overflow occurred\n";

	cout << "\n";

	return 0;
}
