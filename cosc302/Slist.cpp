// include header file(s) needed
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <iterator>

using namespace std;

#include "Slist.h"

// modify the data class and the associated input 
// and output operators to store, set and print a 
// line number identifier called ID

//class data
class data {
	public:

		friend istream & operator>>(istream &, data &);
		friend ostream & operator<<(ostream &, const data &);

	private:
		int ID;
		string firstname;
		string lastname;
		string phonenum;
};

int IDnum = 1;

//istream & operator>>
istream & operator>>(istream &in, data &r) {
	// write this to read data object data
	in >> r.firstname;
	in >> r.lastname;
	in >> r.phonenum;
	r.ID = IDnum;

	IDnum++;
	return in;
}

//ostream & operator<<
ostream & operator<<(ostream &out, const data &r) {
	// write this to write data object data
	out << setw(24) << left << r.lastname + ", " + r.firstname << r.phonenum << setw(9) << right << r.ID;
	return out;
}

//void printlist
	template <typename Tdata>
void printlist(Tdata begin, Tdata end) 
{
	for (auto it= begin; it != end; ++it)
	{
		cout  << *it << '\n';
	}
}

int main(int argc, char *argv[]) {
	// copy command-line check from Qsort.cpp,
	// then modify to apply to this assignment

	string file, sortmode;

	//checks for a correct number of aguments given
	if(argc != 3 && argc != 5)
	{
		cerr << "usage: ./Qsort -stl | -rpivot [k0 k1] file.txt\n";
		return 1;
	}

	//sets sortmode to argv[1] since argv[1] is known to be there since there are 3 or 5 arguments
	sortmode = argv[1];

	//if there is 3 arguments and a correct sortmode, file is set to argv[2]
	if(sortmode == "-stl" || (sortmode == "-rpivot" && argc == 3))
	{
		file = argv[2];
	}
	//if there is 5 arguments and the sortmode is -rpivot, file is set to argv[4]
	else if(sortmode == "-rpivot" && argc == 5)
	{
		file = argv[4];
	}
	//else read out an error message and end the program
	else
	{
		cerr << "usage: ./Qsort -stl | -rpivot [k0 k1] file.txt\n";
		return 1;
	}

	// open input file
	ifstream ifs;
	ifs.open(file.c_str());

	slist<data> A;

	data din;
	string line;
	while(getline(ifs, line))
	{
		istringstream iss(line);
		iss >> din;
		A.push_back(din);
	}

	// close input file
	ifs.close();

	A.sort(sortmode);

	printlist(A.begin(), A.end());
}
