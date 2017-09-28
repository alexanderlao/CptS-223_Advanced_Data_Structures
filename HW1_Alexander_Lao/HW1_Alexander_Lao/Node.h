#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

// forward declaration
class ReversibleStack;

class Node
{
	// enable ReversibleStack to access the private data members
	// of Node
	friend class ReversibleStack;

	public:
		// constructor
		Node (int newData);

		// copy constructor
		Node (Node &copy);

		// destructor
		~Node ();

		// getters
		int getData ();
		Node * getNextPtr ();

		// setters
		void setData (int newData);
		void setNextPtr (Node * newNext);

	private:
		int mData;
		Node *mpNext;
};

#endif