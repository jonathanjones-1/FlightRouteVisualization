#define _USE_MATH_DEFINES
#define earthRadKm 6371.0

#include "Graph.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <cctype>
#include <math.h>
#include <set>
#include <queue>
using namespace std;

Graph::Graph()
{
    // First, read in the datasets
    ifstream airportFile("files/airports.csv");

    // Create an object for every airport with an IATA code
    if (airportFile.is_open())
    {
        string line;

        //Skip the beginning row
        getline(airportFile, line);

        while (getline(airportFile, line))
        {
            istringstream iss(line);
            string unimportant, latitude, longitude, iataCode;

            // Ignore the first 4 columns
            for (int i = 0; i < 3; i++)
            {
                getline(iss, unimportant, ',');
            }
            // Avoid airport names containing commas
            getline(iss, unimportant, '"');
            getline(iss, unimportant, '"');
            getline(iss, unimportant, ',');

            getline(iss, latitude, ',');
            getline(iss, longitude, ',');

            for (int i = 0; i < 7; i++)
            {
                getline(iss, unimportant, ',');
            }

            getline(iss, iataCode, ',');

            if (!iataCode.empty() && iataCode.size() >= 3)
            {
                    double lat = stod(latitude);
                    double lon = stod(longitude);
                    Airport airport(iataCode, lat, lon);
                    adjList[iataCode].push_back(airport);
            }
        }

        airportFile.close();
    }

    auto iter = adjList.begin();
    while (iter != adjList.end())
    {
        // Remove any airports that currently have an adjacency list > 1
        if (iter->second.size() > 1)
            iter = adjList.erase(iter);
        else if (!isupper(iter->first.at(0)))
            iter = adjList.erase(iter);
        else
            iter++;
    }

    cout << "So far, there are " << adjList.size() << " airports in the graph!" << endl;
    printGraph();

    ifstream routeFile("files/routes.csv");

    // If the source and destination airports are already present in the graph, update their adjacency lists
    if (routeFile.is_open())
    {
        string line;
        getline(routeFile, line);

        while (getline(routeFile, line))
        {
            istringstream iss(line);
            string unimportant, sourceAirportName, destinationAirportName;

            getline(iss, unimportant, ',');
            getline(iss, unimportant, ',');

            getline(iss, sourceAirportName, ',');
            getline(iss, unimportant, ',');
            getline(iss, destinationAirportName, ',');
            cout << sourceAirportName << " " << destinationAirportName << endl;
            if (adjList.find(sourceAirportName) != adjList.end() && adjList.find(destinationAirportName) != adjList.end())
            {
                Airport source = adjList.find(sourceAirportName)->second.at(0);
                Airport destination = adjList.find(destinationAirportName)->second.at(0);
                adjList[sourceAirportName].push_back(destination);
                adjList[destinationAirportName].push_back(source);
            }
        }

        routeFile.close();
    }
    /*
    // Remove any airports with 0 adjacent airports
    auto iter = adjList.begin();
    while (iter != adjList.end())
    {
        if (iter->second.size() == 1)
            iter = adjList.erase(iter);
        else
            ++iter;
    }
    */
    cout << "Now, there are " << adjList.size() << " airports in the graph!" << endl;
}

void Graph::printKeys()
{
    for (auto airport : adjList)
    {
        cout << airport.second.at(0).iata << " {" << airport.second.at(0).latitudeDeg << ", " << airport.second.at(0).longitudeDeg << "}" << endl;
    }
}

void Graph::printGraph()
{
    for (auto airport : adjList)
    {
        for (auto adjacent : airport.second)
        {
            cout << adjacent.iata << " ";
        }
        cout << endl;
    }
}

// Breadth first search to calculate the most direct path (fewest intermediate airports)
int Graph::BFS(string source, string destination)
{
    queue<string> adj;
    set<string> visited;
    int count = 1;
    int pLevelSize = 1;

    visited.insert(source);
    adj.push(source);

    while (!adj.empty())
    {
        int cLevelSize = 0;
        for (int i = 0; i < pLevelSize; i++)
        {
            for (int i = 1; i < adjList[adj.front()].size(); i++)
            {
                // Make sure this airport has not already been identified
                if (visited.count(adjList[adj.front()].at(i).iata) != 0)
                    continue;
                // Check if the path has been found
                else if (adjList[adj.front()].at(i).iata == destination)
                    // Returns the length of the shortest path
                    return ++count;
                else
                {
                    visited.insert(adjList[adj.front()].at(i).iata);
                    adj.push(adjList[adj.front()].at(i).iata);
                    cLevelSize++;
                }
            }
        }

        pLevelSize = cLevelSize;
        count++;
        adj.pop();
    }

    // No path exists between source and destination airport
    return -1;
}

double Graph::Dijkstra(string source, string destination)
{
    vector<string> p(adjList.size(), "-1");
    vector<double> d(adjList.size(), INT_MAX);
    
    vector<string> computed;
    set<string> uncomputed;

    // Initialize V - S by placing all vertices into it
    for (auto iter = adjList.begin(); iter != adjList.end(); iter++)
    {
        uncomputed.insert(iter->first);
    }
    // d[0] is the source airport
    d[0] = 0;
    computed.push_back(source);
    int iter = 0;

    while (!uncomputed.empty())
    {
        for (int i = 1; i < adjList[computed.at(iter)].size(); i++)
        {
            double distance = haversineCalc(adjList[computed.at(iter)].at(0).latitudeDeg, adjList[computed.at(iter)].at(0).longitudeDeg,
                adjList[computed.at(iter)].at(i).latitudeDeg, adjList[computed.at(iter)].at(i).longitudeDeg);

            // for (int j = 0; j < compu)
        }
    }
    return 0;
}

double Graph::haversineCalc(double lat1, double long1, double lat2, double long2)
{
		lat1 = (lat1 * M_PI / 180);
		
		long1 = (long1 * M_PI / 180);

		lat2 = (lat2 * M_PI / 180);

		long2 = (long2 * M_PI / 180);

		double a = sin((lat2 - lat1)/2); 
		
		double b = sin((long2 - long1)/2); 

		return earthRadKm * asin(sqrt(a * a + cos(lat1) * cos(lat2) * b * b)); 
}

/*

void Graph::dijkstraAlg()
{
Because we need to calculate the distance, I will be implementing the Haversine formula to calculate the distance between these airports.
Also, I made this method void and without input as I haven't figured out how to start this portion, feel free to change anything/start this!

}
*/
