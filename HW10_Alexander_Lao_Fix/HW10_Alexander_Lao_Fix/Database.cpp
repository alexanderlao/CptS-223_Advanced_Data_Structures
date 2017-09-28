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
	this -> masterDatabase = copy.masterDatabase;
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
		// add the new client
		masterDatabase.emplace (newClient -> name, newClient);

		// print out the newly added client's name
		cout << "client " << masterDatabase[newClient -> name] -> name << " added" << endl;
	}
}

bool Database::find (Client* searchClient)
{
	// use the count () function to check if the client exists
	// returns 1 if found, 0 if not found
	if (masterDatabase.count (searchClient -> name) == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
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
		// increase the searchClient's purchases
		masterDatabase[searchClient -> name] -> purchases++;

		// print out the searchClient's number of purchases
		cout << "client " << masterDatabase[searchClient -> name] -> name << " has made " 
			 << masterDatabase[searchClient -> name] -> purchases << " purchases" << endl;
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
		// print out the removeClient's name before we remove
		cout << "client " << masterDatabase[removeClient -> name] -> name << " was removed" << endl;

		// remove the removeClient
		masterDatabase.erase (removeClient -> name);
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
		// print out the address of the searchClient
		cout << masterDatabase[searchClient -> name] -> address << endl;
	}
}