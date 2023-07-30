// Noah Morris
// Homework 4



// OPTION A
if (mode == 'A')
{
	// use std::partial_sort()
	partial_sort((A.begin(), A.begin() + k, A.end());
}
// OPTION B
else if (mode == 'B')
{
	// use std::make_heap(), loop w/std::pop_heap() and std::reverse()
	make_heap(A.begin(), A.end());
	for(int i = 0; i < k; i++)
	{
		pop_heap(A.begin() + k, A.end() - i);
	}
	reverse(A.begin(), A.end());
}

//OPTION C
else if (mode == 'C')
{
	// modify the code from mode B work likemode A
	make_heap(A.begin(), A.end());
	for(int i = 0; i < k; i++)
	{
		pop_heap(A.begin() + k, A.end() - i);
	}
	reverse(A.begin(), A.end());
	reverse(A.begin(), A.begin() + k);
} 
