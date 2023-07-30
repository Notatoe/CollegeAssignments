// Noah Morris
// 3/21/2021
// cosc302
// Citysim1

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cmath>

using namespace std;

//for uses of PI
const long double PI = 3.141592653589793238L;

class city
{
	public:
		//get member functions
		string get_name() {return name;}
		string get_type() {return type;}
		int get_zone() {return zone;}
		float get_latitude() {return latitude;}
		float get_longitude() {return longitude;}
		int get_population() {return population;}

		//friend input and output operators
		friend istream & operator>>(istream &, city &);
		friend ostream & operator<<(ostream &, const city &);

	private:
		string name;
		string type;
		int zone;
		float latitude;
		float longitude;
		int population;
};

//takes in all of the data in order from the file
istream & operator>>(istream &in, city &c)
{
	in >> c.zone;
	in >> c.name;
	in >> c.type;

	//converts latitude and longitude to radians
	in >> c.latitude;
	c.latitude = c.latitude*(PI/180);
	in >> c.longitude;
	c.longitude = c.longitude*(PI/180);

	in >> c.population;

	return in;
}

//outputs a city and all of its members in the correct format
ostream & operator<<(ostream &out, const city &c) 
{
	out << setw(18) << left << c.name;
	out << setw(12) << c.type;
	out << setw(2) << c.zone;
	out << setw(10) << right << c.population;
	//converts latitude and longitude back to degrees
	out << setw(8) << fixed << setprecision(2) << c.latitude*(180/PI);
	out << setw(8) << fixed << setprecision(2) << c.longitude*(180/PI);

	return out;
}

class costtable
{
	public:
		// () operator and costtable constructor
		float operator()(int mode, int i, int j);
		costtable(vector<city> &cities);

	private:
		vector<float> table[2];
};

//accessor operator that returns the value of either the distance (mode = 0) or time (mode = 1)
float costtable::operator()(int mode, int i, int j)
{
	//makes sure that that i is less than j
	if(i < j)
	{
		int temp = i;
		i = j;
		j = temp;
	}

	return table[mode][i*(i+1)/2+j];
}

costtable::costtable(vector<city> &cities)
{
	//sets the two tables to hold all combinations of cities
	int N = cities.size();
	table[0].resize(N*(N+1)/2);
	table[1].resize(N*(N+1)/2);

	//double for loop that goes through every combination of cities one time
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < i; j++)
		{
			float DLatitude, DLongitude, distance;

			//gets the difference in latitude and longitude of the two cities
			if(cities[i].get_latitude() >= cities[j].get_latitude())
				DLatitude = cities[i].get_latitude() - cities[j].get_latitude();
			else
				DLatitude = cities[j].get_latitude() - cities[i].get_latitude();

			if(cities[i].get_longitude() >= cities[j].get_longitude())
				DLongitude = cities[i].get_longitude() - cities[j].get_longitude();
			else
				DLongitude = cities[j].get_longitude() - cities[i].get_longitude();


			//delta sigma equation
			distance = 2 * asin(sqrt(powf(sin(DLatitude / 2),2)+cos(cities[i].get_latitude())*cos(cities[j].get_latitude())*powf(sin(DLongitude / 2),2)));

			//real distance equation + rounding to the nearest 10.0
			distance = 3982 * distance;
			distance = 10.0*round(distance/10.0);

			table[0][i*(i+1)/2+j] = distance;
		}
	}

	//double for loop that goes through every combination of cities one time
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < i; j++)
		{
			//Goods shipped between two REGIONAL cities by ground
			if(cities[i].get_type() == "REGIONAL" && cities[j].get_type() == "REGIONAL")
			{
				table[1][i*(i+1)/2+j] = table[0][i*(i+1)/2+j] / 60;
			}
			//else one or both cities are GATEWAY cities
			else
			{
				table[1][i*(i+1)/2+j] = table[0][i*(i+1)/2+j] / 570;
			}
		}
	}
}

//reads the city_list.txt file and parses the information into the cities vector
void read_cityinfo(vector<city> &cities)
{
	//opens city_list.txt
	string filename = "city_list.txt";
	ifstream ifs;
	ifs.open(filename.c_str());

	//puts each line into a city object using stringstream
	city temp;
	string line;
	while(getline(ifs, line))
	{
		if(line == "" || line.at(0) == '#')
		{
			continue;
		}
		stringstream ss;
		ss << line;
		ss >> temp;
		cities.push_back(temp);
	}
	ifs.close();
}

//writes the city_info.txt file
void write_cityinfo(vector<city> cities)
{
	//opens the file
	string filename = "city_info.txt";
	ofstream ofs;
	ofs.open(filename.c_str());

	//gives the number of cities
	ofs << "CITY INFO (N=" << cities.size() << "):\n";
	ofs << '\n';

	//outputs each city
	for(unsigned int i = 0; i < cities.size(); i++)
	{
		ofs << setw(3) << right << i << ' ' << cities[i] << '\n';
	}

	ofs.close();
}

//writes the city_distancetable.txt file
void write_distancetable(costtable Table, vector<city> cities)
{
	//opens the file
	string filename = "city_distancetable.txt";
	ofstream ofs;
	ofs.open(filename.c_str());

	ofs << "DISTANCE TABLE:\n";

	//outputs each combination of city and their distance from eachother
	for(unsigned int i = 0; i < cities.size(); i++)
	{
		for(unsigned int j = 0; j < i; j++)
		{
			ofs << setw(3) << right << i << ' ';
			ofs << setw(38) << left << setfill('.') << cities[i].get_name() + " to " + cities[j].get_name() + ' ';
			ofs << setw(7) << right << setfill(' ') << fixed << setprecision(1) << Table(0,i,j) << " miles\n";
		}
		ofs << '\n';
	}
	ofs.close();
}

//writes the city_timetable.txt file
void write_timetable(costtable Table, vector<city> cities)
{
	//opens the file
	string filename = "city_timetable.txt";
	ofstream ofs;
	ofs.open(filename.c_str());

	ofs << "TIME TABLE:\n";

	//outputs each combination of city and their time to get to eachother
	for(unsigned int i = 0; i < cities.size(); i++)
	{
		for(unsigned int j = 0; j < i; j++)
		{
			ofs << setw(3) << right << i << ' ';
			ofs << setw(38) << left << setfill('.') << cities[i].get_name() + " to " + cities[j].get_name() + ' ';
			ofs << setw(5) << right << setfill(' ') << fixed << setprecision(1) << Table(1,i,j) << " hours\n";
		}
		ofs << '\n';
	}
	ofs.close();
}

//create_citygraph() { }
//write_citygraph() { }

//dijkstra_route() { }

int main(int argc, char *argv[])
{
	//commandline option decoding
	if(argc != 2)
	{
		cerr << "usage: ./Citysim1 -mode\n";
		return 1;
	}
	string mode = argv[1];

	if(mode != "-graphinfo" /*&& mode != "-distance" && -time"*/)
	{
		cerr << "Incorrect mode\n";
		return 1;
	}

	//city graph declarations
	//vector<city> cities;
	//read_cityinfo(cities);
	
	vector<city> cities;
	read_cityinfo(cities);

	//set up costtables
	costtable Table(cities);

	//create_citygraph() //VERSION 2

	if (mode == "-graphinfo")
	{
		write_cityinfo(cities);

		write_distancetable(Table, cities);
		write_timetable(Table, cities);

		//write_citygraph()

		//return from program
		return 0;
	}

	//for VERSION 2
	//while (not done) {
	//enter> from, to cities
	//dijkstra_route(costmode,from,to) 
	//}
}
