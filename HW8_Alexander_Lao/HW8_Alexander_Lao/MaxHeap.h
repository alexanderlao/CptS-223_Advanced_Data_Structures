#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

template <class T>
class MaxHeap
{
	public:
		MaxHeap ();
		MaxHeap (int newK);
		~MaxHeap ();
		MaxHeap (MaxHeap<T> &copy);

		void reset (int newK);
		void add (T addValue);
		void siftUp (int index);
		void swap (int currentIndex, int parentIndex);
		void remove ();
		void siftDown (int index);
		void displayVector ();

	private:
		int k;
		vector<T> heapVector;
};

template <class T>
MaxHeap<T>::MaxHeap ()
{
	// initialize k to a value
	// it will be changed in the reset command
	this -> k = 0;
}

template <class T>
MaxHeap<T>::MaxHeap (int newK)
{
	// parameterized constructor will make a k-ary max heap
	// based on the k value passed in
	this -> k = newK;
}

template <class T>
MaxHeap<T>::~MaxHeap ()
{
	// destructor will implicity invoke the vector's destructor
	heapVector;
}

template <class T>
MaxHeap<T>::MaxHeap (MaxHeap<T> &copy)
{
	this -> k = copy.k;
	this -> heapVector = copy.heapVector;
}

template <class T>
void MaxHeap<T>::reset (int newK)
{
	// clear the current heap
	this -> heapVector.clear ();

	// reset the k value
	this -> k = newK;
}

template <class T>
void MaxHeap<T>::add (T addValue)
{
	// push the add value into the vector
	heapVector.push_back (addValue);

	// local variable to hold the newly added value's index
	int addedIndex = ((heapVector.size ()) - 1);

	// sift the newly added value if appropriate
	siftUp (addedIndex);
}

template <class T>
void MaxHeap<T>::siftUp (int index)
{
	// check for a valid index
	if (index <= 0) return;

	// check if the index is still valid and if the value at the index is greater than
	// the value in its parent index
	while ((index > 0) && (heapVector[index]) > ((heapVector[(index - 1) / k])))
	{
		int parentIndex = (index - 1) / k;

		// swap the values if we find a value greater than its parent
		swap (index, parentIndex);

		// keep a pointer to the swapped value
		// to check against its new parent
		index = (index - 1) / k;
	}
}

template <class T>
void MaxHeap<T>::swap (int currentIndex, int parentIndex)
{
	// set a temporary T variable to hold the parentIndex's value
	T temp = heapVector[parentIndex];

	// set currentIndex's value as parentIndex's value
	heapVector[parentIndex] = heapVector[currentIndex];

	// set current's value as the parent's old value
	heapVector[currentIndex] = temp;
}

template <class T>
void MaxHeap<T>::remove ()
{
	// store the root value into a temporary variable
	T returnMe = heapVector[0];

	// print out the value to be removed
	cout << returnMe << endl;

	// store the last index in a temporary variable
	int lastIndex = heapVector.size () - 1;

	// swap the last added value with the root
	heapVector[0] = heapVector[lastIndex];

	// pop the last value from the vector since
	// we moved it into the root
	heapVector.pop_back ();

	// check if the vector is empty
	if (heapVector.size () == 0) return;

	// sift down the root
	else siftDown (0);
}

template <class T>
void MaxHeap<T>::siftDown (int index)
{
	// check if a left-most child exists
	// if not, we can assume that the current index has no children
	// for any k-ary heap
	if (((k * index) + 1) > heapVector.size () - 1) return;

	// local variable to hold the child index with the greatest value
	// initialize it to the left-most child index
	int greatestIndex = (k * index) + 1;

	// loop through all the child indices and find the greatest child index
	for (int i = (k * index) + 1; i <= (k * index) + k; i++)
	{
		// check if i is a valid index in the array and
		// the value at index i is greater than the value in the old greatestIndex
		if ((i <= heapVector.size () - 1) && (heapVector[i] > heapVector[greatestIndex]))
		{
			// update the greatestIndex
			greatestIndex = i;
		}
	}

	// check if the child index with the biggest value is greater than
	// the value in the parent
	if (heapVector[index] > heapVector[greatestIndex]) return;
	else
	{
		// swap the values if we find a value greater than its child
		swap (index, greatestIndex);
	}
	// make the recursive call to the newly swapped child
	siftDown (greatestIndex);
}	

template <class T>
void MaxHeap<T>::displayVector ()
{
	// loop through the vector and print out its content
	for (int i = 0; i < heapVector.size (); i++)
	{
		cout << heapVector[i] << ",";
	}

	// end the line
	cout << endl;
}

#endif