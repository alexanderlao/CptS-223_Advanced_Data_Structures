#include "Graph.h"

// default constructor
Graph::Graph ()
{
	// does nothing
	// vectors will initialize themselves
}

// copy constructor
Graph::Graph (Graph &copy)
{
	// shallow copy of pointers
	this -> masterNodes = copy.masterNodes;
	this -> masterEdges = copy.masterEdges;
}

// destructor
Graph::~Graph ()
{
	// does nothing
}

// this function takes in the whole line (node1,node2,node3,...|n1,n2,w1;n3,n4,w2)
// as an argument. all the parsing is done within the function
void Graph::set (string parseThis)
{
	// clear the masterNodes and masterEdges vectors
	masterNodes.clear ();
	masterEdges.clear ();

	// local string variable to hold the nodes
	string stringNodes = parseThis.substr (0, parseThis.find ("|"));

	// local string variable to hold the edges
	string stringEdges = parseThis.substr (parseThis.find ("|") + 1, parseThis.length () - parseThis.find ("|"));

	// convert the strings to MyString objects
	MyString* myStringNodes = convertToMyString (stringNodes);
	MyString* myStringEdges = convertToMyString (stringEdges);

	// local MyString vector to hold the nodes and edges
	vector<MyString> vectorNodes;
	vector<MyString> vectorEdges;

	// split the nodes based on the comma
	// vectors are passed-by-reference here
	myStringNodes -> split (',', vectorNodes);
	
	// split the edges based on the semi-colon
	// vectors are passed-by-reference here
	// vectorEdges will hold City,City,Distance here
	myStringEdges -> split (';', vectorEdges);

	// push the vectorNodes into the masterNodes
	for (int i = 0; i < vectorNodes.size (); i++)
	{
		GraphNode *newNode = new GraphNode ();
		newNode -> name = vectorNodes[i];

		masterNodes.push_back (newNode);
	}

	// local MyString vector to hold edge data
	vector<MyString> edgeData;

	// loop through the vectorEdges and split based on the comma
	for (int i = 0; i < vectorEdges.size (); i++)
	{
		// edgeData will hold {City}, {City}, {Distance}, {City}, {City}, {Distance}, ...
		vectorEdges[i].split (',', edgeData);
	}

	// loop through the edgeData vector and store the data into the masterEdge vector
	for (int i = 0; i < edgeData.size (); i += 3)
	{
		// need to add edges for node1 -> node2 as well as node2 -> node1
		Edge *newForwardEdge = new Edge ();
		Edge *newBackwardEdge = new Edge ();

		newForwardEdge -> start = edgeData[i];
		newForwardEdge -> destination = edgeData[i + 1];

		newBackwardEdge -> destination = edgeData[i];
		newBackwardEdge -> start = edgeData[i + 1];

		// convert from a MyString to double
		newForwardEdge -> weight = atof (edgeData[i + 2].getString ());
		newBackwardEdge -> weight = atof (edgeData[i + 2].getString ());

		masterEdges.push_back (newForwardEdge);
		masterEdges.push_back (newBackwardEdge);
	}

	// loop through the masterEdges vector and add the edges 
	// to the GraphNodes inside the masterNodes vector
	for (int i = 0; i < masterEdges.size (); i++)
	{
		// loop through the masterNodes vector
		for (int j = 0; j < masterNodes.size (); j++)
		{
			// compare strings to find relevant edges; 0 is returned if strings are equal
			if (0 == strcmp (masterEdges[i] -> start.getString (), masterNodes[j] -> name.getString ()))
			{
				masterNodes[j] -> edges.push_back (masterEdges[i]);
			}
			else if (0 == strcmp (masterEdges[i] -> destination.getString (), masterNodes[j] -> name.getString ()))
			{
				masterNodes[j] -> edges.push_back (masterEdges[i]);
			}
		}
	}
}

MyString* Graph::convertToMyString (string convertString)
{
	// converting the strings to a char*
	char* convertedToChar = new char[convertString.size() + 1];
	memcpy(convertedToChar, convertString.c_str(), convertString.size() + 1);

	// make a new MyString object with the newly converted char*
	MyString *needToParse = new MyString (convertedToChar);

	return needToParse;
}

void Graph::degree (MyString* searchName)
{
	// local variable to hold the total weight
	int totalWeight = 0;
	
	// local variable to check if we found the node
	bool found = false;

	// loop through the masterNodes and search for the search name
	for (int i = 0; i < masterNodes.size (); i++)
	{
		// if we found the searchName in the masterNodes vector
		if (0 == strcmp (masterNodes[i] -> name.getString (), searchName -> getString ()))
		{
			found = true;

			cout << masterNodes[i] -> edges.size () << endl;
		}
	}

	// print out -1 if the searchName wasn't found
	if (found == false)
	{
		cout << "-1" << endl;
	}
}

double Graph::shortestPathLength (MyString* startNode, MyString* endNode)
{
	// reset the costs and visited boolean in the masterNodes vector
	reset ();

	// we first need to find the relevant nodes in the masterNode's vector
	int startIndex = findIndexPointer (startNode);
	int endIndex = findIndexPointer (endNode);

	// set the startNode's cost to zero
	masterNodes[startIndex] -> cost = 0;

	// set a pointer to the starting node
	GraphNode* currentNode = masterNodes[startIndex];

	while (true)
	{
		// set a local variable to hold the temp cost
		double tempCost = 0;

		// loop through the currentNode's edges
		for (int i = 0; i < currentNode -> edges.size (); i++)
		{
			// set the temp cost to the cost of the currentNode and the weight of its edge
			tempCost = cost (currentNode) + currentNode -> edges[i] -> weight;

			// need to find the index of the edge's destination in the masterNodes vector
			int destinationIndex = findIndexValue (currentNode -> edges[i] -> destination);

			// if the tempCost is less than the cost of the destination node
			if (tempCost < cost (masterNodes[destinationIndex]))
			{
				// set the destination node's cost to the temp cost
				setCost (masterNodes[destinationIndex], tempCost);
			}
		}

		// mark the currentNode as visited after all edges were addressed
		currentNode -> visted = true;

		// update the currentNode to the next unvisted node with the lowest cost
		currentNode = findLowestCost ();

		// if the currentNode is the endNode, we have the shortest path
		if (currentNode == masterNodes[endIndex])
		{
			return cost (masterNodes[endIndex]);
		}
	}
}

// returns the index of the searchName in the masterNode vector
int Graph::findIndexPointer (MyString* searchName)
{
	// loop through the masterNodes and search for the search name
	for (int i = 0; i < masterNodes.size (); i++)
	{
		// if we found the searchName in the masterNodes vector
		if (0 == strcmp (masterNodes[i] -> name.getString (), searchName -> getString ()))
		{
			return i;
		}
	}
}

int Graph::findIndexValue (MyString searchName)
{
	// loop through the masterNodes and search for the search name
	for (int i = 0; i < masterNodes.size (); i++)
	{
		// if we found the searchName in the masterNodes vector
		if (0 == strcmp (masterNodes[i] -> name.getString (), searchName.getString ()))
		{
			return i;
		}
	}
}

double Graph::cost (GraphNode* checkNode)
{
	// return the cost
	return checkNode -> cost;
}

void Graph::setCost (GraphNode* checkNode, double newCost)
{
	// set a new cost for the node
	checkNode -> cost = newCost;
}

GraphNode* Graph::findLowestCost ()
{
	GraphNode* cheapestNode = NULL;

	// loop through the masterNodes and find the first unvisited node
	for (int i = 0; i < masterNodes.size (); i++)
	{
		if (masterNodes[i] -> visted == false)
		{
			cheapestNode = masterNodes[i];
			break;
		}
	}

	// loop through the masterNodes to find the node with the lowest cost
	for (int i = 0; i < masterNodes.size (); i++)
	{
		if ((masterNodes[i] -> visted == false) && (cheapestNode -> cost > masterNodes[i] -> cost))
		{
			cheapestNode = masterNodes[i];
		}
	}

	return cheapestNode;
}

void Graph::reset ()
{
	// loop through the masterNodes vector and reset costs to infinity
	// and visited booleans to false
	for (int i = 0; i < masterNodes.size (); i++)
	{
		masterNodes[i] -> cost = std::numeric_limits<double>::infinity ();
		masterNodes[i] -> visted = false;
	}
}

void Graph::shortestPath (MyString* startNode, MyString* endNode)
{
	// find the shortest path length between the startNode
	// and the endNode, store the value in pathLength
	double pathLength = shortestPathLength (startNode, endNode);

	// if the path length is infinity, there is no path
	if (pathLength == std::numeric_limits<double>::infinity ())
	{
		cout << "no path" << endl;
		return;
	}
	else
	{
		// we first need to find the relevant nodes in the masterNode's vector
		int startIndex = findIndexPointer (startNode);
		int endIndex = findIndexPointer (endNode);

		// make a vector of MyStrings to hold the path
		vector<MyString> path;
		
		// push the endIndex node because we know it's part of the path
		path.push_back (masterNodes[endIndex] -> name);

		// set a pointer to the ending node
		// we need to backtrack to determine the path
		GraphNode* currentNode = masterNodes[endIndex];

		while (true)
		{
			// loop through the currentNode's edges
			for (int i = 0; i < currentNode -> edges.size (); i++)
			{
				// need to find the index of the edge's destination in the masterNodes vector
				int destinationIndex = findIndexValue (currentNode -> edges[i] -> destination);

				// the currentNode's cost - weight of the edge = edge's destination cost
				// if this statement is true, this edge is part of the path
				if (currentNode -> cost - currentNode -> edges[i] -> weight == 
					masterNodes[destinationIndex] -> cost)
				{
					// push the destinationIndex node because we know it's part of the path
					path.push_back (masterNodes[destinationIndex] -> name);

					// update the currentNode to the destinationIndex
					currentNode = masterNodes[destinationIndex];

					// break the for loop if the currentNode is the startIndex
					if (currentNode == masterNodes[startIndex]) break;
				}
			}

			// break the while loop if the currentNode is the startIndex
			if (currentNode == masterNodes[startIndex]) break;
		}

		// print out the path vector backwards
		for (int i = path.size () - 1; i >= 0; i--)
		{
			cout << path[i].getString () << ",";
		}

		// end the line
		cout << endl;
	}
}