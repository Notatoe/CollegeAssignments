// Noah Morris
// Dunn - Section 3
// 10/08/2019
// For Lab 7
// TA: Angel
// This program asks the user for  an index of an array of a deck of cards and gives you the which card that correlates to.

#include <iostream>
#include <string>
#include <array>
#include <limits>

using namespace std;

int main()
{
	//creates the int array for the cards, as well as an int for the index and 2 strings to define the card
	int deck[54], index;
	string card, suit;
	
	//error checks and makes sure the index number works with the deck array
	do
	{
		if(!cin)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cout << "Enter a card index: ";
	}
	while(!(cin >> index) || index < 0 || index > 51);
	
	//determines what suit the card is
	if(index < 13)
	{
		suit = "Hearts";
	}
	else if(index < 26)
	{
		suit = "Diamonds";
		index = index - 13;
	}
	else if(index < 39)
	{
		suit = "Spades";
		index = index - 26;
	}
	else
	{
		suit = "Clubs";
		index = index - 39;
	}
	
	//determines what number or title the card has
	if(index + 1 == 1)
	{
		card = "2";
	}
	else if(index + 1 == 2)
	{
		card = "3";
	}
	else if(index + 1 == 3)
	{
		card = "4";
	}
	else if(index + 1 == 4)
	{
		card = "5";
	}
	else if(index + 1 == 5)
	{
		card = "6";
	}
	else if(index + 1 == 6)
	{
		card = "7";
	}
	else if(index + 1 == 7)
	{
		card = "8";
	}
	else if(index + 1 == 8)
	{
		card = "9";
	}
	else if(index + 1 == 9)
	{
		card = "10";
	}
	else if(index + 1 == 10)
	{
		card = "Jack";
	}
	else if(index + 1 == 11)
	{
		card = "Queen";
	}
	else if(index + 1 == 12)
	{
		card = "King";
	}
	else
    {
		card = "Ace";
	}

	//displays what the card is.
	cout << "That's the " << card << " of " << suit << '\n';

	return 0;
}
