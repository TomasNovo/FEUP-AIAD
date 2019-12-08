//
// Created by Francisco Ferreira on 14/03/18.
//

#ifndef PLANERESERVATION_NORMALPASSENGER_H
#define PLANERESERVATION_NORMALPASSENGER_H

#include <iostream>
#include "Passenger.h"

using namespace std;

class NormalPassenger: public Passenger
{
private:
    string name;
    string type;
public:
    NormalPassenger(string name);
    string getType();
    string getName();
};

#endif //PLANERESERVATION_NORMALPASSENGER_H
