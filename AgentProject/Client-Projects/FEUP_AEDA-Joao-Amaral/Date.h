/*
 * Date.h
 *
 *  Created on: 01/11/2017
 *      Author: Francisco Maria / João Gama Amaral
 */

#ifndef DATE_H_
#define DATE_H_

#include "Libraries.h"

/**
 * @brief Class that stores all date information
 */
class Date{
	int day;
	int month;
	int year;
	int hour;
	int minute;
public:
	/**
	 * @brief Default constructor
	 */
	Date();

	/**
	 * @brief Date constructor
	 */
	Date(int d, int m, int y);

	/**
	 * @brief Date constructor with hour and minute
	 */
	Date(int d, int m, int y, int h, int min);

	/**
	 * @brief Gets day
	 * @return day of the date
	 */
	int getDay() const;

	/**
	 * @brief Gets month
	 * @return month of the date
	 */
	int getMonth() const;

	/**
	 * @brief Gets year
	 * @return year of the date
	 */
	int getYear() const;

	/**
	 * @brief Gets hour
	 * @return hour of the date
	 */
	int getHour() const;

	/**
	 * @brief Gets minute
	 * @return minute of the date
	 */
	int getMinute() const;

	/**
	 * @brief Sets day
	 * @param d day of the date
	 */
	void setDay(int d);


	/**
	 * @brief Sets month
	 * @param m month of the date
	 */
	void setMonth(int m);

	/**
	 * @brief Sets year
	 * @param y year of the date
	 */
	void setYear(int y);

	/**
	 * @brief Sets hour
	 * @param h hour of the date
	 */
	void setHour(int h);

	/**
	 * @brief Sets minute
	 * @param m minute of the date
	 */
	void setMinute(int m);

	/**
	 * @brief Checks if two dates are equal
	 * @param d date 1
	 * @param d1 date 2
	 * @return true or false
	 */
	friend bool operator ==(const Date& d, const Date& d1){
		if(d.day == d1.getDay() && d.month == d1.getMonth() && d.year == d1.getYear())
			return true;
		return false;
	}

	/**
	 * @brief prints a date
	 * @param o ostream
	 * @param d date
	 * @return ostream
	 */
	friend std::ostream& operator <<(std::ostream& o, const Date& d){
		o << d.day << "/" << d.month << "/" << d.year << " " << d.hour << ":";

		if(d.minute < 10)
			o << "0" << d.minute;
		else
			o << d.minute;

		return o;
	}

	/**
	 * @brief checks which date is minor
	 * @param d date 1
	 * @param d1 date 2
	 * @return true or false
	 */
	friend bool operator <(const Date& d1, const Date& d2){
		if(d1.year < d2.getYear())
				return true;
		else if(d1.year > d2.getYear())
			return false;

		if(d1.month < d2.getMonth())
			return true;
		else if(d1.month > d2.getMonth())
			return false;

		if(d1.day < d2.getDay())
			return true;
		return false;
	}
};




#endif /* DATE_H_ */
