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
		unordered_map<Airport, unordered_set<Airport, Airport::Hash>Airport::Hash> adjList;
	public:
		Graph (); 
};



