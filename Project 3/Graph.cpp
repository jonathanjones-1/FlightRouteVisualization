#include "Graph.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <cctype>
#include <math.h>
#include <cmath> 
#define earthRadKm 6371.0 
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
            for (int i = 0; i < 4; i++)
            {
                getline(iss, unimportant, ',');
            }

            getline(iss, latitude, ',');
            getline(iss, longitude, ',');

            for (int i = 0; i < 7; i++)
            {
                getline(iss, unimportant, ',');
            }

            getline(iss, iataCode, ',');

            if (!iataCode.empty())
            {
                double lat = stod(latitude);
                double lon = stod(longitude);
                Airport airport(iataCode, lat, lon);
                adjList[airport];
            }
        }

        airportFile.close();
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

            Airport source(sourceAirportName, NULL, NULL), destination(destinationAirportName, NULL, NULL);

            if (adjList.find(source) != adjList.end() && adjList.find(destination) != adjList.end())
            {
                source.latitudeDeg = adjList.find(source)->first.latitudeDeg;
                source.longitudeDeg = adjList.find(source)->first.longitudeDeg;
                destination.latitudeDeg = adjList.find(destination)->first.latitudeDeg;
                destination.longitudeDeg = adjList.find(destination)->first.longitudeDeg;

                adjList[source].insert(destination);
                adjList[destination].insert(source);
            }
        }

        routeFile.close();
    }

    cout << "There are " << adjList.size() << " airports in the graph!" << endl;
}

/*
double Graph::haversineCalc(double lat1, long1, lat2, long2)
{
		lat1 = (lat1 * M_PI / 180);
		
		long1 = (long1 * M_PI / 180);

		lat2 = (lat2 * M_PI / 180);

		long2 = (long2 * M_PI / 180);

		double a = sin((lat2 - lat1)/2); 
		
		double b = sin((long2 - long1)/2); 

		return * earthRadKm * asin(sqrt(a * a + cos(lat1) * cos(lat2) * b * b)); 
}

void Graph::dijkstraAlg()
{
Because we need to calculate the distance, I will be implementing the Haversine formula to calculate the distance between these airports.
Also, I made this method void and without input as I haven't figured out how to start this portion, feel free to change anything/start this!

}
*/