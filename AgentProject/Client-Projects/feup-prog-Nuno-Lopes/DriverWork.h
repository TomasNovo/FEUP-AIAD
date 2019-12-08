#pragma once
#include "Shift.h"
class DriverWork
{
public:
	DriverWork();
	DriverWork(unsigned int startTine, unsigned int endTime, vector <Shift *> WorkShifts, int line, unsigned int busOrderNumber);

	//GET METHODS

	unsigned int getStartTime() const;
	unsigned int getEndTime() const;
	vector <Shift *> getWorkShifts() const;
	int getLine() const;
	unsigned int getBusOrderNumber() const;

	//SET METHODS

	void setStartTime(unsigned int startTime);
	void setEndTime(unsigned int startTime);
	void setWorkShifts(vector <Shift *> WorkShift);
	void setBusOrderNumber(unsigned int busOrderNumber);


private:
	unsigned int startTime;
	unsigned int endTime;
	unsigned int driverID;
	vector <Shift *> WorkShifts;
	int line;
	unsigned int busOrderNumber;
};

