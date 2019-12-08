//
// Created by Francisco Ferreira on 14/03/18.
//

#include "Boeing.h"

Boeing :: Boeing(){
    this->type = " ";
    this->speed = 0;
    this->normalPrice = 0;
    this->capacity = 0;
}

Boeing :: Boeing(string type, Airplane a)
{
    this->type = type;
}

Boeing :: Boeing(string type, int capacity, int normalPrice, int speed)
{
    this->type = type;
}

int Boeing :: getCapacity()
{
    return this->capacity;
}

int Boeing :: getNormalPrice()
{
    return this->normalPrice;
}

int Boeing ::getSpeed()
{
    return this->speed;
}

string Boeing ::getType()
{
    return this->type;
}

void Boeing :: setType(string type){
    this->type = type;
}

