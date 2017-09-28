#include "MaxHeap.h"

#include <string>

using std::cout;
using std::string;

int main (void)
{
	cout << "Alexander Lao, 11481444\n";

	// create a MaxHeap for the user
	// of int type
	MaxHeap<int> userHeap;
	
	while (true)
	{
		// create a local string to read in user inputs
		string line;
		getline (std::cin, line);

		string openParenthesisDelimiter = "(";
		string closeParenthesisDelimiter = ")";
		string commaDelimiter = ",";

		// call the appropriate method based on the user's input
		if (0 == line.compare (0, 6, "reset("))
		{
			// extracting the user defined K value based on the string's index
			// because we know it will always be at a certain index no matter the length
			int userK = stoi (line.substr (6));

			userHeap.reset (userK);
		}
		else if (0 == line.compare (0, 4, "add("))
		{
			// extracting the user defined int based on the string's index
			// because we know it will always be at a certain index no matter the length
			int userInt = stoi (line.substr (4));

			userHeap.add (userInt);
		}
		else if (0 == line.compare (0, 8, "remove()"))
		{
			userHeap.remove ();
		}
		else if (0 == line.compare (0, 14, "displayArray()"))
		{
			userHeap.displayVector ();
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
