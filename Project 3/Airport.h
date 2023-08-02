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

	// Equality operator definition for comparing airports
	bool operator==(const Airport& rhs) const { return iata == rhs.iata; }

	// Hash function object (functor)
	struct Hash
	{
		size_t operator()(const Airport& ap) const
		{
			return std::hash<std::string>()(ap.iata);
		}
	};

};