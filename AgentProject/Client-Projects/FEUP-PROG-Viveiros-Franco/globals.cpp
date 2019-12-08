#include "globals.h"

// -- LINES CLASS -- \\

void LinesClass::AddBusLine(const Line& inputLine)
{
	lines.push_back(inputLine);
	// rebuild bus stops cache
	Bus_Stops.RebuildBus_Stops(lines);
	SaveToFile();
}

bool LinesClass::RemoveBusLine(const Line& inputLine)
{
	for (int i = 0; i < lines.size(); ++i)
	{
		if (lines[i].GetID() == inputLine.GetID())
		{
			lines.erase(lines.begin() + i);
			// rebuild bus stops cache
			Bus_Stops.RebuildBus_Stops(lines);
			// remove all associated shifts
			Shifts_Interface.RemoveLineShifts(lines[i].GetID());
			Drivers.RemoveAllShiftsWithLineID(lines[i].GetID());
			Buses.RemoveShiftsByLineID(lines[i].GetID());
			SaveToFile();
			return true;
		}
	}

	return false;
}

bool LinesClass::RemoveBusLineByID(const string& argIdentifier)
{
	for (auto iterator = lines.begin(); iterator != lines.end(); iterator++) {
	 	if (iterator->GetID() == argIdentifier) { // found
	 		lines.erase(iterator);
	 		// rebuild bus stops cache
	 		Bus_Stops.RebuildBus_Stops(lines);
			// remove all associated shifts
	 		Shifts_Interface.RemoveLineShifts(argIdentifier);
	 		Drivers.RemoveAllShiftsWithLineID(argIdentifier);
	 		Buses.RemoveShiftsByLineID(argIdentifier);
	 		SaveToFile();
	 		return true;
	 	}
	 }

	// return false;

	// Line * lineptr = FindLine(argIdentifier);

	// if (lineptr != nullptr)
	// {
	// 	lines.erase(*lineptr);
	// 	return true;
	// }
	// else
	// 	return false;

	/*for (int i = 0; i < lines.size(); ++i)
	{
		if (lines[i].GetID() == argIdentifier)
		{
			lines.erase(lines.begin() + i);
			Bus_Stops.RebuildBus_Stops(lines);
			return true;
		}
	}
	return false; */
	}

	bool LinesClass::LoadFromFile(const string& argFilename)
	{
		filename = argFilename;
		ifstream lines_file(filename);

		if (lines_file.fail()) 
		{
			lines_file.close();
			return false;
		}

	// Load lines
		string tempstr;
		while (getline(lines_file, tempstr)) {
		// Take line from file to tempstr
			tempstr += ";";
			istringstream line_stream(tempstr);
			Line templine;
			string newtempstr;
			vector<string> stop_vector;
			vector<unsigned int> time_vector;


		// Store line ID
			getline(line_stream, tempstr, ';');
			utilities::trimString(tempstr);
			templine.SetID(tempstr);

		// Store line freq
			getline(line_stream, tempstr, ';');
			utilities::trimString(tempstr);
			templine.SetFreq(stoi(tempstr));

		// Store line's stops
			getline(line_stream, tempstr, ';');
			utilities::trimString(tempstr);
			tempstr += ',';
			istringstream Bus_Stop_stream(tempstr);

			while (getline(Bus_Stop_stream, tempstr, ','))
			{
				utilities::trimString(tempstr);
				stop_vector.push_back(tempstr);

			}
			templine.SetBus_Stops(stop_vector);

		// Store line's time between stops
			getline(line_stream, tempstr, ';');
			utilities::trimString(tempstr);
			tempstr += ',';
			istringstream time_stream(tempstr);

			while (getline(time_stream, tempstr, ','))
			{
				utilities::trimString(tempstr);
				time_vector.push_back(stoi(tempstr));

			}
			templine.SetTimeBetweenStops(time_vector);

		lines.push_back(templine); // Add templine to global line vector
	}
	lines_file.close();
	return true;
}


void LinesClass::SaveToFile() const {
	ofstream lines_file(filename);

	vector<string> stop_vector;
	vector<unsigned int> timebetweenstops;

	for (const Line &templine : lines) {
		lines_file <<  templine.GetID() << " ; " << templine.GetFreq() << " ; ";

		stop_vector = templine.GetBus_Stops();
		for (int i = 0; i < stop_vector.size(); ++i)
		{
			lines_file << stop_vector[i];
			if (i < stop_vector.size() - 1)
				lines_file << ", ";
		}

		lines_file << " ; ";

		timebetweenstops = templine.GetTimeBetweenStops();
		for (int i = 0; i < timebetweenstops.size(); ++i)
		{
			lines_file << timebetweenstops[i];
			if (i < timebetweenstops.size() - 1)
				lines_file << ", ";
		}

		// Only write a newline if it's not the last line
		if (templine.GetID() != lines.back().GetID())
			lines_file << "\n";
	}

	lines_file.close();
}

bool LinesClass::LineExists(const string & argIdentifier) const
{
	for (const auto& line : lines) {
		if (line.GetID() == argIdentifier)	return true;
	}
	return false;
}

int LinesClass::SearchLine(const string& argIdentifier) const
{
	for (int i = 0; i < lines.size(); ++i)
	{
		if (lines[i].GetID() == argIdentifier)
			return i;
	}
	return -1;
}

Line * LinesClass::FindLine(const string & LineID)
{
	for (auto& line : lines) {
		if (line.GetID() == LineID) {
			return &line;
		}
	}
	return nullptr;
}



void LinesClass::PrintLinesNames() const
{
	bool firstIteration = true;
	for (const Line &line : lines) {
		if (firstIteration) {
			(firstIteration = false);
		}
		else (std::cout << ",");
		std::cout << " " << line.GetID();
	}
}

vector<Line>& LinesClass::GetLines()
{
	return lines;
}

// -- DRIVERS CLASS -- \\

void DriversClass::AddDriver(const Driver& argDriver)
{
	drivers.push_back(argDriver);
}

bool DriversClass::RemoveDriver(const Driver& argDriver)
{
	for (auto iterator = drivers.cbegin(); iterator != drivers.cend(); iterator++) {
		if (iterator->GetID() == argDriver.GetID()) { // found
			for (const Shift& shift : iterator->GetDriverShifts()) {
				Shifts_Interface.RemoveShift(shift);
			}
			drivers.erase(iterator);
			return true;
		}
	}

	return false;
}

bool DriversClass::RemoveDriverByID(const string& argDriverID)
{
	// for (auto iterator = drivers.cbegin(); iterator != drivers.cend(); iterator++) {
	// 	if (iterator->GetID() == argDriverID) { // found
	// 		for (const Shift& shift : iterator->GetDriverShifts()) {
	// 			Shifts_Interface.RemoveShift(shift);
	// 		}
	// 		drivers.erase(iterator);
	// 		return true;
	// 	}
	// }

	// return false;

	// Driver * driverptr = FindDriver(argDriverID);

	// if (driverptr != nullptr)
	// {
	// 	drivers.erase(driverptr);
	// 	return true;
	// }
	// else
	// 	return false;

	for (int i = 0; i < drivers.size(); ++i)
	{
		if (drivers[i].GetID() == argDriverID)
		{
			drivers.erase(drivers.begin() + i);
			return true;
		}
	}
	return false;

}
/*
int DriversClass::CanAddShiftToDriver(const string & argDriverID, const Shift& argShift)
{
	Driver* driver = FindDriver(argDriverID);
	if (driver) {
		return driver->CanAddShift(argShift);
	}
	return -1;
} */

void DriversClass::AddShiftToDriver(const string & argDriverID, const Shift& argShift)
{
	Driver* driver = FindDriver(argDriverID);
	if (driver) {
		driver->AddShift(argShift);
	}
}

void DriversClass::RemoveShiftFromDriver(const string & argDriverID, const Shift &argShift)
{
	Driver* driver = FindDriver(argDriverID);
	if (driver) {
		driver->RemoveShift(argShift);
	}
}

void DriversClass::RemoveAllShiftsWithLineID(const string & LineID)
{
	for (auto driver : drivers) {
		driver.RemoveAllLineShifts(LineID);
	}
}

bool DriversClass::LoadFromFile(const string& argFilename)
{
	filename = argFilename;
	ifstream hFile_Drivers(filename);
	if (hFile_Drivers.fail()) {
		hFile_Drivers.close();
		return false;
	}

	// READ FILE LINES
	string motorista_string;
	while (getline(hFile_Drivers, motorista_string)) {
		// PROCESS LINE
		istringstream ss_line(motorista_string);
		Driver newDriver;
		string Temp;
		// READ DRIVER ID
		getline(ss_line, Temp, ';');
		utilities::trimString(Temp);
		newDriver.SetID(Temp);
		// READ DRIVER NAME
		getline(ss_line, Temp, ';');
		utilities::trimString(Temp);
		newDriver.SetName(Temp);
		// READ MAX NR OF HOURS PER SHIFT 
		getline(ss_line, Temp, ';');
		utilities::trimString(Temp);
		newDriver.SetMaxHoursShift( stoi(Temp) );
		// READ MAX WEEKLY LOAD (WORKING HOURS)
		getline(ss_line, Temp, ';');
		utilities::trimString(Temp);
		newDriver.SetMaxHoursWeek( stoi(Temp) );
		// READ MIN NUMBER OF REST HOURS BETWEEN SHIFTS
		getline(ss_line, Temp, '\n');
		utilities::trimString(Temp);
		newDriver.SetMinHoursRest( stoi(Temp) );

		drivers.push_back(newDriver); // add to intern vector
	}
	hFile_Drivers.close();
	return true;
}

void DriversClass::SaveToFile() const
{
	ofstream hFile_Drivers(filename);
	for (const Driver &driver : drivers) {
		hFile_Drivers << driver.GetID() << " ; " << driver.GetName() << " ; " << driver.GetMaxHoursShift() << " ; " << driver.GetMaxHoursWeek() << " ; " << driver.GetMinHoursRest() << endl;
	}
	hFile_Drivers.close();
}

void DriversClass::PrintLinesNames() const
{
	bool firstIteration = true;
	for (const Driver &driver : drivers) {
		if (firstIteration) {
			(firstIteration = false);
		}
		else (std::cout << ",");
		std::cout << " " << driver.GetID();
	}

}


void DriversClass::ListDrivers() const
{
	cout << setw(2) << "" << setw(15) << left << "Identifier" << setw(30) << "Name" << setw(25) << "Hours per Shift" << setw(25) << "Weekly Load" << setw(20) << "Rest Hours" << endl;
	for (const Driver &driver : drivers) {
		cout << setw(2) << "" << setw(15) << driver.GetID() << setw(30) << driver.GetName() << setw(25) << driver.GetMaxHoursShift() << setw(25) << driver.GetMaxHoursWeek() << setw(20) << driver.GetMinHoursRest() << endl;
	}
	cout << right;
}

bool DriversClass::DriverExists(const string& argIdentifier) const
{
	for (const auto& driver : drivers) {
		if (driver.GetID() == argIdentifier)	return true;
	}
	return false;
}

int DriversClass::SearchDriver(const string& argIdentifier) const
{
	for (int i = 0; i < drivers.size(); ++i)
	{
		if (drivers[i].GetID() == argIdentifier)
			return i;
	}
	return -1;
}

void DriversClass::ListAvailableDrivers(const set<Shift>& setShifts) const
{
	for (Driver driver : drivers) {
		unsigned int workingHours = driver.GetNrWorkingHours(utilities::GetShiftsFromDriver(setShifts, driver.GetID()) );
		if (workingHours <= driver.GetMaxHoursWeek()) {
			cout << setw(35) << left << " --> " + driver.GetName() + " : ";
			cout << "Available to work " << driver.GetMaxHoursWeek() - workingHours << " more hours." << endl;
		}
	}
}

Driver * DriversClass::FindDriver(const string & DriverID)
{
	for (auto& driver : drivers) {
		if (driver.GetID() == DriverID) {
			return &driver;
		}
	}
	return nullptr;
}


vector<Driver>& DriversClass::GetDrivers()
{
	return drivers;
}


// -- BUS STOPS CLASS -- \\

void Bus_StopsClass::AddLineToBusStop(Line * ptr_Line, const string & arg_Bus_Stop_Name)
{
	for (auto& Bus_Stop : vecBusStops) {
		if (Bus_Stop.GetName() == arg_Bus_Stop_Name) {
			Bus_Stop.AddLine(ptr_Line);
			return;
		}
	}
	// Else.. Create new bus stop
	Bus_Stop newBusStop(arg_Bus_Stop_Name);
	newBusStop.AddLine(ptr_Line);
	vecBusStops.push_back(newBusStop);
}
//
//void Bus_StopsClass::RemoveLineFromBusStop(Line * ptr_Line, const string & arg_Bus_Stop_Name)
//{
//	Bus_Stop* ptr_BusStop = FindBus_StopByName(arg_Bus_Stop_Name);
//	if (ptr_BusStop->GetLinesCount() > 1) {
//		ptr_BusStop->RemoveLineFromStop(ptr_Line);
//	}
//	else { // delete bus stop if no bus stops there
//		RemoveBusStop(arg_Bus_Stop_Name);
//	}
//}
//
//void Bus_StopsClass::RemoveLineFromALLBus_Stops(Line * ptr_Line)
//{
//	for (auto& bus_stop : vecBusStops) {
//		bus_stop.RemoveLineFromStop(ptr_Line); // will only remove the line if it is present on that bus stop
//	}
//}

Bus_Stop * Bus_StopsClass::FindBus_StopByName(const string & arg_Bus_Stop_Name)
{
	for (auto& bus_stop : vecBusStops) {
		if (bus_stop.GetName() == arg_Bus_Stop_Name) {
			return &bus_stop;
		}
	}
	return nullptr;
}

void Bus_StopsClass::PrintAllBus_Stops_Names() const
{
	bool firstIteration = true;
	for (auto& bus_stop : vecBusStops) {
		if (firstIteration) {
			(firstIteration = false);
		}
		else (cout << ",");
		cout << " " << bus_stop.GetName();
	}
}

void Bus_StopsClass::RebuildBus_Stops(vector<Line>& vecLines)
{
	vecBusStops.clear();
	for (Line& linha : vecLines) {
		for (const Bus_Stop& bus_stop : linha.GetBus_Stops()) {
			AddLineToBusStop(&linha, bus_stop.GetName());
		}
	}
}

void Bus_StopsClass::RemoveBusStop(const string & arg_Bus_Stop_Name)
{
	for (auto iterator = vecBusStops.begin(); iterator != vecBusStops.end(); iterator++) {
		if (iterator->GetName() == arg_Bus_Stop_Name) { // found
			vecBusStops.erase(iterator);
			return;
		}
	}
}

const vector<Bus_Stop>& Bus_StopsClass::getVecBusStops() const
{
	return vecBusStops;
}

// -- BUSES CLASS -- \\

bool Buses_Class::LoadFromFile(const string& argFilename)
{
	filename = argFilename;
	ifstream buses_file(filename);

	if (buses_file.fail())
	{
		buses_file.close();
		return false;
	}

	// Load lines
	string tempstr;
	while (getline(buses_file, tempstr)) {
		utilities::trimString(tempstr); 
		mapBusesIDs.insert(make_pair(tempstr, set<Shift>()));
	}
	buses_file.close();
	return true;
}

void Buses_Class::SaveToFile() const
{
	ofstream buses_file(filename);
	for (const auto& bus_pair : mapBusesIDs) {
		buses_file << bus_pair.first << endl;
	}
	buses_file.close();
}

void Buses_Class::PrintBuses() const
{
	cout << "  ";
	for (const auto& bus_pair : mapBusesIDs) {
		cout << bus_pair.first << endl;
	}
}

bool Buses_Class::InsertBus(const string & BusID)
{
	if (mapBusesIDs.insert(make_pair(BusID, set<Shift>())).second) { // element was inserted with success
		SaveToFile();
		return true;
	}
	return false;
}

bool Buses_Class::RemoveBus(const string & BusID)
{
	auto iterator = mapBusesIDs.find(BusID);
	if (iterator != mapBusesIDs.end()) {
		// Welp, first we will have to delete the corresponding shifts from the other classes..
		for (auto shift : iterator->second) {
			Drivers.RemoveShiftFromDriver(shift.GetDriverID(), shift);
		}
		Shifts_Interface.RemoveBus_Shifts(BusID);

		mapBusesIDs.erase(iterator);
		SaveToFile();
		return true;
	}
	return false;
}

const set<Shift>& Buses_Class::GetShifts(const string & BusID) const
{
	auto iterator = mapBusesIDs.find(BusID);
	if (iterator != mapBusesIDs.end()) {
		return iterator->second;
	}
	static auto emptySet = set<Shift>();
	return emptySet; // return empty set if the busID passed as argument isnt associated with a bus

}

bool Buses_Class::BusExists(const string & BusID)
{
	auto iterator = mapBusesIDs.find(BusID);
	if (iterator != mapBusesIDs.end()) {
		return true;
	}
	return false;
}

bool Buses_Class::CanAddShift(const string & BusID, const Shift& argShift) const
{
	auto iterator = mapBusesIDs.find(BusID);
	if (iterator != mapBusesIDs.end()) {
		for (const auto& bus_Shift : iterator->second) {
			if (bus_Shift.GetDay() == argShift.GetDay() && ( argShift.GetStartHour() >= bus_Shift.GetStartHour() && argShift.GetStartHour() < bus_Shift.GetEndHour()) ) {
				return false;
			}
		}
	}
	return true;
}

bool Buses_Class::CanAddShift(const set<Shift> & shiftSet, const Shift& argShift)
{
	for (const auto& bus_Shift : shiftSet) {
		if (bus_Shift.GetDay() == argShift.GetDay() && (argShift.GetStartHour() >= bus_Shift.GetStartHour() && argShift.GetStartHour() < bus_Shift.GetEndHour())) {
			return false;
		}
	}
	return true;
}

void Buses_Class::AddShift(const string & BusID, const Shift &argShift)
{
	auto iterator = mapBusesIDs.find(BusID);
	if (iterator != mapBusesIDs.end()) {
		iterator->second.insert(argShift);
	}
}

void Buses_Class::RemoveShift(const string & BusID, const Shift& argShift)
{
	auto iterator = mapBusesIDs.find(BusID);
	if (iterator != mapBusesIDs.end()) {
		auto iteratorToShift = iterator->second.find(argShift);
		if (iteratorToShift != iterator->second.end()) {
			iterator->second.erase(iteratorToShift);
		}
	}
}

void Buses_Class::RemoveShiftsByLineID(const string & LineID)
{
	for (auto mapIterator = mapBusesIDs.begin(); mapIterator != mapBusesIDs.end(); mapIterator++) {
		for (auto setShiftsIterator = mapIterator->second.begin(); setShiftsIterator != mapIterator->second.end(); setShiftsIterator++) {
			if (setShiftsIterator->GetLineID() == LineID) {
				mapIterator->second.erase(setShiftsIterator);
			}
		}
	}
}

unsigned int Buses_Class::GetNumberOfBuses() const
{
	return mapBusesIDs.size();
}

void Buses_Class::ListBuses() const
{
	bool firstIteration = true;
	for (auto mapIterator = mapBusesIDs.begin(); mapIterator != mapBusesIDs.end(); mapIterator++) {
		if (firstIteration) {
			(firstIteration = false);
		}
		else (std::cout << ",");
		std::cout << " " << mapIterator->first;
	}
}

void Buses_Class::ShowServiceSchedule(const string & BusID, const set<Shift>& setShifts) const
{
	auto busIterator = mapBusesIDs.find(BusID);
	if (busIterator != mapBusesIDs.end()) {
		static string blankFiller = "                ";
		cout << blankFiller << string(60, '#') << endl;
		size_t nameLengthLeft = busIterator->first.length();
		size_t nameLengthRight = nameLengthLeft % 2 == 1 ? (nameLengthLeft + 1) : nameLengthLeft;
		cout << blankFiller << "#" << string(28 - nameLengthLeft / 2, '#') << " " + busIterator->first + " " << string(28 - nameLengthRight / 2, '#') << "#" << endl;
		cout << blankFiller << "############# 8:00                    20:00 ################" << endl;

		for (int i = 0; i < 7; i++) {
			DisplaySpecificDay(i, blankFiller, setShifts);
		}
		cout << blankFiller << string(60, '#') << endl;
		cout << blankFiller << "             A- Available | N- Not Available";

	}
}

void Buses_Class::DisplaySpecificDay(unsigned int day, const string & blankFiller, const set<Shift>& setShifts)
{
	const string dayName = utilities::DayNumberToString(day);
	unsigned int nrSpaces = 9 - dayName.length();

	cout << blankFiller << "# " + dayName + string(nrSpaces, ' ') + " | ";

	for (unsigned int i = 8; i < SCHEDULE_END; i++) {
		Shift tempShift(day, i, i + 1, "", "", "");
		if (CanAddShift(setShifts, tempShift)) {
			cout << "A";
		}
		else cout << "N";
		cout << " ";
	}

	cout << "################";
	cout << endl;
}

// -- SHIFTS_INTERFACE CLASS -- \\

bool Shifts_InterfaceClass::LoadFromFile(const string& argFilename)
{
	ifstream shifts_file(argFilename);
	filename = argFilename;

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
		InsertShift(newShift, false);
		
	}
	shifts_file.close();
	return true;

}

void Shifts_InterfaceClass::SaveToFile() const
{
	ofstream shifts_file(filename);
	if (shifts_file.fail())
	{
		shifts_file.close();
	}
	// Load lines
	for (const Shift& shift : setShifts) {
		shifts_file 
		<< shift.GetDay() << ","
		<< shift.GetStartHour() << ","
		<< shift.GetEndHour() << ","
		<< shift.GetDriverID() << ","
		<< shift.GetBusID() << ","
		<< shift.GetLineID() << endl;
	}
	shifts_file.close();
}


void Shifts_InterfaceClass::InsertShift(const Shift &argShift, bool saveToFile)
{
	setShifts.insert(argShift);
	// but we will also have to add the shift to the corresponding driver and bus..
	// first to the buses
	//Buses.AddShift(argShift.GetBusID(), argShift);
	// then to the moon... I mean, the corresponding driver;
	//Drivers.AddShiftToDriver(argShift.GetDriverID(), argShift);
	if(saveToFile) SaveToFile();
}

void Shifts_InterfaceClass::RemoveShift(const Shift& argShift)
{
	auto iterator = setShifts.find(argShift);
	if (iterator != setShifts.end()) {
		setShifts.erase(iterator);
	}
	// but we also have to remove the shift from the corresponding driver and bus object
	Buses.RemoveShift(argShift.GetBusID(), argShift);
	Drivers.RemoveShiftFromDriver(argShift.GetDriverID(), argShift);
	SaveToFile();
}

void Shifts_InterfaceClass::RemoveShiftByIndex(unsigned int Index)
{
	unsigned int x = 1;
	for (auto iterator = setShifts.begin(); iterator != setShifts.end(); iterator++) {
		if (x == Index) {
			setShifts.erase(iterator); 
			Buses.RemoveShift(iterator->GetBusID(), *iterator);
			Drivers.RemoveShiftFromDriver(iterator->GetDriverID(), *iterator);
			SaveToFile();
		}
	}
}

void Shifts_InterfaceClass::RemoveLineShifts(const string & LineID)
{
	for (const Shift& shift : setShifts) {
		if (shift.GetLineID() == LineID) {
			RemoveShift(shift);
		}
	}
}

void Shifts_InterfaceClass::RemoveBus_Shifts(const string & BusID)
{
	for (const Shift& shift : setShifts) {
		if (shift.GetBusID() == BusID) {
			RemoveShift(shift);
		}
	}
}

const set<Shift> Shifts_InterfaceClass::GetShifts() const
{
	return setShifts;
}

// helper function... for some reason GetDriver is always returning nullptr when inside the following method.
// the compiler gods for sure are not pleased. remind me to sacrifice a sheep when starting my next project
Driver* FindMyDriver(const string& DriverName, vector<Driver>& vecDrivers) {
	for (auto& driver : vecDrivers) {
		if (driver.GetID() == DriverName) {
			return &driver;
		}
	}
	return nullptr;
}

void Shifts_InterfaceClass::ListShifts(const set<Shift> &setShifts, vector<Driver>& DriversVector, bool showIndexColumn)
{
	if (showIndexColumn) {
		unsigned int x = 1;
		cout << setw(2) << "" << "#" << "   " << setw(12) << left << "Day" << setw(15) << "Start Hour" << setw(15) << "End Hour" << setw(10) << "Line" << setw(30) << "Driver" << setw(10) << "Bus" << endl;
		for (const Shift &shift : setShifts) {
			Driver* driver = FindMyDriver(shift.GetDriverID(), DriversVector);
			string driverName = driver->GetName();
			string dayName = utilities::DayNumberToString(shift.GetDay());
			string startHour = to_string(shift.GetStartHour());
			string endHour = to_string(shift.GetEndHour());
			cout << setw(2) << "" << setw(4) << x << setw(12) << left << dayName << setw(15) << startHour + ":00" << setw(15) << endHour + ":00" << setw(10) << shift.GetLineID() << setw(30) << "[" + shift.GetDriverID() + "] " + driverName << setw(10) << shift.GetBusID() << endl;
			x++;
		}
		cout << right;
	}
	else {
		cout << setw(2) << "" << setw(12) << left << "Day" << setw(15) << "Start Hour" << setw(15) << "End Hour" << setw(10) << "Line" << setw(30) << "Driver" << setw(10) << "Bus" << endl;
		for (const Shift &shift : setShifts) {
			Driver* driver = FindMyDriver(shift.GetDriverID(), DriversVector);
			string driverName = driver->GetName();
			string dayName = utilities::DayNumberToString(shift.GetDay());
			string startHour = to_string(shift.GetStartHour());
			string endHour = to_string(shift.GetEndHour());
			cout << setw(2) << "" << setw(12) << left << dayName << setw(15) << startHour + ":00" << setw(15) << endHour + ":00" << setw(10) << shift.GetLineID() << setw(30) << "[" + shift.GetDriverID() + "] " + driverName << setw(10) << shift.GetBusID() << endl;
		}
		cout << right;
	}
}
