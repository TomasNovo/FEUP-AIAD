//
// Created by Francisco Ferreira on 14/03/18.
//

#ifndef PLANERESERVATION_AIRBUS_H
#define PLANERESERVATION_AIRBUS_H

#include <iostream>
#include "Airplane.h"

using namespace std;

class Airbus: public Airplane
{
private:
    string type;
    int capacity;
    int normalPrice;
    int speed;
public:
    Airbus();
    Airbus(string type, int capacity, int normalPrice, int speed);
    string getType();
    int getCapacity();
    int getNormalPrice();
    int getSpeed();
    void setType(string type);

};

#endif //PLANERESERVATION_AIRBUS_H
