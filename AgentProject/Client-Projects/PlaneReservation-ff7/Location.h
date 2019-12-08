//
// Created by Francisco Ferreira on 14/03/18.
//

#ifndef PLANERESERVATION_LOCATION_H
#define PLANERESERVATION_LOCATION_H

#include <iostream>
using namespace std;

class Location
{
private:
    string city;
    string country;
public:
    Location();
    Location(string country, string city);
    string getCountry();
    string getCity();
};

#endif //PLANERESERVATION_LOCATION_H
