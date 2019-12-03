//
// Created by Francisco Ferreira on 17/03/18.
//

#ifndef PLANERESERVATION_COMMERCIALFLIGHT_H
#define PLANERESERVATION_COMMERCIALFLIGHT_H

#include "Flight.h"

class CommercialFlight : public Flight{
private:
    vector<Passenger> passengerList;
public:
    CommercialFlight();
    CommercialFlight(Airplane * airplane, Date departureDate, Date arrivalDate, Location departureLocation, Location arrivalLocation, vector<Passenger> passengerList);
    vector<Passenger> getPassengerList();
    void setPassengerList(vector<Passenger> passengerList);

};

#endif //PLANERESERVATION_COMMERCIALFLIGHT_H
