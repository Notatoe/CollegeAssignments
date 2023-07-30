/* Noah Morris
 * COSC 130
 * Lab 1
 * This lab has 2 functions written that either changes a decimal to binary or binary to decimal
 */
#include <cctype> 
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

enum format  { BINARY, DECIMAL, HEXADEC };

/*------------ FUNCTIONS IN LIBNC ------------*/

void printusage();

void dec2bin(string &, string &);
void bin2dec(string &, string &);
void bin2hex(string &, string &);
void hex2bin(string &, string &);

void processDECIMAL(string &, string &, format);
void processBINARY(string &, string &, format);
void processHEXADEC(string &, string &, format);

/*----------- YOUR IMPLEMENTATIONS -----------*/

void dec2bin(string &dec, string &bin)
{
	//creates a integer that will hold the decimal value after it is converted to an integer
	int num;

	//makes sure that the bin string is clear before it is used
	bin.clear();
	
	//converts the decimal string to an integer
	stringstream s(dec);
	s >> num;
	
	//an array of 2 that holds the two numbers that can be put into a 
	string bindigit[2] = {"0", "1"};
	
	//while loop that builds a binary string
	while(num > 0)
	{
		if(num % 2 == 1)
		{
			bin = "1" + bin;
		}
		else
		{
			bin = "0" + bin;
		}

		num /= 2;
	}	
}
void bin2dec(string &bin, string &dec)
{
	//initializes three ints; temp holds the size of the binary string, tem2 holds the decimal value, and temp3 holds a value that gets added to temp2.
	int temp = bin.size();
	int temp2 = 0;
	int temp3;

	//makes sure the dec string is clear before it is used
	dec.clear();
	
	//subtracts 1 from the temp value to act as the index of the binary string
	temp--;
	
	//for loop that goes through the entire length of the binary string
	for(int i = 0; i < bin.size(); i++)
	{
		//if the value at index i is a one it adds value to temp2, otherwise it does not
		if(bin.at(i) == '1')
		{
			//finds the temporary value of temp3 by simulating exponents of 2
			if(temp > 0)
			{
				temp3 = 1;
				for(int j = 0; j < temp; j++)
				{
					temp3 *= 2;
				}
			}
			else if(temp == 0)
			{
				temp3 = 1;
			}
			
			//adds temp3 to temp2
			temp2 += temp3;
			temp--;
		}
		else
		{
			temp--;
		}
	}
	
	//converts the integer value of the decimal to a string
	stringstream s;
	s << temp2;			
	s >> dec;
}
// void bin2hex(string &, string &) { optional }
// void hex2bin(string &, string &) { optional }

/*----------- USER INTERFACE CODE ------------*/

int main(int argc, char *argv[]) {
  string mode;
  string input;
  string output;

  format imode = DECIMAL;
  format omode = BINARY;

  while (1) {
    cout << "enter> ";
    cin >> mode;

	if (cin.eof())
	  break;

	if (mode.compare("dec2bin") == 0) {
      imode = DECIMAL;
      omode = BINARY;
    } else 
	if (mode.compare("dec2hex") == 0) {
      imode = DECIMAL;
      omode = HEXADEC;
    } else 
	if (mode.compare("bin2dec") == 0) {
      imode = BINARY;
      omode = DECIMAL;
    } else 
	if (mode.compare("bin2hex") == 0) {
      imode = BINARY;
      omode = HEXADEC;
    } else 
	if (mode.compare("hex2bin") == 0) {
      imode = HEXADEC;
      omode = BINARY;
    } else 
	if (mode.compare("hex2dec") == 0) {
      imode = HEXADEC;
      omode = DECIMAL;
    } else {
	  cout << mode << " unknown\n";
	  continue;
	}

    cin >> input;

    switch (imode) {
    case DECIMAL:
      processDECIMAL(input, output, omode);
      break;
    case BINARY:
      processBINARY(input, output, omode);
      break;
    case HEXADEC:
      processHEXADEC(input, output, omode);
      break;
    }

	cout << output << "\n";
  }
}
