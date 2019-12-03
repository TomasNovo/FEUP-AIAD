#ifndef __UTILITIES_INCLUDED__
#define __UTILITIES_INCLUDED__

#include <string>
#include "globals.h"

class Drivers;
class Buses;
class Shift_Interface;
class Shift;

using namespace std;

namespace utilities{

	template <class T>

	void swap(T&, T&);
	void trimString(string&);
	int intSize(int);
	bool isNumeric(string);
	string DayNumberToString(const unsigned int&);
	int DayStringToNumber(const string&);
	void InsertShift(const Shift& argShift, bool saveToFile = true);
	bool LoadShiftsFile(const string& FileName);

	const set<Shift>& GetShiftsFromDriver(const set<Shift>& setShifts, const string& driverid);

	const set<Shift>& GetShiftsFromBusID(const set<Shift>& setShifts, const string& busid);
};


#endif