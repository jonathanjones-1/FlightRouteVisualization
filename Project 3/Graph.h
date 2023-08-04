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
	map<string, vector<Airport>> adjList;

	// Helper functions
	double haversineCalc(double lat1, double long1, double lat2, double long2);
	int scanList(const string& iata);
	bool checkList(const string& iata, vector<string>& airplanes);

public:
	Graph();

	// Test functions
	void printKeys();
	void printGraph();

	// Traversals
	int BFS(string source, string destination);
	double Dijkstra(string source, string destination);
};
