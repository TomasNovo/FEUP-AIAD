//
// Created by Francisco Ferreira on 14/03/18.
//

#include "NormalPassenger.h"

NormalPassenger :: NormalPassenger(string name)
{
    this->name = name;
    this->type = "normal";
}

string NormalPassenger :: getName()
{
    return this->name;
}

string NormalPassenger ::getType()
{
    return this->type;
}