#include "ArraySort.h"

int main (void)
{
	cout << "Alexander Lao, 11481444\n";

	// create a local ArraySort object for the user
	ArraySort sortBy;

	// create a MyString vector for reading in lines/parsing
	std::vector<MyString> myStringVector;

	while (true)
	{
		// create a local string to read in user inputs
		string line;
		getline (std::cin, line);

		// call the appropriate method based on the user's input
		if (0 == line.compare (0, 4, "set("))
		{
			// parse the read-in line and store it in the MyString vector
			// MyString vector will have {(int,int), (int,int), (int,int)...}
			myStringVector = sortBy.parse (line, ';', 4);
			sortBy.set (myStringVector);
		}
		else if (0 == line.compare (0, 9, "insertion"))
		{
			// create a local Item vector that will hold a copy of the original Item vector's content
			std::vector<Item> duplicateItemVector = sortBy.duplicate ();

			// sort the duplicatedVector by insertion sort
			sortBy.insertionSort (duplicateItemVector, duplicateItemVector.size ());

			// print out the content of the sorted duplicatedVector
			sortBy.printVector (cout, duplicateItemVector);
		}
		else if (0 == line.compare (0, 6, "shell("))
		{
			// parse the read-in line and store it in the MyString vector
			// MyString vector will have {int, int, int}
			myStringVector = sortBy.parse (line, ',', 6);
			std::vector<int> gaps = sortBy.myStringToInt (myStringVector);

			// create a local Item vector that will hold a copy of the original Item vector's content
			std::vector<Item> duplicateItemVector = sortBy.duplicate ();

			// sort the duplicatedVector by shell sort
			sortBy.shellSort (duplicateItemVector, gaps);

			// print out the content of the sorted duplicatedVector
			sortBy.printVector (cout, duplicateItemVector);
		}
		else if (0 == line.compare (0, 10, "merge_sort"))
		{
			// create a local Item vector that will hold a copy of the original Item vector's content
			std::vector<Item> duplicateItemVector = sortBy.duplicate ();

			// sort the duplicatedVector by merge sort
			duplicateItemVector = sortBy.mergeSort (duplicateItemVector);

			// print out the content of the sorted duplicatedVector
			sortBy.printVector (cout, duplicateItemVector);
		}
		else if (0 == line.compare (0, 10, "partition("))
		{
			// extracting the user defined pivot based on the string's index
			// because we know it will always be at a certain index no matter the length
			int userPivot = stoi (line.substr (10));

			// create a local Item vector that will hold a copy of the original Item vector's content
			std::vector<Item> duplicateItemVector = sortBy.duplicate ();

			// sort the duplicatedVector by partition
			sortBy.partition (duplicateItemVector, userPivot, 0, duplicateItemVector.size () - 1);

			// print out the content of the sorted duplicatedVector
			sortBy.printVector (cout, duplicateItemVector);
		}
		else if (0 == line.compare (0, 10, "quick_sort"))
		{
			// create a local Item vector that will hold a copy of the original Item vector's content
			std::vector<Item> duplicateItemVector = sortBy.duplicate ();

			// sort the duplicatedVector by quick sort
			sortBy.quickSort (duplicateItemVector, 0, duplicateItemVector.size() - 1, 
							  duplicateItemVector.size ());

			// print out the content of the sorted duplicatedVector
			sortBy.printVector (cout, duplicateItemVector);
		}
		else if (0 == line.compare (0, 4, "quit"))
		{
			break;
		}
		else
		{
			cout << "Please enter a valid command.\n";
		}
	}

	cout << "Done\n";

	return 0;
}