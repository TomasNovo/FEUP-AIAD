#ifndef BUS_H
#define BUS_H

#include <iostream>
#include <vector>
#include "Shift.h"


using namespace std;

class Bus
{
 private:
  unsigned int orderInLine;
  unsigned int driverId;
  unsigned int lineId;
  vector<Shift> schedule;
 public:
  Bus(unsigned int order, unsigned int driver, unsigned int line);
  // get methods
  unsigned int getBusOrderInLine() const;
  unsigned int getDriverId() const;
  unsigned int getLineId() const;
  vector<Shift> getSchedule() const;
  // set methods
  void setDriverId(unsigned int d_id);
  void setShifts(vector<Shift> vs);
  void setLineId(unsigned int l_id);
  
  // other methods

  void AddShift(Shift new_shift);
  bool RemoveShift(unsigned int day_of_the_week, unsigned int shift_starting_time);
};

#endif