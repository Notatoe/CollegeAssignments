// Noah Morris
// Dunn - Section 3
// 10/09/2019
// Lab 7
// TA: Angel
// This program asks the user for a number of people and gives each person two cards from a deck

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>
#include <random>
#include <chrono>

using namespace std;

//Gets a random number from 0 to 51
int GetRandom()
{	
	unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine rng(seed);
	uniform_int_distribution<int> rand_int(0, 51);

	return rand_int(rng);
}

//assigns a random card to a number that is associated with each player without giving two players the same card
int DealCard(int d[])
{
	int g,h;

	do
	{
		g = GetRandom();
		h = d[g];
	}
	while(h != 0);

	return g;
}

//takes the array of cards and player number to give the score of the hand they were given
int ScoreHand(int c[],int player)
{
	int temp = 0;
	
	for(int q = 0; q < 52; q++)
	{
		if(c[q] == player)
		{
			if(q % 13 > 9)
			{
				temp = temp + 10;
			}
			else
			{
				temp = temp + (q % 13) + 1;
			}
		}
	}

	return temp;
}

int main()
{
	//intitializes the arrays for the deck and its components as well as the integers that are used throughout the code
	int players, index, i, index1, index2, score;
	int deck[52] = {0};
	char suit[52];
	string card[52], string1;
	
	//sets the arrays for the card face and suit in order of Ace to King and Hearts to Clubs
	for(i = 0; i < 13; i++)
	{
		suit[i] = 'H';
		suit[i + 13] = 'D';
		suit[i + 26] = 'S';
		suit[i + 39] = 'C';

		if(i % 13 == 0)
		{
			card[i] = "A";
			card[i + 13] = "A";
			card[i + 26] = "A";
			card[i + 39] = "A";
		}
		else if(i % 13 == 10)
		{
			card[i] = "J";
			card[i + 13] = "J";
			card[i + 26] = "J";
			card[i + 39] = "J";
		}
		else if(i % 13 == 11)
		{
			card[i] = "Q";
			card[i + 13] = "Q";
			card[i + 26] = "Q";
			card[i + 39] = "Q";

		}
		else if(i % 13 == 12)
		{
			card[i] = "K";
			card[i + 13] = "K";
			card[i + 26] = "K";
			card[i + 39] = "K";
		}
		else
		{
			card[i] = to_string(i + 1);
			card[i + 13] = to_string(i + 1);
			card[i + 26] = to_string(i + 1);
			card[i + 39] = to_string(i + 1);
		}
	}

	//asks the users to input the amount of players
	cout << "How many players? ";
	cin >> players;
	
	//error checks to see if the user put in a non-integer or invalid number for a single deck
	if((!players) || players < 1)
	{
		cout << "Invalid input.\n";
		return 1;
	}
	else if(players > 26)
	{
		cout << "Too many players.\n";
		return 1;
	}
	
	//Deals the cards and scores the hand, then displays these to the user
	for(i = 1; i <= players; i++)
	{
		//sets these to an impossible index so that it can be easily seen if they have been used
		index1 = -1;
		index2 = -1;
		
		//deals the cards to the player and records what index the cards are at
		for(int j = 0; j < 2; j++)
		{
			if(index1 == -1)
			{
				index1 = DealCard(deck);
				deck[index1] = i;
			}
			else
			{
				index2 = DealCard(deck);
				deck[index2] = i;
			}
		}
		
		//creates a string that holds the card both cards the player drew
		string1 = card[index1] + suit[index1] + " " + card[index2] + suit[index2];

		//calculates the score of the player's hand
		score = ScoreHand(deck, i);
		
		//displays the player statistics to the user
		cout << "Player " << i << " has cards: ";
		cout << setfill(' ') << setw(19) << left << string1;
		cout << '(' << score << ")\n";
	}	 

	return 0;
}
