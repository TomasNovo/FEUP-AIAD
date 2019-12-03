//
// Created by Francisco Ferreira on 14/03/18.
//

#include "Passenger.h"

Passenger ::Passenger() {}

Passenger :: Passenger(string name)
{
    this->name = name;
    this->type = " ";
}

string Passenger :: getName()
{
    return this->name;
}

string Passenger ::getType()
{
    return this->type;
}

void Passenger ::setName(string name)
{
    this->name = name;
}

void Passenger ::setType(string type)
{
    this->type = type;
}