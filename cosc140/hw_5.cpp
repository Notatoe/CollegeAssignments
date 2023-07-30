// Noah Morris
// 9/14/2020
// cosc 140
// Homework 5
// This program takes in integers until forcibly stopped. Then it will output how many numbers were put in, the sum, as well as the smallest and largest number


#include <iostream>
#include <string>

using namespace std;

//class for the stats object
template <typename T>
class stats
{
	public:
		//the variables for each stat of the stats object
		int Count = 0;
		T Sum = T();

		//function that adds to each stat respectively
		void push(const T &v)
		{
			Count++;
			Sum += v;
		}

		//function that prints all of the stats
		void print()
		{
			cout << "N   = " << Count << '\n';
			cout << "sum = " << Sum << '\n';
		}
};

int main()
{
	//calls the stats object and initializes all of its values
	stats<int> stats;


	//for the life of me I can't get these two to work

	//stats<double> stats2;

	//stats<string> stats3;

	
	//initializes an int for the inputed value
	int Input;

	//infinite while loop that only stops when the user presses ctrl + d
	while(1)
	{
		//takes in the value
		cin >> Input;

		//breaks out of the loop when cin is closed (when ctrl + d)
		if(cin.eof())
		{
			break;
		}

		//adds to each stat
		stats.push(Input);
	}
	
	//displays each stat
	stats.print();

	return 0;
}
