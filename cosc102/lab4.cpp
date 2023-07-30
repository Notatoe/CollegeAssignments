// Noah Morris
// Dunn - Section 3
// 09/11/2019
// Lab 4
// TA: Angel
// This program takes car's and truck's miles and gallons to find an average in the miles per gallon in cars and trucks.

#include <iostream>
#include <string>
#include <limits>
using namespace std;

int main()
{
	//initailizes all of the variables that will be used
	string command;
	double carMiles, carGallons, tCarMiles, tCarGallons, carNum, carMPG, truckMiles, truckGallons, tTruckMiles, tTruckGallons, truckNum, truckMPG;

	//sets these to 0 since they will only be added upon
	carNum = 0;
	truckNum = 0;
	tCarMiles = 0;
	tCarGallons = 0;
	tTruckMiles = 0;
	tTruckGallons = 0;
	
	//a large do/while loop that only ends when the user gives the "done" command
	do
	{
		//asks the user for their command
		cout << "Enter command: ";
		cin >> command;
		
		//large if statement that runs one of the four outcomes based on what command the user gave
		if(command == "car")
		{
			//adds 1 to tell later if the fleet has cars
			carNum++;

			//asks for the car's miles and error checks to make sure the user's response was valid
			do
			{
				if(!cin)
				{	
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				cout << "Enter car's miles: ";
			}
			while(!(cin >> carMiles) || !(carMiles > 0));
			
			//asks for the car's gallons and error checks to make sure the user's response was valid
			do
			{
				if(!cin)
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				cout << "Enter car's gallons: ";
			}
			while(!(cin >> carGallons) || !(carGallons > 0));
			
			//adds the inputted values to the total car miles and gallons and also sets the average car MPG as of the latest car
			tCarMiles = tCarMiles + carMiles;
			tCarGallons = tCarGallons + carGallons;
			carMPG = tCarMiles / tCarGallons;
		}
		else if(command == "truck")
		{
			//adds 1 to tell later if the fleet has trucks
			truckNum++;
			
			//asks for the truck's miles and error checks to make sure the user's response was valid
			do
			{
				if(!cin)
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				cout << "Enter truck's miles: ";
			}
            while(!(cin >> truckMiles) || !(truckMiles > 0));
			
			//asks for the truck's gallons and error checks to make sure the user's response was valid
			do
			{
				if(!cin)
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				cout << "Enter truck's gallons: ";
			}
			while(!(cin >> truckGallons) || !(truckGallons > 0));
			
			//adds the inputted values to the total truck miles and gallons and also sets the average truck MPG as of the latest truck
			tTruckMiles = tTruckMiles + truckMiles;
			tTruckGallons = tTruckGallons + truckGallons;
			truckMPG = tTruckMiles / tTruckGallons;

		}
		else if(command == "done")
		{
			//displays the a message saying that the fleet has no cars or trucks or just gives the MPG of cars and trucks
			if(carNum == 0)
			{
				cout << "Fleet has no cars.\n";
			}
			else
			{
				cout << "Average car MPG = " << carMPG << endl;
			}

			if(truckNum == 0)
			{
				cout << "Fleet has no trucks.\n";
			}
			else
			{
				cout << "Average truck MPG = " << truckMPG << endl;
			}

		}
		else
		{
			//displays "Unknown command." if the user didn't use a valid command
			cout << "Unknown command.\n";
		}
	}
	while(command != "done");

	return 0;
}
