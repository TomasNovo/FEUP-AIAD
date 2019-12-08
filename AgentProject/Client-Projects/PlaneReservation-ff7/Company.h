//
// Created by Francisco Ferreira on 14/03/18.
//

#ifndef PLANERESERVATION_COMPANY_H
#define PLANERESERVATION_COMPANY_H

#include <iostream>
#include <vector>

#include "Flight.h"
#include "CommercialFlight.h"
#include "RentedFlight.h"
#include "Airplane.h"
#include "Boeing.h"
#include "Concorde.h"
#include "Passenger.h"
#include "RegisteredPassenger.h"
#include "Utilities.h"

class Company
{
private:
    string name;
    vector<Airplane *> fleet;
    vector<RegisteredPassenger> clientList;
    vector<Flight*> flightList;
public:
    Company();
    Company(string name);
    vector<Airplane*> getFleet();
    vector<RegisteredPassenger> getClientList();
    vector<Flight*> getFligthList();
    void addClient(RegisteredPassenger p);
    void listClients();
    void addAirplane(Airplane *a);
    void listAirplanes();
    void addFlight(Flight * f);
    void listFlights();


};

#endif //PLANERESERVATION_COMPANY_H
