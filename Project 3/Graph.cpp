#include "Graph.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

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



