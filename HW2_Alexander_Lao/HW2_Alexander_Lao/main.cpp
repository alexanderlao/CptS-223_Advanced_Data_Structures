#include "MyString.h"
#include <string>

using std::cout;
using std::string;

int main (void)
{
	// creating a MyString object for the user
	MyString userString;

	std::vector<MyString> outputVector;
	int badCharTable[256];
	
	cout << "Alexander Lao, 11481444\n";

	while (true)
	{
		// create a local string to read in user inputs
		string line;
		getline (std::cin, line);

		string parenthesisDelimiter = ")";
		string commaDelimiter = ",";

		// call the appropriate method based on the user's input
		if (0 == line.compare (0, 4, "set("))
		{
			// parsing the string based on the delimiter
			string token = line.substr (4, line.find (parenthesisDelimiter) - 4);

			// converting the string to a char*
			char* convertedToChar = new char[token.size() + 1];
			memcpy(convertedToChar, token.c_str(), token.size() + 1);

			// set the user string based on the new converted char*
			userString.set (convertedToChar);
		}
		else if (0 == line.compare (0, 7, "substr("))
		{
			// extracting the user defined index based on the string's index
			// because we know it will always be at a certain index no matter the length
			int userIndex = stoi (line.substr (7));

			// parse the string based on the comma to
			// extract the userLength
			string token = line.substr (line.find (commaDelimiter) + 1, line.length ());

			// convert the string to an int
			int userLength = stoi (token.substr (0));

			// make a new MyString object based on the substring
			MyString subString = userString.substr(userIndex, userLength);

			// print out the substring
			subString.write (cout);
			cout << "\n";
		}
		else if (0 == line.compare (0, 8, "indexof("))
		{
			// parsing the string based on the delimiter
			string token = line.substr (8, line.find (commaDelimiter) - 8);

			// converting the string to a char*
			char* convertedToChar = new char[token.size() + 1];
			memcpy(convertedToChar, token.c_str(), token.size() + 1);

			// parse the string based on the comma and closing parenthesis to
			// extract the startIndex
			string secondToken = line.substr (line.find (commaDelimiter) + 1, line.length ());

			// convert the string to an int
			int userStartIndex = stoi (secondToken.substr (0));

			int indexOf = userString.indexof (convertedToChar, userStartIndex);

			cout << indexOf << "\n";
		}
		else if (0 == line.compare (0, 14, "bad_char_table"))
		{
			userString.bad_char_table (badCharTable);

			// loop through each index of the bad char table
			// and print put its contents
			for (int i = 0; i < 256; i++)
			{
				cout << badCharTable[i] << ",";
			}

			cout << "\n";
		}
		else if (0 == line.compare (0, 6, "split("))
		{
			// parse the line to extract the needed parameter
			string token = line.substr (6, line.find (parenthesisDelimiter) - 6);

			// convert the string to a char
			char convertedToChar = token.at (0);

			// copy the userString into a new MyString object
			// so we don't change the original userString
			MyString subString = userString;

			// call split function
			subString.split (convertedToChar, outputVector);
			
			// print out the contents of the vector
			for (int i = 0; i < outputVector.size (); i++)
			{
				outputVector[i].write (cout);
				cout << ",";
			}
			
			// wipe the vector clean so we don't append to it
			outputVector.clear ();

			cout << "\n";
		}
		else if (0 == line.compare (0, 9, "anagrams("))
		{
			// parse the line to extract the needed parameters
			string token = line.substr (9, line.find (parenthesisDelimiter) - 9);

			// converting the string to a char*
			char* convertedToChar = new char[token.size() + 1];
			memcpy(convertedToChar, token.c_str(), token.size() + 1);

			// make a new MyString object with the newly converted char*
			MyString *needToParse = new MyString (convertedToChar);

			// declare a local vector that will hold the candidates
			std::vector<MyString> candidates;

			// split the MyString object we just instantiated based on a comma, 
			// and store them in the local vector
			needToParse -> split (',', candidates);

			userString.anagrams (candidates, outputVector);

			// print out the contents of the vector
			for (int i = 0; i < outputVector.size (); i++)
			{
				outputVector[i].write (cout);
				cout << ",";
			}
			
			// wipe the vector clean so we don't append to it
			outputVector.clear ();

			cout << "\n";
		}
		else if (0 == line.compare (0, 17, "suffix_of_length("))
		{
			// extracting the user defined length based on the string's index
			// because we know it will always be at a certain index no matter the length
			int userLength = stoi (line.substr (17));

			// make a new MyString object based on the substring
			MyString suffixString = userString.suffix_of_length (userLength);

			suffixString.write (cout);

			cout << "\n";
		}
		else if (0 == line.compare (0, 12, "starts_with("))
		{
			// parsing the string based on the delimiter
			string token = line.substr (12, line.find (parenthesisDelimiter) - 12);

			// converting the string to a char*
			char* convertedToChar = new char[token.size() + 1];
			memcpy(convertedToChar, token.c_str(), token.size() + 1);

			bool boolean = userString.starts_with (convertedToChar);

			string truthValue;

			// converting the boolean value to a string
			if (boolean == 1)
			{
				truthValue = "true";
			}
			else
			{
				truthValue = "false";
			}

			cout << truthValue << "\n";
		}
		else if (0 == line.compare (0, 7, "reverse"))
		{
			// create a local char vector to hold the string
			std::vector<char> outputVector;

			userString.reverse (outputVector);

			// print out the contents of the vector
			for (int i = 0; i < outputVector.size (); i++)
			{
				cout << outputVector[i];
			}
			
			// wipe the vector clean so we don't append to it
			outputVector.clear ();

			cout << "\n";
		}
		else if (0 == line.compare (0, 10, "is_integer"))
		{
			bool boolean = userString.is_integer ();

			string truthValue;

			// converting the boolean value to a string
			if (boolean == 1)
			{
				truthValue = "true";
			}
			else
			{
				truthValue = "false";
			}

			cout << truthValue << "\n";
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