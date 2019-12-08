#pragma once

#include <iostream>
#include <string>
#include <vector>



using namespace std;

class Line{
 private:
  unsigned int id;
  unsigned int freq;
  unsigned int numberOfBuses;
  vector<string> busStopList;
  vector<unsigned int> timesList;
 public:
	 Line();
  Line(string textLine);
  // methds get
  unsigned int getId() const;
  unsigned int getFreq() const;
  unsigned int getNumberOfBuses() const;
  vector<string> getBusStops() const;
  vector<unsigned int> getTimes() const;
  // set methods
  void setId(unsigned int newId);
  void setFreq(unsigned int newFreq);
  void setBusStops(vector<string> newBusStops);
  void setTimesList(vector<unsigned int> newTimesList);
  void getNumberOfBuses(unsigned int newNumber);
  // other methods

};
