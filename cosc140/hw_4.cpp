// Noah Morris
// 9/10/2020
// cosc140
// Homework 4

//PROBLEM 1:

#ifndef STACK_H
#define STACK_H
#include "slinked_list.h"
class stack {
	public:
		void stack();
		void ~stack();
		bool empty();
		int size();
		void push(int num);
		void pop();
		int top();
	private:
		list v;
		int[] a;
}stack()
{
	int* a = NULL;

	a = new int[10];

	a = {0};
}

stack::void ~stack()
{
	delete a;

	a = NULL;
}

stack::bool empty()
{
	for(int i = 0; i < 10; i++)
	{
		if(a[i] != 0)
		{
			break;
		}
		else if(i == 9)
		{
			return true;
		}
	}

	return false;
}

stack::int size()
{
	int temp;

	for(int i = 0; i < 10; i++)
	{
		if(a[i] != 0)
		{
			temp++;
		}
	}

	return temp;
}

stack::void push(int num)
{
	int temp;	

	for(int i = 0; i < 10; i++)
	{
		temp = a[i];
		a[i] = num;
		num = temp;
	}
}

stack::void pop()
{
	int temp = 0;
	int temp2;

	for(int = 9; i >= 0; i--)
	{
		temp2 = a[i];
		a[i] = temp;
		temp = temp2;
	}
}

stack::int top()
{
	return a[0];
}

#endif

//PROBLEM 2:
//
// Check for empty elements in the array and skip them in the case of top() or correct the array by removing them if they are between non-zero elements.
