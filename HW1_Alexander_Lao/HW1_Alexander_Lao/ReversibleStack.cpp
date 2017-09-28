#include "ReversibleStack.h"

// constructor
ReversibleStack::ReversibleStack ()
{
	this -> mpTop = NULL;
}

// copy constructor
ReversibleStack::ReversibleStack (ReversibleStack &copy)
{
	this -> mpTop = copy.mpTop;
}

// destructor
ReversibleStack::~ReversibleStack ()
{
	// the destructor will not need to release any dynamic memory
}

void ReversibleStack::push (int item)
{
	// dynamically allocate the new node
	Node *newNode = new Node (item);

	// if the newNode was dynamically allocated correctly
	if (!(newNode == NULL))
	{
		// set the newNode's next to the old top
		newNode -> mpNext = mpTop;

		// set the top as the new node
		mpTop = newNode;
	}
}

int ReversibleStack::pop ()
{
	// check if the stack is empty
	if (mpTop == NULL)
	{
		// there's nothing to pop
	}
	else
	{
		// create a local variable for storing the data being popped
		int poppedData;

		// store the top in a temporary node
		Node *pTemp = mpTop;

		// the old top's next is now the new top
		mpTop = mpTop -> mpNext;

		// get the popped node's data and store it 
		// in the local variable
		poppedData = pTemp -> mData;

		// delete pTemp
		delete pTemp;

		return poppedData;
	}
}

bool ReversibleStack::isEmpty () const
{
	// check if the top is empty
	if (mpTop == NULL)
	{
		cout << "true\n";
		return true;
	}
	else
	{
		cout << "false\n";
		return false;
	}
}

void ReversibleStack::reverse ()
{
	// create a local ReversibleStack object
	ReversibleStack reversed;

	// create a new pointer to a node and set it to the top of the list
	Node *pCur = mpTop;

	// while the top node is not null
	while (pCur != NULL)
	{
		// push the node's data to our local reversible stack object
		reversed.push (pCur -> mData);

		// cycle to the next node
		pCur = pCur -> mpNext;
	}
	
	// update the old list to the new list
	mpTop = reversed.mpTop;
}

void ReversibleStack::display (std::ostream& writer) const
{
	// store the top node in a temporary node
	Node *pTemp = mpTop;

	// while the temporary node is not null
	while (pTemp != NULL)
	{
		// print out the temporary node's data
		writer << pTemp -> mData << " ";

		// if we're at the last node
		if (pTemp -> mpNext == NULL)
		{
			// end the line
			writer << "\n";
		}

		// cycle to the next node
		pTemp = pTemp -> mpNext;
	}
}