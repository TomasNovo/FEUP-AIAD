//
// Created by Francisco Ferreira on 14/03/18.
//

#include "Flight.h"

Flight ::Flight() {
    this->airplane = new Airplane();
    this->arrivalLocation = Location();
    this->arrivalDate = Date();
    this->departureLocation = Location();
    this->departureDate = Date();
}

Flight :: Flight(Airplane *airplane, Date departureDate, Date arrivalDate, Location departureLocation, Location arrivalLocation)
{
    this->airplane = airplane;
    this->departureDate = departureDate;
    this->arrivalDate = arrivalDate;
    this->departureLocation = departureLocation;
    this->arrivalLocation = arrivalLocation;
}
Airplane * Flight :: getAirplane()
{
    return this->airplane;
}

Date Flight :: getDepartureDate()
{
    return this->departureDate;
}
Date Flight :: getArrivalDate()
{
    return this->arrivalDate;
}
Location Flight :: getDepartureLocation()
{
    return this->departureLocation;
}
Location Flight :: getArrivalLocation()
{
    return this->arrivalLocation;
}

//---------------------------------------------------//

void Flight ::setAirplane(Airplane * a) {
    this->airplane = a;
}

void Flight ::setArrivalDate(Date arrivalDate) {
    this->arrivalDate = arrivalDate;
}

void Flight ::setArrivalLocation(Location arrivalLocation) {
    this->arrivalLocation = arrivalLocation;
}

void Flight ::setDepartureDate(Date departureDate) {
    this->departureDate = departureDate;
}

void Flight ::setDepartureLocation(Location departureLocation) {
    this->departureLocation = departureLocation;
}
