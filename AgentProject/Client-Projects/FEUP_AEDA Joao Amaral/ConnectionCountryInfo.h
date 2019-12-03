/*
 * ConnectionCountryInfo.h
 *
 *  Created on: 13/11/2017
 *      Author: Francisco Maria / João Gama Amaral
 */

#ifndef CONNECTIONCOUNTRYINFO_H_
#define CONNECTIONCOUNTRYINFO_H_

#include "Libraries.h"

class Country;

/**
 * @brief Class that stores country information
 */
class ConnectionCountryInfo{
	Country* country;
	int zone;
	float baseRate;
public:
	/**
	 * @brief Default constructor
	 */
	ConnectionCountryInfo(){};

	/**
	 *  @brief Constructor to initialize a new country with its info
	 */
	ConnectionCountryInfo(Country* c, int z, float bR);

	/**
	 * @brief Gets zone of the destination country
	 * @return 1 or 2 depending on its zone
	 */
	int getZone() const;

	/**
	 * @brief Gets the rate cost of the destination country
	 * @return base rate of its country
	 */
	float getBaseRate() const;

	/**
	 * @brief Gets country name
	 * @return string with country name
	 */
	std::string getName() const;

	/**
	 * @brief Gets country
	 * @return country pointer
	 */
	Country* getCountry() const;
};


#endif /* CONNECTIONCOUNTRYINFO_H_ */
