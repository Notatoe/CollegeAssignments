//Noah Morris
//3/7/2021
//cosc302
//Crypto.cpp

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

#include "PPM.h"
#include "Rnumgen.h"

const char ETX = 0x3;

//Pixel struct 
struct pixel {
	int row;
	int column;
};

void set_pixel_list(PPM &image, vector<pixel> &pix, int seed) 
{
	//double for loop to go through every pixel on the PPM image
	for(int i = 0; i < image.get_Nrows(); i++)
	{
		for(int j = 0; j < image.get_Ncols(); j++)
		{
			pixel temp;
			//if the pixel is on an even column and row, set temp to that pixel's
			//location and add it to the vector
			if(i % 2 == 0 && j % 2 == 0)
			{
				temp.row = i;
				temp.column = j;
				pix.push_back(temp);
			}
		}
	}

	//creates the histogram with specified values
	vector<int> histogram(4096, 0);
	int key;

	//takes the bits of 3-6 of each RGB value and puts them into a 12-bit
	//key and into the histogram
	for(int i = 0; i < image.get_Nrows(); i++)
	{
		for(int j = 0; j < image.get_Ncols(); j++)
		{
			char r = (image[i][j].R & 0x3F) >> 2;
			char g = (image[i][j].G & 0x3F) >> 2;
			char b = (image[i][j].B & 0x3F) >> 2;
			key = (r << 8) | (g << 4) | b;
			histogram[key]++;
		}
	}

	//creates the rnumgen
	rnumgen rng(seed, histogram);
	
	//form 24 bit values that allow for more pixels to be used
	for(unsigned int i = pix.size(); i > 0; i--)
	{
		int r1_12 = rng.rand();
		int r2_12 = rng.rand();
		int r_24 = (r1_12 << 12) | r2_12;

		swap(pix[i], pix[r_24 % (i+1)]);
	}
}

void encode(vector<pixel> &pix, PPM &image)
{
	//color and current values keep track of which rgb value to change and which pixel
	//is being edited respectively, temp is the current letter being encoded
	int color = 0, current = 0;
	char temp;
	//while loop that goes through every letter the user inputs
	while(cin.get(temp))
	{
		//for loop that goes through every bit of the current letter
		for(int i = 0; i < 7; i++)
		{
			//finds which rgb value to edit through modular division and 
			//sets the lsb of the rgb to 0 and replaces it with the current
			//bit of the letter
			if(color % 3 == 0)
			{
				image[pix[current].row][pix[current].column].R &= 0xFE;
				image[pix[current].row][pix[current].column].R |= ((temp >> i) & 0x1);
			}
			else if(color % 3 == 1)
			{
				image[pix[current].row][pix[current].column].G &= 0xFE;
				image[pix[current].row][pix[current].column].G |= ((temp >> i) & 0x1);
			}
			else
			{
				image[pix[current].row][pix[current].column].B &= 0xFE;
				image[pix[current].row][pix[current].column].B |= ((temp >> i) & 0x1);
			}

			//increments color and current to move to the next rgb/pixel
			color++;
			current++;
		}
	}

	//Afer the message has been encoded, encode ETX so that the decode function knows
	//where to stop
	for(int i = 0; i < 7; i++)
	{
		if(color % 3 == 0)
		{
			image[pix[current].row][pix[current].column].R &= 0xFE;
			image[pix[current].row][pix[current].column].R |= ((ETX >> i) & 0x1);
		}
		else if(color % 3 == 1)
		{
			image[pix[current].row][pix[current].column].G &= 0xFE;
			image[pix[current].row][pix[current].column].G |= ((ETX >> i) & 0x1);
		}
		else
		{
			image[pix[current].row][pix[current].column].B &= 0xFE;
			image[pix[current].row][pix[current].column].B |= ((ETX >> i) & 0x1);
		}

		//increments color and current to move to the next rgb/pixel
		color++;
		current++;
	}
}

void decode(vector<pixel> &pix, PPM &image)
{
	//color and current values keep track of which rgb value to change and which pixel
	//is being edited respectively
	int color = 0, current = 0;
	while(1)
	{
		//letter and bit chars that keep track of the current letter being decoded as
		//well the current bit that will be shifted into the letter
		char letter = 0, bit = 0;
		for(int i = 0; i < 7; i++)
		{
			//uses modular division to figure out which rgb value to extract from
			if(color % 3 == 0)
			{
				bit = image[pix[current].row][pix[current].column].R & 0x1;
			}
			else if(color % 3 == 1)
			{
				bit = image[pix[current].row][pix[current].column].G & 0x1;
			}
			else
			{
				bit = image[pix[current].row][pix[current].column].B & 0x1;
			}

			//increments color and current to move to the next rgb/pixel
			color++;
			current++;

			//shifts bit into correct place using the i from the for loop
			letter |= bit << i;
		}

		//removes the msb from the letter
		letter &= 0x7F;

		//if letter is equal to ETX, the message has been decoded and 
		//should break from the loop
		if(letter == ETX)
		{
			break;
		}
		cout << letter;
	}
}



int main(int argc, char *argv[]) {
	/*parse command line arguments
	  if something not right,
	  print error message and exit*/
	if(argc != 3 && argc != 4)
	{
		cerr << "usage: ./Crypto -encode|-decode (-seed=num) file.ppm\n";
		return 1;
	}

	//takes mode, filename, and seed from the commandline arguments
	string mode = argv[1];
	string filename, stringseed;
	int seed = 0;

	//in the case of argc == 4
	if(argc == 4)
	{
		stringseed = argv[2];
		filename = argv[3];
	
		//if a seed is given, set seed to that
		if(stringseed != "-seed=")
		{
			stringseed.erase(0,6);
			stringstream ss(stringseed);
			ss >> seed;
		}
	}
	else
	{
		filename = argv[2];
	}

	//make sure the mode is correct
	if(mode != "-encode" && mode != "-decode")
	{
		cerr << "usage: ./Crypto -encode|-decode (-seed=num) file.ppm\n";
		return 1;
	}

	//create img and insert the ppm file into img
	PPM img;
	img.read(filename);

	//declare pixel_list and set the pixel list
	vector<pixel> pixel_list;
	set_pixel_list(img, pixel_list, seed);

	//if mode is encode, encode message and write the image to a new file
	if(mode == "-encode")
	{
		encode(pixel_list, img);
		img.write(filename);
	}
	//else decode the message from the image given
	else
	{
		decode(pixel_list, img);
	}
}
