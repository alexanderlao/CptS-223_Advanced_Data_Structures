#ifndef REVERSIBLE_STACK_H
#define REVERSIBLE_STACK_H

#include <iostream>
#include <string>
#include "Node.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

class ReversibleStack
{
	public:
		// constructor
		ReversibleStack ();

		// copy constructor
		ReversibleStack (ReversibleStack &copy);

		// destructor
		~ReversibleStack ();

		void push (int item);
		int pop ();
		bool isEmpty () const;
		void reverse ();
		void display (std::ostream& writer) const;

	private:
		Node *mpTop;
};

#endif