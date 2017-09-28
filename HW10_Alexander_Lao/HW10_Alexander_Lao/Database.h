#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <string>
#include <unordered_map>

using std::string;
using std::cout;
using std::endl;

struct Client
{
	// default constructor
	Client ()
	{
		this -> name = "";
		this -> address = "";
		this -> purchases = 0;
		this -> pNext = NULL;
	}

	// parameterized constructor
	Client (string newName, string newAddress)
	{
		this -> name = newName;
		this -> address = newAddress;
		this -> purchases = 0;
		this -> pNext = NULL;
	}

	bool operator== (const Client& rhs) const
	{
		// we only care about the name
		return (this -> name == rhs.name);
	}

	string name;
	string address;
	int purchases;
	Client* pNext;
};

class Database
{
	public:
		Database ();
		Database (Database &copy);
		~Database ();

		void add (Client* newClient);
		unsigned int getHashCode (const string &s);
		bool find (Client* searchClient);
		void clientMakesPurchase (Client* searchClient);
		void remove (Client* removeClient);
		void getAddress (Client* searchClient);

	private:
		std::unordered_map<int, Client*> masterDatabase;
};

#endif