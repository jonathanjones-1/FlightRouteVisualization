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


void Graph::Graph()
{
	//use this default constructor to make the graph object, taking in the csv files we discussed on discord and reading all of the airports and their IATA codes, sifting through it all.
	//I'll be working on this more on 8/2/23, not today but just writing in some key details that I don't want to forget, especially concerning this portion of the work. 
}

