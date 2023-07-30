// Noah Morris
// Dunn - Section 3
// 09/24/2019
// For Lab 6
// TA: Angel
// This program tells if a date is within the bounds of two other dates

#include <iostream>
#include <string>
#include <limits>

using namespace std;

int main()
{
	//initializes all of the date integers
	int startYear, endYear, year, startMonth, endMonth, month, startDay, endDay, day;
	
	/*three do/while loops that check to see if the user types in three integers for each date as well as if the month is within 1 to 12 and day
	 *is within 0 to 31*/
	do
	{
		if(!cin)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cout << "Enter start date: ";
	}
	while(!(cin >> startYear >> startMonth >> startDay) || startMonth > 12 || startMonth < 0 || startDay < 0 || startDay > 31);

	do
	{
		if(!cin)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cout << "Enter end date  : ";
	}
	while(!(cin >> endYear >> endMonth >> endDay) || endMonth > 12 || endMonth < 0 || endDay < 0 || endDay > 31);

	do
	{
		if(!cin)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cout << "Enter date      : ";
	}
	while(!(cin >> year >> month >> day) || month > 12 || month < 0 || day < 0 || day > 31);

	//large line of if statements that displays "IN RANGE" if the date is between the start and end date and "OUT OF RANGE" if it is not
	//if statement for if the year is between the start and end year
	if(startYear < year && year < endYear)
	{
		cout << "IN RANGE\n";
	}
	//line of if/else statements to check if the date is within bounds while having the same year as the start year
	else if(year == startYear)
	{
		if(month > startMonth)
		{
			cout << "IN RANGE\n";
		}
		else if(month = startMonth)
		{
			if(day > startDay)
			{
				cout << "IN RANGE\n";
			}
			else
			{
				cout << "OUT OF RANGE\n";
			}
		}
		else
		{
			cout << "OUT OF RANGE\n";
		}
	}
	//line of if/else statements to check if the date is within bounds while having the same year as the end year
	else if(year == endYear)
	{
		if(month < startMonth)
		{
			cout << "IN RANGE\n";
		}
		else if(month = endMonth)
		{
			if(day < startDay)
			{
				cout << "IN RANGE\n";
			}
			else
			{
				cout << "OUT OF RANGE\n";
			}
		}
		else
		{
			cout << "OUT OF RANGE\n";
		}
	}
	//else statement that only runs if the year itself if not within the bounds
	else
	{
		cout << "OUT OF RANGE\n";
	}

	return 0;
}
