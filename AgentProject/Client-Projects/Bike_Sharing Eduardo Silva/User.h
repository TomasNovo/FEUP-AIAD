#ifndef AEDA_P1_USER_H
#define AEDA_P1_USER_H

#include "Station.h"
#include <iomanip>

using namespace std;

class HQ;

class User
{
    bool active;
    Bike *bike;
    string name;
	pair <int, int> Localization;

public:
	static double price_hour;
	User(string username);
	void setName(string new_name);
	void setLocalization(int x, int y);
	void setBike(Bike *bk);
	void set_active(bool cond);
	string getName() const;
	pair<int, int> getLocalization() const;
    Station* getClosestStation(vector<Station *> vs) const;
	Bike* getBike() const;
    virtual double getPrice() const;
    void addBike(Bike *bk, HQ *hq);
    void removeBike();
	virtual void Checkout(Date global_date);
};

class Member: public User
{
    int total_monthly_time;
    static double price_month;

public:
    Member(string username);
	void setHours(int hours);
	void addHours(int hours);
    double getPrice() const;
	int getHours() const;
	void Checkout(Date global_date);
};

class Regular: public User
{
    static double price_hour;
public:
    Regular(string username);
	void Checkout(Date global_date);
};

class Already_Active_User
{
	string name;

public:
	Already_Active_User(string name);
	string getName() const;
};

class Not_Active_User 
{
	string name;

public:
	Not_Active_User(string nm);
	string getName() const;
};

class Another_member
{
	string name;

public:
	Another_member(string am_name);
	string getName() const;
};

#endif

