#include "Graph.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cctype>
#include <math.h>
#include <cmath> 
#define earthRadKm 6371.0 
using namespace std

Graph::Graph() 
{
    
    ifstream airportFile("airports.csv");

    if (airportFile.is_open()) 
			{
        string line;

        //Skip the beginning row
        getline(airportFile, line);

        while (getline(airportFile, line)) 
						{
            istringstream iss(line);
            string airportName;
            string latitude;
            string longitude;
            string iataCode;

            if (getline(iss, airportName, ',') && getline(iss, latitude, ',') && getline(iss, longitude, ',') && getline(iss, iataCode, ',')) 
										{
                
                if (!iataCode.empty()) 
													{
                    Airport airport(iataCode, latitude, longitude);
                    adjList[airport];
                }
            }
        }

        airportFile.close();
    }

    
    ifstream routeFile("routes.csv");

    if (routeFile.is_open()) 
				{
        string line
        getline(routeFile, line);

        while (getline(routeFile, line)) 
							{
            istringstream iss(line);
            string sourceAirportName;
            string destinationAirportName;

            if (getline(iss, sourceAirportName, ',') && getline(iss, destinationAirportName, ',')) 
											{

                if (sourceAirportIt != adjList.end() && destinationAirportIt != adjList.end() && !sourceAirportName.empty() && destinationAirportName.empty()) 
													{
                    adjList[sourceAirportIt->first].insert(destinationAirportIt->first);
                    adjList[destinationAirportIt->first].insert(sourceAirportIt->first);
                }
            }
        }

        routeFile.close();
    }
}

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
		/*  Because we need to calculate the distance, I will be implementing the Haversine formula to calculate the distance between these airports.*/ 
}

