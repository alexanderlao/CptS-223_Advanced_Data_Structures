#include "Graph.h"

int main (void)
{
	cout << "Alexander Lao, 11481444\n";

	// create a local Graph object for the user
	Graph userGraph;

	while (true)
	{
		// create a local string to read in user inputs
		string line;
		getline (std::cin, line);

		// call the appropriate method based on the user's input
		if (0 == line.compare (0, 4, "set("))
		{
			// parsing the string based on the open parenthesis delimiter 
			// and close parenthesis delimiter to extract the line between the parenthesis
			string extractLine = line.substr (4, line.find (")") - line.find ("(") - 1);

			userGraph.set (extractLine);
		}
		else if (0 == line.compare (0, 7, "degree("))
		{
			// parsing the string based on the open parenthesis delimiter 
			// and close parenthesis delimiter to extract the line between the parenthesis
			string token = line.substr (7, line.find (")") - line.find ("(") - 1);

			MyString *userNodeName = userGraph.convertToMyString (token);

			userGraph.degree (userNodeName);
		}
		else if (0 == line.compare (0, 21, "shortest_path_length("))
		{
			// parsing the string based on the open parenthesis delimiter 
			// and the comma to extract the userStart name
			string userStart = line.substr (21, line.find (",") - line.find ("(") - 1);

			// parsing the string based on the comma 
			// and the end parenthesis to extract the userEnd name
			string userEnd = line.substr (line.find (",") + 1, line.find (")") - line.find (",") - 1);

			//convert the strings to MyStrings
			MyString *myStringStart = userGraph.convertToMyString (userStart);
			MyString *myStringEnd = userGraph.convertToMyString (userEnd);

			double length = userGraph.shortestPathLength (myStringStart, myStringEnd);

			// if the length is infinity there is no path
			if (length == std::numeric_limits<double>::infinity ())
			{
				cout << "no path" << endl;
			}
			else
			{
				// print out the length
				cout << length << endl;
			}
		}
		else if (0 == line.compare (0, 14, "shortest_path("))
		{
			// parsing the string based on the open parenthesis delimiter 
			// and the comma to extract the userStart name
			string userStart = line.substr (14, line.find (",") - line.find ("(") - 1);

			// parsing the string based on the comma 
			// and the end parenthesis to extract the userEnd name
			string userEnd = line.substr (line.find (",") + 1, line.find (")") - line.find (",") - 1);

			//convert the strings to MyStrings
			MyString *myStringStart = userGraph.convertToMyString (userStart);
			MyString *myStringEnd = userGraph.convertToMyString (userEnd);

			userGraph.shortestPath (myStringStart, myStringEnd);
		}
		else if (0 == line.compare (0, 4, "quit"))
		{
			break;
		}
	}

	cout << "Done\n";

	return 0;
}