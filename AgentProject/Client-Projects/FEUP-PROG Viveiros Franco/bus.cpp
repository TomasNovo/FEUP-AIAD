#include "bus.h"

bool Bus::AddShift(const Shift &)
{
	return false;
}

const vector<Shift*>& Bus::GetShifts()
{
	return shifts;
}

Line Bus::GetLine()
{
	return *line;
}

Driver Bus::GetDriver()
{
	return *driver;
}