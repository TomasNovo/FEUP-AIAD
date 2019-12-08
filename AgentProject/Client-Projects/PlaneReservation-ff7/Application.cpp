//
// Created by Francisco Ferreira on 14/03/18.
//

#include "Application.h"

Application ::Application()
{
    this->company = Company("AirRoyal");
}

void Application ::startApp()
{
    loadRegisteredPassengers("/Users/ff/CLionProjects/PlaneReservation/res/RegisteredPassengers.txt");
    loadAirplanes("/Users/ff/CLionProjects/PlaneReservation/res/Airplanes.txt");
    loadFlights("/Users/ff/CLionProjects/PlaneReservation/res/Flights.txt");
    this->company.listFlights();
    //this->company.listAirplanes();
    //this->company.listFlights();
    //addClient();
    addFlight();
    this->company.listFlights();
    //saveRegisteredPassengers();
}

// Loading Passengers

void Application ::loadRegisteredPassengers(string path)
{
    ifstream buffer;
    buffer.open(path);

    string info;
    vector<string> passengerData;

    while(!buffer.eof())
    {
        getline(buffer, info);
        passengerData.push_back(info);
    }
    treatPassengerInfo(passengerData);

    buffer.close();

}

void Application ::treatPassengerInfo(vector<string> passengerInfo)
{
    for (int i = 0; i < passengerInfo.size(); i++)
    {
        this->company.addClient(createClient(passengerInfo[i]));
    }
}


RegisteredPassenger Application :: createClient(string s)
{
    string name, job, date, average;
    vector<string> v = {name, job, date, average};
    int count = 0;

    string :: iterator it = s.begin();

    for (; it < s.end(); it++)
    {
        if((*it) != ';')
        {
            v.at(count).push_back(*it);
        }
        else
        {
            count++;
        }
    }
    return RegisteredPassenger(v[0],v[1],stringToDate(v[2]), stringToInt(v[3]));
}

// Loading Airplanes

void Application ::loadAirplanes(string path) {
    ifstream buffer;
    buffer.open(path);

    string info;
    vector<string> planeData;

    while(!buffer.eof())
    {
        getline(buffer, info);
        planeData.push_back(info);
    }
    treatAirplaneInfo(planeData);

    buffer.close();
}

void Application ::treatAirplaneInfo(vector<string> airplaneInfo)
{
    for (int i = 0; i < airplaneInfo.size(); i++)
    {
        Airplane *a = createAirplane(airplaneInfo[i]);
        this->company.addAirplane(a);
    }
}

Airplane *Application ::createAirplane(string s) {
    string type, capacity, price, speed;
    vector<string> v = {type, capacity, price, speed};

    Airplane *a;

    string :: iterator it = s.begin();
    int count = 0;
    for (; it < s.end(); it++)
    {
        if((*it) != ';')
        {
            v.at(count).push_back(*it);
        }
        else
        {
            count++;
        }
    }
    if (v[0] == "Boeing") {
        a = new Boeing();
        a->setType(v[0]);
        a->setCapacity(stringToInt(v[1]));
        a->setNormalPrice(stringToInt(v[2]));
        a->setSpeed(stringToInt(v[3]));
        return a;
    }
    else if (v[0] == "Airbus"){
        a = new Airbus();
        a->setType(v[0]);
        a->setCapacity(stringToInt(v[1]));
        a->setNormalPrice(stringToInt(v[2]));
        a->setSpeed(stringToInt(v[3]));
        return a;    }
    else if (v[0] == "Concorde"){
        a = new Concorde();
        a->setType(v[0]);
        a->setCapacity(stringToInt(v[1]));
        a->setNormalPrice(stringToInt(v[2]));
        a->setSpeed(stringToInt(v[3]));
        return a;    }

    return nullptr;
}

// Loading Flights

void Application ::loadFlights(string path) {
    ifstream buffer;
    buffer.open(path);

    string info;
    vector<string> flightData;

    while(!buffer.eof())
    {
        getline(buffer, info);
        flightData.push_back(info);
    }
    treatFlightInfo(flightData);
    buffer.close();
}

void Application ::treatFlightInfo(vector<string> flightInfo) {
    for (int i = 0; i < flightInfo.size(); i++)
    {
        Flight *f = createFlight(flightInfo[i]);
        this->company.addFlight(f);
    }
}

Flight * Application ::createFlight(string s) {
    string airplane, passengers, arrivalDate, departureDate, arrivalLocation, departureLocation;
    vector<string> v = {airplane, passengers, arrivalDate, departureDate, arrivalLocation, departureLocation};

    string :: iterator it = s.begin();
    int count = 0;

    for (; it < s.end(); it++)
    {
        if((*it) != ';')
        {
            v.at(count).push_back(*it);
        }
        else
        {
            count++;
        }
    }

    Flight *f;

    if (v[1].find(',')) // Se so tiver um passageiro e porque e alugado
    {
        f = new CommercialFlight();
        f->setAirplane(stringToAirplane(v[0]));
        f->setPassengerList(stringToPassengerVector(v[1]));
        f->setArrivalDate(stringToDate(v[2]));
        f->setDepartureDate(stringToDate(v[3]));
        f->setArrivalLocation(stringToLocation(v[4]));
        f->setDepartureLocation(stringToLocation(v[5]));
        return f;
    }
    else{
        f = new RentedFlight();
        f->setAirplane(stringToAirplane(v[0]));
        f->setPassengerList(stringToPassengerVector(v[1]));
        f->setArrivalDate(stringToDate(v[2]));
        f->setDepartureDate(stringToDate(v[3]));
        f->setArrivalLocation(stringToLocation(v[4]));
        f->setDepartureLocation(stringToLocation(v[5]));
        return f;
    }
}

void Application ::addClient() {
    string name, job, date, average;
    cout << "Client Name: ";
    getline(cin, name);
    cout << "Job: ";
    getline(cin, job);
    cout << "Date of Birth (dd/mm/yyyy): ";
    cin >> date;
    cout << "Average Number of Flights: ";
    cin >> average;

    RegisteredPassenger r = RegisteredPassenger(name, job, stringToDate(date), stringToInt(average));
    this->company.addClient(r);
}


void Application ::addAirplane() {
    string type;
    string capacity, price, speed;
    cout << "Airplane Type: ";
    cin >> type;
    cout << "Capacity: ";
    cin >> capacity;
    cout << "Normal Price: ";
    cin >> price;
    cout << "Speed: ";
    cin >> speed;

    Airplane * a;

    if (type == "Boeing"){
        a = new Boeing(type, stringToInt(capacity), stringToInt(price), stringToInt(speed));
    }
    else if (type == "Airbus")
        a = new Airbus(type, stringToInt(capacity), stringToInt(price), stringToInt(speed));
    else if (type == "Concorde"){
        a = new Concorde(type, stringToInt(capacity), stringToInt(price), stringToInt(speed));
    }

    this->company.addAirplane(a);
}

void Application ::addFlight() {
    string airplane, arrivalDate, departureDate, arrivalLocation, departureLocation, passengerList;

    cout << "Airplane Type: ";
    cin >> airplane;
    cout << "Passengers (Passenger X,Passenger Y,...): ";
    getline(cin, passengerList);
    cout << "Arrival Date (dd/mm/yyyy): ";
    cin >> arrivalDate;
    cout << "Departure Date (dd/mm/yyyy): ";
    cin >> departureDate;
    cout << "Arrival Location (City,Country): ";
    getline(cin, arrivalLocation);
    cout << "Departure Location (City,Country): ";
    getline(cin, departureLocation);

    Airplane * a;
    if (airplane == "Boeing"){
        a = new Boeing(airplane,0,0,0);
    }
    else if (airplane == "Airbus") {
        a = new Airbus(airplane, 0, 0, 0);
    }
    else if (airplane == "Concorde"){
        a = new Concorde(airplane,0,0,0);
    }

    Flight * f;
    vector<Passenger> p;
    p = stringToPassengerVector(passengerList);
    Date ad = stringToDate(arrivalDate);
    Date dd = stringToDate(departureDate);
    Location al = stringToLocation(arrivalLocation);
    Location dl = stringToLocation(departureLocation);

    if (p.size() > 1)
        f = new CommercialFlight(a, dd, ad, dl, al, p);
    else
        f = new RentedFlight(a, dd, ad, dl, al, p);

    this->company.addFlight(f);

}

void Application ::saveRegisteredPassengers() {
    ofstream file;
    file.open("/Users/ff/CLionProjects/PlaneReservation/res/RegisteredPassengers.txt");

    for (int i = 0; i < this->company.getClientList().size(); i++)
    {
        if (i != this->company.getClientList().size() - 1)
            file << this->company.getClientList()[i].getName() + ";" + this->company.getClientList()[i].getJob() + ";" + dateToString(this->company.getClientList()[i].getDateOfBirth()) + ";" << (this->company.getClientList()[i].getAverageNFlights()) << ";\n";
        else
            file << this->company.getClientList()[i].getName() + ";" + this->company.getClientList()[i].getJob() + ";" + dateToString(this->company.getClientList()[i].getDateOfBirth()) + ";" << (this->company.getClientList()[i].getAverageNFlights()) << ";";

    }

    file.close();
}