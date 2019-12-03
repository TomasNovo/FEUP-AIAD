#include "Bus.h"


Bus::Bus(unsigned int orderInLine, unsigned int driver, unsigned int line) {
	this->orderInLine = orderInLine;
	driverId = driver;
	lineId = line;
}

Bus::Bus(unsigned int orderInLine) {
	this->orderInLine = orderInLine;
}
////////////////////////////////
// get methods
///////////////////////////////
unsigned int Bus::getBusOrderInLine() const {
	return orderInLine;
}

unsigned int Bus::getDriverId() const {
	return driverId;
}

unsigned int Bus::getLineId() const {
	return lineId;
}

vector<Shift> Bus::getSchedule() const {
	return schedule;
}


//////////////////////////////
// metodos set
/////////////////////////////

////////////////////////////
// outher methods
///////////////////////////
