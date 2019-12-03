#pragma once

#include <iostream>
#include <vector>


using namespace std;

class Shift {
public:
	Shift();
	Shift(unsigned int busLineId, unsigned int StartTime, unsigned int  endTime, unsigned int busOrderNumber);

	// get methdos
	unsigned int getBusLineId() const;
	unsigned int getDriverId() const;
	unsigned int getBusOrderNumber() const; // order of the bus within the bus line
	unsigned int getStartTime() const;
	unsigned int getEndTime() const;
	bool getInUse() const;
	unsigned int getDuration() const;

	//  set methods
	void setBusLineId(unsigned int);
	void setDriverId(unsigned int);
	void setBusOrderNumber(unsigned int);
	void setStartTime(unsigned int);
	void setEndTime(unsigned int);
	void setInUse(bool state);

	// other methods


private:
	unsigned int busLineId;
	unsigned int driverId;
	unsigned int busOrderNumber;
	unsigned int startTime;
	unsigned int endTime;
	unsigned int Duration;
	bool InUse;
};
