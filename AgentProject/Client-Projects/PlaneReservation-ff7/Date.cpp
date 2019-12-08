//
// Created by Francisco Ferreira on 14/03/18.
//

#include "Date.h"

Date :: Date(){}

Date ::Date(int day, int month, int year)
{
    this->day = day;
    this->month = month;
    this->year = year;
}

int Date ::getDay()
{
    return this->day;
}

int Date ::getMonth()
{
    return this->month;
}

int Date ::getYear()
{
    return this->year;
}