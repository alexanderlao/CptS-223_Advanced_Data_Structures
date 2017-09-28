#ifndef ARRAY_SORT_H
#define ARRAY_SORT_H

#include "MyString.h"

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::string;

struct Item
{
	int value;
	int index;

	// overloaded comparator operators for Item types
	bool operator< (const Item& rhs) const
	{
		return this -> value < rhs.value;
	}

	bool operator> (const Item& rhs) const
	{
		return this -> value > rhs.value;
	}

	bool operator<= (const Item& rhs) const
	{
		return this -> value <= rhs.value;
	}

	bool operator>= (const Item& rhs) const
	{
		return this -> value >= rhs.value;
	}
};

class ArraySort
{
	public:
		ArraySort ();
		ArraySort (ArraySort &copy);
		~ArraySort ();

		std::vector<MyString> parse (string line, char delimiter, int index);
		std::vector<int> myStringToInt (std::vector<MyString> convertThis);
		std::vector<Item> duplicate ();
		void printVector (std::ostream& stream, std::vector<Item> printThis) const;
		void set (std::vector<MyString>& input);
		void swap (Item &a, Item &b);
		void insertionSort (std::vector<Item>& sortThisVector, int size);
		void shellSort (std::vector<Item>& sortThisVector, std::vector<int> gaps);
		std::vector<Item> mergeSort (std::vector<Item> sortThisVector);
		std::vector<Item> mergeSorted (std::vector<Item> firstHalf, std::vector<Item> secondHalf,
									   std::vector<Item> output);
		int partition (std::vector<Item>& sortThisVector, int pivot, int left, int right);
		void quickSort (std::vector<Item>& sortThisVector, int left, int right, int size);

	private:
		std::vector<Item> itemVector;
};

#endif