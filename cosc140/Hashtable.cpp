// Noah Morris
// 10/13/2020
// Lab 4

#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <ctype.h>

using namespace std;

typedef unsigned int uint;

class hash_table 
{
	//key_line structure that holds the key word as well as each line it appears on
	struct key_line
	{
		bool inuse();
		bool operator==(const string &) const;

		string key;
		vector<int> lines;
	};

	//constructor, function that inserts a key word and line number, function that allows stas to be seen, function that shows the stats, function that returns a lines vector
	public:
	hash_table(int);
	~hash_table();
	void insert(const string &, int);
	void set_showstats();
	void insert_done();
	const vector<int> find(string &);


	//mostly functions from the hash table handout
	private:
	int hash(const string &);
	int nextprime(int);
	int qprobe(const string &, bool);
	void resize();
	void showload();

	//boolean that determine if stats should be shown, number the table is on, max number of the table, number of collisions, vector of key_lines
	bool show_stats;
	int num_inuse;
	int max_inuse;
	int collisions;
	vector<key_line> table;
};

//key_line structure function that checks if the key_line is empty or not
bool hash_table::key_line::inuse()
{
	//returns false if the key is empty, true otherwise
	if (key == "")
	{
		return false;
	}
	else
	{
		return true;
	}
}

//key_line structure function that compares the key of the key_line to a string
bool hash_table::key_line::operator==(const string &temp) const
{
	//returns true if the key is equal to the string, false otherwise
	if(temp == key)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//constructs a hash_table object and initializes all of its values
hash_table::hash_table(int temp)
{
	int N;

	//sets N to 0 if not specified
	if(temp == 0)
	{
		N = 23;
	}
	else
	{
		N = nextprime(temp);
	}
	table.assign(N, key_line());
	num_inuse = 0;
	max_inuse = N/2;
	collisions = 0;
	show_stats = false;
};

//deconstructor
hash_table::~hash_table()
{
	//outputs if show_stats is true
	if(show_stats == true)
	{
		cout << "Run stats ...\n";
		cout << "Number of slots used: " << num_inuse << '\n';
		cout << "Max number of slots: " << max_inuse << '\n';
		cout << "Number of collisions: " << collisions << '\n';
	}
}

//function that inserts a key and line into the table vector
void hash_table::insert(const string &key, int linenum)
{
	//finds the index where the key word is located
	int index = qprobe(key, true);

	//if the key word is not found
	if (!(table[index].inuse()))
	{
		//set the open spot to the key word and add one to num_inuse
		table[index].key = key;
		num_inuse++;
	}

	//if num_insuse is equal to or greater than the max amount, resize
	if (num_inuse >= max_inuse)
	{
		if(show_stats == true)
		{
			insert_done();
		}
		resize();
	}


	//finds if the lines vector already has the line number
	vector<int>::iterator temp = std::find(table[index].lines.begin(),table[index].lines.end(), num_inuse);
	if (temp == table[index].lines.end()) {
		table[index].lines.push_back(num_inuse);
	}
}

//sets show_stats to true
void hash_table::set_showstats()
{
	show_stats = true;
}

//straight from the handout
int hash_table::hash(const string &key) {
	uint index = 0;
	const char *c = key.c_str();
	while (*c)
	{
		index = ((index << 5) | (index >> 27)) + *c++;
	}
	return index % table.size();
}

//computes the next prime number double the inputed number
int hash_table::nextprime(int N) {
	int i = 2;
	N = (N * 2) + 1;
	while (i*i <= N)
	{
		if (N%i == 0)
		{
			N++;
			i = 1;
		}
		i++;
	}
	return max(3,N);
}

//seaches the table for the index of a key word
int hash_table::qprobe(const string &key, bool col)
{
	int index = hash(key);
	int k = 0;
	while(table[index].key != string() && table[index].key != key)
	{
		index += 2*(++k) - 1;
		index = index % table.size();

		//adds to collisions if col is true
		if(col == true)
		{
			collisions++;
		}
	}
	return index;
}

//makes the table of key_lines bigger
void hash_table::resize()
{
	vector<key_line> tmp_table;
	for (int i=0; i<(int)table.size(); i++)
	{
		if (table[i].key != string())
		{
			tmp_table.push_back(table[i]);
		}
	}
	int N = nextprime(table.size());
	table.assign(N, key_line());
	num_inuse = 0;
	max_inuse = N/2;
	for (int i=0; i<(int)tmp_table.size(); i++) 
	{
		key_line &key = tmp_table[i];
		table[qprobe(key.key, false)] = key;
		num_inuse++;
	}
}

//finds the lines vector associated to a word
const vector<int> hash_table::find(string &key)
{ 
	return table[qprobe(key, false)].lines;
}

//displays load information
void hash_table::showload()
{
	cout << "**N =" << setw(6) << table.size() << " load = " << setprecision(2) << fixed << (double) (num_inuse / table.size()) << '\n';
}

//outputs load information
void hash_table::insert_done()
{
	if(show_stats == true)
	{
		showload();
	}
}

//removes punctuation from a line
char remove_punctuation(char temp)
{
	if(ispunct(temp))
	{
		return ' ';
	}
	return temp;
}

int main(int argc, char const *argv[]) 
{
	//temp is the N value, temp2 is for the file name, and temp3 is for if stats should be shown or not
	int temp = 0;
	string temp2;
	bool temp3 = false;

	//checks the command line arguments for each command 
	for(int i = 1; i < argc; i++)
	{
		string argu = argv[i];
		if(argu == "-N")
		{
			temp = atoi(argv[i+1]);
		}
		else if(argu == "-f")
		{
			temp2 = argv[i+1];
		}
		else if(argu == "-showstats")
		{
			temp3 = true;
		}
	}

	//creates a string for the lines of a file and two vectors that hold each line, one with and one without punctuation
	string fileline;
	vector<string> filelines1;
	vector<string> filelines2;

	//opens the file
	fstream hashfile;
	hashfile.open(temp2.c_str());

	//while file is open, extracts each line
	if(hashfile.is_open())
	{
		while(getline(hashfile, fileline))
		{
			filelines1.push_back(fileline);
			transform(fileline.begin(), fileline.end(), fileline.begin(), remove_punctuation);
			filelines2.push_back(fileline);
		}
	}

	//opens a string stream
	stringstream ss;

	//creates the hashtable
	hash_table Htable(temp);

	//sets to show stats or not
	if(temp3)
	{
		Htable.set_showstats();
	}
	
	//temp4 is used to take in each word from the files lines and puts them into the hash table
	string temp4;
	for(unsigned int i = 0; i < filelines2.size(); i++)
	{
		getline(ss, filelines2.at(i));
		while(ss >> temp4)
		{
			Htable.insert(temp4, i+1);
		}
	}
	
	//the file is not needed so it is closed
	hashfile.close();

	//string for the word the user gives
	string word;

	//final stats as the hash table won't take in anymore key words
	Htable.insert_done();

	while(1)
	{
		//takes in the word
		cout << "find> ";
		getline(cin, word);

		//finds the lines the word is located in
		vector<int> lines = Htable.find(word);

		if(cin.eof())
		{
			break;
		}
		
		//outputs the line its in
		for(unsigned int i = 0; i < lines.size(); i++)
		{
			cout << lines.at(i) << ":  " << filelines1.at(lines.at(i)-1) << '\n'; 
		}
	}

	return 0;
}
