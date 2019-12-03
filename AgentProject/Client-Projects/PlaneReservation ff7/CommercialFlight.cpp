//
// Created by Francisco Ferreira on 17/03/18.
//

#include "CommercialFlight.h"

CommercialFlight ::CommercialFlight() {
    Flight();
    vector<Passenger> v = {};
    this->passengerList = v;
}

CommercialFlight ::CommercialFlight(Airplane * airplane, Date departureDate, Date arrivalDate, Location departureLocation,
                                    Location arrivalLocation, vector<Passenger> passengerList) {
    Flight(airplane, departureDate, arrivalDate, departureLocation, arrivalLocation);
    this->passengerList = passengerList;
}

vector<Passenger> CommercialFlight ::getPassengerList() {
    return this->passengerList;
}

void CommercialFlight ::setPassengerList(vector<Passenger> passengerList) {
    this->passengerList = passengerList;
}