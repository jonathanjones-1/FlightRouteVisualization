#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "Airport.h"
using namespace std;

class Graph
{
	private:
		// Adjacency list representation
		unordered_map<Airport, unordered_set<Airport, Airport::Hash>Airport::Hash> adjList;
	public:
		Graph (); 
}



