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

void timeBFS(Graph& graph, string source, string destination)
{
	auto start = high_resolution_clock::now();
	int iataCodeCount = graph.BFS(source, destination);
	auto stop = high_resolution_clock::now(); 

	// Using chrono to time the algorithms, feel free to change       
    // milliseconds here to nanoseconds if needed. 

	auto duration = duration_cast <nanoseconds>(stop - start); 

    cout << endl << "Breadth-first search executed in " << duration.count() << " milliseconds!" << endl;
}

void timeDijkstra(Graph& graph, string source, string destination)
{
	auto start = high_resolution_clock::now();
	int iataCodeCount = graph.Dijkstra(source, destination);
	auto stop = high_resolution_clock::now(); 
	auto duration = duration_cast<nanoseconds>(stop - start);

	cout << "Dijkstra's Algorithm executed in " << duration.count() << " milliseconds!" << endl; 
	cout << "Dijkstra's shortest path is " << iataCodeCount << " kilometers." << endl;
}

void testSamplePairs(Graph& graph, string filename)
{
		// Assumes pairs are formatted correctly (e.g., LAX YMP)	
		ifstream inFile(filename);  

		if (inFile.is_open())
		{
			string line;
			while (getline(inFile, line))
			{
				istringstream in(line);
				string source, destination;

				in >> source;
				in >> destination;

				cout << endl << "Source: " << source << ", Destination: " << destination << endl;

				int num = graph.BFS(source, destination);

				if (num == -1)
					cout << endl << "Sorry, there is no path between the specified airports." << endl;
				else
				{
					timeBFS(graph, source, destination);
					cout << "BFS shortest path uses " << num << " intermediate airports." << endl;
					timeDijkstra(graph, source, destination);
				}
			}

			inFile.close();
		}
		else
			cout << endl << "Cannot open file." << endl;
}

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
	cout << setw(33) << setfill('=') << "" << setfill(' ') << endl;
	cout << "1. View a list of airports" << setw(7) << "+" << endl;
	cout << "2. Determine flight distances" << setw(4) << "+" << endl;
	cout << "3. View predetermined routes" << setw(5) << "+" << endl;
	cout << "4. View possible direct flights" << setw(2) << "+" << endl;
	cout << "5. Exit" << setw(26) << "+" << endl;
	cout << setw(33) << setfill('=') << "" << setfill(' ') << endl;
	cout << setw(19) << "Choice: ";
}

int main()
{
	Graph airports;
	string line;

	printWelcome();
	printMenu();

	int option;

	getline(cin, line);
	istringstream in(line);
	in >> option;

	while (option != 5)
	{
		if (option == 1)
			airports.printKeys();

		else if (option == 2)
		{
			string source, destination;
			cout << "Enter IATA codes for a source and destination airport: ";

			getline(cin, line);
			istringstream in(line);

			in >> source;
			in >> destination;

			int num = airports.BFS(source, destination);

			if (num == -1)
				cout << endl << "Sorry, there is no path between the specified airports." << endl;
			else
			{
				timeBFS(airports, source, destination);
				cout << "BFS shortest path uses " << num << " intermediate airports." << endl;
				timeDijkstra(airports, source, destination);
			}
		}

		else if (option == 3)
		{
			cout << "Enter the name of a file to read: ";

			getline(cin, line);
			testSamplePairs(airports, line);
		}

		else if (option == 4)
			airports.printGraph();

		else
			cout << "Invalid input!" << endl;

		printMenu();
		getline(cin, line);
		istringstream in(line);
		in >> option;
	}

    return 0;
}