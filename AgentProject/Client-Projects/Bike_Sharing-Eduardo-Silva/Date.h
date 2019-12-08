#ifndef AEDA_P1_DATE_H
#define AEDA_P1_DATE_H

#include <iostream>
#include <string>

using namespace std;

class Date

{
	int day;
	int month;
	int hour;
	int minutes;
public:
	
	Date(int month, int day, int hour, int minutes);
	int getDay() const;
	int getMonth() const;
	int getHour() const;
	int getMinutes() const;
	void setDay(int d);
	void setMonth(int m);
	void setHour(int h);
	void setMinutes(int min);
	void addMonth(int m);
	void addDay(int d);
	void addHour(int h);
	void addMinutes(int min);
	int operator-(const Date &date1) const;
	bool operator<(const Date &date1) const;
	bool operator==(const Date &date1) const;
};

class InvalidDate
{
	Date dt;

public:
	InvalidDate(Date d);
	Date getDate() const;
};

#endif







