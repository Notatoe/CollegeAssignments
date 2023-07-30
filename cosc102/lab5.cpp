// Noah Morris
// Dunn - Section 3
// 09/18/2019
// Lab 5
// TA: Angel
// This program allows the user to bet based on the seed they provide and then displays stats on their betting

#include <iostream>
#include <string>
#include <random>
#include <limits>
#include <array>
#include <vector>

using namespace std;

int main()
{
	//initializes the all of the integers that will be used as well as the array and 2 vectors
	int seed, balance, arr[3], bet, i, bigBet, smallBet, bigWin, smallWin, plays;
	vector<int> bets;
	vector<int> win;
	
	//sets starting balance to 1000 and number of plays to 0
	balance = 1000;
	plays = 0;
	
	//asks the user for a seed for the random number generator
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
	
	cout << endl;
	
	//sets up the random number generator with the seed and sets up a way to distribute the random numbers with the bounds of 0 and 7
	default_random_engine rng(seed);
	uniform_int_distribution<int> rand_int(2,7);
	
	//large do/while loop that keeps going until the user bets 0 and stops playing or if they run out of money
	do
	{
		//displays balance between every play
		cout << "Your money: $" << balance << '\n';
		
		//asks the user to make a bet then checks if it is an integer and if its less than zero or more than the available balance to bet with 
		do
		{
			if(!cin)
		    {
			    cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			cout << "Place a bet: $";
		}
		while(!(cin >> bet) || bet < 0 || balance - bet < 0);
		
		//breaks out of the loop if the bet is zero
		if(bet == 0)
		{
			cout << '\n';
			break;
		}
		
		//adds one to the amount of times it was played
		++plays;
		
		//sets the balance to subtract the bet as the bet is calculated
		balance = balance - bet;
		
		//adds the bet to the bets vector which stores the value of each bet
		bets.push_back(bet);

		//sets the values of the array to random numbers
		for(i = 0; i < 3; ++i)
		{
			arr[i] = rand_int(rng);
			cout << " " << arr[i];
		}
		
		cout << endl;
		
		//if statement if the array's values were all equal
		if(arr[0] == arr[1] && arr[1] == arr[2])
		{
			if(arr[0] == 7)
			{
				bet = bet * 10;
			}
			else
			{
				bet = bet * 5;
			}
			cout << "You won $" << bet << "!\n";
			balance = balance + bet;
			win.push_back(bet);
		}
		//if statement if only two of the array's values were equal
		else if(arr[0] == arr[1] || arr[0] == arr[2] || arr[1] == arr[2])
		{
			bet = bet * 2;
			cout << "You won $" << bet << "!\n";
			balance = balance + bet;
			win.push_back(bet);
		}
		//else statement if none of the array's values were equal
		else
		{
			cout << "You didn't win.\n";
			win.push_back(bet * 0);
		}
		
		//breaks out of the loop if the balance has become zero
		if(balance == 0)
		{
			cout << "\nYou are out of money!\n\n";
			break;
		}

		cout << '\n';
	}
	while(bet != 0);
	
	//determine if the user has made a bet by if the number of plays is zero or not
	if(plays == 0)
	{
		cout << "You walked away without playing.\n";
		return 0;
	}
	
	//prints out each bet that was made as well as the amount that was won from that bet
	for(i = 0; i < bets.size(); ++i)
	{
		cout << "You wagered $" << bets.at(i) << " and won $" << win.at(i) << ".\n";
	}

	cout << endl;
	
	//sets each bigBet, smallBet, and bigWin to the first bet's values
	bigBet = bets.at(0);
	smallBet = bets.at(0);
	bigWin = win.at(0);
	
	//sets smallWin to the last a non-zero value in the win vector
	for(i = 0; i < bets.size(); ++i)
	{
		if(win.at(i) != 0)
		{
			smallWin = win.at(i);
		}
	}
	
	/*sets bigBet and bigWin to the largest values in their respective vectors and smallBet to the smallest value in the bets vector and smallWin to the
	 *smallest non-zero value in the win vector*/
	for(i = 0; i < bets.size(); ++i)
	{
		if(bets.at(i) > bigBet)
		{
			bigBet = bets.at(i);
		}
		if(bets.at(i) < smallBet)
		{
			smallBet = bets.at(i);
		}
		if(win.at(i) > bigWin)
		{
			bigWin = win.at(i);
		}
		if(win.at(i) < smallWin && win.at(i) != 0)
		{
			smallWin = win.at(i);
		}
	}
	
	//displays to the user the smallest wager and winnings as well as the largest wager and winnings
	cout << "Your smallest wager was $" << smallBet << ".\n";
	cout << "Your largest wager was $" << bigBet << ".\n";
	cout << "Your smallest winnings was $" << smallWin << ".\n";
	cout << "Your largest winnings was $" << bigWin << ".\n";

	return 0;
}
