#ifndef __LINE_INCLUDED__
#define __LINE_INCLUDED__

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
//#include "bus_stop.h"
#include "utilities.h"
#include "globals.h"

using namespace std;

class Line {
	public:
		void ShowSchedule() const;
		void SetID(const string&);
		void SetFreq(const unsigned int&);
		void SetBus_Stops(const vector<string>&);
		void SetTimeBetweenStops(const vector<unsigned int>&);

		string GetID() const;
		unsigned int GetFreq() const;
		const vector<string>& GetBus_Stops() const;
		vector<unsigned int> GetTimeBetweenStops() const;


	private:
		static void PrintSpecificSchedule(const vector<string>& bus_stops, const vector<unsigned int>& timeBetweenStops, unsigned int freq, unsigned int offset);
		static int CalculateOffset(const vector<unsigned int> timeBetweenStops, const unsigned int &Bus_Stop_Number);
		string ID;
		unsigned int freq;
		vector<string> bus_stops;
		vector<unsigned int> timeBetweenStops;

};


#endif