//
// Created by Francisco Ferreira on 17/03/18.
//

#include "RentedFlight.h"

RentedFlight :: RentedFlight()
{
    Flight();
    vector<Passenger> v = {};
    this->passengerList = v;
}

RentedFlight ::RentedFlight(Airplane * airplane, Date departureDate, Date arrivalDate, Location departureLocation,
                                    Location arrivalLocation, vector<Passenger> passengerList) {
    Flight(airplane, departureDate, arrivalDate, departureLocation, arrivalLocation);
    this->passengerList = passengerList;
}

vector<Passenger> RentedFlight ::getPassengerList() {
    return this->passengerList;
}

void RentedFlight ::setPassengerList(vector<Passenger> passengerList) {
    this->passengerList = passengerList;
}