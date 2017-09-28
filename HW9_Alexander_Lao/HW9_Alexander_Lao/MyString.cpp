#include "MyString.h"

// default constructor
MyString::MyString ()
{
	this -> mString = '\0';
}

// parameterized constructor
MyString::MyString (char* newString)
{
	this -> mString = newString;
}

// copy constructor
MyString::MyString (const MyString &copy)
{
	// perform a deep copy
	int length = strlen (copy.mString);
	mString = new char[length + 1]; // + 1 for the null character
	strcpy (mString, copy.mString);
}

// destructor
MyString::~MyString ()
{
	// the destructor will not need to free any dynamically allocated memory
}

// overloaded assignment operator
MyString & MyString::operator= (const MyString &rhs)
{
	// checking for self-assignment
	if (this != &rhs)
	{
		this -> mString = rhs.mString;
	}

	return *this;
}

// getter
char* MyString::getString () const
{
	return this -> mString;
}

void MyString::set (char* stringValue)
{
	// set the mString data member to the passed in stringValue
	this -> mString = stringValue;
}

MyString MyString::substr (int startIndex, int length) const
{
	// create a local char* that will hold the substring
	char* subChar = new char[length + 1]; // + 1 for the null character

	// check if the length goes beyond the length of the string
	if (length > strlen (mString))
	{
		// shorten the length so it only goes to the
		// last character of the string
		length = strlen (mString) - startIndex;
	}

	// create a local looping variable
	int j = 0;

	for (int i = 0; i < length; i++)
	{
		subChar[j++] = mString[startIndex + i];
	}

	// set the last character in the subChar char* as the null character
	subChar[j] = '\0';

	// dynamically allocate a MyString object using the subChar char*
	// that has the wanted substring
	MyString *subString = new MyString (subChar);

	return *subString;
}

int MyString::indexof (char* substr, int startIndex)
{
	// create a local looping variable
	// and counter
	int i = 0;
	int foundCount = 0;

	// loop until the end of the string
	while (mString[startIndex] != '\0') 
	{
		// if the first character in the substring matches the
		// starting index of the string
		if (substr[i] == mString[startIndex])
		{
			// go to the next character in the substring and string
			// and increment the counter
			i++;
			startIndex++;
			foundCount++;

			// if we found the substring within the string
			if (foundCount == strlen (substr))
			{
				// break out of the loop otherwise
				// it will keep going and reset the counter
				break;
			}
		}
		// if the characters in the substring and string don't match
		else
		{
			// go to the next character in the string ...
			startIndex++;

			// ... but reset back to the beginning of the substring
			i = 0;
			foundCount = 0;
		}
	}

	// if we found the substring return 1
	if (foundCount == strlen (substr))
	{
		// subtract i to get the starting index
		return startIndex - i;
	}
	// if we didn't return 0
	else
	{
		return -1;
	}
}

int* MyString::bad_char_table (int* badCharTable)
{
	// loop through the badCharTable and initialize
	// every index to -1
	for (int i = 0; i < 256; i++)
	{
		badCharTable[i] = -1;
	}

	// loop through each index of the string
	for (int j = 0; j <= strlen (mString); j++)
	{
		// nested loop to loop through each index of the array
		for (int k = 0; k < 256; k++)
		{
			// check for the character at each index of the char array
			if (mString[j] == k)
			{
				// if they match, set the matched index
				// to its corresponding spot in the bad char table
				badCharTable[k] = j;
			}
		}
	}

	return badCharTable;
}

void MyString::split (char c, std::vector<MyString>& outputVector) const
{
	bool check = false;

	// initial checks for the delimeter appearing
	// at the beginning or last index of the string
	if (c == mString[strlen (mString) - 1])
	{
		check = true;
	}
	// if it's at the end, push the null character first
	else if (c == mString[0])
	{
		// make a new MyString object with the null character
		MyString *subString = new MyString ((char*)"");

		// push the newly made MyString object into the vector
		outputVector.push_back (*subString);
	}

	// strtok will extract a char* based on the input string and delimiting char
	char* extracted = strtok (mString, &c);

	while (extracted != NULL)
	{
		// make a new MyString object with the extracted char*
		MyString *subString = new MyString (extracted);

		// push the newly made MyString object into the vector
		outputVector.push_back (*subString);

		// extract the next char* from the string
		extracted = strtok (NULL, &c);
	}

	// want to push the null character last if the delimiter
	// is at the end of the string
	if (check)
	{
		// make a new MyString object with the null character
		MyString *subString = new MyString ((char*)"");

		// push the newly made MyString object into the vector
		outputVector.push_back (*subString);
	}
}

int MyString::anagrams (std::vector<MyString>& candidates, std::vector<MyString>& output)
{
	// loop through each element in the candidates vector
	for (int i = 0; i < candidates.size (); i++)
	{
		// strspn will scan the first parameter and search for matching characters
		// from the second parameter. it will then return an int for the length
		// of matching characters from the first parameter. this if-statement will 
		// check backwards and forwards to see if the number of matching characters
		// in the candidates matches the length of the string
		if ((strlen (mString) == strspn (mString, candidates[i].mString)) &&
			(strlen (mString) == strspn (candidates[i].mString, mString)))
		{
			// if they match both ways, it's an anagram so push it into the vector
			output.push_back (candidates[i]);
		}
	}

	return output.size ();
}

MyString MyString::suffix_of_length (int length)
{
	// make a local MyString object that holds the mString
	MyString *newString = new MyString (mString);

	// if the length is less than 0
	if (length <= 0)
	{
		// overwrite the MyString's mString to the null character
		newString -> mString = ((char*)"");
	}
	// if the length is greater than the length of the string
	else if (length > strlen (mString))
	{
		// do nothing, it already holds the wanted mString value
	}
	else
	{
		// extract the wanted suffix using the substr function
		*newString = newString -> substr ((strlen (mString) - length), length);
	}

	return *newString;
}

bool MyString::starts_with (char* testString)
{
	// create a local MyString object that holds
	// the user-inputted mString data
	MyString *baseString = new MyString (mString);

	// "trim" the string using the substr function so we only
	// have the relevant parts to compare
	*baseString = baseString -> substr (0, strlen (testString));

	// strcmp will check to see if the two strings are equal
	// returns 0 if they are equal
	if ((strcmp ((baseString -> mString), testString)) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void MyString::reverse (std::vector<char>& output)
{
	// push each char into the vector starting at the end
	for (int i = strlen (mString); i > 0 ; i--)
	{
		// subtract 1 to skip the null character
		output.push_back (mString[i - 1]);
	}

	// loop through the output vector and update
	// mString as the reversed string
	for (int i = 0; i < strlen (mString); i++)
	{
		mString[i] = output[i];
	}
}

bool MyString::is_integer ()
{
	int i;

	// initial check: if the first character is not a negative sign
	// or a number, return false and we're done
	if (!(mString[0] == '-' || isdigit(mString[0])))
	{
		return false;
	}
	else
	{
		// if the first character in the string is a negative sign
		// we'll start looping at index 1
		if (mString[0] == '-')
		{
			i = 1;
		}
		else
		{
			// otherwise we'll loop from the beginning
			i = 0;
		}
		// loop through each character in the string
		for (i; i < strlen (mString); i++)
		{
			// anytime we find a character that is not a digit
			// return false and we're done
			if ((isdigit (mString[i]) == 0))
			{
				return false;
			}
		}
	}

	// if all tests pass...
	return true;
}

void MyString::write (std::ostream& stream) const
{
	// write out mString
	stream << mString;
}