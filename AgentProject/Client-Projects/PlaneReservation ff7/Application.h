//
// Created by Francisco Ferreira on 14/03/18.
//

#ifndef PLANERESERVATION_APPLICATION_H
#define PLANERESERVATION_APPLICATION_H

#include <iostream>
#include <fstream>
#include <vector>
#include "Passenger.h"
#include "RegisteredPassenger.h"
#include "Company.h"
#include "Utilities.h"
#include "Date.h"

using namespace std;

class Application
{
private:
    Company company;
public:
    Application();
    void startApp();
    // Loading Passengers
    void loadRegisteredPassengers(string path);
    void treatPassengerInfo(vector<string> passengerInfo);
    RegisteredPassenger createClient(string s);
    // Loading airplanes
    void loadAirplanes(string path);
    void treatAirplaneInfo(vector<string> airplaneInfo);
    Airplane *createAirplane(string s);
    // Loading Flights
    void loadFlights(string path);
    void treatFlightInfo(vector<string> flightInfo);
    Flight *createFlight(string s);
    //
    void addClient();
    void addAirplane();
    void addFlight();
    //
    void saveRegisteredPassengers();
    void saveAirplanes();
    void saveFlights();


};

#endif //PLANERESERVATION_APPLICATION_H
