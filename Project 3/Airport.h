#pragma once
#include<string>
using namespace std;

struct Airport
{
	// Constructor
	Airport(const string& name, double lat, double lon)
		: iata(name), latitudeDeg(lat), longitudeDeg(lon) {}

	// Member functions
	string iata;
	double latitudeDeg, longitudeDeg;

	// 
	bool operator==(const Airport& rhs) const { return iata == rhs.iata; }
};