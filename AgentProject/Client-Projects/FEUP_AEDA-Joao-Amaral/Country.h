/*
 * Country.h
 *
 *  Created on: 12/11/2017
 *      Author: Francisco Maria / João Gama Amaral
 */

#ifndef COUNTRY_H_
#define COUNTRY_H_

#include "Libraries.h"
#include"ConnectionCountryInfo.h"

/**
 * @brief Class that stores all country information
 */
class Country{
	std::string name;
	std::vector<ConnectionCountryInfo> countriesInfo;
public:
	/**
	 * @brief Country Constructor
	 */
	Country(std::string n);

	/**
	 * @brief Gets country name
	 * @return string with name of country
	 */
	std::string getName() const;

	/**
	 * @brief Adds country to countriesInfo
	 * @param ci ConnectionCountryInfo to add to countriesInfo
	 */
	void addCountryConnection(ConnectionCountryInfo& ci);

	/**
	 * @brief Gets all countries
	 * @return all countries
	 */
	std::vector<ConnectionCountryInfo> getCountriesInfo() const;

	/**
	 * @brief Gets the destination country
	 * @param id destination country ID
	 * @return ConnectionCountryInfo object (destination country)
	 */
	ConnectionCountryInfo& getDestination(int id);

	/**
	 * @brief Prints all countries to which it operates to
	 */
	void printCountriesTo() const;

	/**
	 * @brief Prints a country
	 * @param o ostream
	 * @param c country
	 * @return ostream
	 */
	friend std::ostream& operator <<(std::ostream& o, const Country* c){
		o << c->getName();
		return o;
	}
};

#endif /* COUNTRY_H_ */
