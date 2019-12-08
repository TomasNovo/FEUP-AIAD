
#include <iostream>
#include <string>
#include <vector>
#include "Shift.h"
#include "DriverWork.h"
#include <utility>

#pragma once

using namespace std;

class Driver
{
public:
	//construtores
	Driver();
	Driver(string one_driver);
	Driver(int id, string name);
	Driver(int id, string name, int maxDayWorkingTime, int maxWeekWorkingTime, int minRestTime);

	//modificadores
	void setID(int id);
	void setMaxHours(int maxDayWorkingTime);
	void setMaxWeekWorkingTime(int maxWeekWorkingTime);
	void setMinRestTime(int MinRestTime);
	void setName(string name);
	void addShift(pair <int, DriverWork>);
	void removeShift(pair <int, DriverWork>);

	//aceder
	int getID() const;
	string getName() const;
	int getMaxHours() const;
	int getMaxWeekWorkingTime() const;
	int getMaxWeekWorkingTimeConst() const;
	int getMinRestTime() const;
	int getMaxHoursDayVector(int day);
	vector <int> getStartTimes(int day);
	vector <int> getEndTimes(int day);

	vector <Shift*> getShifts(int day);

	vector <pair <int, vector < DriverWork>>> getAllDriverShifts();

	vector < DriverWork > getDayWork(int day);

	//display
	void showInfo() const;
	

private:
	string name;
	int id;
	int maxDayWorkingTime;
	int maxWeekWorkingTime;
	int maxWeekWorkingTimeConst;
	int minRestTime;
	vector <pair <int,vector < DriverWork>>> DriverShifts;
};
