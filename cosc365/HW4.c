// Noah Morris
// nmorri11

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node struct
struct node {
	int value;
	struct node *next;
};

// head node for keeping the location of the first node and current for traversing
struct node *head = NULL;
struct node *current = NULL;

// List sorting function
void sortList()
{
	// Using sorted as a boolean for if the whole list was traversed without a value swap
	int sorted = 1;

	// temp temporarily holds values for swapping
	int temp;

	current = head;

	while(1)
	{
		// If the list is empty, no need to sort
		if(head == NULL)
			break;

		// Once the end of the list is hit
		if(current->next == NULL)
		{
			// Break out if no swaps happened in the last traversal
			if(sorted == 1)
				break;
			// Reset
			else
			{
				current = head;
				sorted = 1;
			}
		}

		// Compares values and swaps if the earlier value is larger
		if(current->value > current->next->value)
		{
			temp = current->value;
			current->value = current->next->value;
			current->next->value = temp;
			sorted = 0;
		}

		// Moves to next node
		current = current->next;
	}
}

// Function for adding a node to the list
void addNode(int num)
{
	// Initializes the node
	struct node *temp = (struct node*)malloc(sizeof(struct node));
	temp->value = num;
	temp->next = NULL;

	// Set new node to head if it is the first insert
	if(head == NULL)
		head = temp;
	else
	{
		// Adds the new node to the end of the list
		current = head;
		while(current->next != NULL)
		{
			current = current->next;
		}
		current->next = temp;
	}
}

// Function for printing the list
void printList()
{
	// Starts from the head and prints each value of the list by traversal
	int num;
	current = head;
	while(current != NULL)
	{
		num = current->value;
		printf("%d\n", num);


		current = current->next;
	}
}

int main()
{
	// Input message
	int num;
	printf("Please input multiple numbers (input a 'X' when finished):");

	// Reads in numbers until a non-number is found
	while(scanf("%d", &num))
	{
		addNode(num);
	}

	// Prints the unsorted list
	printf("\nunsorted list:\n");
	printList();

	// Sorts the list
	sortList();

	// Prints the sorted list
	printf("\nsorted list:\n");
	printList();

	return 0;
}
