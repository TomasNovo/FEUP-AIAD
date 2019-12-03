#include "Bus.h"


Bus::Bus(unsigned int id, unsigned int driver, unsigned int line){
	orderInLine = id;
	driverId = driver;
	lineId = line;
}

////////////////////////////////
// get methods
///////////////////////////////
unsigned int Bus::getBusOrderInLine() const{
  return orderInLine;
}

unsigned int Bus::getDriverId() const{
  return driverId;
}

unsigned int Bus::getLineId() const{
  return lineId;
}

vector<Shift> Bus::getSchedule() const{
  return schedule;
}


//////////////////////////////
// metodos set
/////////////////////////////

void Bus::setDriverId(unsigned int newDriverId) {
	driverId = newDriverId;
}

void Bus::setLineId(unsigned int newLineId) {
	lineId = newLineId;
}
////////////////////////////
// outher methods
///////////////////////////
