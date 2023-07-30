// Noah Morris
// 9/8/2020
// cosc140
// Homework 3

node findnode(int i) 
{
	//checks to see if the head is called
	if (i == -1)
	{
		return head;
	}

	//checks if the node is in the first half or is the center of the list
	if(i < (N / 2) || i == (N / 2))
	{
		//searches down the list by going forward until i is equal to 0
		node *p = head->next;

		while (i--)
		{
			p = p->next;
		}
	}
	//checks if the node is in the second half of the list
	else if(i > (N / 2))
	{
		//sets i to be the difference in number of nodes
		i = N - i;

		//searches down the list by going backwards until i is equal to 0
		node *p = head->prev;

		while (i--)
		{
			p = p->prev;
		}
	}

	return p;
}
