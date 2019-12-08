//
// Created by Francisco Ferreira on 14/03/18.
//

#ifndef PLANERESERVATION_PASSENGER_H
#define PLANERESERVATION_PASSENGER_H

#include <iostream>
using namespace std;

class Passenger
{
private:
    string name;
    string type;
public:
    Passenger();
    Passenger(string name);
    string getName();
    string getType();
    void setName(string name);
    void setType(string type); // Caso algum passageiro queira mudar

};

#endif //PLANERESERVATION_PASSENGER_H
