// Noah Morris
// 9/16/20
// cosc140
// Homework 6

//PROBLEM 1

#include <iostream>
#include <list>
using namespace std;

//ex_count with template implimentation
template <typename T>
int ex_count(T l1, T l2, int target)
{
	int count = 0;
	while(1)
	{
		if(*l1 == target)
		{
			count++;
		}

		if(l1 == l2)
		{
			break;
		}

		l1++;
	}
	return count;
}

int main() {
	list<int> v;
	list<int>::iterator iv;
	int value;
	while (cin >> value)
		v.push_back(value);
	int target = *v.begin();
	int N = ex_count(v.begin(), v.end(), target);
	cout << "Found " << N << " instances of " << target << "\n";
}

//PROBLEM 2

#include <iostream>
#include <list>
using namespace std;

//ex_eq function object
struct ex
{
	int ex_eq(int target)
	{
		return target;
	}
};

template <typename T>
int ex_count(T l1, T l2, int target)
{
	int count = 0;
	while(1)
	{
		if(*l1 == target)
		{
			count++;
		}

		if(l1 == l2)
		{
			break;
		}

		l1++;
	}
	return count;
}


int main() {
	list<int> v;
	list<int>::iterator iv;
	int value;
	while (cin >> value)
		v.push_back(value);
	int target = *v.begin();
	int N = ex_count(v.begin(), v.end(), ex_eq<int>(target));
	cout << "Found " << N << " instances of " << target << "\n";
}
