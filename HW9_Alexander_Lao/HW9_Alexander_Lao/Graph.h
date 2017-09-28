#ifndef GRAPH_H
#define GRAPH_H

#include "MyString.h"

#include <iostream>
#include <vector>
#include <string>
#include <limits>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::numeric_limits;

struct Edge;

struct GraphNode
{
	// default constructor
	GraphNode ()
	{
		this -> cost = std::numeric_limits<double>::infinity ();
		this -> visted = false;
	}

	MyString name;
	vector<Edge*> edges;
	double cost;
	bool visted;
};

struct Edge
{
	// default constructor
	Edge ()
	{
	
	}

	double weight;
	MyString start;
	MyString destination;
};

class Graph
{
	public:
		Graph ();
		Graph (Graph &copy);
		~Graph ();

		void set (string parseThis);
		MyString* convertToMyString (string convertString);
		void degree (MyString* searchName);
		double shortestPathLength (MyString* startNode, MyString* endNode);
		int findIndexPointer (MyString* searchName);
		int findIndexValue (MyString searchName);
		double cost (GraphNode* checkNode);
		void setCost (GraphNode* checkNode, double newCost);
		GraphNode* findLowestCost ();
		void reset ();
		void shortestPath (MyString* startNode, MyString* endNode);

	private:
		vector<GraphNode*> masterNodes;
		vector<Edge*> masterEdges;
};

#endif