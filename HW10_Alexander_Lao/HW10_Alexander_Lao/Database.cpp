#include "Database.h"

// default constructor
Database::Database ()
{
	// does nothing
}

// copy constructor
Database::Database (Database &copy)
{
	// shallow copy
	for (int i = 0; i < masterDatabase.size (); i++)
	{
		this -> masterDatabase[i] = copy.masterDatabase[i];
	}
}

// destructor
Database::~Database ()
{
	// does nothing
}

void Database::add (Client* newClient)
{
	// first check if the client already exists
	bool found = find (newClient);

	if (found)
	{
		cout << "client already exists" << endl;
	}
	else
	{
		// get the hashCode for the newClient
		unsigned int hashCode = getHashCode (newClient -> name);

		// modulus the hashCode by the map size to get the index
		int index = hashCode % masterDatabase.max_size ();

		// check if the index in the hash table is occupied
		// not occupied
		if (masterDatabase[index] == NULL)
		{
			masterDatabase[index] = newClient;
			cout << "client " << newClient -> name << " added" << endl;
		}
		else
		{
			// keep a pointer to the currentClient
			Client* currentClient = masterDatabase[index];

			// loop to the end of the clients at that index
			while (currentClient -> pNext)
			{
				currentClient = currentClient -> pNext;
			}

			// put the new client at the end
			currentClient -> pNext = newClient;
			cout << "client " << newClient -> name << " added" << endl;
		}
	}
}

unsigned int Database::getHashCode (const string &hashString)
{
	int hashCode = 0;

	// loop through the entire string
	for (int i = 0; i < hashString.length (); i++)
	{
		// add each character's ascii value in the string together
		hashCode += hashString[i];
	}

	return hashCode;
}

bool Database::find (Client* searchClient)
{
	// local variable for the truth value
	bool found = false;

	// get the hash code for the searchClient
	unsigned int hashCode = getHashCode (searchClient -> name);

	// get the index by modding the hashCode by the map size
	int index = hashCode % masterDatabase.max_size ();

	// local variable to hold the currentClient
	Client* currentClient = masterDatabase[index];

	// loop through each client at that index
	while (currentClient)
	{
		// if we found the searchClient
		if (*currentClient == *searchClient)
		{
			found = true;
			break;
		}
		// otherwise go to the next client
		else 
		{
			currentClient = currentClient -> pNext;
		}
	}
	
	return found;
}

void Database::clientMakesPurchase (Client* searchClient)
{
	// first check if the client exists
	bool found = find (searchClient);

	if (!found)
	{
		cout << "client not found" << endl;
	}
	else
	{
		// get the hashCode for the searchClient
		unsigned int hashCode = getHashCode (searchClient -> name);

		// modulus the hashCode by the map size to get the index
		int index = hashCode % masterDatabase.max_size ();

		// local variable to hold the currentClient
		Client* currentClient = masterDatabase[index];

		// loop through each client at that index
		while (currentClient)
		{
			// if we found the searchClient
			if (*currentClient == *searchClient)
			{
				// increase that client's purchases by 1
				currentClient -> purchases++;

				cout << "client " << currentClient -> name << " has made " 
					 << currentClient -> purchases << " purchases" << endl;

				break;
			}
			// otherwise go to the next client
			else 
			{
				currentClient = currentClient -> pNext;
			}
		}
	}
}

void Database::remove (Client* removeClient)
{
	// first check if the client exists
	bool found = find (removeClient);

	if (!found)
	{
		cout << "client not found" << endl;
	}
	else
	{
		// get the hashCode for the removeClient
		unsigned int hashCode = getHashCode (removeClient -> name);

		// modulus the hashCode by the map size to get the index
		int index = hashCode % masterDatabase.max_size ();

		// local variable to hold the currentClient and previousClient
		Client* currentClient = masterDatabase[index];
		Client* previousClient = NULL;

		// loop through each client at that index
		while (currentClient)
		{
			// if we found the removeClient
			if (*currentClient == *removeClient)
			{
				// keep a pointer to the currentClient's pNext
				Client* tempClient = currentClient -> pNext;

				cout << "client " << currentClient -> name << " was removed" << endl;

				delete currentClient;

				// special case when we're removing the
				// front of the linked list
				if (previousClient == NULL)
				{
					masterDatabase[index] = tempClient;
				}
				else
				{
					// fix the pointers
					previousClient -> pNext = tempClient;
				}

				break;
			}
			// otherwise go to the next client
			else 
			{
				// keep a pointer to the previous client
				previousClient = currentClient;

				// go to the next client in the list
				currentClient = currentClient -> pNext;
			}
		}
	}
}

void Database::getAddress (Client* searchClient)
{
	// first check if the client exists
	bool found = find (searchClient);

	if (!found)
	{
		cout << "client not found" << endl;
	}
	else
	{
		// get the hashCode for the searchClient
		unsigned int hashCode = getHashCode (searchClient -> name);

		// modulus the hashCode by the map size to get the index
		int index = hashCode % masterDatabase.max_size ();

		// local variable to hold the currentClient
		Client* currentClient = masterDatabase[index];

		// loop through each client at that index
		while (currentClient)
		{
			// if we found the searchClient
			if (*currentClient == *searchClient)
			{
				// print out the address
				cout << currentClient -> address << endl;

				break;
			}
			// otherwise go to the next client
			else 
			{
				// go to the next client in the list
				currentClient = currentClient -> pNext;
			}
		}
	}
}