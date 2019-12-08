#ifndef LINE_H
#define LINE_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class Line
{
 private:
  unsigned int id, freq;
  vector<string> stops_vector;
  vector<int> times_vector;
 public:
  Line(string textLine);
  Line(int id, int freq, vector<string> stops_v, vector<int> times_v);

  // get methods

  unsigned int getId() const;
  unsigned int getFreq() const;
  vector<string> getBusStops() const;
  vector<int> getTimings() const;

  // set methods

  void SetID(unsigned int new_id);
  void SetFrequency(unsigned int new_freq);
  void SetStops(vector<string> New_Stops);
  void SetSchedule(vector<int> New_Schedule);

  // other functions

  unsigned int Calc_No_Busses() const;// Calculates the number of busses neede for a line
  void Show_Available_Start_Time(unsigned int day_start, unsigned int day_end) const; /*  Displays the hours at which is
																						   possible to start a shift */
};

#endif