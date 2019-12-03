#ifndef DRIVER_H
#define DRIVER_H

#include <iostream>
#include <string>
#include <vector>
#include "Shift.h"

using namespace std;

class Driver
{
 private:
  unsigned int id;
  string name;
  unsigned int maxHours;        // maximum number of working hours in a day
  unsigned int maxWeekWorkingTime;  // maximum number of hours of work in a week
  unsigned int minRestTime;     // minimum number of rest hours between shifts
  vector<Shift> shifts;         // assigned shifts
 public:
  Driver(string textLine);
  Driver(unsigned int id, string name, unsigned int day_lim, unsigned int w_lim, unsigned int r_min);
  // get methods
  unsigned int getId() const;
  string getName() const;
  unsigned int getShiftMaxDuration() const;
  unsigned int getMaxWeekWorkingTime() const;
  unsigned int getMinRestTime() const;
  vector<Shift> getShifts() const;

  // set methods
  void setID(unsigned int new_id);
  void setName(string name);
  void setMaxHours(unsigned int hours);
  void setMaxWeekHours(unsigned int hours);
  void setMinRestHours(unsigned int hours);
  void setShifts(vector<Shift> vs);

  // Other methods

  void AddShift(Shift shift);
  bool RemoveShift(unsigned int day_of_the_week, unsigned int shift_starting_time);
};

#endif