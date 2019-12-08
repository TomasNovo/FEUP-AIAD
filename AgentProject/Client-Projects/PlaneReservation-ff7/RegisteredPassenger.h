//
// Created by Francisco Ferreira on 14/03/18.
//

#ifndef PLANERESERVATION_REGISTEREDPASSENGER_H
#define PLANERESERVATION_REGISTEREDPASSENGER_H

#include <iostream>
#include "Passenger.h"
#include "Date.h"

using namespace std;

class RegisteredPassenger: public Passenger
{
private:
    string type;
    string name;
    string job;
    Date dateOfBirth;
    double averageNFlights; // Average number of flights per year
public:
    RegisteredPassenger(string name, string job, Date dateOfBirth, double averageNFlights);
    string getType();
    string getName();
    string getJob();
    Date getDateOfBirth();
    double getAverageNFlights();
    void setJob(string job);
    void setDateOfBirth(Date dateOfBirth);
    void setAverageNFlights(int n);


};

#endif //PLANERESERVATION_REGISTEREDPASSENGER_H
