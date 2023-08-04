#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <ios>
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
/*
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
*/

void printWelcome()
{
	cout << endl;
	cout << "             Welcome to Flight Route Planner!" << endl;
	cout << "    Here, you'll find the shortest route guaranteed using" << endl;
	cout << " Dijkstra's algorithm to find routes based on shortest distance" << endl;
	cout << " and a Breadth First search algorithm to find the route with" << endl;
	cout << "             the fewest intermediate airports." << endl;
	cout << endl << "Please select an option to begin!" << endl;
}

void printMenu()
{
	cout << endl << setw(20) << "Options:" << endl;
	cout << setw(32) << setfill('=') << "" << setfill(' ') << endl;
	cout << "1. View a list of airports" << setw(6) << "+" << endl;
	cout << "2. Determine flight distances" << setw(3) << "+" << endl;
	cout << "3. View predetermined routes" << setw(4) << "+" << endl;
	cout << "4. Exit" << setw(25) << "+" << endl;
	cout << setw(32) << setfill('=') << "" << setfill(' ') << endl;
	cout << setw(19) << "Choice: ";
}

int main()
{
	Graph airports;

	printWelcome();
	printMenu();

	int option;
	cin >> option;

	while (option != 4)
	{
		if (option == 1)
			airports.printKeys();

		else if (option == 2)
		{
			string line, source, destination;
			cout << "Enter IATA codes for a source and destination airport: ";
			
			// Discards the input buffer
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin, line);
			istringstream in(line);

			in >> source;
			in >> destination;

			cout << endl << "BFS shortest path uses " << airports.BFS(source, destination) << " intermediate airports." << endl;
		}

		else
			cout << "Invalid input!" << endl;

			//testSamplePairs(testGraph); 

			//Do not run the testSamplePairs without a sample text file. 

			/*
			string test1 = "LAX";
			string test2 = "JFK";

			timeBFS(testGraph, test1, test2);

			timeDijkstra(testGraph, test1, test2);
			*/
		printMenu();
		cin >> option;
	}

    return 0;
}