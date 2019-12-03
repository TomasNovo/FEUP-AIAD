//
// Created by Francisco Ferreira on 14/03/18.
//

#ifndef PLANERESERVATION_CONCORDE_H
#define PLANERESERVATION_CONCORDE_H

#include <iostream>
#include "Airplane.h"

using namespace std;

class Concorde: public Airplane
{
private:
    string type;
    int capacity;
    int normalPrice;
    int speed;
public:
    Concorde();
    Concorde(string type, int capacity, int normalPrice, int speed);
    string getType();
    int getCapacity();
    int getNormalPrice();
    int getSpeed();
    void setType(string type);

};

#endif //PLANERESERVATION_CONCORDE_H
