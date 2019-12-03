//
// Created by Francisco Ferreira on 14/03/18.
//

#ifndef PLANERESERVATION_AIRPLANE_H
#define PLANERESERVATION_AIRPLANE_H

#include <iostream>

using namespace std;

class Airplane
{
private:
    string type;
    int capacity;
    int normalPrice;
    int speed;
public:
    Airplane();
    Airplane(int capacity, int normalPrice, int speed);
    virtual string getType();
    int getCapacity();
    int getNormalPrice();
    int getSpeed();
    void setCapacity(int capacity);
    void setNormalPrice(int normalPrice);
    void setSpeed(int speed);
    virtual void setType(string type){};
};

#endif //PLANERESERVATION_AIRPLANE_H
