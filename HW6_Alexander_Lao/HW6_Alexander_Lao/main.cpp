#include "TwoThreeFourTree.h"

int main (void)
{
	cout << "Alexander Lao, 11481444\n";

	// create a TwoThreeFourTree for the user
	// of Student type
	TwoThreeFourTree<Student> userTree;
	
	while (true)
	{
		// create a local string to read in user inputs
		string line;
		getline (std::cin, line);

		string openParenthesisDelimiter = "(";
		string closeParenthesisDelimiter = ")";
		string commaDelimiter = ",";

		// call the appropriate method based on the user's input
		if (0 == line.compare (0, 4, "add("))
		{
			// parsing the string based on the open parenthesis delimiter 
			// and comma delimiter to find the userName
			string userName = line.substr (4, line.find (commaDelimiter) - 
										   line.find (openParenthesisDelimiter) - 1);

			// parse the string based on the comma delimiter and closing parenthesis
			// delimiter to extract the userID
			int userID = stoi (line.substr (line.find (commaDelimiter) + 1, 
				               line.find (closeParenthesisDelimiter) - line.find (commaDelimiter) - 1));

			Student* newStudent = new Student (userName, userID);

			// add the userName and userID to the tree
			userTree.add (newStudent);
		}
		else if (0 == line.compare (0, 13, "countLevels()"))
		{
			int levels = userTree.countLevels ();

			cout << levels << endl;
		}
		else if (0 == line.compare (0, 16, "displayInOrder()"))
		{
			userTree.displayInOrder (userTree.getRoot ());

			cout << endl;
		}
		else if (0 == line.compare (0, 8, "getName("))
		{
			// extracting the user defined ID based on the string's index
			// because we know it will always be at a certain index no matter the length
			int userSearchID = stoi (line.substr (8));

			// make a new student that has the search ID, the name does not matter
			Student* searchStudent = new Student ("", userSearchID);
				
			userTree.getName (userTree.getRoot (), searchStudent);

			// print out the student's name if found
			if ((searchStudent -> name) != "")
			{
				cout << searchStudent -> name << endl;
			}
			else if ((searchStudent -> name) == "")
			{
				cout << "(student not found)" << endl;
			}
		}
		else if (0 == line.compare (0, 9, "getLevel("))
		{
			// extracting the user defined ID based on the string's index
			// because we know it will always be at a certain index no matter the length
			int userSearchID = stoi (line.substr (9));

			// make a new student that has the search ID, the name does not matter
			Student* searchStudent = new Student ("", userSearchID);

			bool truth = false;
			
			userTree.getLevel (userTree.getRoot (), searchStudent, 0, truth);

			if (!(truth))
			{
				cout << "-1" << endl;
			}
		}
		else if (0 == line.compare (0, 18, "countValuesInNode("))
		{
			// extracting the user defined ID based on the string's index
			// because we know it will always be at a certain index no matter the length
			int userSearchID = stoi (line.substr (18));

			// make a new student that has the search ID, the name does not matter
			Student* searchStudent = new Student ("", userSearchID);

			// local variable for returning the size
			int size = -1;
			
			userTree.countValuesInNode (userTree.getRoot (), searchStudent, size);

			cout << size << endl;
		}
		else if (0 == line.compare (0, 7, "remove("))
		{
			// extracting the user defined ID based on the string's index
			// because we know it will always be at a certain index no matter the length
			int userSearchID = stoi (line.substr (7));

			// make a new student that has the search ID, the name does not matter
			Student* searchStudent = new Student ("", userSearchID);

			// local variable for returning the size
			int size = -1;

			userTree.remove (searchStudent, size);
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