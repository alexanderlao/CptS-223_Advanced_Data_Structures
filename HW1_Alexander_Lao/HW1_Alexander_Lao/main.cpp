#include "Node.h"
#include "ReversibleStack.h"

int main (void)
{
	// creating a ReversibleStack object for the user
	ReversibleStack userStack;
	
	cout << "Alexander Lao, 11481444\n";

	while (true)
	{
		// create a local string to read in user inputs
		string line;
		getline (std::cin, line);

		// call the appropriate method based on the user's input
		if (0 == line.compare (0, 4, "push"))
		{
			// converting the user's string version of the item
			// they want to push into an int
			int userInt = stoi (line.substr (5));

			userStack.push (userInt);
		}
		else if (0 == line.compare (0, 3, "pop"))
		{
			userStack.pop ();
		}
		else if (0 == line.compare (0, 7, "isempty"))
		{
			userStack.isEmpty ();
		}
		else if (0 == line.compare (0, 7, "display"))
		{
			userStack.display (cout);
		}
		else if (0 == line.compare (0, 7, "reverse"))
		{
			userStack.reverse ();
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