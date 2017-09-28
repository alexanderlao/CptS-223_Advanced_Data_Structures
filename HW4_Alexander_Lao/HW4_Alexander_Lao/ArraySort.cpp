#include "ArraySort.h"

// default constructor
ArraySort::ArraySort ()
{
	// constructor will not need to dynamically allocate memory
	// for an item vector
}

// copy constructor
ArraySort::ArraySort (ArraySort &copy)
{
	this -> itemVector = copy.itemVector;
}

// destructor
ArraySort::~ArraySort ()
{
	// the destructor will not need to free any dynamically allocated memory
}

// this function will accept a string as an argument
// (ex. "23,5;32,5;12,24"), split it, and pass it
// into a MyString vector (vector will hold {23,5}, {32,5},
// {12,24})
std::vector<MyString> ArraySort::parse (string line, char delimiter, int index)
{
	// parse the line to extract the needed parameters
	string token = line.substr (index, line.find (')') - index);

	// converting the string to a char*
	char* convertedToChar = new char[token.size() + 1];
	memcpy(convertedToChar, token.c_str(), token.size() + 1);

	// make a new MyString object with the newly converted char*
	MyString *needToParse = new MyString (convertedToChar);

	// declare a local vector that will hold the candidates
	std::vector<MyString> candidates;

	// split the MyString object we just instantiated based on a comma, 
	// and store them in the local vector
	needToParse -> split (delimiter, candidates);

	return candidates;
}

// this function will convert a MyString vector to an int vector
std::vector<int> ArraySort::myStringToInt (std::vector<MyString> convertThis)
{
	std::vector<int> intVector;

	// loop through the MyString vector
	for (int i = 0; i < convertThis.size (); i++)
	{
		// convert the char* data type in the MyString vector to an int
		// and push the converted int into the int vector
		intVector.push_back (atoi (convertThis[i].getString ()));
	}

	return intVector;
}

std::vector<Item> ArraySort::duplicate ()
{
	// declare a local Item vector that will copy the orginal vector's content
	std::vector<Item> copyVector;

	// loop through the original vector
	for (int i = 0; i < itemVector.size (); i++)
	{
		// and push the originalVector's items into the copyVector
		copyVector.push_back (itemVector[i]);
	}

	return copyVector;
}

void ArraySort::printVector (std::ostream& stream, std::vector<Item> printThis) const
{
	// loop through the Item vector and print out its contents
	for (int i = 0; i < printThis.size (); i++)
	{
		stream << printThis[i].value << "," << printThis[i].index << ";";
	}

	stream << "\n";
}

// this function will accept a MyString vector in the form {23,5}, {32,5},
// {12,24}, split it, convert the char* to ints, and pass it into an Item type vector
void ArraySort::set (std::vector<MyString>& input)
{
	// create a local MyString vector to hold values
	std::vector<MyString> separatedIntValues;

	// local variables for converting char* to int
	int extractedValue;
	int extractedIndex;
	Item itemToPush;

	// loop through the MyString vector and split it based on a comma
	// {23,5} will become 23 and 5 and each number will be stored into 
	// a MyString object
	for (int i = 0; i < input.size (); i++)
	{
		input[i].split (',', separatedIntValues);
	}

	// clear the itemVector before we add new Items to it
	// so we don't retain old values every time we call the set function
	itemVector.clear ();

	// loop through the MyString vector and convert each char* into an int
	// i += 2 will differentiate between groups of values and indices
	for (int i = 0; i < separatedIntValues.size (); i += 2)
	{
		// converting the char* to an int
		extractedValue = atoi (separatedIntValues[i].getString ());
		extractedIndex = atoi (separatedIntValues[i + 1].getString ());

		// taking our converted ints and putting them into our local struct
		itemToPush.value = extractedValue;
		itemToPush.index = extractedIndex;

		// push the struct into the vector
		itemVector.push_back (itemToPush);
	}
}

void ArraySort::swap (Item &a, Item &b)
{
	// set a temporary Item variable to hold a
	Item temp = a;

	// set a's value as b's value
	a = b;

	// set b's value as a's value
	b = temp;
}

void ArraySort::insertionSort (std::vector<Item>& sortThisVector, int size)
{
	// loop through the Item vector
	// start at i = 1 because we assume everything before index 1 is sorted
	for (int i = 1; i < size; i++)
	{
		// compare adjacent items in the vector
		for (int j = i; j > 0 && sortThisVector[j - 1].value > sortThisVector[j].value; j--)
		{
			// swap if an item on the left is greater than the item to the right
			swap (sortThisVector[j], sortThisVector[j - 1]);
		}
	}
}

void ArraySort::shellSort (std::vector<Item>& sortThisVector, std::vector<int> gaps)
{
	// loop through each gap value in the gap vector
	for (int k = 0; k < gaps.size (); k++)
	{
		// loop through the the "subvector" determined by the gap value
		for (int i = gaps[k]; i < sortThisVector.size (); i++)
		{
			// compare values of the "subvector"
			for (int j = i; j >= gaps[k] && sortThisVector[j - gaps[k]].value > sortThisVector[j].value; j -= gaps[k])
			{
				// swap if an item on the left is greater than the item to the right
				swap (sortThisVector[j], sortThisVector[j - gaps[k]]);
			}
		}
	}
}

std::vector<Item> ArraySort::mergeSort (std::vector<Item> sortThisVector)
{
	// base case: subvector only has one element
	if (sortThisVector.size () == 1)
	{
		return sortThisVector;
	}
	else
	{
		// declare local variables to hold the first and second
		// halves of the vector
		std::vector<Item> firstHalf;
		std::vector<Item> secondHalf;
		std::vector<Item> output;

		// push items from the first half of the vector
		// into the firstHalf vector
		for (int i = 0; i < sortThisVector.size () / 2; i++)
		{
			firstHalf.push_back (sortThisVector[i]);
		}

		// push items from the second half of the vector
		// into the secondHalf vector
		for (int i = (sortThisVector.size () / 2); i < sortThisVector.size (); i++)
		{
			secondHalf.push_back (sortThisVector[i]);
		}

		// call the recursive function for the halves
		firstHalf = mergeSort (firstHalf);
		secondHalf = mergeSort (secondHalf);

		// mergeSorted will sort the firstHalf and secondHalf and store it in output
		output = mergeSorted (firstHalf, secondHalf, output);

		return output;
	}
}

std::vector<Item> ArraySort::mergeSorted (std::vector<Item> firstHalf, std::vector<Item> secondHalf,
									      std::vector<Item> output)
{
	// declare local looping variables
	// i for items for the firstHalf
	// j for items for the secondHalf
	// k for items for the output
	int i = 0, j = 0, k = 0;

	// k will only increment when we add something to the output vector
	// keep looping until we add everything from the firstHalf and secondHalf
	while (k < (firstHalf.size () + secondHalf.size ()))
	{
		// if we pushed all of the secondHalf items
		if (j >= secondHalf.size ())
		{
			// push the firstHalf items
			output.push_back (firstHalf[i++]);
			k++;
		}
		// if we pushed all the firstHalf items
		else if (i >= firstHalf.size ())
		{
			// push the secondHalf items
			output.push_back (secondHalf[j++]);
			k++;
		}
		// comparing items from the firstHalf and secondHalf...
		// if the item at index i of the firstHalf is less than the secondHalf
		else if (firstHalf[i] <= secondHalf[j])
		{
			// push the item from the firstHalf into the output
			// and increment i
			output.push_back (firstHalf[i++]);
			k++;
		}
		else
		{
			// otherwise the item from the secondHalf is lower
			// so push that into the output and increment j
			output.push_back (secondHalf[j++]);
			k++;
		}
	}

	return output;
}

int ArraySort::partition (std::vector<Item>& sortThisVector, int pivot, int left, int right)
{
	// need to set a right bound for the pivot
	// right will be the last index of our subvector
	int newPivot = right;

	// need access to the element before the pivot
	int newRight = right - 1;

	// swap the pivot with the last element in the vector
	swap (sortThisVector[pivot], sortThisVector[newPivot]);

	// moving inwards in the vector
	while (left <= newRight)
	{
		// iterators cannot move any further
		if (sortThisVector[left] > sortThisVector[newPivot] &&
			sortThisVector[newRight] <= sortThisVector[newPivot])
		{
			// swap the indices that cannot move
			swap (sortThisVector[left], sortThisVector[newRight]);
		}

		// once the left and right iterator are at the same index...
		// need this before the left increment and before the right decrement
		// because there is a case where the left will increment when they're equal
		// and it'll never go in
		if (left == newRight)
		{
			// if the pivot is less than the value at the matching index
			if (sortThisVector[newPivot] < sortThisVector[left])
			{
				// move the pivot to that position and we're done
				swap (sortThisVector[left], sortThisVector[newPivot]);
				newPivot = left;
				break;
			}
			// if the pivot is greater than the value at the matching index
			else if (sortThisVector[newPivot] > sortThisVector[left])
			{
				// move the pivot to the next index to preserve order and we're done
				swap (sortThisVector[left + 1], sortThisVector[newPivot]);
				newPivot = left + 1;
				break;
			}
		}
		
		// if the item on the left is less that or equal to the pivot
		if (sortThisVector[left] <= sortThisVector[newPivot])
		{
			left++;
		}

		// once the left and right iterator are at the same index...
		// need this after the left increment and before the right decrement
		// because there is a case where the left will increment and the right
		// will decrement and they're never equal
		if (left == newRight)
		{
			// if the pivot is less than the value at the matching index
			if (sortThisVector[newPivot] < sortThisVector[left])
			{
				// move the pivot to that position and we're done
				swap (sortThisVector[left], sortThisVector[newPivot]);
				newPivot = left;
				break;
			}
			// if the pivot is greater than the value at the matching index
			else if (sortThisVector[newPivot] > sortThisVector[left])
			{
				// move the pivot to the next index to preserve order and we're done
				swap (sortThisVector[left + 1], sortThisVector[newPivot]);
				newPivot = left + 1;
				break;
			}
		}

		// if the item on the right is greater than the pivot
		if (sortThisVector[newRight] > sortThisVector[newPivot])
		{
			newRight--;
		}

		// once the left and right iterator are at the same index...
		// need this after the left increment and after the right decrement
		// because there is a case where the right will decrement and they're never equal
		if (left == newRight)
		{
			// if the pivot is less than the value at the matching index
			if (sortThisVector[newPivot] < sortThisVector[left])
			{
				// move the pivot to that position and we're done
				swap (sortThisVector[left], sortThisVector[newPivot]);
				newPivot = left;
				break;
			}
			// if the pivot is greater than the value at the matching index
			else if (sortThisVector[newPivot] > sortThisVector[left])
			{
				// move the pivot to the next index to preserve order and we're done
				swap (sortThisVector[left + 1], sortThisVector[newPivot]);
				newPivot = left + 1;
				break;
			}
		}
	}

	return newPivot;
}

void ArraySort::quickSort (std::vector<Item>& sortThisVector, int left, int right, int size)
{
	// base case
	if (size <= 1)
	{
		return;
	}
	// if there's only two items in the vector, we don't need to
	// find a median. we just need to swap accordingly
	else if (size == 2)
	{
		if (sortThisVector[left] > sortThisVector[right])
		{
			swap (sortThisVector[left], sortThisVector[right]);
		}

		return;
	}
	else
	{
		// local variables for determining the median of three values
		int beginning = left;
		int middle = (left + right) / 2;
		int end = right;
		int median;

		// chceking if index 0 is the median
		if ((sortThisVector[beginning] >= sortThisVector[middle] &&
			 sortThisVector[beginning] <= sortThisVector[end]) ||
			(sortThisVector[beginning] >= sortThisVector[end] &&
			 sortThisVector[beginning] <= sortThisVector[middle]))
		{
			median = beginning;
		}
		// checking if the middle index is the median
		else if ((sortThisVector[middle] >= sortThisVector[beginning] &&
				  sortThisVector[middle] <= sortThisVector[end]) ||
		   		 (sortThisVector[middle] >= sortThisVector[end] &&
				  sortThisVector[middle] <= sortThisVector[beginning]))
		{
			median = middle;
		}
		// if the first and middle index are not the median
		// then the last index is the median
		else
		{
			median = end;
		}

		// partition call for the median as the pivot
		// return the pivot's final index to determine subvectors
		int pivot = partition (sortThisVector, median, left, right);

		// re-adjust the size for the left subvector
		size = pivot - left;
		quickSort (sortThisVector, left, pivot - 1, size);

		// re-adjust the size for the right subvector
		size = right - pivot;
		quickSort (sortThisVector, pivot + 1, right, size);
	}
}