#define _USE_MATH_DEFINES
#define earthRadKm 6371.0

#include "Graph.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <cctype>
#include <math.h>
#include <algorithm>
#include <set>
#include <queue>
using namespace std;

Graph::Graph()
{
    cout << "Loading airports..." << endl;

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
                    iataCode.erase(remove(iataCode.begin(), iataCode.end(), '"'), iataCode.end());
                    Airport airport(iataCode, lat, lon);
                    adjList[iataCode].push_back(airport);
            }
        }

        airportFile.close();
    }

    // Cleanup the current graph
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

            if (adjList.find(sourceAirportName) != adjList.end() && adjList.find(destinationAirportName) != adjList.end())
            {
                Airport source = adjList.find(sourceAirportName)->second.at(0);
                Airport destination = adjList.find(destinationAirportName)->second.at(0);
                
                // Make sure not to add duplicates to adjacency lists
                bool found = false;
                for (int i = 0; i < adjList[sourceAirportName].size(); i++)
                {
                    if (adjList[sourceAirportName].at(i).iata == destinationAirportName)
                        found = true;
                }
                if (!found)
                    adjList[sourceAirportName].push_back(destination);

                found = false;
                for (int i = 0; i < adjList[destinationAirportName].size(); i++)
                {
                    if (adjList[destinationAirportName].at(i).iata == sourceAirportName)
                        found = true;
                }
                if (!found)
                    adjList[destinationAirportName].push_back(source);
            }
        }

        routeFile.close();
    }

    // Get rid of any airports not connected to the graph
    iter = adjList.begin();
    while (iter != adjList.end())
    {
        if (iter->second.size() == 1)
            iter = adjList.erase(iter);
        else
            ++iter;
    }

}

void Graph::printKeys()
{
    int count = 0;
    bool first = true;

    cout << "{ ";
    for (auto airport : adjList)
    {
        if (count % 25 == 0 && !first)
            cout << "}" << endl << "{ ";
        cout << airport.first << " ";
        count++;
        if (first)
            first = false;
    }
    cout << "}" << endl;
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

    cout << endl << "There are " << adjList.size() << " airports in the graph!" << endl;
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
            for (int j = 1; j < adjList[adj.front()].size(); j++)
            {
                // Make sure this airport has not already been identified
                if (visited.count(adjList[adj.front()].at(j).iata) != 0)
                    continue;
                // Check if the path has been found
                else if (adjList[adj.front()].at(j).iata == destination)
                    // Returns the number of intermediate airports
                    return count;
                else
                {
                    visited.insert(adjList[adj.front()].at(j).iata);
                    adj.push(adjList[adj.front()].at(j).iata);
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

int Graph::scanList(const string& iata)
{
    int count = 0;
    for (auto airport : adjList)
    {
        if (airport.first == iata)
            return count;
        count++;
    }
}

bool Graph::checkList(const string& iata, vector<string>& airplanes)
{
    for (int i = 0; i < airplanes.size(); i++)
    {
        if (airplanes.at(i) == iata)
            return true;
    }
    return false;
}

double Graph::Dijkstra(string source, string destination)
{
    vector<string> p(adjList.size(), "-1");
    vector<double> d(adjList.size(), INT_MAX);
    
    vector<string> computed;
    vector<string> uncomputed;

    // Initialize V - S by placing all vertices into it
    for (auto iter = adjList.begin(); iter != adjList.end(); iter++)
    {
        uncomputed.push_back(iter->first);
    }

    int index = scanList(source);

    // This is the source airport
    d[index] = 0;
    computed.push_back(source);

    // Process edges adjacent to the source vertex
    for (int i = 1; i < adjList[source].size(); i++)
    {
        double distance = haversineCalc(adjList[source].at(0).latitudeDeg, adjList[source].at(0).longitudeDeg,
            adjList[source].at(i).latitudeDeg, adjList[source].at(i).longitudeDeg);

        index = scanList(adjList[source].at(i).iata);
        d[index] = distance;
        p[index] = computed.back();
    }

    while (computed.size() != adjList.size())
    {
        // Find the smallest distance uncomputed airport
        int smallestINDX = 0;
        for (int i = 0; i < d.size(); i++)
        {
            if (d.at(i) < d.at(smallestINDX))
            {
                if (!checkList(uncomputed.at(i), computed))
                    smallestINDX = i;
            }
        }

        computed.push_back(uncomputed.at(smallestINDX));

        // Relax edges
        for (int i = 1; i < adjList[computed.back()].size(); i++)
        {
            double distance = haversineCalc(adjList[computed.back()].at(0).latitudeDeg, adjList[computed.back()].at(0).longitudeDeg,
                adjList[computed.back()].at(i).latitudeDeg, adjList[computed.back()].at(i).longitudeDeg);

            index = scanList(adjList[computed.back()].at(i).iata);
            if (d[smallestINDX] + distance < d[index])
            {
                d[index] = d[smallestINDX] + distance;
                p[index] = computed.back();
            }
        }
    }
    
    index = scanList(destination);
    return d[index];
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
