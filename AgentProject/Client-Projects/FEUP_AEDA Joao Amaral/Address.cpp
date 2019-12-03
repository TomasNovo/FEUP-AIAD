/*
 * Address.cpp
 *
 *  Created on: 02/11/2017
 *      Author: Francisco Maria / João Gama Amaral
 */


#include "Address.h"

Address::Address(std::string street, std::string zipCode, std::string city, std::string country){
	this->street = street;
	this->zipCode = zipCode;
	this->city = city;
	this->country_aux = country;
}

Address::Address(std::string street, std::string zipCode, std::string city, Country* c){
	this->street = street;
	this->zipCode = zipCode;
	this->city = city;
	this->country_aux = c->getName();
}

Address::Address(std::string street, std::string zipCode, std::string city, ConnectionCountryInfo& c){
	this->street = street;
	this->zipCode = zipCode;
	this->city = city;
	this->country = c;
	this->country_aux = c.getName();
}

std::string Address::getStreet() const{
	return street;
}

std::string Address::getZipCode() const{
	return zipCode;
}

std::string Address::getCity() const{
	return city;
}

std::string Address::getCountryAux() const{
	return country_aux;
}

ConnectionCountryInfo& Address::getCountry(){
	return country;
}

void Address::setStreet(std::string s){
	street = s;
}

void Address::setZipCode(std::string z){
	zipCode = z;
}

void Address::setCity(std::string c){
	city = c;
}

void Address::setCountry(std::string cnt){
	country_aux = cnt;
}

void Address::setCountry(ConnectionCountryInfo& cnt){
	country = cnt;
	country_aux = cnt.getName();
}

bool Address::operator ==(const Address& a1){
	if(this->street == a1.getStreet() && this->city == a1.getCity()
			&& this->zipCode == a1.getZipCode() && this->country_aux == a1.getCountryAux())
		return true;
	return false;
}




