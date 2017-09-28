#include "Database.h"

int main (void)
{
	cout << "Alexander Lao, 11481444\n";

	// create a local Database object for the user
	Database userDatabase;

	while (true)
	{
		// create a local string to read in user inputs
		string line;
		getline (std::cin, line);

		// call the appropriate method based on the user's input
		if (0 == line.compare (0, 11, "add_client("))
		{
			// parsing the string based on the open parenthesis delimiter 
			// and the comma to extract the userName
			string userName = line.substr (11, line.find (",") - line.find ("(") - 1);

			// parsing the string based on the comma 
			// and the end parenthesis to extract the userAddress
			string userAddress = line.substr (line.find (",") + 1, line.find (")") - line.find (",") - 1);

			// make a client object with the userName and userAddress
			Client *newClient = new Client (userName, userAddress);

			userDatabase.add (newClient);
		}
		else if (0 == line.compare (0, 22, "client_makes_purchase("))
		{
			// parsing the string based on the open parenthesis delimiter 
			// and the comma to extract the userName
			string userName = line.substr (22, line.find (")") - line.find ("(") - 1);

			// make a client object with the userName
			Client *newClient = new Client (userName, "");

			userDatabase.clientMakesPurchase (newClient);
		}
		else if (0 == line.compare (0, 14, "remove_client("))
		{
			// parsing the string based on the open parenthesis delimiter 
			// and the comma to extract the userName
			string userName = line.substr (14, line.find (")") - line.find ("(") - 1);

			// make a client object with the userName
			Client *newClient = new Client (userName, "");

			userDatabase.remove (newClient);
		}
		else if (0 == line.compare (0, 19, "get_client_address("))
		{
			// parsing the string based on the open parenthesis delimiter 
			// and the comma to extract the userName
			string userName = line.substr (19, line.find (")") - line.find ("(") - 1);

			// make a client object with the userName
			Client *newClient = new Client (userName, "");

			userDatabase.getAddress (newClient);
		}
		else if (0 == line.compare (0, 4, "quit"))
		{
			break;
		}
	}

	cout << "Done\n";

	return 0;
}