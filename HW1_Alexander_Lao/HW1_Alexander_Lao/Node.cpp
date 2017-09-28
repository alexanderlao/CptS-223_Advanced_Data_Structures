#include "Node.h"

// constructor
Node::Node (int newData)
{
	this -> mData = newData;
	this -> mpNext = NULL;
}

// copy constructor
Node::Node (Node &copy)
{
	this -> mData = copy.mData;
	this -> mpNext = copy.mpNext;
}

// destructor
Node::~Node ()
{
	// the destructor will not need to release any dynamic memory
}

// getters
int Node::getData ()
{
	return this -> mData;
}

Node * Node::getNextPtr ()
{
	return this-> mpNext;
}

// setters
void Node::setData (int newData)
{
	this -> mData = newData;
}

void Node::setNextPtr (Node * newNext)
{
	this -> mpNext = newNext;
}