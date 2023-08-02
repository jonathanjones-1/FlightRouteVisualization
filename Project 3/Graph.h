#pragma once
#include <string>
#include <vector>
#include <map>
#include "Airport.h"
using namespace std;

class Graph
{
	private:
		// Adjacency list representation
		map<Airport, vector<Airport>> adjList;
	public:

		Graph (); 
};



