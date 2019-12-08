//
// Created by Francisco Ferreira on 14/03/18.
//

#include "Location.h"

Location ::Location() {}

Location ::Location(string country, string city)
{
    this->country = country;
    this->city = city;
}

string Location ::getCountry()
{
    return this->country;
}

string Location ::getCity()
{
    return this->city;
}