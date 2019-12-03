#include "driver.h"
#include "globals.h"

void Driver::SetID(const string& input)
{
	this->ID = input;
}

void Driver::SetName(const string& input)
{
	this->name = input;
}

void Driver::SetMaxHoursShift(const unsigned int& input)
{
	this->maxhoursshift = input;
}

void Driver::SetMaxHoursWeek(const unsigned int& input)
{
	this->maxhoursweek = input;
}

void Driver::SetMinHoursRest(const unsigned int& input)
{
	this->minhoursrest = input;
}

string Driver::GetID() const
{
	return ID;
}

string Driver::GetName() const
{
	return name;
}

unsigned int Driver::GetMaxHoursShift() const
{
	return maxhoursshift;
}

unsigned int Driver::GetMaxHoursWeek() const
{
	return maxhoursweek;
}

unsigned int Driver::GetMinHoursRest() const
{
	return minhoursrest;
}

int Driver::CanAddShift(const Shift& argShift, const set<Shift>& setShifts) const
{
	// First we'll have to check if the driver is free at the specified time. Since we're looping the set we might as well count the work hours of the driver.
	// We'll also have to check if the resting hours are respected.
	unsigned int workHours = 0;
	for (const auto& shift : setShifts) {
		if (shift.GetDay() == argShift.GetDay() && argShift.GetStartHour() >= shift.GetStartHour() && argShift.GetStartHour() < shift.GetEndHour()) {
			return NOT_AVAILABLE;
		}
		if (shift.GetDay() == argShift.GetDay() && (shift.GetEndHour() + GetMinHoursRest()) >= argShift.GetStartHour()) {
			return MUST_RESPECT_REST_TIME;
		}
		workHours += shift.GetDuration();
	}
	// if we reached this step then it seems the driver is available to work in the hour. But did we respect the weekly limit?
	if (workHours + argShift.GetDuration() > GetMaxHoursWeek()) {
		return WEEKLY_LIMIT_REACHED;
	}
	// but... is the shift too long?
	if (argShift.GetDuration() > GetMaxHoursShift()) {
		return SHIFT_TOO_LONG;
	}
	// it seems that the driver is able to work this shift.
	return AVAILABLE;
}

void Driver::AddShift(const Shift& argShift)
{
	driverShifts.insert(argShift);
}

void Driver::RemoveShift(const Shift& argShift)
{
	auto iterator = driverShifts.find(argShift);
	if (iterator != driverShifts.end()) {
		driverShifts.erase(iterator);
	}
}

void Driver::RemoveAllLineShifts(const string & LineID)
{
	for (auto iterator = driverShifts.begin(); iterator != driverShifts.end(); iterator++) {
		if (iterator->GetLineID() == LineID) {
			driverShifts.erase(iterator);
		}
	}
}

const set<Shift>& Driver::GetDriverShifts() const
{
	//return driverShifts;
	static set<Shift> tempShift;
	tempShift.clear();
	for (auto shift : Shifts_Interface.GetShifts()) {
		if (shift.GetDriverID() == ID) {
			tempShift.insert(shift);
		}
	}
	cout << Shifts_Interface.GetShifts().size();
	return tempShift;
}

void Driver::ShowWorkSchedule(const set<Shift>& setShifts) const
{
	static string blankFiller = "                ";
	cout << blankFiller << string(60, '#') << endl;
	size_t nameLengthLeft = name.length();
	size_t nameLengthRight = name.length() % 2 == 1 ? (name.length() + 1) : name.length();
	cout << blankFiller << "#" << string(28 - nameLengthLeft / 2, '#') << " " + name + " " << string(28 - nameLengthRight / 2, '#') << "#" << endl;
	cout << blankFiller << "############# 8:00                    20:00 ################" << endl;
	
	for (int i = 0; i < 7; i++) {
		DisplaySpecificDay(i, blankFiller, setShifts);
	}
	cout << blankFiller << string(60, '#') << endl;
	cout << blankFiller << "        W- Working | R- Rest Hours | N- Not working";
}


void Driver::DisplaySpecificDay(int day, const string& blankFiller, const set<Shift>& setShifts) const {

	const string dayName = utilities::DayNumberToString(day);
	unsigned int nrSpaces = 9 - dayName.length();

	cout << blankFiller << "# " + dayName + string(nrSpaces, ' ') + " | ";

	for (unsigned int i = 8; i < SCHEDULE_END; i++) {
		Shift tempShift(day, i, i + 1, "", "", "");
		switch (CanAddShift(tempShift, setShifts)) {
			case NOT_AVAILABLE:
				cout << "W";
				break;
			case MUST_RESPECT_REST_TIME:
				cout << "R";
				break;
			default:
				cout << "N";
		}
		cout << " ";
	}

	cout << "################";
	cout << endl;
}

unsigned int Driver::GetNrWorkingHours(const set<Shift>& setShifts) const
{
	unsigned int acumulator = 0;
	for (auto shift : setShifts) {
		acumulator += shift.GetDuration();
	}
	return acumulator;
}
