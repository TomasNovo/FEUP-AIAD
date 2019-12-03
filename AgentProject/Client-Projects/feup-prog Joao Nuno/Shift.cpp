#include "Shift.h"

Shift::Shift(unsigned int line, unsigned int driver, unsigned int bus, unsigned int start, unsigned int end){
  
	busLineId = line;
	driverId = driver;
	busOrderNumber = bus;
	startTime = start;
	endTime = end;
}

// metodos get
unsigned int Shift::getBusLineId() const{
  return busLineId;
}

unsigned int Shift::getDriverId() const{
  return driverId;
}
unsigned int Shift::getBusOrderNumber() const{
  return busOrderNumber;
}

unsigned int Shift::getStartTime() const{
  return startTime;
}

unsigned int Shift::getEndTime() const{
  return endTime;
}

///////////////
// set methods
//////////////

void Shift::setBusLineId(unsigned int newBusLineId){
  this->busLineId = newBusLineId;
}

void Shift::setDriverId(unsigned int newDriverId){
  this->driverId = newDriverId;
}

void Shift::setBusOrderNumber(unsigned int newBusOrderNumber){
  this->busOrderNumber = newBusOrderNumber;
}

void Shift::setStartTime(unsigned int newStartTime){
  this->startTime = newStartTime;
}

void Shift::setEndTime(unsigned int newEndTime){
  this->endTime = newEndTime;
}
