#include "Line.h"
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

Line::Line(string line_string) // Builds an element of the class from a string
{  
	unsigned int hours;
	string stop, comma, next = "", time; //The string comma is just a way to get rid of the ; while reading the stringstream
	istringstream l(line_string), sch;
	vector<string> stops;
	vector<int> schedule;

	l >> id >> comma >> freq >> comma >> stop;

	while (true)
	{
		while (stop[stop.length() - 1] != ',' && stop[stop.length() - 1] != ';')
		{
			l >> next;
			stop = stop + " " + next; //If there isn't a , at the end of the name, it isn't the full name of the stop yet
		}

		if (stop[stop.length() - 1] == ';') //If there is a ; at the end of the name, it's the last stop in that route
			break;

		stop = stop.substr(0, stop.length() - 1); //Gets rid of the , at the end of the stops (except the last one)
		stops.push_back(stop);
		l >> stop;
	}

	stop = stop.substr(0, stop.length() - 1); //Gets rid of the ; at the end of the last stop
	stops.push_back(stop);
	l >> time;

	while (time[time.length() - 1] == ',') /*If there is a , at the end of the value, it isn't the last one, therefore it
										   needs to be removed */
	{
		time = time.substr(0, time.length() - 1);
		sch.clear();
		sch.str(time);
		sch >> hours;
		schedule.push_back(hours);
		l >> time;
	}

	sch.clear();
	sch.str(time);
	sch >> hours;
	schedule.push_back(hours);
	stops_vector = stops;
	times_vector = schedule;
}

Line::Line(int id, int freq, vector<string> stops_v, vector<int> times_v) /* Builds an element of the class from all the other
																		  parameters */
{
	this->id = id;
	this->freq = freq;
	stops_vector = stops_v;
	times_vector = times_v;
}

////////////////
// get methods
//////////////// 

unsigned int Line::getId() const{ // Returns the id of the line
  return id;
}

unsigned int Line::getFreq() const { // Returns the frequency of the line
	return freq;
}

vector<string> Line::getBusStops() const{ // Returns the stop's vector
  return stops_vector;
}

vector<int> Line::getTimings() const{ // Returns the time's vector
  return times_vector;
}

////////////////
// set methods
//////////////// 

void Line::SetID(unsigned int new_id) // Changes the id of the line
{
	id = new_id;
}

void Line::SetFrequency(unsigned int new_freq) // Changes the frequency of the line
{
	freq = new_freq;
}

void Line::SetStops(vector<string> New_Stops) // Changes the stops vector
{
	stops_vector = New_Stops;
}

void Line::SetSchedule(vector<int> New_Schedule) // Changes the times vector
{
	times_vector = New_Schedule;
}

// other functions

unsigned int Line::Calc_No_Busses() const// Calculates the number of busses neede for a line
{
	int total_travelling_time = 0;
	unsigned int time_it;

	for (time_it = 0; time_it < getTimings().size(); time_it++)
	{
		total_travelling_time = total_travelling_time + getTimings()[time_it];
	}

	if (total_travelling_time % getFreq() == 0)
		return total_travelling_time / getFreq();
	else return total_travelling_time / getFreq() + 1;
}

void Line::Show_Available_Start_Time(unsigned int day_start, unsigned int day_end) const /*  Displays the hours at which is
																						     possible to start a shift */
{
	unsigned int new_start;

	for (new_start = day_start; new_start < day_end; new_start += getFreq())
	{
		cout << setfill('0') << setw(2) << new_start / 60
			<< ":"
			<< setfill('0') << setw(2) << new_start % 60 << " | ";
	}
}




