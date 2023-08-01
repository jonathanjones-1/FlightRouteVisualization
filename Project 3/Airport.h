#pragma once
#include<string>
using namespace std;

class Airport
{
	private:
		string IATA;
		double latitudeDeg;
		double longitudeDeg;
	public:
		Airport(string IATA, double latitudeDeg, double longitudeDeg);
};

