// Noah Morris
// Dunn - Section 3
// 11/13/2019
// Lab 10
// TA: Angel
// This program takes a picture file and creates an output that edits it in the way the user desires

#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

//structure for a pixel which holds all three RGB color values
struct Pixel
{
	unsigned int red, green, blue;
};

//calss for a picture that holds all of its pixels in a vector as well as its width, height, and maxinum intensity. It also holds prototypes for its accesors and mutators
class Picture
{
	private:
		vector<Pixel> pixels;
		int width;
		int height;
		unsigned int maxIntensity;
	public:
		Picture();
		Pixel get_pixel(int row, int column) const;
		Pixel& get_pixel(int row, int column);
		void set_pixel(int row, int column, Pixel pix);
		void remove_channel(string color);
		void flip_x();
		void flip_y();
		bool read_input(istream &in);
		void write_output(ostream &out) const;
		int getWidth();
		int getHeight();
		int getMaxIntensity();
		vector<Pixel> getPixels();
};

int main(int argc, char* argv[])
{
	//values that will be used throughout the code
	Picture pic;
	string inputFile;
	char test1, test3;
	string test2;
	
	//initializes the input file stream and output file stream
	ifstream in;
	ofstream out;
	
	//makes a stringstream to put argv[1] into the form of a string
	stringstream ss1(argv[1]);
	ss1 >> test1;
	
	//checks to see if the user put a dash then opens the file
	if(test1 != '-')
	{
		in.open(argv[1]);

		if(!in)
		{
			cerr << "The file '" << argv[1] << "' cannot be read.\n";
			return 1;
		}
	}
	else
	{
		do
		{
			if(!cin)
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			cout << "Enter a PPM file address: ";
		}
		while(!(cin >> inputFile));

		in.open(inputFile);

		if(!in)
		{
			cerr << "The file '" << inputFile << "' cannot be read.\n";
			return 1;
		}
	}
	
	//puts the user's command into string form
	stringstream ss2(argv[3]);
	ss2 >> test2;
	
	//puts the file input to picture value
	pic.read_input(in);
	
	//activates the command the user gave
	if(test2 == "remove_red")
	{
		pic.remove_channel("red");
	}
	else if(argv[3] == "remove_green")
	{
		pic.remove_channel("green");
	}
	else if(argv[3] == "remove_blue")
	{
		pic.remove_channel("blue");
	}
	else if(argv[3] == "remove_gray")
	{
		pic.remove_channel("gray");
	}
	else if(argv[3] == "flip_x")
	{
		pic.flip_x();
	}
	else if(argv[3] == "flip_y")
	{
		pic.flip_y();
	}
	else if(test2 != "-")
	{
		cout << "Invalid command.\n";
		return 1;
	}
	
	//puts where the picture goes to a string format
	stringstream ss3(argv[2]);
	ss2 >> test3;
	
	//outputs or prints the output
	if(test3 != '-')
	{
		out.open(argv[2]);

		pic.write_output(out);
	}
	else
	{
		vector<Pixel> picPix = pic.getPixels();

		cout << "P3\n";
		cout << pic.getWidth() << ' ' << pic.getHeight() << '\n';
		cout << pic.getMaxIntensity() << '\n';
		for(int i = 0; i < picPix.size(); i++)
		{
			cout << picPix.at(i).red << ' ' << picPix.at(i).green << ' ' << picPix.at(i).blue << '\n';
		}
	}

	return 0;
}

//default constructor for a picture
Picture::Picture()
{
	width = 0;
	height = 0;
	maxIntensity = 0;
}

//accesor for a pixel at a given point
Pixel Picture::get_pixel(int row, int column) const
{
	return pixels.at((row * width) + column);
}

//mutator for a pixel at a given point that allows it to be edited
Pixel& Picture::get_pixel(int row, int column)
{
	return pixels.at((row * width) + column);
}

//sets a pixel at the point given to the pixel that was given
void Picture::set_pixel(int row, int column, Pixel pix)
{
	get_pixel(row, column).red = pix.red;
	get_pixel(row, column).green = pix.green;
	get_pixel(row, column).blue = pix.blue;
}

//edits the color of a picture by changing the RGB values of all of its pixels
void Picture::remove_channel(string color)
{
	Pixel temp;

	if(color == "red")
	{
		for(int i = 0; i < height; i++)
		{
			for(int j = 0; j < width; j++)
			{
				temp = get_pixel(i, j);
				temp.red = 0;
				set_pixel(i, j, temp);
			}
		}
	}
	else if(color == "green")
	{
		for(int i = 0; i < height; i++)
		{
			for(int j = 0; j < width; j++)
			{
				temp = get_pixel(i, j);
				temp.green = 0;
				set_pixel(i, j, temp);
			}
		}

	}
	else if(color == "blue")
	{
		for(int i = 0; i < height; i++)
		{
			for(int j = 0; j < width; j++)
			{
				temp = get_pixel(i, j);
				temp.blue = 0;
				set_pixel(i, j, temp);
			}
		}

	}
	else if(color == "gray")
	{
		for(int i = 0; i < height; i++)
		{
			for(int j = 0; j < width; j++)
			{
				temp = get_pixel(i, j);

				if(temp.red < 45)
				{
					temp.red = 0;
				}
				else
				{
					temp.red = temp.red - 45;
				}

				if(temp.green < 45)
				{
					temp.green = 0;
				}
				else
				{
					temp.green = temp.green - 45;
				}

				if(temp.blue < 45)
				{
					temp.blue = 0;
				}
				else
				{
					temp.blue = temp.blue - 45;
				}

				set_pixel(i, j, temp);
			}
		}

	}
}

//flips the picture around the x-axis
void Picture::flip_x()
{
	Pixel temp1, temp2;

	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < ((height / 2) + (height % 2)); j++)
		{
			temp1 = get_pixel(j, i);
			temp2 = get_pixel(height - j - 1, i);
			set_pixel(height - j - 1, i, temp1);
			set_pixel(j, i, temp2);
		}
	}
}

//flips the picture around the y axis
void Picture::flip_y()
{
	Pixel temp1, temp2;

	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < ((width / 2) + (width % 2)); j++)
		{
			temp1 = get_pixel(i, j);
			temp2 = get_pixel(i, width - j - 1);
			set_pixel(i, width - j - 1, temp1);
			set_pixel(i, j, temp2);
		}
	}
}

//reads the inputed file to set up a picture object
bool Picture::read_input(istream &in)
{
	string line;
	Pixel temp;
	
	//skips the P3 line
	getline(in, line);
	line.clear();
	in.clear();
	
	//gets the next line
	getline(in, line);
	
	//skips anyline that starts with a #
	while(line.find('#') != string::npos)
	{
		getline(in, line);
	}
	
	//finds the width and height values
	stringstream s(line);
	s >> width;
	s >> height;
	line.clear();

	getline(in, line);

	while(line.find('#') != string::npos)
	{
		getline(in, line);
	}
	
	//finds the max intensity value
	stringstream s2(line);
	s2 >> maxIntensity;
	line.clear();
	
	//puts all of the pixels into the pixels vector inside of the picture object
	for(int i = 0; i < height; i++)
	{
		getline(in, line);
		while(line.find('#') != string::npos)
		{
			getline(in, line);
		}
		stringstream ss3(line);

		for(int j = 0; j < width; j++)
		{
			ss3 >> temp.red;
			if(temp.red > maxIntensity)
			{
				temp.red = maxIntensity;
			}

			ss3 >> temp.green;
			if(temp.green > maxIntensity)
			{
				temp.green = maxIntensity;
			}

			ss3 >> temp.blue;
			if(temp.blue > maxIntensity)
			{
				temp.blue = maxIntensity;
			}

			pixels.push_back(temp);
		}
	}

	return 1;
}

//outputs the final picture to a file
void Picture::write_output(ostream &out) const
{
	out << "P3\n";
	out << width << ' ' << height << '\n';
	out << maxIntensity << '\n';
	for(int i = 0; i < pixels.size(); i++)
	{
		out << pixels.at(i).red << ' ' << pixels.at(i).green << ' ' << pixels.at(i).blue << '\n';
	}
}

int Picture::getWidth()
{
	return width;
}

int Picture::getHeight()
{
	return height;
}

int Picture::getMaxIntensity()
{
	return maxIntensity;
}

vector<Pixel> Picture::getPixels()
{
	return pixels;
}
