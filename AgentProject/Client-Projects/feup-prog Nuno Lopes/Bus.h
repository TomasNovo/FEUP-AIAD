#pragma once


#include <iostream>
#include <vector>

#include "Shift.h"


using namespace std;

class Bus {

public:
	Bus(unsigned int orderInLine, unsigned int driver, unsigned int line);
	Bus(unsigned int orderInLine);

	// get methods
	unsigned int getBusOrderInLine() const;
	unsigned int getDriverId() const;
	unsigned int getLineId() const;
	vector<Shift> getSchedule() const;

	// set methods
	unsigned int setDriverId() const;
	unsigned int setLineId() const;

	// other methods

private:

	unsigned int orderInLine;

	unsigned int driverId;

	unsigned int lineId;

	vector<Shift> schedule;
};

