#include "utilities.h"
#include "globals.h"

template <class T>

//Swap the value of two integers
void utilities::swap(T &a, T &b)
{
	T temp = a;
	a = b;
	b = temp;
}

// Remove spaces at the beginning and at the end of a string
void utilities::trimString(string &input)
{
	if (input.length() < 2) return;
	while (input[0] == ' ')
		input.erase(input.begin());

	while (input.back() == ' ')
		input.erase(input.end() - 1);
}

// Caluclates the length of a string
int utilities::intSize(int input)
{
	int res = 0;

	while (input)
	{
		res++;
		input /= 10;
	}

	return res;
}

bool utilities::isNumeric(string input)
{
	utilities::trimString(input);

	if (input.size() == 0)
		return false;

	for (size_t i = 0; i < input.size(); i++)
	{
		if (input[i] < '0' || input[i] > '9')
			return false;
	}

	return true;
}

string utilities::DayNumberToString(const unsigned int& num)
{
	static string daysArray[] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
	return daysArray[num];
}

int utilities::DayStringToNumber(const string& dayName)
{
	if (dayName == "monday") {
		return 0;
	}
	else if (dayName == "tuesday") {
		return 1;
	}
	else if (dayName == "wednesday") {
		return 2;
	}
	else if (dayName == "thursday") {
		return 3;
	}
	else if (dayName == "friday") {
		return 4;
	}
	else if (dayName == "saturday") {
		return 5;
	}
	else if (dayName == "sunday") {
		return 6;
	}
	else return -1;
}

void utilities::InsertShift(const Shift & argShift, bool saveToFile)
{
	Shifts_Interface.InsertShift(argShift, saveToFile);
	// but we will also have to add the shift to the corresponding driver and bus..
	// first to the buses
	Buses.AddShift(argShift.GetBusID(), argShift);
	// then to the moon... I mean, the corresponding driver;
	Drivers.AddShiftToDriver(argShift.GetDriverID(), argShift);
}

bool utilities::LoadShiftsFile(const string & argFilename)
{
	ifstream shifts_file(argFilename);

	if (shifts_file.fail())
	{
		shifts_file.close();
		return false;
	}

	// Load shifts
	string tempstr;
	while (getline(shifts_file, tempstr)) {
		utilities::trimString(tempstr);
		istringstream sstreamFileLine(tempstr);
		unsigned int day, startHour, endHour;
		string driverID, busID, lineID;
		getline(sstreamFileLine, tempstr, ',');
		day = stoi(tempstr);
		getline(sstreamFileLine, tempstr, ',');
		startHour = stoi(tempstr);
		getline(sstreamFileLine, tempstr, ',');
		endHour = stoi(tempstr);
		//
		getline(sstreamFileLine, driverID, ',');
		getline(sstreamFileLine, busID, ',');
		getline(sstreamFileLine, lineID, ',');
		Shift newShift(day, startHour, endHour, driverID, busID, lineID);
		utilities::InsertShift(newShift, false);

	}
	shifts_file.close();
	return true;
}

const set<Shift>& utilities::GetShiftsFromDriver(const set<Shift>& setShifts, const string & driverid)
{
	static set<Shift> tempShift;
	tempShift.clear();
	for (auto shift : setShifts) {
		if (shift.GetDriverID() == driverid) {
			tempShift.insert(shift);
		}
	}
	return tempShift;
}

const set<Shift>& utilities::GetShiftsFromBusID(const set<Shift>& setShifts, const string & busid)
{
	static set<Shift> tempShift;
	tempShift.clear();
	for (auto shift : setShifts) {
		if (shift.GetBusID() == busid) {
			tempShift.insert(shift);
		}
	}
	return tempShift;
}

