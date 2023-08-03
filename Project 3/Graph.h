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
	unordered_map<string, vector<Airport>> adjList;
public:
	Graph();
	void printKeys();
	void printGraph();
	/*
	double haversineCalc(double lat1, lat2, lat3, lat4);

	void dijkstraAlg(); //left it as void as I will figure out what to   	return late
	*/
};
