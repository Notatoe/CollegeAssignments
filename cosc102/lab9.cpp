// Noah Morris
// Dunn - Section 3
// 11/06/2019
// Lab 9
// TA: Angel
// This program outputs speeding tickets within two dates to a file using command-line arguments, classes, structures, and functions

#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

//sets up the date structure
struct Date
{
	int month, day, year;	
};

//sets up the ticket structure
struct Ticket
{
	string citNum;
	Date citDate;
	int clockedSpd;
	int spdLimit;
	char type;
};

//sets up the database class with a private vector of tickets and a mutator and accessor
class Database
{
	private:
		vector<Ticket> tickets;

	public:
		void add_ticket(Ticket &t);
		vector<Ticket> gen_report(Date start, Date end) const;
};

//prototypes for the 3 stand alone functions
bool Read(Database &d, istream &in);

bool Write(const vector<Ticket> &tickets, ostream &out);

int Encode(const Date &d);

//the global constants for calculating the fine
const double IM = 5.2252;
const double HM = 9.4412;
const double RM = 17.1525;
const double OM = 12.152;

//sets up the main with the command-line arguments
int main(int argc, char *argv[])
{
	//variables that will be used throughout the code
	string inputFile, outputFile;
	Date start, end;
	vector<Ticket> finalCount;
	Database data;
	
	//checks if there is the correct amount of arguments
	if(argc != 5)
	{
		cerr << "Usage: ./lab9 <input file> <start: year-month-day> <end: year-month-day> <output or '-'>\n";
		return 1;
	}
	
	//uses input string streams to convert the date from the arguments to the date structure
	istringstream sss(argv[2]);
	istringstream ess(argv[3]);

	sss >> start.year;
	sss >> start.month;
	sss >> start.day;

	ess >> end.year;
	ess >> end.month;
	ess >> end.day;
	
	//sets the file names
	inputFile = argv[1];
	outputFile = argv[4];
	
	//sets up the input and output file
	ifstream in;
	ofstream out;

	in.open(inputFile);
	
	//checks that the input file exists
	if(!in)
	{
		cerr << "The file '" << inputFile << "' cannot be read.\n";
		return 1;
	}
	
	//uses the read function to set up a database with all of the tickets from the input file
	Read(data, in);

	in.clear();
	in.seekg(0, ios::beg);
	
	//creates a vector that holds tickets that fall between the start and end date
	finalCount = data.gen_report(start, end);

	out.open(outputFile);
	
	//puts the tickets with the dates that fit into the output file
	Write(finalCount, out);

	in.close();

	return 0;
}

//adds a ticket to a database's tickets vector
void Database::add_ticket(Ticket &t)
{
	tickets.push_back(t);
}

//finds which tickets fit withing the start and end dates
vector<Ticket> Database::gen_report(Date start, Date end) const
{
	vector<Ticket> temp;

	for(int i = 0; i < tickets.size(); i++)
	{
		if(tickets.at(i).citDate.year > start.year && tickets.at(i).citDate.year < end.year)
		{
			temp.push_back(tickets.at(i));
		}
		else if(tickets.at(i).citDate.year == start.year)
		{
			if(tickets.at(i).citDate.month > start.month)
			{
				temp.push_back(tickets.at(i));
			}
			else if(tickets.at(i).citDate.month == start.month)
			{
				if(tickets.at(i).citDate.day >= start.day)
				{
					temp.push_back(tickets.at(i));
				}
				else
				{
					continue;
				}
			}
			else
			{
				continue;	
			}
		}
		else if(tickets.at(i).citDate.year == end.year)
		{
			if(tickets.at(i).citDate.month < end.month)
			{
				temp.push_back(tickets.at(i));
			}
			else if(tickets.at(i).citDate.month == end.month)
			{
				if(tickets.at(i).citDate.day <= end.day)
				{
					temp.push_back(tickets.at(i));
				}
				else
				{
					continue;
				}
			}
			else
			{
				continue;
			}
		}
		else
		{
			continue;
		}
	}

	return temp;
}

//puts the input files values into the database
bool Read(Database &d, istream &in)
{
	string line, name;
	int month, day, year, clockedSpeed, speedLimit;
	char roadType;
	while(in >> name >> month >> day >> year >> clockedSpeed >> speedLimit >> roadType)
	{
		Ticket temp;
		
		temp.citNum = name;
		temp.citDate.month = month;
		temp.citDate.day = day;
		temp.citDate.year = year;
		temp.clockedSpd = clockedSpeed;
		temp.spdLimit = speedLimit;
		temp.type = roadType;

		if(temp.citDate.year < 1000)
		{
			temp.citDate.year = temp.citDate.year + 2000;
		}

		d.add_ticket(temp);
	}

	return true;
}

//Calulates the fine for each ticket and puts those values into the output file
bool Write(const vector<Ticket> &tickets, ostream &out)
{
	string Month[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	for(int i = 0; i < tickets.size(); i++)
	{
		double fine = 0.00;

		if(tickets.at(i).type == 'i' || tickets.at(i).type == 'I')
		{
			fine = (tickets.at(i).clockedSpd - tickets.at(i).spdLimit) * IM;
		}
		else if(tickets.at(i).type == 'r' || tickets.at(i).type == 'R')
		{
			fine = (tickets.at(i).clockedSpd - tickets.at(i).spdLimit) * RM;
		}
		else if(tickets.at(i).type == 'h' || tickets.at(i).type == 'H')
		{
			fine = (tickets.at(i).clockedSpd - tickets.at(i).spdLimit) * HM;
		}
		else
		{
			fine = (tickets.at(i).clockedSpd - tickets.at(i).spdLimit) * OM;
		}

		if(fine < 0.00)
		{
			fine = 0.00;
		}

		out << setfill('0') << setw(2) << right << tickets.at(i).citDate.day;
		out << setfill('-') << setw(4) << Month[tickets.at(i).citDate.month-1];
		out << setw(1) << '-';
		out << setw(4) << tickets.at(i).citDate.year;
		out << setw(1) << ' ';
		out << left << setfill(' ') << setw(10) << tickets.at(i).citNum;
		out << setw(2) << " $";
		out << right << setfill(' ') << setw(9) << fixed << setprecision(2) << fine << '\n';
	}

	return true;
}

//turns the date into a single integer
int Encode(const Date &d)
{
	return (d.year * 10000) + (d.month * 100) + d.day;
}
