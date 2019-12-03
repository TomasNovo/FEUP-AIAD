//
// Created by Francisco Ferreira on 14/03/18.
//

#include "Airplane.h"

Airplane ::Airplane() {
    this->speed = 0;
    this->normalPrice = 0;
    this->capacity = 0;
}

Airplane :: Airplane(int capacity, int normalPrice, int speed)
{
    this->capacity = capacity;
    this->normalPrice = normalPrice;
    this->speed = speed;
}

int Airplane :: getCapacity()
{
    return this->capacity;
}

int Airplane :: getNormalPrice()
{
    return this->normalPrice;
}

int Airplane ::getSpeed()
{
    return this->speed;
}

string Airplane ::getType()
{
    return this->type;
}

void Airplane ::setCapacity(int capacity) {
    this->capacity = capacity;
}

void Airplane ::setNormalPrice(int normalPrice) {
    this->normalPrice = normalPrice;
}

void Airplane ::setSpeed(int speed) {
    this->speed = speed;
}