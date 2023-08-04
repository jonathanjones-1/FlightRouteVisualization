#include <SFML/Graphics.hpp>
#include <chrono>
#include "Graph.h"

using namespace std; 
using namespace chrono; 

void timeBFS(const Graph& testGraph, string source, string destination)
{
			auto start = high_resolution_clock::now(); 

			int iataCodeCount = testGraph.BFS(test1, test2); 
		
			auto stop = high_resolution_clock::now(); 

			// Using chrono to time the algorithms, feel free to change       
    // milliseconds here to nanoseconds if needed. 

			auto duration = duration_cast <milliseconds>(stop - start); 

    cout << "Breadth-first search executed in " << duration.count() << " milliseconds!" << endl;
			cout << "Breadth-first search's path included " << iataCodeCount << " pairs!" << endl;  
}

void timeDijkstra(const Graph& testGraph, string source, string destination)
{
			auto start = high_resolution_clock::now();
			
			iataCodeCount = testGraph.Dijkstra(test1, test2); 
	
			auto stop = high_resolution_clock::now(); 

			auto duration = duration_cast<milliseconds>(stop - start);

			cout << "Dijkstra's Algorithm executed in " << duration.count() << " milliseconds!" << endl; 
			cout << "Dijkstra's Algorithm's path included " << iataCodeCount << " pairs!" << endl; 
}


int main()
{

    Graph testGraph;
    testGraph.printGraph();

			string test1 = "LAX"; 
			string test2 = "JFK";

			timeBFS(testGraph, test1, test2); 

			timeDijkstra(testGraph, test1, test2); 
			
    return 0;
}