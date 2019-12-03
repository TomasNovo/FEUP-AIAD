//
// Created by Francisco Ferreira on 14/03/18.
//

#include "RegisteredPassenger.h"

RegisteredPassenger :: RegisteredPassenger(string name, string job, Date dateOfBirth, double averageNFlights)
{
    this->name = name;
    this->type = "registered";
    this->job = job;
    this->dateOfBirth = dateOfBirth;
    this->averageNFlights = averageNFlights;
}

string RegisteredPassenger :: getName()
{
    return this->name;
}

string RegisteredPassenger ::getType()
{
    return this->type;
}

string RegisteredPassenger :: getJob()
{
    return this->job;
}

Date RegisteredPassenger ::getDateOfBirth()
{
    return this->dateOfBirth;
}

double RegisteredPassenger ::getAverageNFlights()
{
    return this->averageNFlights;
}

void RegisteredPassenger ::setDateOfBirth(Date dateOfBirth)
{
    this->dateOfBirth = dateOfBirth;
}

void RegisteredPassenger ::setJob(string job)
{
    this->job = job;
}

void RegisteredPassenger ::setAverageNFlights(int n) {
    this->averageNFlights = n;
}