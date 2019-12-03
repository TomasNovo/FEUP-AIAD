#ifndef __SHIFT_INCLUDED__
#define __SHIFT_INCLUDED__

#include <string>

using namespace std;

class Shift {
	public:
		unsigned int GetDay() const;
		unsigned int GetStartHour() const;
		unsigned int GetEndHour() const;
		unsigned int GetDuration() const;
		const string& GetDriverID() const;
		const string& GetBusID() const;
		const string& GetLineID() const;

		void SetDay(const unsigned int&);
		void SetStartHour(const unsigned int&);
		void SetEndHour(const unsigned int&);
		void SetDriverID(const string&);
		void SetBusID(const string&);
		void SetLineID(const string&);
		// Construtor:
		Shift(unsigned int day, unsigned int startHour, unsigned int endHour, const string& DriverID, const string& BusID, const string& LineID);
		Shift();
		// "less than" operator overload. Used to order the intern set container of Shifts_Interface
		// Set order is defined by cronological order of the shifts.
		friend bool operator<(const Shift&, const Shift&);
	private:
		unsigned int day;
		unsigned int startHour;
		unsigned int endHour;
		string driverID;
		string busID;
		string lineID;
};


#endif