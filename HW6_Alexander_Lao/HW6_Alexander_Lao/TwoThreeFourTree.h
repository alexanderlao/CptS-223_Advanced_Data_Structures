#ifndef TWO_THREE_FOUR_TREE_H
#define TWO_THREE_FOUR_TREE_H

#include "Node.h"

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

template <class T>
class TwoThreeFourTree
{
	public:
		TwoThreeFourTree ();
		TwoThreeFourTree (TwoThreeFourTree<T> &copy);
		~TwoThreeFourTree ();

		Node<T>* getRoot ();

		void add (T* newType);
		void remove (T* removeType, int &size);
		void splitRoot (Node<T>*& splitThisNode);
		void splitLeaf (Node<T>*& splitThisNode, Node<T>*& parentNode);
		Node<T>* branch (Node<T>* currentNode, T* newType);
		int countLevels ();
		void displayInOrder (Node<T>* currentNode);
		T* getName (Node<T>* currentNode, T*& searchStudent);
		void getLevel (Node<T>* currentNode, T*& searchStudent, int counter, bool& truth);
		void countValuesInNode (Node<T>* currentNode, T*& searchStudent, int& size);
		void fuse (Node<T>*& currentNode, Node<T>*& parentNode, T* removeType, int &size);
		bool containsValue (Node<T>* currentNode, T* checkType);
		bool isLeaf (Node<T>* currentNode);
		int countValuesInCurrentNode (Node<T>* currentNode);
		T* minOfRightSubtree (Node<T>* currentNode, T* removeType);
		void replace (Node<T>*& currentNode, T* deleteValue, T* replaceValue);
		void fixBorrowedNode (Node<T>*& fixThisNode);
		void borrowFromParentLM1 (Node<T>*& currentNode, Node<T>*& parentNode, T* removeType);
		void borrowFromParentM2 (Node<T>*& currentNode, Node<T>*& parentNode, T* removeType);
		void borrowFromParentR (Node<T>*& currentNode, Node<T>*& parentNode, T* removeType);

	private:
		Node<T>* pRoot;
		
		bool add (Node<T> *&pTree, T* newType);
		bool addAfterBranch (Node<T> *&pTree, Node<T> *&parentNode, T* newType);
		bool addAfterSplit (Node<T> *&pTree, T* newType);
		void remove (Node<T> *&currentNode, Node<T> *&parentNode, T* removeType, int &size);
};

// default constructor
template <class T>
TwoThreeFourTree<T>::TwoThreeFourTree ()
{
	this -> pRoot = NULL;
}

// copy constructor
template <class T>
TwoThreeFourTree<T>::TwoThreeFourTree (TwoThreeFourTree<T> &copy)
{
	// shallow copy
	this -> pRoot = copy.pRoot;
}

// destructor
template <class T>
TwoThreeFourTree<T>::~TwoThreeFourTree ()
{

}

template <class T>
Node<T>* TwoThreeFourTree<T>::getRoot ()
{
	return pRoot;
}

template <class T>
void TwoThreeFourTree<T>::add (T* newType)
{
	// calls the private add function
	// hides pointer information
	add (pRoot, newType);
}

template <class T>
void TwoThreeFourTree<T>::remove (T* removeType, int &size)
{
	// make a null node for the root
	// the root has no parent
	Node<T>* pNull = NULL;

	// calls the private remove function
	// hides pointer information
	remove (pRoot, pNull, removeType, size);
}

template <class T>
void TwoThreeFourTree<T>::splitRoot (Node<T>*& splitThisNode)
{
	// make a new node using the root's A value
	Node<T>* newL = new Node<T> (splitThisNode -> A);
	newL -> L = splitThisNode -> L;
	newL -> M1 = splitThisNode -> M1;

	// make a new node using the root's C value
	Node<T>* newR = new Node<T> (splitThisNode -> C);
	newR -> L = splitThisNode -> M2;
	newR -> M1 = splitThisNode -> R;

	// assign the root's L and M1 to the newly created nodes
	splitThisNode -> L = newL;
	splitThisNode -> M1 = newR;

	// set the root's M2 and R to null
	// because they're not being used
	splitThisNode -> M2 = splitThisNode -> R = NULL;

	// delete the root's A and C value
	// all we have is the B (middle) value
	delete splitThisNode -> A;
	delete splitThisNode -> C;

	// shift the root's B value into the A position
	splitThisNode -> A = splitThisNode -> B;

	// set the root's B and C value to null
	// because they're not being used anymore
	splitThisNode -> B = splitThisNode -> C = NULL;
}

template <class T>
void TwoThreeFourTree<T>::splitLeaf (Node<T>*& splitThisNode, Node<T>*& parentNode)
{
	// at this point the splitThisNode has three values
	// and it is a leaf node. we need to push its B value into its parent
	
	// check how many values the parent node has
	// one value
	if ((parentNode -> A) && !(parentNode -> B) && !(parentNode -> C))
	{
		// if the B value is less than the root's A value
		if (*(splitThisNode -> B) < *(parentNode -> A))
		{
			// move the root's A value into the root's B spot
			parentNode -> B = parentNode -> A;

			// put the new Student in the A spot
			parentNode -> A = splitThisNode -> B;

			// reassigning child pointers
			// need to make a new Node for M2 because it is initially
			// pointing to nothing. if we just set it to parentNode's -> M1 -> A,
			// the two values will have the same address
			Node<T>* tempM1 = new Node<T> (splitThisNode -> C);
			tempM1 -> L = parentNode -> M2;
			tempM1 -> M1 = parentNode -> R;
			parentNode -> M2 = parentNode -> M1;
			parentNode -> M1 = tempM1;
			parentNode -> L -> B = parentNode -> L -> C = NULL;
		}
		// if the B value is greater than the root's A value
		else if (*(splitThisNode -> B) > *(parentNode -> A))
		{
			// put the new Student in the B spot
			parentNode -> B = splitThisNode -> B;

			// reassigning child pointers
			// need to make a new Node for M2 because it is initially
			// pointing to nothing. if we just set it to parentNode's -> M1 -> A,
			// the two values will have the same address
			Node<T>* tempM2 = new Node<T> (splitThisNode -> C);
			tempM2 -> L = splitThisNode -> M2;
			tempM2 -> M1 = splitThisNode -> R;
			parentNode -> M2 = tempM2;
			parentNode -> M1 -> A = splitThisNode -> A;
			parentNode -> M1 -> B = parentNode -> M1 -> C = NULL;
			parentNode -> M1 -> M2 = parentNode -> M1 -> R = NULL;
		}
	}
	// two values
	else if ((parentNode -> A) && (parentNode -> B) && !(parentNode -> C))
	{
		// if the B value is less than both values in the root
		if ((*(splitThisNode -> B) < *(parentNode -> A)) && 
			(*(splitThisNode -> B) < *(parentNode -> B)))
		{
			// make a temporary Student that holds the B spot's values
			T *tempB = parentNode -> B;

			// move the B value to the C spot
			parentNode -> C = tempB;

			// move the A value to the B spot
			parentNode -> B = parentNode -> A;

			// put the B value in the A spot
			parentNode -> A = splitThisNode -> B;

			// reassign child pointers
			parentNode -> R = parentNode -> M2;
			parentNode -> M2 = parentNode -> M1;
			Node<T>* tempM1 = new Node<T> (parentNode -> L -> C);
			tempM1 -> L = parentNode -> L -> M2;
			tempM1 -> M1 = parentNode -> L -> R;
			parentNode -> M1 = tempM1;
			parentNode -> L -> B = parentNode -> L -> C = NULL;
			parentNode -> L -> M2 = parentNode -> L -> R = NULL;

		}
		// if the B value is greater than
		// the root's A value but less than the root's B value
		else if ((*(splitThisNode -> B) > *(parentNode -> A)) && 
				 (*(splitThisNode -> B) < *(parentNode -> B)))
		{
			// make a temporary Student that holds the B spot's values
			T *tempB = parentNode -> B;

			// move the tempB Student to the C spot
			parentNode -> C = tempB;

			// put the B value in the root's B spot
			parentNode -> B = splitThisNode -> B;

			// reassign child pointers
			parentNode -> R = parentNode -> M2;
			Node<T>* tempM2 = new Node<T> (parentNode -> M1 -> C);
			tempM2 -> L = parentNode -> M1 -> M2;
			tempM2 -> M1 = parentNode -> M1 -> R;
			parentNode -> M2 = tempM2;
			parentNode -> M1 -> B = parentNode -> M1 -> C = NULL;
			parentNode -> M1 -> M2 = parentNode -> M1 -> R = NULL;

		}
		// otherwise it's greater than both values so it goes into the C spot
		else
		{
			// put the B value in the root's C spot
			parentNode -> C = splitThisNode -> B;

			// reassign child pointers
			Node<T>* tempR = new Node<T> (parentNode -> M2 -> C);
			tempR -> L = parentNode -> M2 -> M2;
			tempR -> M1 = parentNode -> M2 -> R;
			parentNode -> R = tempR;
			parentNode -> M2 -> B = parentNode -> M2 -> C = NULL;
			parentNode -> M2 -> M2 = parentNode -> M2 -> R = NULL;
		}
	}
}

template <class T>
Node<T>* TwoThreeFourTree<T>::branch (Node<T>* currentNode, T* newType)
{
	// if the ID is less than the currentNode's A value
	if (*newType < *(currentNode -> A))
	{
		// branch left
		return currentNode -> L;
	}
	// otherwise it must be greater
	else
	{
		// check if B is in use
		if (currentNode -> B)
		{
			// if the ID is less than the currentNode's B value
			if (*newType < *(currentNode -> B))
			{
				// branch to M1
				return currentNode -> M1;
			}
			// otherwise it must be greater
			else
			{
				// check if C is in use
				if (currentNode -> C)
				{
					// if the ID is less than the currentNode's C value
					if (*newType < *(currentNode -> C))
					{
						// branch to M2
						return currentNode -> M2;
					}
					// otherwise it's greater
					else
					{
						// so branch to R
						return currentNode -> R;
					}
				}
				// if C isn't in use branch to M2
				else
				{
					return currentNode -> M2;
				}
			}
		}
		// if B isn't in use branch to M1
		else
		{
			return currentNode -> M1;
		}
	}
}

template <class T>
int TwoThreeFourTree<T>::countLevels ()
{
	// create a local variable for a counter
	int counter = 0;

	// set a local node to the root
	Node<T>* pCurrent = pRoot;

	// while the currentNode is not null
	while (pCurrent != NULL)
	{
		// increment the counter
		counter++;

		// set the currentNode to the currentNode's left node
		pCurrent = pCurrent -> L;
	}

	return counter;
}

template <class T>
void TwoThreeFourTree<T>::displayInOrder (Node<T>* currentNode)
{
	// if the currentNode is empty
	if (!(currentNode)) return;
		
	// a left and right subtree will always have an A value
	displayInOrder (currentNode -> L);
	cout << *(currentNode -> A);
	displayInOrder (currentNode -> M1);

	// a left and right subtree is not guaranteed to have a B and C value
	// check if a B exists
	if (currentNode -> B)
	{
		cout << *(currentNode -> B);
		displayInOrder (currentNode -> M2);

		// a C value cannot exist without a B
		// check if a C value exists
		if (currentNode -> C)
		{
			cout << *(currentNode -> C);
			displayInOrder (currentNode -> R);
		}
	}
}

template <class T>
T* TwoThreeFourTree<T>::getName (Node<T>* currentNode, T*& searchStudent)
{
	// base case
	if (currentNode == NULL)
	{
		return NULL;
	}

	// recursive call to the left
	getName (currentNode -> L, searchStudent); 
	
	// an A value will always exist in a left and right subtree
	// check if the ID matches
	if (*(currentNode -> A) == *searchStudent)
	{
		// set the search student to the found student
		searchStudent = currentNode -> A;

		return searchStudent;
	}

	// recursive call to M1
	getName (currentNode -> M1, searchStudent); 

	// a left and right subtree is not guaranteed to have a B and C value
	// check if a B exists
	if (currentNode -> B)
	{
		// check if the B value's ID matches
		if (*(currentNode -> B) == *searchStudent)
		{
			// set the search student to the found student
			searchStudent = currentNode -> B;

			return searchStudent;
		}

		// recursive call to M2
		getName (currentNode -> M2, searchStudent); 

		// a C value cannot exist without a B
		// check if a C value's ID matches
		if (currentNode -> C)
		{
			if (*(currentNode -> C) == *searchStudent)
			{
				// set the search student to the found student
				searchStudent = currentNode -> C;

				return searchStudent;
			}

			// recursive call to R
			getName (currentNode -> R, searchStudent); 
		}
	}
}

template <class T>
void TwoThreeFourTree<T>::getLevel (Node<T>* currentNode, T*& searchStudent, int counter, bool& truth)
{
	// base case
	if (currentNode == NULL)
	{
		return;
	}

	// recursive call to the left
	// increment the counter because we went down a level
	getLevel(currentNode -> L, searchStudent, counter + 1, truth); 
	
	// an A value will always exist in a left and right subtree
	// check if the ID matches
	if (*(currentNode -> A) == *searchStudent)
	{
		cout << counter << endl;

		truth = true;

		return;
	}

	// recursive call to M1
	getLevel (currentNode -> M1, searchStudent, counter + 1, truth);

	// a left and right subtree is not guaranteed to have a B and C value
	// check if a B exists
	if (currentNode -> B)
	{
		// check if the B value's ID matches
		if (*(currentNode -> B) == *searchStudent)
		{
			cout << counter << endl;

			truth = true;

			return;
		}

		// recursive call to M2
		getLevel(currentNode -> M2, searchStudent, counter + 1, truth); 

		// a C value cannot exist without a B
		// check if a C value's ID matches
		if (currentNode -> C)
		{
			if (*(currentNode -> C) == *searchStudent)
			{
				cout << counter << endl;

				truth = true;

				return;
			}

			// recursive call to R
			getLevel(currentNode -> R, searchStudent, counter + 1, truth);
		}
	}
}

template <class T>
void TwoThreeFourTree<T>::countValuesInNode (Node<T>* currentNode, T*& searchStudent, int& size)
{
	// base case
	if (currentNode == NULL)
	{
		return;
	}

	// recursive call to the left
	countValuesInNode(currentNode -> L, searchStudent, size); 
	
	// an A value will always exist in a left and right subtree
	// check if the ID matches
	if (*(currentNode -> A) == *searchStudent)
	{
		// if the node contains one value
		if ((currentNode -> A) && (!(currentNode -> B)) && (!(currentNode -> C)))
		{
			size = 1;
			return;
		}
		// if the node contains two values
		else if ((currentNode -> A) && (currentNode -> B) && (!(currentNode -> C)))
		{
			size = 2;
			return;
		}
		// if the node contains three values
		else if ((currentNode -> A) && (currentNode -> B) && (currentNode -> C))
		{
			size = 3;
			return;
		}
	}

	// recursive call to M1
	countValuesInNode(currentNode -> M1, searchStudent, size); 

	// a left and right subtree is not guaranteed to have a B and C value
	// check if a B exists
	if (currentNode -> B)
	{
		// check if the B value's ID matches
		if (*(currentNode -> B) == *searchStudent)
		{
			// if the node contains one value
			if ((currentNode -> A) && (!(currentNode -> B)) && (!(currentNode -> C)))
			{
				size = 1;
				return;
			}
			// if the node contains two values
			else if ((currentNode -> A) && (currentNode -> B) && (!(currentNode -> C)))
			{
				size = 2;
				return;
			}
			// if the node contains three values
			else if ((currentNode -> A) && (currentNode -> B) && (currentNode -> C))
			{
				size = 3;
				return;
			}
		}

		// recursive call to M2
		countValuesInNode(currentNode -> M2, searchStudent, size); 

		// a C value cannot exist without a B
		// check if a C value's ID matches
		if (currentNode -> C)
		{
			if (*(currentNode -> C) == *searchStudent)
			{
				// if the node contains one value
				if ((currentNode -> A) && (!(currentNode -> B)) && (!(currentNode -> C)))
				{
					size = 1;
					return;
				}
				// if the node contains two values
				else if ((currentNode -> A) && (currentNode -> B) && (!(currentNode -> C)))
				{
					size = 2;
					return;
				}
				// if the node contains three values
				else if ((currentNode -> A) && (currentNode -> B) && (currentNode -> C))
				{
					size = 3;
					return;
				}
			}

			// recursive call to R
			countValuesInNode(currentNode -> R, searchStudent, size); 
		}
	}
}

template <class T>
void TwoThreeFourTree<T>::fuse (Node<T>*& currentNode, Node<T>*& parentNode, T* removeType, int &size)
{
	// check which subtree of the parent we're in
	// in the left subtree
	if (*(parentNode -> L) == *currentNode)
	{
		// the left subtree can only borrow from the M1 subtree
		// check if there is a value to borrow in M1 (need at least 2 values in M1)
		if ((parentNode -> M1 -> A) && (parentNode -> M1 -> B))
		{
			// take the parent's A value and move it down to the currentNode's B spot
			currentNode -> B = parentNode -> A;

			// move the parent's M1's A value into the parent
			parentNode -> A = parentNode -> M1 -> A;

			// set the parent's M1's A value to null since we moved it
			parentNode -> M1 -> A = NULL;
			
			// need to fix the node we borrowed from (parentNode -> M1)
			fixBorrowedNode (parentNode -> M1);

			// need to fix child pointers
			parentNode -> L -> M2 = parentNode -> M1 -> L;
			parentNode -> M1 -> L = parentNode -> M1 -> M1;
			parentNode -> M1 -> M1 = parentNode -> M1 -> M2;
			parentNode -> M1 -> M2 = parentNode -> M1 -> R;
			parentNode -> M1 -> R = NULL;

			return;
		}
		// only 1 value in the M1 subtree
		else if ((parentNode -> M1 -> A) && !(parentNode -> M1 -> B) && !(parentNode -> M1 -> C))
		{
			// need to borrow from the parent
			borrowFromParentLM1 (currentNode, parentNode, removeType);
		}
	}
	// in the M1 subtree
	else if (*(parentNode -> M1) == *currentNode)
	{
		// the M1 subtree can borrow from L and M2
		// check if there is a value to borrow in L (need at least 2 values in L)
		if ((parentNode -> L -> A) && (parentNode -> L -> B))
		{
			// move the currentNode's A value into the B spot
			currentNode -> B = currentNode -> A;

			// take the parent's A value and move it down to the currentNode's A spot
			currentNode -> A = parentNode -> A;

			int borrowSize = countValuesInCurrentNode (parentNode -> L);

			// if the borrow node has two values take the B value (right most)
			if (borrowSize == 2)
			{
				// move the parent's L's B value into the parent
				parentNode -> A = parentNode -> L -> B;

				// update the parent's L's B value to null since we moved it
				parentNode -> L -> B = NULL;

				// need to fix child pointers
				parentNode -> M1 -> M2 = parentNode -> M1 -> M1;
				parentNode -> M1 -> M1 = parentNode -> M1 -> L;
				parentNode -> M1 -> L = parentNode -> L -> M2;
				parentNode -> L -> M2 = NULL;
			}
			else if (borrowSize == 3)
			{
				// move the parent's L's C value into the parent
				parentNode -> A = parentNode -> L -> C;

				// update the parent's L's C value to null since we moved it
				parentNode -> L -> C = NULL;

				// need to fix child pointers
				parentNode -> M1 -> M2 = parentNode -> M1 -> M1;
				parentNode -> M1 -> M1 = parentNode -> M1 -> L;
				parentNode -> M1 -> L = parentNode -> L -> R;
				parentNode -> L -> R = NULL;
			}
			
			// no need to fix the node we borrowed from (parentNode -> L)
			// since we took right-most values and updated them to null
			
			return;
		}
		// check if there is a value to borrow in M2 (need at least 2 values in M2)
		// first check if an M2 even exists
		else if ((parentNode -> M2))
		{
			if ((parentNode -> M2 -> A) && (parentNode -> M2 -> B))
			{
				int borrowSize = countValuesInCurrentNode (parentNode -> M2);

				// take the parent's B value and move it down to the currentNode's B spot
				currentNode -> B = parentNode -> B;

				// move the parent's M2's A value into the parent
				parentNode -> B = parentNode -> M2 -> A;

				// update the parent's M2's A value to null since we moved it
				parentNode -> M2 -> A = NULL;
			
				// need to fix the node we borrowed from (parentNode -> M2)
				fixBorrowedNode (parentNode -> M2);

				if (borrowSize == 2)
				{
					// need to fix child pointers
					parentNode -> M1 -> M2 = parentNode -> M2 -> L;
					parentNode -> M2 -> L = parentNode -> M2 -> M1;
					parentNode -> M2 -> M1 = parentNode -> M2 -> M2;
					parentNode -> M2 -> M2 = NULL;
				}
				else if (borrowSize == 3)
				{
					// need to fix child pointers
					parentNode -> M1 -> M2 = parentNode -> M2 -> L;
					parentNode -> M2 -> L = parentNode -> M2 -> M1;
					parentNode -> M2 -> M1 = parentNode -> M2 -> M2;
					parentNode -> M2 -> M2 = parentNode -> M2 -> R;
					parentNode -> M2 -> R = NULL;
				}
			
				return;
			}
		}
		// only 1 value in the L and M2 subtree
		else
		{
			// need to borrow from the parent
			borrowFromParentLM1 (currentNode, parentNode, removeType);
		}
	}
	// in the M2 subtree
	else if (*(parentNode -> M2) == *currentNode)
	{
		// the M2 subtree can borrow from M1 and R
		// check if there is a value to borrow in M1 (need at least 2 values in M1)
		if ((parentNode -> M1 -> A) && (parentNode -> M1 -> B))
		{
			// move the currentNode's A value into the B spot
			currentNode -> B = currentNode -> A;

			// take the parent's B value and move it down to the currentNode's A spot
			currentNode -> A = parentNode -> B;

			int borrowSize = countValuesInCurrentNode (parentNode -> M1);

			// if the borrow node has two values take the B value (right most)
			if (borrowSize == 2)
			{
				// move the parent's M1's B value into the parent
				parentNode -> B = parentNode -> M1 -> B;

				// update the parent's M1's B value to null since we moved it
				parentNode -> M1 -> B = NULL;

				// need to fix child pointers
				parentNode -> M2 -> M2 = parentNode -> M2 -> M1;
				parentNode -> M2 -> M1 = parentNode -> M2 -> L;
				parentNode -> M2 -> L = parentNode -> M1 -> M2;
				parentNode -> M1 -> M2 = NULL;
			}
			else if (borrowSize == 3)
			{
				// move the parent's M1's C value into the parent
				parentNode -> B = parentNode -> M1 -> C;

				// update the parent's M1's C value to null since we moved it
				parentNode -> M1 -> C = NULL;

				// need to fix child pointers
				parentNode -> M2 -> M2 = parentNode -> M2 -> M1;
				parentNode -> M2 -> M1 = parentNode -> M2 -> L;
				parentNode -> M2 -> L = parentNode -> M1 -> R;
				parentNode -> M1 -> R = NULL;
			}
			
			// no need to fix the node we borrowed from (parentNode -> M1)
			// since we took right-most values and updated them to null
			
			return;
		}
		// check if there is a value to borrow in R (need at least 2 values in R)
		// first check if an R even exists
		else if (parentNode -> R)
		{
			if ((parentNode -> R -> A) && (parentNode -> R -> B))
			{
				// take the parent's C value and move it down to the currentNode's B spot
				currentNode -> B = parentNode -> C;

				// move the parent's R's A value into the parent
				parentNode -> R -> A = parentNode -> C;

				// update the parent's R's A value to null since we moved it
				parentNode -> R -> A = NULL;
			
				// need to fix the node we borrowed from (parentNode -> L)
				fixBorrowedNode (parentNode -> R);

				// need to fix child pointers
				parentNode -> M2 -> M2 = parentNode -> R -> L;
				parentNode -> R -> L = parentNode -> R -> M1;
				parentNode -> R -> M1 = parentNode -> R -> M2;
				parentNode -> R -> M2 = parentNode -> R -> R;
				parentNode -> R -> R = NULL;
			
				return;
			}
		}
		// only 1 value in the M1 and R subtree
		else
		{
			// need to borrow from the parent
			borrowFromParentM2 (currentNode, parentNode, removeType);
		}
	}
	// in the R subtree
	else if (*(parentNode -> R) == *currentNode)
	{
		// the R subtree can only borrow from the M2 subtree
		// check if there is a value to borrow in M2 (need at least 2 values in M1)
		if ((parentNode -> M2 -> A) && (parentNode -> M2 -> B))
		{
			// move the currentNode's A value into the B spot
			currentNode -> B = currentNode -> A;

			// take the parent's C value and move it down to the currentNode's A spot
			currentNode -> A = parentNode -> C;

			int borrowSize = countValuesInCurrentNode (parentNode -> M2);

			// if the borrow node has two values take the B value (right most)
			if (borrowSize == 2)
			{
				// move the parent's M2's B value into the parent
				parentNode -> C = parentNode -> M2 -> B;

				// update the parent's M2's B value to null since we moved it
				parentNode -> M2 -> B = NULL;

				// need to fix child pointers
				parentNode -> R -> M2 = parentNode -> R -> M1;
				parentNode -> R -> M1 = parentNode -> R -> L;
				parentNode -> R -> L = parentNode -> M2 -> M2;
				parentNode -> M2 -> M2 = NULL;
			}
			else if (borrowSize == 3)
			{
				// move the parent's M2's C value into the parent
				parentNode -> C = parentNode -> M2 -> C;

				// update the parent's M2's C value to null since we moved it
				parentNode -> M2 -> C = NULL;

				// need to fix child pointers
				parentNode -> R -> M2 = parentNode -> R -> M1;
				parentNode -> R -> M1 = parentNode -> R -> L;
				parentNode -> R -> L = parentNode -> M2 -> R;
				parentNode -> M2 -> R = NULL;
			}
			
			// no need to fix the node we borrowed from (parentNode -> M1)
			// since we took right-most values and updated them to null
			
			return;
		}
		// only 1 value in the M2 subtree
		else if ((parentNode -> M2 -> A) && !(parentNode -> M2 -> B) && !(parentNode -> M2 -> C))
		{
			// need to borrow from the parent
			borrowFromParentR (currentNode, parentNode, removeType);
		}
	}
}

template <class T>
bool TwoThreeFourTree<T>::containsValue (Node<T>* currentNode, T* checkValue)
{
	// an A value will always exist in a left and right subtree
	// check if the ID matches
	if (*(currentNode -> A) == *checkValue)
	{
		return true;
	}

	// a left and right subtree is not guaranteed to have a B and C value
	// check if a B exists
	if (currentNode -> B)
	{
		// check if the B value's ID matches
		if (*(currentNode -> B) == *checkValue)
		{
			return true;
		}

		// a C value cannot exist without a B
		// check if a C value's ID matches
		if (currentNode -> C)
		{
			if (*(currentNode -> C) == *checkValue)
			{
				return true;
			}
		}
	}

	// otherwise it doesn't contain the value
	// so return false
	return false;
}

template <class T>
bool TwoThreeFourTree<T>::isLeaf (Node<T>* currentNode)
{
	return (!(currentNode -> L || currentNode -> M1 || currentNode -> M2 || currentNode -> R));
}

template <class T>
int TwoThreeFourTree<T>::countValuesInCurrentNode (Node<T>* currentNode)
{
	// if the node contains no values
	if ((!(currentNode -> A)) && (!(currentNode -> B)) && (!(currentNode -> C)))
	{
		return 0;
	}
	// if the node contains one value
	else if (((currentNode -> A) && (!(currentNode -> B)) && (!(currentNode -> C))) ||
			 ((!(currentNode -> A) && ((currentNode -> B)) && (!(currentNode -> C)))) ||
			 (!(currentNode -> A) && (!(currentNode -> B)) && ((currentNode -> C))))
	{
		return 1;
	}
	// if the node contains two values
	else if (((currentNode -> A) && (currentNode -> B) && (!(currentNode -> C))) ||
			 ((!(currentNode -> A) && (currentNode -> B) && ((currentNode -> C)))) ||
			 ((currentNode -> A) && (!(currentNode -> B)) && ((currentNode -> C))))
	{
		return 2;
	}
	// if the node contains three values
	else if ((currentNode -> A) && (currentNode -> B) && (currentNode -> C))
	{
		return 3;
	}
}

template <class T>
T* TwoThreeFourTree<T>::minOfRightSubtree (Node<T>* currentNode, T* removeType)
{
	// create a local variable that holds the size of the current node
	int nodeSize = countValuesInCurrentNode (currentNode);

	// if the node's size is 1
	if (nodeSize == 1)
	{
		// the right subtree would be M1
		currentNode = currentNode -> M1;

		// loop to the left most value in the subtree
		while (currentNode -> L != NULL)
		{
			currentNode = currentNode -> L;
		}

		// return the smallest value in the subtree
		return currentNode -> A;
	}
	// if the node's size is 2
	else if (nodeSize == 2)
	{
		// need to find if the removeType is in the A spot
		// or B spot so we can branch appropriately
		if (*(currentNode -> A) == *removeType)
		{
			// the right subtree would be M1
			currentNode = currentNode -> M1;

			// loop to the left most value in the subtree
			while (currentNode -> L != NULL)
			{
				currentNode = currentNode -> L;
			}

			// return the smallest value in the subtree
			return currentNode -> A;
		}
		// check if the B value's ID matches
		else if (*(currentNode -> B) == *removeType)
		{
			// the right subtree would be M2
			currentNode = currentNode -> M2;

			// loop to the left most value in the subtree
			while (currentNode -> L != NULL)
			{
				currentNode = currentNode -> L;
			}

			// return the smallest value in the subtree
			return currentNode -> A;
		}
	}
	// if the node's size is 3
	else if (nodeSize == 3)
	{
		// need to find if the removeType is in the A spot
		// or B spot so we can branch appropriately
		if (*(currentNode -> A) == *removeType)
		{
			// the right subtree would be M1
			currentNode = currentNode -> M1;

			// loop to the left most value in the subtree
			while (currentNode -> L != NULL)
			{
				currentNode = currentNode -> L;
			}

			// return the smallest value in the subtree
			return currentNode -> A;
		}
		// check if the B value's ID matches
		else if (*(currentNode -> B) == *removeType)
		{
			// the right subtree would be M2
			currentNode = currentNode -> M2;

			// loop to the left most value in the subtree
			while (currentNode -> L != NULL)
			{
				currentNode = currentNode -> L;
			}

			// return the smallest value in the subtree
			return currentNode -> A;
		}
		// check if the C value's ID matches
		else if (*(currentNode -> C) == *removeType)
		{
			// the right subtree would be R
			currentNode = currentNode -> R;

			// loop to the left most value in the subtree
			while (currentNode -> L != NULL)
			{
				currentNode = currentNode -> L;
			}

			// return the smallest value in the subtree
			return currentNode -> A;
		}
	}
}

template <class T>
void TwoThreeFourTree<T>::replace (Node<T>*& currentNode, T* deleteValue, T* replaceValue)
{
	// base case
	if (currentNode == NULL)
	{
		return;
	}

	// recursive call to the left
	replace (currentNode -> L, deleteValue, replaceValue); 
	
	// an A value will always exist in a left and right subtree
	// check if the ID matches
	if (*(currentNode -> A) == *deleteValue)
	{
		currentNode -> A = replaceValue;
	}

	// recursive call to M1
	replace (currentNode -> M1, deleteValue, replaceValue); 

	// a left and right subtree is not guaranteed to have a B and C value
	// check if a B exists
	if (currentNode -> B)
	{
		// check if the B value's ID matches
		if (*(currentNode -> B) == *deleteValue)
		{
			currentNode -> B = replaceValue;
		}

		// recursive call to M2
		replace (currentNode -> M2, deleteValue, replaceValue); 

		// a C value cannot exist without a B
		// check if a C value's ID matches
		if (currentNode -> C)
		{
			if (*(currentNode -> C) == *deleteValue)
			{
				currentNode -> C = replaceValue;
			}

			// recursive call to R
			replace (currentNode -> R, deleteValue, replaceValue); 
		}
	}
}

template <class T>
void TwoThreeFourTree<T>::fixBorrowedNode (Node<T>*& fixThisNode)
{
	int sizeOfBorrowed = countValuesInCurrentNode (fixThisNode);

	// if we borrowed from a node with two values
	if (sizeOfBorrowed == 1)
	{
		// need to move the node's B into the A spot
		fixThisNode -> A = fixThisNode -> B;

		// clear the node's B spot
		fixThisNode -> B = NULL;
	}
	// if we borrowed from a node with three values
	else if (sizeOfBorrowed == 2)
	{
		// need to move the node's B into the A spot
		fixThisNode -> A = fixThisNode -> B;

		// need to move the node's C into the B spot
		fixThisNode -> B = fixThisNode -> C;

		// clear the node's C
		fixThisNode -> C = NULL;
	}
}

template <class T>
void TwoThreeFourTree<T>::borrowFromParentLM1 (Node<T>*& currentNode, Node<T>*& parentNode, T* removeType)
{
	// check how many values the parent node has
	// one value
	if ((parentNode -> A) && !(parentNode -> B) && !(parentNode -> C))
	{
		// special case where we push values into the parent

		// the parent's B spot will hold the parent's current A spot
		parentNode -> B = parentNode -> A;

		// the parent's A spot will hold the parent's L's A value
		parentNode -> A = parentNode -> L -> A;
		
		// the parent's C spot will hold the parent's M1's A value
		parentNode -> C = parentNode -> M1 -> A;

		// local variables to hold the child pointers
		Node<T>* tempL = parentNode -> L -> L;
		Node<T>* tempM1 = parentNode -> L -> M1;
		Node<T>* tempM2 = parentNode -> M1 -> L;
		Node<T>* tempR = parentNode -> M1 -> M1;


		// need to reassign child pointers
		// special case when we are fusing children with no children of their own
		if (!(parentNode -> L -> L) && !(parentNode -> L -> M1) && !(parentNode -> M1 -> L) && !(parentNode -> M1 -> M1))
		{
			parentNode -> L = NULL;
			parentNode -> M1 = NULL;
			parentNode -> M2 = NULL;
			parentNode -> R = NULL;
		}
		else
		{
			parentNode -> L = tempL;
			parentNode -> M1 = tempM1;
			parentNode -> M2 = tempM2;
			parentNode -> R = tempR;

			parentNode -> L -> L = NULL;
			parentNode -> L -> M1 = NULL;
			parentNode -> M1 -> L = NULL;
			parentNode -> M1 -> M1 = NULL;
		}

		// the currentNode will now be the parentNode since we put everthing in the parent
		currentNode = parentNode;
	}
	// two values
	else if ((parentNode -> A) && (parentNode -> B) && !(parentNode -> C))
	{
		// move the parentNode's A value into its L's B spot
		parentNode -> L -> B = parentNode -> A;

		// move the parentNode's M1's A value into  its L's C spot
		parentNode -> L -> C = parentNode -> M1 -> A;

		// set the parentNode's A value to null since we moved it
		parentNode -> A = NULL;

		// fix the parentNode
		parentNode -> A = parentNode -> B;
		parentNode -> B = NULL;

		// reassign child pointers
		parentNode -> M1 = parentNode -> M2;
		parentNode -> M2 = NULL;
	}
	// three values
	else if ((parentNode -> A) && (parentNode -> B) && (parentNode -> C))
	{
		// move the parentNode's A value into its L's B spot
		parentNode -> L -> B = parentNode -> A;

		// move the parentNode's M1's A value into its L's C spot
		parentNode -> L -> C = parentNode -> M1 -> A;

		// set the parentNode's A value to null since we moved it
		parentNode -> A = NULL;

		// fix the parentNode
		parentNode -> A = parentNode -> B;
		parentNode -> B = parentNode -> C;
		parentNode -> C = NULL;

		// reassign child pointers
		parentNode -> M1 = parentNode -> M2;
		parentNode -> M2 = parentNode -> R;
		parentNode -> R = NULL;
	}
}

template <class T>
void TwoThreeFourTree<T>::borrowFromParentM2 (Node<T>*& currentNode, Node<T>*& parentNode, T* removeType)
{
	// check how many values the parent node has
	// one value
	if ((parentNode -> A) && !(parentNode -> B) && !(parentNode -> C))
	{
		// special case where we push values into the parent

		// the parent's B spot will hold the parent's current A spot
		parentNode -> B = parentNode -> A;

		// the parent's A spot will hold the parent's L's A value
		parentNode -> A = parentNode -> L -> A;
		
		// the parent's C spot will hold the parent's M1's A value
		parentNode -> C = parentNode -> M1 -> A;

		// local variables to hold the child pointers
		Node<T>* tempL = parentNode -> L -> L;
		Node<T>* tempM1 = parentNode -> L -> M1;
		Node<T>* tempM2 = parentNode -> M1 -> L;
		Node<T>* tempR = parentNode -> M1 -> M1;


		// need to reassign child pointers
		// special case when we are fusing children with no children of their own
		if (!(parentNode -> L -> L) && !(parentNode -> L -> M1) && !(parentNode -> M1 -> L) && !(parentNode -> M1 -> M1))
		{
			parentNode -> L = NULL;
			parentNode -> M1 = NULL;
			parentNode -> M2 = NULL;
			parentNode -> R = NULL;
		}
		else
		{
			parentNode -> L = tempL;
			parentNode -> M1 = tempM1;
			parentNode -> M2 = tempM2;
			parentNode -> R = tempR;

			parentNode -> L -> L = NULL;
			parentNode -> L -> M1 = NULL;
			parentNode -> M1 -> L = NULL;
			parentNode -> M1 -> M1 = NULL;
		}

		// the currentNode will now be the parentNode since we put everthing in the parent
		currentNode = parentNode;
	}
	// two values
	else if ((parentNode -> A) && (parentNode -> B) && !(parentNode -> C))
	{
		// move the parentNode's M2's A value over to its C spot
		parentNode -> M2 -> C = parentNode -> M2 -> A;

		// move the parentNode's B value into its M2's B spot
		parentNode -> M2 -> B = parentNode -> B;

		// move the parentNode's M1's A value into its M2's A spot
		parentNode -> M2 -> A = parentNode -> M1 -> A;

		// set the parentNode's B value to null since we moved it
		parentNode -> B = NULL;

		// reassign child pointers
		parentNode -> M1 = parentNode -> M2;
		parentNode -> M2 = NULL;
	}
	// three values
	else if ((parentNode -> A) && (parentNode -> B) && (parentNode -> C))
	{
		// move the parentNode's M2's A value over to its C spot
		parentNode -> M2 -> C = parentNode -> M2 -> A;

		// move the parentNode's B value into its M2's B spot
		parentNode -> M2 -> B = parentNode -> B;

		// move the parentNode's M1's A value into its M2's A spot
		parentNode -> M2 -> A = parentNode -> M1 -> A;

		// fix the parentNode
		parentNode -> B = parentNode -> C;
		parentNode -> C = NULL;

		// reassign child pointers
		parentNode -> M1 = parentNode -> M2;
		parentNode -> M2 = parentNode -> R;
		parentNode -> R = NULL;
	}
}

template <class T>
void TwoThreeFourTree<T>::borrowFromParentR (Node<T>*& currentNode, Node<T>*& parentNode, T* removeType)
{
	if ((parentNode -> A) && (parentNode -> B) && (parentNode -> C))
	{
		// move the parentNode's R's A value over to its C spot
		parentNode -> R -> C = parentNode -> R -> A;

		// move the parentNode's C value into its R's B spot
		parentNode -> R -> B = parentNode -> C;

		// move the parentNode's M2's A value into its R's A spot
		parentNode -> R -> A  = parentNode -> M2 -> A;

		// set the parentNode's C value to null since we moved it
		parentNode -> C = NULL;

		// reassign child pointers
		parentNode -> M2 = parentNode -> R;
		parentNode -> R = NULL;
	}
}

template <class T>
bool TwoThreeFourTree<T>::add (Node<T> *&pTree, T* newType)
{
	// check if the root is empty
	if (!(pRoot))
	{
		// put the new student in the A value
		pRoot = new Node<T> (newType);

		return true;
	}

	// check if the tree already contains the value
	// first have to check if the nodes exist
	if (pTree -> A)
	{
		if (*(pTree -> A) == *newType) return false;
	}
	if (pTree -> B)
	{
		if (*(pTree -> B) == *newType) return false;
	}
	if (pTree -> C)
	{
		if (*(pTree -> C) == *newType) return false;
	}

	// make a Node pointer to the root
	Node<T> *pNode = pRoot;

	// check if the node is full
	if (pNode -> A && pNode -> B && pNode -> C)
	{
		splitRoot (pNode);
		add (newType);
	}
	// check if the node is a leaf node
	else if (!(pNode -> L || pNode -> M1 || pNode -> M2 || pNode -> R))
	{
		// if the leaf node has only one value and 
		// the newID is less than the node's A ID
		if ((*newType < *(pNode -> A)) && (pNode -> B == NULL) && (pNode -> C == NULL))
		{
			// make a temporary Student that holds the A spot's values
			T *tempA = pNode -> A;

			// move the temporary A Student into the B spot
			pNode -> B = tempA;

			// put the new Student in the A spot
			pNode -> A = newType;

			return true;
		}
		// the newID is greater than the node's A ID
		else if ((*(newType) > *(pNode -> A)) && (pNode -> B == NULL) && (pNode -> C == NULL))
		{
			// put the new Student in the B spot
			pNode -> B = newType;

			return true;
		}
		// if the leaf node has two values and the newID is less than both values
		else if ((*(newType) < *(pNode -> A)) && (*(newType) < *(pNode -> B)) && (pNode -> C == NULL))
		{
			// make a temporary Student that holds the B spot's values
			T *tempB = pNode -> B;

			// move the B value to the C spot
			pNode -> C = tempB;

			// move the A value to the B spot
			pNode -> B = pNode -> A;

			// put the new Student in the A spot
			pNode -> A = newType;
		}
		// if the leaf node has two values and the newID is greater than
		// the A value but less than the B value
		else if ((*(newType) > *(pNode -> A)) && (*(newType) < *(pNode -> B)) && (pNode -> C == NULL))
		{
			// make a temporary Student that holds the B spot's values
			T *tempB = pNode -> B;

			// move the tempB Student to the C spot
			pNode -> C = tempB;

			// put the new Student in the B spot
			pNode -> B = newType;
		}
		// otherwise it's greater than both values so it goes into the C spot
		else
		{
			// put the new Student in the C spot
			pNode -> C = newType;
		}
	}
	// check if the node is an internal node
	else if ((pNode -> L && pNode -> M1) ||
			 (pNode -> L && pNode -> M1 && pNode -> M2) ||
			 (pNode -> L && pNode -> M1 && pNode -> M2 && pNode -> R))
	{
		// need to save a pointer to the parent
		Node<T>* parentNode = pNode;

		pNode = branch (pNode, newType);
		addAfterBranch (pNode, parentNode, newType);
	}
}

template <class T>
bool TwoThreeFourTree<T>::addAfterBranch (Node<T> *&pTree, Node<T> *&parentNode, T* newType)
{
	// check if the tree already contains the value
	// first have to check if the nodes exist
	if (pTree -> A)
	{
		if (*(pTree -> A) == *newType) return false;
	}
	if (pTree -> B)
	{
		if (*(pTree -> B) == *newType) return false;
	}
	if (pTree -> C)
	{
		if (*(pTree -> C) == *newType) return false;
	}

	// check if the node is full
	if (pTree -> A && pTree -> B && pTree -> C)
	{
		splitLeaf (pTree, parentNode);
		addAfterSplit (parentNode, newType);
	}
	// check if the node is a leaf node
	else if (!(pTree -> L || pTree -> M1 || pTree -> M2 || pTree -> R))
	{
		// if the leaf node has only one value and 
		// the newID is less than the node's A ID
		if ((*newType < *(pTree -> A)) && (pTree -> B == NULL) && (pTree -> C == NULL))
		{
			// make a temporary Student that holds the A spot's values
			T *tempA = pTree -> A;

			// move the temporary A Student into the B spot
			pTree -> B = tempA;

			// put the new Student in the A spot
			pTree -> A = newType;

			return true;
		}
		// the newID is greater than the node's A ID
		else if ((*newType > *(pTree -> A)) && (pTree -> B == NULL) && (pTree -> C == NULL))
		{
			// put the new Student in the B spot
			pTree -> B = newType;

			return true;
		}
		// if the leaf node has two values and the newID is less than both values
		else if ((*newType < *(pTree -> A)) && (*newType < *(pTree -> B)) && (pTree -> C == NULL))
		{
			// make a temporary Student that holds the B spot's values
			T *tempB = pTree -> B;

			// move the B value to the C spot
			pTree -> C = tempB;

			// move the A value to the B spot
			pTree -> B = pTree -> A;

			// put the new Student in the A spot
			pTree -> A = newType;
		}
		// if the leaf node has two values and the newID is greater than
		// the A value but less than the B value
		else if ((*newType > *(pTree -> A)) && (*newType < *(pTree -> B)) && (pTree -> C == NULL))
		{
			// make a temporary Student that holds the B spot's values
			T *tempB = pTree -> B;

			// move the tempB Student to the C spot
			pTree -> C = tempB;

			// put the new Student in the B spot
			pTree -> B = newType;
		}
		// otherwise it's greater than both values so it goes into the C spot
		else
		{
			// put the new Student in the C spot
			pTree -> C = newType;
		}
	}
	// check if the node is an internal node
	else if ((pTree -> L && pTree -> M1) ||
			 (pTree -> L && pTree -> M1 && pTree -> M2) ||
			 (pTree -> L && pTree -> M1 && pTree -> M2 && pTree -> R))
	{
		// need to save a pointer to the parent
		Node<T>* parentNode = pTree;

		pTree = branch (pTree, newType);
		addAfterBranch (pTree, parentNode, newType);
	}
}

template <class T>
bool TwoThreeFourTree<T>::addAfterSplit (Node<T> *&pTree, T* newType)
{
	// check if the tree already contains the value
	// first have to check if the nodes exist
	if (pTree -> A)
	{
		if (*(pTree -> A) == *newType) return false;
	}
	if (pTree -> B)
	{
		if (*(pTree -> B) == *newType) return false;
	}
	if (pTree -> C)
	{
		if (*(pTree -> C) == *newType) return false;
	}

	// check if the node is a leaf node
	if (!(pTree -> L || pTree -> M1 || pTree -> M2 || pTree -> R))
	{
		// if the leaf node has only one value and 
		// the newID is less than the node's A ID
		if ((*newType < *(pTree -> A)) && (pTree -> B == NULL) && (pTree -> C == NULL))
		{
			// make a temporary Student that holds the A spot's values
			T *tempA = pTree -> A;

			// move the temporary A Student into the B spot
			pTree -> B = tempA;

			// put the new Student in the A spot
			pTree -> A = newType;

			return true;
		}
		// the newID is greater than the node's A ID
		else if ((*newType > *(pTree -> A)) && (pTree -> B == NULL) && (pTree -> C == NULL))
		{
			// put the new Student in the B spot
			pTree -> B = newType;

			return true;
		}
		// if the leaf node has two values and the newID is less than both values
		else if ((*newType < *(pTree -> A)) && (*newType < *(pTree -> B)) && (pTree -> C == NULL))
		{
			// make a temporary Student that holds the B spot's values
			T *tempB = pTree -> B;

			// move the B value to the C spot
			pTree -> C = tempB;

			// move the A value to the B spot
			pTree -> B = pTree -> A;

			// put the new Student in the A spot
			pTree -> A = newType;
		}
		// if the leaf node has two values and the newID is greater than
		// the A value but less than the B value
		else if ((*newType > *(pTree -> A)) && (*newType < *(pTree -> B)) && (pTree -> C == NULL))
		{
			// make a temporary Student that holds the B spot's values
			T *tempB = pTree -> B;

			// move the tempB Student to the C spot
			pTree -> C = tempB;

			// put the new Student in the B spot
			pTree -> B = newType;
		}
		// otherwise it's greater than both values so it goes into the C spot
		else
		{
			// put the new Student in the C spot
			pTree -> C = newType;
		}
	}
	// check if the node is an internal node
	else if ((pTree -> L && pTree -> M1) ||
			 (pTree -> L && pTree -> M1 && pTree -> M2) ||
			 (pTree -> L && pTree -> M1 && pTree -> M2 && pTree -> R))
	{
		// need to save a pointer to the parent
		Node<T>* parentNode = pTree;

		pTree = branch (pTree, newType);
		addAfterBranch (pTree, parentNode, newType);
	}
}

template<class T>
void TwoThreeFourTree<T>::remove (Node<T> *&currentNode, Node<T> *&parentNode, T* removeType, int &size)
{
	// base case
	if (currentNode == NULL)
	{
		return;
	}

	// first count the number of values in the currentNode
	size = countValuesInCurrentNode (currentNode);

	// check if the node that contains the value that 
	// we want to delete is not the root and its size is one
	if (!((*currentNode) == (*pRoot)) && (size == 1))
	{
		// have to fuse here
		fuse (currentNode, parentNode, removeType, size);
	}

	// check if the node contains the value
	// the node does not contain the value
	if (!(containsValue (currentNode, removeType)))
	{
		// check if the node is a leaf node
		if (isLeaf (currentNode))
		{
			// the value was not found so return
			return;
		}
		// the node is an internal node
		else
		{
			// save a pointer to the parent node before we branch
			Node<T>* saveParent = currentNode;

			// branch and recursively call remove
			Node<T>* branchedNode = branch (currentNode, removeType);
			remove (branchedNode, saveParent, removeType, size);
		}
	}
	// the node contains the value
	else if (containsValue (currentNode, removeType))
	{
		// check if the node is a leaf node
		if (isLeaf (currentNode))
		{
			// update size of currentNode
			size = countValuesInCurrentNode (currentNode);

			// remove the value

			// if the node that contains the removeType has 1 value
			// case: node with only 1 value
			if (size == 1)
			{
				// make sure the removeType is in the A spot
				if (*(currentNode -> A) == *removeType)
				{
					// just remove the A spot
					currentNode -> A = NULL;

					// update the size
					size = 0;

					return;
				}
			}
			// if the node that contains the removeType has 2 values
			else if (size == 2)
			{
				// check if the removeType is in the A spot
				if (*(currentNode -> A) == *removeType)
				{
					// move the B value into the A spot
					currentNode -> A = currentNode -> B;

					// delete the B spot since we moved it to the A spot
					currentNode -> B = NULL;

					// update the size
					size = 1;

					return;
				}
				// check if the removeType is in the B spot
				else if (*(currentNode -> B) == *removeType)
				{
					// just remove it and we're done
					currentNode -> B = NULL;

					// update the size
					size = 1;

					return;
				}
			}
			// if the node that contains the removeType has 3 values
			else if (size == 3)
			{
				// check if the removeType is in the A spot
				if (*(currentNode -> A) == *removeType)
				{
					// move the B value into the A spot
					currentNode -> A = currentNode -> B;

					// move the C value into the B spot
					currentNode -> B = currentNode -> C;

					// delete the value in the C spot since it's unoccupied
					currentNode -> C = NULL;

					// update the size
					size = 2;

					return;
				}
				// check if the removeType is in the B spot
				else if (*(currentNode -> B) == *removeType)
				{
					// move the C value into the B spot
					currentNode -> B = currentNode -> C;

					// delete the C value since it's unoccupied
					currentNode -> C = NULL;

					// update the size
					size = 2;

					return;
				}
				// check if the removeType is in the C spot
				else if (*(currentNode -> C) == *removeType)
				{
					// just delete the value in the C spot and we're done
					currentNode -> C = NULL;

					// update the size
					size = 2;

					return;
				}
			}
		}
		// otherwise we're in an internal node
		else
		{
			// find the minimum value of the right subtree and
			// store it in a temporary variable
			T* tempRemove = minOfRightSubtree (currentNode, removeType);

			// recursively call the remove function on that value
			remove (tempRemove, size);

			// replace the value we want to delete with the tempRemove
			replace (currentNode, removeType, tempRemove);

			return;
		}
	}
}

#endif