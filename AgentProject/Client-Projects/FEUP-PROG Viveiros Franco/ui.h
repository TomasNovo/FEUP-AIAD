#ifndef __UI_INCLUDED__
#define __UI_INCLUDED__

#include <string>
#include <fstream>
#include <cctype>
#include "utilities.h"
#include "ui_utilities.h"
#include "globals.h"

using namespace std;

class ui{

public:
	void StartMenu();
	bool StartMenu(const string&);
	bool StartMenu(const int&, const int&, const string&);

	bool SetConsoleWidth(const unsigned int&);
	bool SetConsoleHeight(const unsigned int&);
	bool SetBannerFilename(const string&);

	unsigned int GetConsoleWidth();
	unsigned int GetConsoleHeight();
	string GetBannerFilename();

	void PrintBanner();

private:
	unsigned int ConsoleWidth = 150;
	unsigned int ConsoleHeight = 40;

	string bannerfilename = "asciibanner.txt";

	void PreMenu();
	void MainMenu();

	void LineManagementMenu();
	void CreateLineMenu();
	void EditLineMenu();
	void RemoveLineMenu();

	void DriverManagementMenu();
	void CreateDriverMenu();
	void EditDriverMenu();
	void ListDriversMenu();
	void ListDriverShiftsMenu();
	void RemoveDriverMenu();

	void BusManagementMenu();
	void CreateBusMenu();
	void ListBusesMenu();
	void ListBusShiftsMenu();
	void RemoveBusMenu();

	void ShiftManagementMenu();
	void CreateShiftMenu();
	void RemoveShiftMenu();
	void VisualizeDriverWorkScheduleMenu();
	void ListAvailableDriversMenu();
	void ListAllShiftsMenu();
	void VisualizeBusServiceScheduleMenu();

	void FindShortestTrip();

	void SchedulesMenu();
	void ViewLineScheduleMenu();
	void ViewBus_StopScheduleMenu();

	void FindBusLineByBusStop();


};

#endif