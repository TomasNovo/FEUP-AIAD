#ifndef __DRIVER_INCLUDED__
#define __DRIVER_INCLUDED__

#include <string>
#include <sstream>
#include <fstream>
#include <set>
#include <iostream>
#include "utilities.h"
#include "shift.h"

using namespace std;

enum CanAddShiftFuncReturns {
	NOT_AVAILABLE,
	WEEKLY_LIMIT_REACHED,
	MUST_RESPECT_REST_TIME,
	SHIFT_TOO_LONG,
	AVAILABLE

};

class Driver{

public:
	void SetID(const string&);
	void SetName(const string&);
	void SetMaxHoursShift(const unsigned int&);
	void SetMaxHoursWeek(const unsigned int&);
	void SetMinHoursRest(const unsigned int&);

	string GetID() const;
	string GetName() const;
	unsigned int GetMaxHoursShift() const;
	unsigned int GetMaxHoursWeek() const;
	unsigned int GetMinHoursRest() const;

	int CanAddShift(const Shift&, const set<Shift>& setShifts) const;
	void AddShift(const Shift&);
	void RemoveShift(const Shift&);
	void RemoveAllLineShifts(const string& LineID);
	const set<Shift>& GetDriverShifts() const;

	void ShowWorkSchedule(const set<Shift>& setShifts) const;
	unsigned int GetNrWorkingHours(const set<Shift>& setShifts) const;

private:
	string ID;
	string name;
	unsigned int maxhoursshift;
	unsigned int maxhoursweek;
	unsigned int minhoursrest;
	set<Shift> driverShifts;

	void DisplaySpecificDay(int day, const string& spacer, const set<Shift>& setShifts) const;

};


#endif