// Noah Morris
// Dunn - Section 3
// 09/10/2019
// For Lab 4
// TA: Angel
// This program asks for your account balance then lets you deposit, withdraw, or check the balance as many times as you'd like.

#include <iostream>
#include <string>
using namespace std;

int main()
{
	//initializes the doubles for  account balance and transaction amount and string for inputted command
	double balance;
	double transaction;
	string command;
	
	//asks the user what their initial account value is
	cout << "Enter your initial account amount: ";
	cin >> balance;
	
	//starts a loop that keeps asking and performing commands until the user quits
	do
	{
		//asks the user what they want to do
		cout << "What do you want to do? ";
		cin >> command;
		
		//if they wanted to deposit, it asks them how much they want to deposit then adds that value to their balance
		if(command == "deposit")
		{
			cout << "How much? ";
			cin >> transaction;
			balance = balance + transaction;
		}
		//if they wanted to make a withdrawal, it asks how much they want to withdraw then subtracts that value from their balance
		else if(command == "withdrawal")
		{
			cout << "How much? ";
			cin >> transaction;
			balance = balance - transaction;
		}
		//if they wanted to check their balance, displays the value of their balance
		else if(command == "balance")
		{
			cout << "You have $" << balance << endl;
		}
		//if they want to quit then they continue to the end of the do while loop where it will end it since the command is equal to quit
		else if(command == "quit")
		{
			continue;
		}
		//if they give a command that is not one the four, it tells them that they put an invalid command and lists all available commands
		else
		{
			cout << "Invalid command. Available commands are deposit, withdrawal, balance, or quit.\n";
		}
	}
	while(command != "quit");

	return 0;
}

