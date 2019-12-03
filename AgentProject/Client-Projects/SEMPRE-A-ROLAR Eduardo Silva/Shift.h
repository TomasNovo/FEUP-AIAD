#ifndef SHIFT_H
#define SHIFT_H

#include <iostream>
#include <vector>

using namespace std;

class Shift
{
 private:
  unsigned int busLineId;
  unsigned int driverId;  
  unsigned int busOrderNumber; 
  unsigned int startTime; 
  unsigned int endTime;   
  unsigned int day_of_the_week;

 public:
	 Shift(unsigned int linha, unsigned int condutor, unsigned int autocarro, unsigned day_of_the_week, unsigned int inicio,
		 unsigned int fim);
  // get methdos
  unsigned int getBusLineId() const;
  unsigned int getDriverId() const;
  unsigned int getBusOrderNumber() const; // order of the bus within the bus line
  unsigned int getStartTime() const;
  unsigned int getEndTime() const;
  unsigned int getWeekDay() const;

  //  set methods
 void setBusLineId(unsigned int);
 void setDriverId(unsigned int);
 void setBusOrderNumber(unsigned int);
 void setStartTime(unsigned int);
 void setEndTime(unsigned int);
 void setWeekDay(unsigned int);

};

#endif