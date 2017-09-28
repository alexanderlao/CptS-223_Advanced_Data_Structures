#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::ostream;

// foward declaration
template <class T>
class TwoThreeFourTree;

struct Student
{
	// parameterized constructor
	Student (string newName, int newID)
	{
		this -> name = newName;
		this -> ID = newID;
	}

	// fields of the struct
	string name;
	int ID;

	void display ()
	{
		cout << name << "," << ID << ";";
	}

	// overloaded comparator operators for Student types
	bool operator< (const Student &rhs) const
	{
		return this -> ID < rhs.ID;
	}

	bool operator> (const Student &rhs) const
	{
		return this -> ID > rhs.ID;
	}

	bool operator<= (const Student &rhs) const
	{
		return this -> ID <= rhs.ID;
	}

	bool operator>= (const Student &rhs) const
	{
		return this -> ID >= rhs.ID;
	}
	bool operator== (const Student &rhs) const
	{
		return this -> ID == rhs.ID;
	}
	bool operator!= (const Student& rhs) const
	{
		return this -> ID != rhs.ID;
	}
	friend ostream & operator<< (ostream &output, const Student &rhs)
	{
		cout << rhs.name << "," << rhs.ID << ";";
		return output;
	}
};

template <class T>
class Node
{
	friend class TwoThreeFourTree<T>;

	public:
		Node ();
		Node (const T* aValue);
		Node (Node<T> &copy);
		bool operator== (const Node& rhs) const;
		bool operator!= (const Node& rhs) const;

	private:
		T* A, *B, *C;
		Node<T>* L, *M1, *M2, *R;
};

template <class T>
Node<T>::Node ()
{
	A = B = C = NULL;
	L = M1 = M2 = R = NULL;
}

// parameterized constructor
template <class T>
Node<T>::Node (const T* aValue)
{
	A = new T (*aValue);
	B = C = NULL;
	L = M1 = M2 = R = NULL;
}

// copy constructor
template <class T>
Node<T>::Node (Node<T> &copy)
{
	this -> A = copy.A;
	this -> B = copy.B;
	this -> C = copy.C;
	this -> L = copy.L;
	this -> M1 = copy.M1;
	this -> M2 = copy.M2;
	this -> R = copy.R;
}

template <class T>
bool Node<T>::operator== (const Node& rhs) const
{
	return ((this -> A == rhs.A) && (this -> B == rhs.B) && (this -> C == rhs.C));
}

template <class T>
bool Node<T>::operator!= (const Node& rhs) const
{
	return ((this -> A != rhs.A) && (this -> B != rhs.B) && (this -> C != rhs.C));
}

#endif