// Noah Morris
// Dunn - Section 3
// 10/23/2019
// Lab 8
// TA: Angel
// This program is a basic version of blackjack with one player playing against the AI dealer and includes the ability for an Ace to be worth 1 or 11 points

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <random>
#include <chrono>

using namespace std;

//prototypes for the functions that get a random int, deals cards to the people, scores each side's hand, and initializes the deck respectivley
int GetRandom();
int DealCard(int d[]);
int ScoreHand(int c[],int player);
void InitializeDeck(int deck[], char suit[], string card[]);

int main()
{
	//initializes the values and arrays for the deck that will be used throughout the code
	int i, j, temp;
	int score[2] = {0};
	int deck[52];
	char suit[52];
	string hand[2] = {" "," "};
	string card[52], play;
	string title[2] = {"Dealer has cards:", "You have cards  :"};
	
	//initializes the deck, suit, and card array which make up the deck
	InitializeDeck(deck,suit,card);
	
	//deals the initial two cards to the dealer and player
	for(i = 1; i <= 2; i++)
	{
		for(j = 0; j < 2; j++)
		{
			temp = DealCard(deck);
			deck[temp] = i;
			hand[i - 1] += card[temp] + suit[temp] + ' ';
		}
		
		//scores the hand of the player and dealer
		score[i - 1] = ScoreHand(deck, i);
		
		//displays the hand and score of the player and dealer
		cout << title[i - 1];
		cout << setfill(' ') << setw(19) << left << hand[i - 1];
		cout << '(' << score[i - 1] << ")\n";
	}
	
	//the players turn at drawing cards until they are satisfied
	do
	{
		//error checks to make sure the player has chosen to hit or stand
		do
		{
			if(!cin)
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			cout << "Hit or Stand    ? ";
		}
		while(!(cin >> play) || !(play == "stand" || play == "Stand" || play == "hit" || play == "Hit"));
		
		//puts a empty line for formatting
		cout << endl;
		
		//breaks out of the loop if they choose to keep their current hand
		if(play == "stand" || play == "Stand")
		{
			break;
		}
		
		//deals another card to the player
		temp = DealCard(deck);
		deck[temp] = 2;
		hand[1] += card[temp] + suit[temp] + ' ';
		score[1] = ScoreHand(deck, 2);
		
		//displays the dealer's hand and score
		cout << title[0];
		cout << setfill(' ') << setw(19) << left << hand[0];
		cout << '(' << score[0] << ")\n";
		
		//displays the player's hand and score
		cout << title[1];
		cout << setfill(' ') << setw(19) << left << hand[1];
		cout << '(' << score[1] << ")\n";
		
		//outcome if the player's score goes over 21
		if(score[1] > 21)
		{
			cout << "Player busts, dealer wins!\n";
			return 1;
		}
		
		//outcome if the player's score is exactly 21
		if(score[1] == 21)
		{
			cout << "Player wins!\n";
			return 1;
		}
	}
	while(play != "Stand" || play != "stand");
	
	//checks to see if the player got an ace and if they'd like to mkae it equal to 11
	if(deck[0] == 2 || deck[13] == 2 || deck[26] == 2 || deck[39] == 2)
	{
		//error checks to make sure the user put 1 or 11
		do
		{
			if(!cin)
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			cout << "Do you want your ace to be worth 1 or 11? ";
		}
		while(!(cin >> play) || !(play == "1" || play == "11"));
		
		//adds 10 to the score if the player chooses for their ace to equal 11
		if(play == "11")
		{
			score[1] += 10;
		}
		
		//displays the hand and score of the player and dealer
		cout << endl;
		cout << "Dealer has cards:";
		cout << setfill(' ') << setw(19) << left << hand[0];
		cout << '(' << score[0] << ")\n";
		cout << "You have cards  :";
		cout << setfill(' ') << setw(19) << left << hand[1];
		cout << '(' << score[1] << ")\n";
		
		//results if making the ace an 11 put the player's score up to 21 or above
		if(score[1] == 21)
		{
			cout << "Player wins!\n";
			return 1;
		}
		else if(score[1] > 21)
		{
			cout << "Player busts, Dealer wins!\n";
			return 1;
		}

		cout << endl;
	}
	
	//sees if the dealer has an ace and if they'd like to make it worth 1 or 11
	if(deck[0] == 1 || deck[13] == 1 || deck[26] == 1 || deck[39] == 1)
	{
		//checks if the dealer would be up to a 20 or 21 if the ace were 11, if not they keep it equal to 1
		if(score[0] == 10 || score[0] == 11)
		{
			cout << "The dealer chose for their ace to be worth 11.\n";
			score[0] += 10;
		}
	}

	//deals cards to the dealer until they are at 18 or above in score
	while(score[0] < 18)
	{
		temp = DealCard(deck);
		deck[temp] = 1;
		hand[0] += card[temp] + suit[temp] + ' ';
		score[0] = ScoreHand(deck, 1);

		cout << "Dealer hits     :";
		cout << setfill(' ') << setw(19) << left << hand[0];
		cout << '(' << score[0] << ")\n";
		
		//checks to see if the dealer would be at 20 or 21 if their ace was worth 11, if not they leave it as worth 1
		if(deck[0] == 1 || deck[13] == 1 || deck[26] == 1 || deck[39] == 1)
		{
			if(score[0] == 10 || score[0] == 11)
			{
				cout << "The dealer chose for their ace to be worth 11.\n";
				score[0] +=10;
			}
		}
	}
	
	//outcome for the dealer busting while drawing
	if(score[0] > 21)
	{
		cout << "Dealer busts, player wins!\n";
		return 1;
	}

	//displays the dealers score and hand after standing
	cout << "Dealer stands   :";
	cout << setfill(' ') << setw(19) << left << hand[0];
	cout << '(' << score[0] << ")\n";

	cout << endl;
	
	//displays the final hand and score of the player and dealer
	cout << "Dealer has cards:";
	cout << setfill(' ') << setw(19) << left << hand[0];
	cout << '(' << score[0] << ")\n";
	cout << "You have cards  :";
	cout << setfill(' ') << setw(19) << left << hand[1];
	cout << '(' << score[1] << ")\n";

	//compares the scores to see who won or if it was a draw
	if(score[0] > score[1])
	{
		cout << "Dealer wins!\n";
	}
	else if(score[0] == score[1])
	{
		cout << "Player and dealer draw.\n";
	}
	else if(score[0] < score[1])
	{
		cout << "Player wins!\n";
	}

	return 0;
}

//gets a random number within the bounds of the array of a deck
int GetRandom()
{
	unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine rng(seed);
	uniform_int_distribution<int> rand_int(0, 51);

	return rand_int(rng);
}

//returns the index of an undelt card so that it may be assigned to the player or dealer
int DealCard(int d[])
{
	int g;

	do
	{
		g = GetRandom();
	}
	while(d[g] != 0);

	return g;
}

//scores the hand of the the player or dealer
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

//initializes the three arrays that make up the deck of cards
void InitializeDeck(int deck[], char suit[], string card[])
{
	deck = {0};

	for(int i = 0; i < 13; i++)
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
}
