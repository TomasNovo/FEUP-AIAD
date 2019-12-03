#pragma once
#include <vector>
#include <string>
#include "Shift.h"

using namespace std;
class Line
{
public:
	//construtores
	Line();
	Line(int id, int freq, vector<string> stops, vector <int> times_between_stops);
	Line(string one_line);

	//modificadores
	void setID(int id);
	void setFreq(int freq);
	void setBusStops(vector<string> stops);
	void setTimings(vector <int> times_between_stops);

	//aceder
	int getID() const;
	int getFreq() const;
	vector <string> getBusStops() const;
	vector <int> getTimings() const;
	int getNumberBusNeeded() const;

	//display
	void showInfo() const;

	//organizar
	vector <string> getBusStopsFromString(string line);
	vector<int> getTimingsFromString(string line);


private:
	int id;
	int freq;
	vector <string> busStops;
	vector <int> times_between_stops;
	int NumberBusNeeded;
};