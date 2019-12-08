//
// Created by Francisco Ferreira on 15/03/18.
//

#ifndef PLANERESERVATION_UTILITIES_H
#define PLANERESERVATION_UTILITIES_H

#include <iostream>
#include "Date.h"
#include "Location.h"
#include "Passenger.h"
#include "Airplane.h"
#include "Airbus.h"
#include "Boeing.h"
#include "Concorde.h"
#include <string>
#include <vector>

using namespace std;

Location stringToLocation(string s);
Date stringToDate(string s);
int stringToInt(string s);
vector<Passenger> stringToPassengerVector(string s);
Airplane * stringToAirplane(string s);
string dateToString(Date d);
string locationToString(Location l);
string intToString(int i);

#endif //PLANERESERVATION_UTILITIES_H
