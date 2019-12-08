//
// Created by Francisco Ferreira on 14/03/18.
//

#ifndef PLANERESERVATION_FLIGHT_H
#define PLANERESERVATION_FLIGHT_H

#include <iostream>
#include <vector>

#include "Airplane.h"
#include "Boeing.h"
#include "Concorde.h"
#include "Airbus.h"
#include "Passenger.h"
#include "RegisteredPassenger.h"
#include "NormalPassenger.h"
#include "Date.h"
#include "Location.h"

using namespace std;

class Flight
{
private:
    Airplane *airplane;
    Date departureDate;
    Date arrivalDate;
    Location departureLocation;
    Location arrivalLocation;
public:
    Flight();
    Flight(Airplane * airplane, Date departureDate, Date arrivalDate, Location departureLocation, Location arrivalLocation);
    //Gets
    Airplane* getAirplane();
    Date getDepartureDate();
    Date getArrivalDate();
    Location getDepartureLocation();
    Location getArrivalLocation();
    virtual vector<Passenger> getPassengerList(){vector<Passenger> v = {}; return v;};
    //Sets
    void setAirplane(Airplane * a);
    void setDepartureDate(Date departureDate);
    void setArrivalDate(Date arrivalDate);
    void setDepartureLocation(Location departureLocation);
    void setArrivalLocation(Location arrivalLocation);
    virtual void setPassengerList(vector<Passenger>){}

};
#endif //PLANERESERVATION_FLIGHT_H
