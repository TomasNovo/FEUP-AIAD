//
// Created by Francisco Ferreira on 14/03/18.
//

#ifndef PLANERESERVATION_DATE_H
#define PLANERESERVATION_DATE_H

#include <iostream>

using namespace std;

class Date
{
private:
    int day;
    int month;
    int year;
public:
    Date();
    Date(int day, int month, int year);
    int getDay();
    int getMonth();
    int getYear();
};

#endif //PLANERESERVATION_DATE_H
