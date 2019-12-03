#include "Shift.h"

Shift::Shift(unsigned int linha, unsigned int condutor, unsigned int autocarro, unsigned day_of_the_week,unsigned int inicio, 
	unsigned int fim) // Class builder
{
	busLineId = linha;
	driverId = condutor;
	busOrderNumber = autocarro;
	startTime = inicio;
	endTime = fim;
	this->day_of_the_week = day_of_the_week;
}

// get methods

unsigned int Shift::getBusLineId() const{ // Returns the line's id
  return busLineId;
}

unsigned int Shift::getDriverId() const{ // Returns the driver's id
  return driverId;
}

unsigned int Shift::getBusOrderNumber() const{ // Returns the order number of the bus
  return busOrderNumber;
}

unsigned int Shift::getStartTime() const{ // Returns the shift's starting time
  return startTime;
}

unsigned int Shift::getEndTime() const{ // Returns the shift's ending time
  return endTime;
}

unsigned int Shift::getWeekDay() const { // Returns the number corresponding to the week day
	return day_of_the_week;
}

///////////////
// set methods
//////////////

void Shift::setBusLineId(unsigned int busLineId){ // Changes the line's id
  this->busLineId = busLineId;
}

void Shift::setDriverId(unsigned int driverId){ // Changes the drivers id
  this->driverId = driverId;
}

void Shift::setBusOrderNumber(unsigned int busOrderNumber){ // Changes the bus's order number
  this->busOrderNumber = busOrderNumber;
}

void Shift::setStartTime(unsigned int startTime){ // Changes the shift's starting time
  this->startTime = startTime;
}

void Shift::setEndTime(unsigned int endTime){ // Changes the shift ending time
  this->endTime = endTime;
}

void Shift::setWeekDay(unsigned int week_day) { // Changes the week day
	day_of_the_week = week_day;
}
