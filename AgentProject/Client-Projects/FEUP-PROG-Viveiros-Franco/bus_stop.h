#ifndef __BUS_STOP_INCLUDED__
#define __BUS_STOP_INCLUDED__

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include "line.h"
#include "globals.h"

using namespace std;

// Must re-declare classes so the compiler doesnt get upset
class Line;

class Bus_Stop {

	public:

		const string& GetName() const;
		unsigned int GetLinesCount() const;
		const vector< Line* >& GetLines() const;
		void RemoveLineFromStop(const Line*);
		void AddLine(Line*);

		void ShowSchedule() const; // falta implementar

		// Constructor:
		Bus_Stop(const string& argBus_StopName);

		static int GetBus_StopNumber(const vector<string> &vec_Bus_Stops, const string& Bus_Stop_Name);
		static int CalculateOffset(const vector<unsigned int> timeBetweenStops, const unsigned int &Bus_Stop_Number);

	private:
		static void PrintSpecificSchedule(const unsigned int &Start, const unsigned int &End, const unsigned int &offset, const unsigned int &freq);
		string name;
		vector<Line*> linesAtStop;

};

#endif