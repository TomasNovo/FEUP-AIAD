#pragma once
#include <string>
#include "Shift.h"
#include "Line.h"
#include "Driver.h"
#include "Bus.h"
#include <utility>
#include "Constants.h"  //to get the initial and end times of a day

using namespace std;

class Company
{
public:
	Company();
	Company(string name, string LinesFile, string DriversFile, string ShiftsFile);
	string getName() const;
	string getLinesFile() const;
	string getDriversFile() const;
	string getShiftsFile() const;
	


	//=========================LINES=====================================
	void CreateVectorLines();

	void insertLines(Line line);

	void showAllLines() const;

	bool existsLines(int id) const;

	void newLine(int id, int freq, vector<string> busStops, vector <int> times_between_stops);

	void rewriteFileLines(string FileName);

	void removeLines(int id, ptrdiff_t j);

	vector <int> lines_used_ids();

	Line& getLinhaById(int ID);

	vector <int> getLinhaWithStop(string stop) const;

	vector <pair<string, vector<int>>> getTimesLineForward(int id, int minuto_inicial_global, int minuto_final_global);

	vector <pair<string, vector<int>>> getTimesLineBackward(int id, int minuto_inicial_global, int minuto_final_global);

	vector <pair<int, vector<int>>> getTimesStopForward(string Stop, int minuto_inicial_global, int minuto_final_global);

	vector <pair<int, vector<int>>> getTimesStopBackward(string Stop, int minuto_inicial_global, int minuto_final_global);

	vector <int> getLinhaWithBothStops(string Stop1, string Stop2);

	vector <pair<int, int>> getTimeBetweenStops(string Stop1, string Stop2);

	vector <pair <int, vector <string>>> getPathBetweenStops(string Stop1, string Stop2);



	//=======================DRIVERS========================

	void CreateVectorDrivers();

	void insertDrivers(Driver one_driver);

	void showAllDrivers() const;

	bool existsDrivers(int id) const;

	void removeDrivers(int id, ptrdiff_t j);

	void newCondutor(int id, string name, int maxDayWorkingTime, int maxWeekWorkingTime, int minRestTime);

	void rewriteFileDrivers(string FIleName);

	vector<int> drivers_used_ids();

	Driver& getDriverById(int id);

	Driver& getDriverByName(string name);

	bool addNewShiftToDriver(int day, int id, int line, int startTime);

	bool removeWorkFromDriver(int day, int id, int line, int startTime);

	vector <Driver *> getDriversWithSpareTime();

	
	//==============================SHIFTS======================

	void CreateVectorAllShifts();

	Shift * getShift(int day, int line, int startTime);

	void displayAllShifts();

	vector<Shift> Shifts_of_a_Line(int id);

	//Pointer to all the line shifts in a specific day
	vector <Shift *> Pointers_To_Line_Shifts(int id, int day);

	
	vector < pair <int, vector <Shift> >> All_Shifts_inUse();

	//Pointers to all the line shifts being used in a specific day
	vector <Shift * > Line_Shifts_Use(int id, int day);

	void ReadShiftsFromFile(string one_shift);

	void rewriteFileShifts(string FileName);

	vector <pair < int, vector <int >> > BusWithoutDriver(int day);

	//==============================BUS=========================


private:
	string name;

	string LinesFile;

	string DriversFile;

	string ShiftsFile;

	vector <pair <int, vector <Shift> >> All_Shifts; //the int goes from 0 to 6, representing the days of the week

	vector<Line> Lines;

	vector <Driver> Drivers;
};

