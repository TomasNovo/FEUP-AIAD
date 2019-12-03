#include "Station.h"

using namespace std;

Station::Station(int max_spots,string name, int x, int y)
{
    vector<Bike *> empty_available_bikes;

    no_max_spots = max_spots;
    this->name = name;
    available_bikes = empty_available_bikes;
	Localization.first = x;
	Localization.second = y;
}

void Station::addBike(Bike *bk)
{
	available_bikes.push_back(bk);
}

void Station::removeBike(string bike_id)
{
	for (unsigned int i = 0; i < available_bikes.size(); i++)
		if (bike_id == available_bikes[i]->getID())
			available_bikes.erase(available_bikes.begin() + i);
}

vector<Bike *> Station::getAvailableBikes() const
{
	return available_bikes;
}

bool Station::findBike(string type) const
{
	for (unsigned int i = 0; i < available_bikes.size(); i++)
		if(available_bikes[i]->getID() == type)
			return true;
		
	return false;
}

pair<int, int> Station::getLocalization() const
{
	return Localization;
}

string Station::getName() const
{
	return name;
}

int Station::getMaxSpots() const
{
	return no_max_spots;
}

int Station::getSpots() const
{
	return no_max_spots - available_bikes.size();
}

void Station::show_station() const
{
	int n_us = 0, n_ub = 0, n_ch = 0, n_rc = 0;
	
	cout << name << endl
		<< endl
		<< "Coordinates: " << getLocalization().first << ", " << getLocalization().second
		<< endl
		<< "Maximum capacity: " << getMaxSpots() << endl
		<< "No of available spots: " << getMaxSpots() - getAvailableBikes().size() << endl
		<< "Available Bikes:\n";

	for (unsigned int j = 0; j < getAvailableBikes().size(); j++)
		if (getAvailableBikes()[j]->getID() == "US") //Might need to change
			n_us++;
		else
			if (getAvailableBikes()[j]->getID() == "UB")
				n_ub++;
			else
				if (getAvailableBikes()[j]->getID() == "CH")
					n_ch++;
				else
					if (getAvailableBikes()[j]->getID() == "RC")
						n_rc++;

	cout << "Urban: " << n_ub << endl
		<< "Simple urban: " << n_us << endl
		<< "Child: " << n_ch << endl
		<< "Racing: " << n_rc << endl << endl;
}

bool Station::operator==(const Station *s) const
{
	if (s->getName() == name || s->getLocalization() == Localization)
		return true;
	else return false;
}

//Inexistant Station

Inexistent_Station::Inexistent_Station(string nm)
{
	name = nm;
}

string Inexistent_Station::getName() const
{
	return name;
}

//Another Station

Another_station::Another_station(string nm, int x, int y)
{
	name = nm;
	
	Localization.first = x;
	Localization.second = y;
}

string Another_station::getName() const
{
	return name;
}

pair<int, int> Another_station::getLocalization() const
{
	return Localization;
}

