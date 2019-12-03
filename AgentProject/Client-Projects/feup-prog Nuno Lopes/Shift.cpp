#include "Shift.h"

Shift::Shift() {
	startTime = 0;
	endTime = 0; 
}

Shift::Shift(unsigned int busLineId, unsigned int startTime, unsigned int endTime, unsigned int busOrderNumber) {
	this->busLineId = busLineId;
	this->startTime = startTime;
	this->endTime = endTime;
	this->busOrderNumber = busOrderNumber;
	Duration = endTime - startTime;
	InUse = false;
}


// metodos get

unsigned int Shift::getBusLineId() const {
	return busLineId;
}

unsigned int Shift::getDriverId() const {
	return driverId;
}
unsigned int Shift::getBusOrderNumber() const {
	return busOrderNumber;
}

unsigned int Shift::getStartTime() const {
	return startTime;
}

unsigned int Shift::getEndTime() const {
	return endTime;
}

bool Shift::getInUse() const {
	return InUse;
}

unsigned int Shift::getDuration() const {
	return Duration;
}


// set methods

void  Shift::setBusLineId(unsigned int busLineId) {
	this->busLineId = busLineId;
}

void  Shift::setDriverId(unsigned int driverId) {
	this->driverId = driverId;
}

void  Shift::setBusOrderNumber(unsigned int busOrderNumber) {
	this->busOrderNumber = busOrderNumber;
}

void Shift::setStartTime(unsigned int startTime) {
	this->startTime = startTime;
}
void Shift::setEndTime(unsigned int) {
	this->endTime = endTime;
}

void Shift::setInUse(bool state) {
	InUse = state;
}