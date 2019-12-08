#ifndef __BUS_INCLUDED__
#define __BUS_INCLUDED__

#include "line.h"
#include "driver.h"
#include "shift.h"

class Bus {
	public:
		bool AddShift(const Shift&); // estes 2 metodos parecem um bocado inuteis considerando o resto da arquitetura mas e' o que esta indicado no pdf
		const vector<Shift*>& GetShifts(); // 
		Line GetLine();
		Driver GetDriver();
		Bus(Line*, unsigned int orderNum, Driver*); // incompleto
	private:
		Line* line;
		unsigned int orderNum;
		Driver* driver;
		vector<Shift*> shifts;
};


#endif