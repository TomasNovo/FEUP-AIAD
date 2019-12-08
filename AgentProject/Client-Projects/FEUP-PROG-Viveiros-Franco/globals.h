#ifndef __GLOBALS_INCLUDED__
#define __GLOBALS_INCLUDED__

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <set>
#include <map>
#include <sstream>
#include "driver.h"
#include "bus_stop.h"
#include "shift.h"
#include "utilities.h"
#include "line.h"

// The compiler was throwing a tantrum... Seems like the only way to please its desires is to re-declare this classes here despite the corresponding
// header file being included just above. 
class Line;
class Bus_Stop;
class Driver;

#define SCHEDULE_START 8
#define SCHEDULE_END 23

using namespace std;

class LinesClass {
	public:
		void AddBusLine(const Line&);
		bool RemoveBusLine(const Line&);
		bool RemoveBusLineByID(const string&);

		bool LoadFromFile(const string&);
		void SaveToFile() const;

		void PrintLinesNames() const;
		bool LineExists(const string&) const;
		int SearchLine(const string&) const;
		Line* FindLine(const string&);
		vector<Line>& GetLines(); // cant be const because some methods from other classes only work with non const vectors
	private:
		string filename;
		vector<Line> lines;

};

class DriversClass {
	public:
		void AddDriver(const Driver&);
		bool RemoveDriver(const Driver&);
		bool RemoveDriverByID(const string&);

		//int CanAddShiftToDriver(const string& DriverID, const Shift&);
		void AddShiftToDriver(const string& DriverID, const Shift&);
		void RemoveShiftFromDriver(const string& DriverID, const Shift&);
		void RemoveAllShiftsWithLineID(const string& LineID);

		bool LoadFromFile(const string&);
		void SaveToFile() const;

		void PrintLinesNames() const;
		void ListDrivers() const;	
		bool DriverExists(const string&) const;
		int SearchDriver(const string&) const;
		void ListAvailableDrivers(const set<Shift>& setShifts) const;

		Driver* FindDriver(const string& DriverID); // returns a pointer to the specified driver or nullptr if it doesnt exist
		vector<Driver>& GetDrivers(); // removed const qualifier because the compiler gods were not pleased.
	private:
		string filename;
		vector<Driver> drivers;
};

class Bus_StopsClass {
	// esta classe tem que ser seriamente repensada e re-escrita. OK FEITO
	public:
		void AddLineToBusStop(Line* ptr_Line, const string& Bus_Stop_Name);
		//void RemoveLineFromBusStop(Line* ptr_Line, const string& Bus_Stop_Name);
		//void RemoveLineFromALLBus_Stops(Line* ptr_Line);
		Bus_Stop* FindBus_StopByName(const string&); // returns a pointer to the specified bus stop or nullptr if it doesnt exist
		void PrintAllBus_Stops_Names() const;
		void RebuildBus_Stops(vector<Line>&);
		void RemoveBusStop(const string&);
		const vector<Bus_Stop>& getVecBusStops() const;
		//static void PrintTripBetweenBus_Stops(Bus_Stop* bus_stop1, Bus_Stop* bus_stop2); // had to move it back to ui.cpp because it was throwing runtime exceptions with no valuable information
	private:
		vector<Bus_Stop> vecBusStops;
};

class Buses_Class {
	public:
		bool LoadFromFile(const string&);
		void SaveToFile() const;
		void PrintBuses() const;
		bool InsertBus(const string& BusID); // These 2 methods will return false when the bus specified isnt valid
		bool RemoveBus(const string& BusID);
		const set<Shift>& GetShifts(const string& BusID) const;
		bool BusExists(const string& BusID);
		bool CanAddShift(const string& BusID, const Shift&) const;
		static bool CanAddShift(const set<Shift> & shiftSet, const Shift& argShift);
		void AddShift(const string& BusID, const Shift&);
		void RemoveShift(const string& BusID, const Shift&);
		void RemoveShiftsByLineID(const string& LineID);
		unsigned int GetNumberOfBuses() const;
		void ListBuses() const;
		void ShowServiceSchedule(const string& BusID, const set<Shift>&) const;
	private:
		string filename;
		map<string, set<Shift> > mapBusesIDs;
		static void DisplaySpecificDay(unsigned int day, const string& spacer, const set<Shift>&);
};

class Shifts_InterfaceClass {
	public:
		bool LoadFromFile(const string&);
		void SaveToFile() const;
		void InsertShift(const Shift&, bool saveToFile = true);
		const set<Shift> GetShifts() const;
		static void ListShifts(const set<Shift>&, vector<Driver>& DriverVector, bool showIndexColumn = false);
		void RemoveShift(const Shift&);
		void RemoveShiftByIndex(unsigned int Index);
		void RemoveLineShifts(const string& LineID);
		void RemoveBus_Shifts(const string& BusID);
	private:
		set<Shift> setShifts;
		string filename = "turnos.txt";
};

static LinesClass	 Lines;
static DriversClass	 Drivers;
static Bus_StopsClass	Bus_Stops;
static Buses_Class Buses;
static Shifts_InterfaceClass Shifts_Interface;

#endif