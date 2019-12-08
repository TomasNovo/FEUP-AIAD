//
// Created by Francisco Ferreira on 14/03/18.
//

#include "Airbus.h"

Airbus :: Airbus(){
    this->type = " ";
    this->speed = 0;
    this->normalPrice = 0;
    this->capacity = 0;
}

Airbus :: Airbus(string type, int capacity, int normalPrice, int speed)
{
    this->capacity = capacity;
    this->normalPrice = normalPrice;
    this->speed = speed;
    this->type = type;
}

int Airbus :: getCapacity()
{
    return this->capacity;
}

int Airbus :: getNormalPrice()
{
    return this->normalPrice;
}

int Airbus ::getSpeed()
{
    return this->speed;
}

string Airbus ::getType()
{
    return this->type;
}

void Airbus :: setType(string type){
    this->type = type;
}
