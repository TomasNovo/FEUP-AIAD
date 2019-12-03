//
// Created by Francisco Ferreira on 14/03/18.
//

#include "Company.h"

Company :: Company()
{
    this->name = " ";
}

Company :: Company(string name)
{
    this->name = name;
}

vector<Airplane*> Company :: getFleet()
{
    return this->fleet;
}
vector<RegisteredPassenger> Company :: getClientList()
{
    return this->clientList;
}
vector<Flight*> Company :: getFligthList()
{
    return this->flightList;
}

void Company :: addClient(RegisteredPassenger p)
{
    this->clientList.push_back(p);
}

void Company ::listClients()
{
    cout << endl << "|| ---------------------------------------------------------- ||";
    cout << endl << "|| ----------------- RegisteredPassengers ------------------- ||";
    cout << endl << "|| ---------------------------------------------------------- ||" << endl;

    for (int i = 0; i < clientList.size(); i++)
    {
        cout << i + 1 << " - " << clientList[i].getName() << ": ";
        cout << clientList[i].getJob() << " | " << dateToString(clientList[i].getDateOfBirth()) << " | " << clientList[i].getAverageNFlights() << endl;
    }
}

void Company ::addAirplane(Airplane *a) {
    this->fleet.push_back(a);
}

void Company ::listAirplanes() {

    cout << endl << "|| ---------------------------------------------------------- ||";
    cout << endl << "|| ------------------------- Fleet -------------------------- ||";
    cout << endl << "|| ---------------------------------------------------------- ||" << endl;

    for (int i = 0; i < fleet.size(); i++)
    {
        cout << i + 1 << " - " << fleet[i]->getType() << ": ";
        cout << fleet[i]->getCapacity() << " | " << fleet[i]->getNormalPrice() << " | " << fleet[i]->getSpeed() << endl;
    }
}

void Company ::addFlight(Flight * f) {
    this->flightList.push_back(f);
}

void Company ::listFlights() {

    cout << endl << "|| ---------------------------------------------------------- ||";
    cout << endl << "|| ---------------------- Flight List ----------------------- ||";
    cout << endl << "|| ---------------------------------------------------------- ||" << endl;

    for (int i = 0; i < flightList.size(); i++)
    {
        cout << i + 1 << " - " << flightList[i]->getAirplane()->getType() << ": ";
        for (int j = 0; j < flightList[i]->getPassengerList().size(); j++){
            if (j != (flightList[i]->getPassengerList().size() - 1))
                cout << flightList[i]->getPassengerList()[j].getName() << ",";
            else
                cout << flightList[i]->getPassengerList()[j].getName();
        }
        cout << " | " << dateToString(flightList[i]->getArrivalDate()) << " | " << dateToString(flightList[i]->getDepartureDate());
        cout << " | " << locationToString(flightList[i]->getArrivalLocation()) << " | " << locationToString(flightList[i]->getDepartureLocation()) << endl;
    }
}