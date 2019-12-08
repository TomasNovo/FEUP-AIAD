#ifndef AEDA_P1_BIKE_H
#define AEDA_P1_BIKE_H

#include <iostream>
#include <string>
#include "Date.h"

using namespace std;

//////////////////////BIKE/////////////////////////////////
class Bike
{
protected:
	string ID;
	Date start_date;
	
public:
	Bike(Date start_date);
	void setID(string Id);
	Date getDate();
	virtual double getPrice(Date global_date) = 0;
	string getID() ;
	void setDate(Date &date);
};

////////////////////URBAN BIKE/////////////////////////////
class Urban_b : public Bike
{
	static double price_h;

public:
	Urban_b( Date start_date);
	double getPrice(Date global_date);
};

/////////////////URBAN SIMPLE BIKE/////////////////////////
class Urban_simple_b : public Bike
{
	static double price_h;

public:
	Urban_simple_b( Date start_date);
	double getPrice(Date global_date);
};

/////////////////////RACE BIKE///////////////////////////

class Race_b : public Bike
{
	static double price_h;

public:
	Race_b( Date start_date);
	double getPrice(Date global_date);
};

///////////////////CHILD BIKE//////////////////////////////

class Child_b : public Bike
{
	static double price_h;

public:
	Child_b( Date start_date);
	double getPrice(Date global_date);
};
#endif //P1_BIKE_H

