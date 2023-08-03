#include "Graph.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;


Graph::Graph()
{
	ifstream airportsFile; 
	
	string IATA;

	airportsFile.open("airports.csv");

	while (!airportsFile.eof())
	{
			getline(airportsFile, IATA, ','); 
			if (IATA.size() == 3)
			{
					Airport (
			}
	}

	       
	//ifstream routes; 



}

