#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>
#include "Graph.h"

using namespace std; 
using namespace chrono; 

void timeBFS(Graph& testGraph, string source, string destination)
{
	auto start = high_resolution_clock::now(); 

	int iataCodeCount = testGraph.BFS(source, destination); 
		
	auto stop = high_resolution_clock::now(); 

	// Using chrono to time the algorithms, feel free to change       
    // milliseconds here to nanoseconds if needed. 

	auto duration = duration_cast <milliseconds>(stop - start); 

    cout << "Breadth-first search executed in " << duration.count() << " milliseconds!" << endl;
	cout << "Breadth-first search's path included " << iataCodeCount << " pairs!" << endl;  
}

void timeDijkstra(Graph& testGraph, string source, string destination)
{
	auto start = high_resolution_clock::now();
			
	int iataCodeCount = testGraph.Dijkstra(source, destination); 
	
	auto stop = high_resolution_clock::now(); 

	auto duration = duration_cast<milliseconds>(stop - start);

	cout << "Dijkstra's Algorithm executed in " << duration.count() << " milliseconds!" << endl; 
	cout << "Dijkstra's Algorithm's path included " << iataCodeCount << " pairs!" << endl; 
}

void testSamplePairs(const Graph& graph)
{
		//This is assuming the sample file we created follows a simple format
		//like this: JFK, LAX   (and so on, each line containing a pair of IATA
		//codes 		

		ifstream sampleInput(PUT FILE NAME HERE); 

		string line; 

		while(getline(sampleInput, line)
		{
				istringstream temp(line);
				string sourceAirport, destinationAirport; 
	
				getline(temp, sourceAirport, ',');
				getline(temp, destination, ','); 

				timeBFS(graph, sourceAirport, destinationAirport); 
				timeDijkstra(graph, sourceAirport, destinationAirport); 

		}
}


int main()
{

    Graph testGraph;
    testGraph.printKeys();


	//testSamplePairs(testGraph); 

	//Do not run the testSamplePairs without a sample text file. 

	/*
	string test1 = "LAX"; 
	string test2 = "JFK";

	timeBFS(testGraph, test1, test2); 

	timeDijkstra(testGraph, test1, test2); 
	*/

    return 0;
}