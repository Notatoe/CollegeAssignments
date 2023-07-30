#ifndef SLIST_H
#define SLIST_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <ctime>
using namespace std;
// include header file(s) neededi


// qsort_r3: randomly chosen pivot, 3-way partition {<},{=},{>}

template <class T>
class slist {
	private:
		struct node {
		  node() { data = T(); next = NULL; }

		// add node(const T &key) { write this }
		node(const T &key)
		{
		data = key;
		next = NULL;
		}

		// add overloaded operator< code
		bool operator<(const node &rhs) const
		{
		return (data < rhs.data);
		}

		T data;
		node *next;
		};

		// add class sptr { write this for node data }
		class sptr {
			public:
				sptr(node *_ptr=NULL) {
					ptr = _ptr;
				}
				bool operator< (const sptr &rhs) const {
					return (*ptr < *rhs.ptr);
				}
				operator node * () const { return ptr; }
			private:
				node *ptr;
		};

	public:
		class iterator {
			public:
				iterator() { p = NULL; }
				T & operator*() { return p->data; }
				iterator & operator++() { p = p->next; return *this; }
				bool operator!=(const iterator & rhs) const { return p != rhs.p; }

			private:
				iterator(node *n_p) { p = n_p; }
				node *p;

				friend class slist<T>;
		};

	public:
		slist();
		~slist();

		void push_back(const T &);
		void sort(const string &);

		iterator begin() { return iterator(head->next); }
		iterator end() { return iterator(NULL); }

	private:
		node *head;
		node *tail;
};

template <typename T>
slist<T>::slist() {
	head = new node();
	tail = head;
}

template <typename T>
slist<T>::~slist() {
	while (head->next != NULL) {
		node *p = head->next;
		head->next = p->next;
		delete p;
	}
	delete head;

	head = NULL;
	tail = NULL;
}

template <typename T>
void slist<T>::push_back(const T &din) {
	tail->next = new node(din);
	tail = tail->next;
}

	template <typename T>
void slist<T>::sort(const string &algname)
{
	node *temp = head;
	int length = 0;
	// determine number of list elements
	while(temp != NULL)
	{
		temp = temp->next;
		length++;
	}
	// set up smart pointer array called Ap
	vector<sptr> Ap(length);
	temp = head;
	for(unsigned int i = 0; i < length; i++)
	{
		Ap[i] = temp->next;
		node *temp2 = temp;
		temp = temp->next;
		temp2->next = NULL;
	}

	// if quicksort, apply std::sort
	if(algname == "-quicksort")
	{
		std::sort(Ap.begin(), Ap.end());
	}

	// if mergesort, apply std::stable_sort
	if(algname == "-mergesort")
	{
		std::stable_sort(Ap.begin(), Ap.end());
	}

	// if qsort_r3, apply qsort_r3

	// use sorted Ap array to relink list
	temp = head;
	for(unsigned int i = 0; i < length; i++)
	{
		temp->next = Ap[i];
		temp = temp->next;
	}
}

#endif // SLIST_H
