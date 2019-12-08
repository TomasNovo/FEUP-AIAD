//
// Created by Francisco Ferreira on 17/03/18.
//

#ifndef PLANERESERVATION_RENTEDFLIGHT_H
#define PLANERESERVATION_RENTEDFLIGHT_H

#include "Flight.h"

class RentedFlight : public Flight{
private:
    vector<Passenger> passengerList;
public:
    RentedFlight();
    RentedFlight(Airplane * airplane, Date departureDate, Date arrivalDate, Location departureLocation, Location arrivalLocation, vector<Passenger> passengerList);
    vector<Passenger> getPassengerList();
    void setPassengerList(vector<Passenger> passengerList);

};

#endif //PLANERESERVATION_RENTEDFLIGHT_H
