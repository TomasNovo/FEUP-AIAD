#include "DriverWork.h"



DriverWork::DriverWork()
{
}

DriverWork::DriverWork(unsigned int startTime, unsigned int endTime, vector <Shift *> WorkShifts, int line, unsigned int busOrderNumber) {
	this->startTime = startTime;
	this->endTime = endTime;
	this->WorkShifts = WorkShifts;
	this->line = line;
	this->busOrderNumber = busOrderNumber;
}

//GET METHODS
unsigned int DriverWork::getStartTime() const {
	return startTime;
}

unsigned int DriverWork::getEndTime() const {
	return endTime;
}
vector <Shift *> DriverWork::getWorkShifts() const {
	return WorkShifts;
 }

int DriverWork::getLine() const {
	return line;
}
unsigned int DriverWork::getBusOrderNumber() const{
	return busOrderNumber;
}

//SET METHODS

void DriverWork::setStartTime(unsigned int startTime) {
	this->startTime = startTime;
}

void DriverWork::setEndTime(unsigned int endTime) {
	this->endTime = endTime;
}

void DriverWork::setWorkShifts(vector<Shift *> WorkShifts) {
	this->WorkShifts = WorkShifts;
}

void DriverWork::setBusOrderNumber(unsigned int busOrderNumber) {
	this->busOrderNumber = busOrderNumber;
}