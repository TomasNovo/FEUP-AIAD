/*
 * Address.h
 *
 *  Created on: 01/11/2017
 *      Author: Francisco Maria / João Gama Amaral
 */

#ifndef ADDRESS_H_
#define ADDRESS_H_

#include "Libraries.h"
#include "Country.h"

/**
 * 	@brief Class that stores all information about an address.
 */
class Address{
	std::string street;
	std::string zipCode;
	std::string city;
	std::string country_aux;
	ConnectionCountryInfo country;
public:
	/**
	 * @brief Default Constructor
	 */
	Address(){}

	/**
	 * @brief Constructor with country as string
	 */
	Address(std::string street, std::string zipCode, std::string city, std::string country);

	/**
	 * @brief Constructor with country as pointer
	 */
	Address(std::string street, std::string zipCode, std::string city, Country* c);

	/**
	 * @brief Constructor with country as ConnectionCountryInfo object
	 */
	Address(std::string street, std::string zipCode, std::string city, ConnectionCountryInfo& c);

	/**
	 * @brief Gets street from address
	 * @return string with street address
	 */
	std::string getStreet() const;

	/**
	 * @brief Gets zip code from address
	 * @return string with zip code
	 */
	std::string getZipCode() const;

	/**
	 * @brief Gets city from address
	 * @return string with city
	 */
	std::string getCity() const;

	/**
	 * @brief Gets only the string with the name of the country
	 * @return country name
	 */
	std::string getCountryAux() const;

	/**
	 * @return country as ConnectionCountryInfo object
	 */
	ConnectionCountryInfo& getCountry();

	/**
	 * @brief Sets street address
	 * @param s
	 */
	void setStreet(std::string s);

	/**
	 * @brief Sets zip code
	 * @param z
	 */
	void setZipCode(std::string z);

	/**
	 * @brief Sets city name
	 * @param c
	 */
	void setCity(std::string c);

	/**
	 * @brief Sets country
	 * @param cnt
	 */
	void setCountry(std::string cnt);

	/**
	 * @brief Sets country
	 * @param cnt
	 */
	void setCountry(ConnectionCountryInfo& cnt);

	/**
	 * @brief Compares two addresses
	 * @param a1
	 * @return true or false if addresses are equal
	 */
	bool operator ==(const Address& a1);

	/**
	 * @brief Prints address in determined way
	 * @param o ostream
	 * @param a an address
	 * @return ostream
	 */
	friend std::ostream& operator <<(std::ostream& o, const Address a){
		o << "Address: " << a.street << ", " << a.zipCode << "\n\t\t " << a.city << ", " << a.country_aux;
		return o;
	}
};

#endif /* COUNTRY_H_ */
