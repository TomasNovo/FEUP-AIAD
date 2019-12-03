//
// Created by Francisco Ferreira on 15/03/18.
//

#include "Utilities.h"
#include <string>


Date stringToDate(string s)
{
    string day = s.substr(0, s.find("/"));
    string month = s.substr(3,5);
    string year = s.substr(6,10);
    Date d(stoi(day), stoi(month), stoi(year));
    return d;

}

Location stringToLocation(string s)
{
    string city = s.substr(0, s.find(','));
    string country = s.substr(s.find(' '), s.size());
    Location l(country, city);
    return l;
}

int stringToInt(string s)
{
    return stoi(s);
}

vector<Passenger> stringToPassengerVector(string s)
{
    vector<Passenger> v;
    string :: iterator it = s.begin();

    string name = "";
    for (; it < s.end(); it++)
    {
        if ((*it) != ',')
        {
            name.push_back(*it);
        }
        else
        {
            Passenger p = Passenger(name);
            v.push_back(p);
            name = "";
        }
    }
    return v;
}

Airplane * stringToAirplane(string s)
{
    Airplane * a;
    if (s == "Boeing") {
        a = new Boeing();
        a->setType(s);
        return a;
    }
    else if (s == "Airbus"){
        a = new Airbus();
        a->setType(s);
        return a;    }
    else if (s == "Concorde"){
        a = new Concorde();
        a->setType(s);
        return a;    }

    return nullptr;
}

string dateToString(Date d){
    return (to_string(d.getDay()) + "/" + to_string(d.getMonth()) + "/" + to_string(d.getYear()));
}

string locationToString(Location l){
    return (l.getCity() + "," + l.getCountry());
}

string intToString(int i)
{
    return to_string(i);
}
