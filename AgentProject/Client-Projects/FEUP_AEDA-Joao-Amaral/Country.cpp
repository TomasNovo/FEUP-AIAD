/*
 * Country.cpp
 *
 *  Created on: 12/11/2017
 *      Author: Francisco Maria / João Gama Amaral
 */

#include "Country.h"

Country::Country(std::string n): name(n){}

std::string Country::getName() const{ return name; }

void Country::printCountriesTo() const{
	unsigned int i;

	for(i = 0; i < countriesInfo.size(); i++){

		if(countriesInfo[i].getZone() == 1){
			std::cout << "\n\t\t\t\t\t\t( ZONE 1 ) ";
		}
		if(countriesInfo[i].getZone() == 2){
			std::cout << "\n\t\t\t\t\t\t( ZONE 2 ) ";
		}
		std::cout << i+1 << " - " << countriesInfo[i].getCountry()->getName();
	}
}

ConnectionCountryInfo& Country::getDestination(int id){
	return countriesInfo[id-1];
}

void Country::addCountryConnection(ConnectionCountryInfo& ci){
	countriesInfo.push_back(ci);
}

std::vector<ConnectionCountryInfo> Country::getCountriesInfo() const{
	return countriesInfo;
}

