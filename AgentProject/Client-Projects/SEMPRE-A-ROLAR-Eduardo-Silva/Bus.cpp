#include "Bus.h"
#include <algorithm>


Bus::  Bus(unsigned int order, unsigned int driver, unsigned int line) // Class builder
{
	orderInLine = order;
	lineId = line;
	driverId = driver;
}

////////////////////////////////
// get methods
///////////////////////////////
unsigned int Bus::getBusOrderInLine() const{ // Returns the bus's order number in the line
  return orderInLine;
}

unsigned int Bus::getDriverId() const{ // Returns the bus's current driver's id
  return driverId;
}

unsigned int Bus::getLineId() const{ // Returns the id of the line in which the bus circulates
  return lineId;
}

vector<Shift> Bus::getSchedule() const{ // Returns the vector with all the bus's shifts
  return schedule;
}

//////////////////////////////
// metodos set
/////////////////////////////

void Bus::setDriverId(unsigned int d_id) // Changes the ID of the bus's driver
{
	driverId = d_id;
}

void Bus::setShifts(vector<Shift> vs) // Replaces the shifts vector with a new one
{
	schedule.clear();
	copy(vs.begin(), vs.end(), schedule.begin());
}

void Bus::setLineId(unsigned int l_id) // Changes the id of the line in which the bus circulates
{
	lineId = l_id;
}

////////////////////////////
// outher methods
///////////////////////////

void Bus::AddShift(Shift new_shift) // Adds a new shift to the shift's vector
{
	schedule.push_back(new_shift);
}

bool Bus::RemoveShift(unsigned int day_of_the_week, unsigned int shift_starting_time) /* Removes a shif from the shift's
																					  vector, returning true if the operation
																					  was succesfull, or false otherwise*/
{
	unsigned int shift_it;
	
	for (shift_it = 0; shift_it < schedule.size(); shift_it++)
	{
		if (schedule[shift_it].getWeekDay() == day_of_the_week
			&&
			schedule[shift_it].getStartTime() == shift_starting_time)
		{
			schedule.erase(schedule.begin() + shift_it);
			return true;
		}

	}

	return false;
}
