#include "Driver.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

Driver::Driver(string driver_string) // Builds an element of this class from a string
{
	istringstream dr(driver_string);
	string name_i = "", next = "", comma; //The string comma is used just to get rid of the ; while reading the stringstream

	dr >> id >> comma;

	while (next != ";")
	{
		name_i = name_i + next;
		name_i = name_i + " ";
		dr >> next;
	}

	dr >> maxHours >> comma >> maxWeekWorkingTime >> comma >> minRestTime;
	name = name_i;
}

Driver::Driver(unsigned int id, string name, unsigned int d_lim, unsigned int w_lim, unsigned int r_min)
// Builds an element of this class from all the parameters
{
	this->id = id;
	this->name = name;
	maxHours = d_lim;
	maxWeekWorkingTime = w_lim;
	minRestTime = r_min;
}

//////////////
// get methods
//////////////

unsigned int Driver::getId() const{ // Returns the ID of the driver
  return id;
}

string Driver::getName() const{ // Returns the driver's name
  return name;
}

unsigned int Driver::getShiftMaxDuration() const{ // Returns the maximum number of working hours in a day
  return maxHours;
}

unsigned int Driver::getMaxWeekWorkingTime() const{ // Returns the maximum number of working hours in a week
  return maxWeekWorkingTime;
}

unsigned int Driver::getMinRestTime() const{ // Returns the minimum number of hours of rest between shifts
  return minRestTime;
}

vector<Shift> Driver::getShifts() const{ // Returns the shift's vector
  return shifts;
}

// Set methods

void Driver::setID(unsigned int new_id) // Changes the id of the driver
{
	id = new_id;
}

void Driver::setName(string name) // Changes the name of the driver
{
	this->name = name;
}

void Driver::setMaxHours(unsigned int hours) // Changes the daily limit of working hours
{
	maxHours = hours;
}

void Driver::setMaxWeekHours(unsigned int hours) // Changes the weekly limit of working hours
{
	maxWeekWorkingTime = hours;
}

void Driver::setMinRestHours(unsigned int hours) // Changes the minimum number of rest hours between shifts
{
	minRestTime = hours;
}

void Driver::setShifts(vector<Shift> vs) // Replaces the shift's vector with a new one
{
	shifts.clear();
	copy(vs.begin(), vs.end(), shifts.begin());
}

// Other methods

void Driver::AddShift(Shift shift) // Adds a shift to the shift's vector
{
	shifts.push_back(shift);
}

bool Driver::RemoveShift (unsigned int day_of_the_week, unsigned int shift_starting_time) /* Removes a shift from the shift's
																						  vector, returning true if the 
																						  operation was succesfull, or false
																						  otherwise */
{
	unsigned int shift_it;

	for (shift_it = 0; shift_it < shifts.size(); shift_it++)
	{
		if (shifts[shift_it].getWeekDay() == day_of_the_week
			&& shifts[shift_it].getStartTime() == shift_starting_time)
		{
			shifts.erase(shifts.begin() + shift_it);
			return true;
		}
	}

	return false;
}
