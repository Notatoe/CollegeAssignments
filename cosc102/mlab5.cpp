// Noah Morris
// Dunn - Section 3
// 09/17/2019
// For Lab 5
// TA: Angel
// This program asks the user for a seed, then that seed is used to get numbers from -10 to 10 in an array of 25

#include <iostream>
#include <string>
#include <random>
#include <limits>
using namespace std;

int main()
{
	//initializes the array, seed, i for the for loop, and the total for the total of the array
	int arr[25], seed, i;
	int total = 0;
	
	//asks the user to enter a integer for the seed and error checks for non-integers
	do
	{
		if(!cin)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cout << "Enter a seed: ";
	}
	while(!(cin >> seed));
	
	//initializes a ranfom number generator using the seed the user gave
	default_random_engine rng(seed);
	
	//sets the range on what the number generator can output
	uniform_int_distribution<int> rand_int(-10,10);
	
	//sets each value of the array to a random number
	for(i = 0; i < 25; ++i)
	{
		arr[i] = rand_int(rng);
	}
	
	//adds all of the array's values to a total
	for(i = 0; i < 25; ++i)
	{
		total = total +  arr[i];
	}
	
	//tells the user the sum of the values within the array
	cout << "Sum of array = " << total << endl;

	return 0;
}
