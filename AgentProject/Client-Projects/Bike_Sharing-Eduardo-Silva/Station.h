#ifndef AEDA_P1_STATION_H
#define AEDA_P1_STATION_H

#include <iostream>
#include <string>
#include <vector>
#include "Bike.h"
using namespace std;

class Station
{
    int no_max_spots;
	string name;
    vector<Bike *> available_bikes;
	pair <int, int> Localization;
	
public:
    Station(int max_spots, string name, int x, int y);
    bool findBike(string type) const;
	void addBike(Bike *bk);
	void removeBike(string bike_id);
	pair<int, int> getLocalization() const;
	vector<Bike *> getAvailableBikes() const;
	string getName() const;
	int getMaxSpots() const;
	int getSpots() const;
	void show_station() const;
	bool operator==(const Station *s) const;
};

class Inexistent_Station
{
	string name;

public:
	Inexistent_Station(string nm);
	string getName() const;
};

class Another_station
{
	string name;
	pair<int, int> Localization;

public:
	Another_station(string nm, int x, int y);
	string getName() const;
	pair<int,int> getLocalization() const;
};

#endif

