/*
 * ConnectionCountryInfo.cpp
 *
 *  Created on: 13/11/2017
 *      Author: Francisco Maria / João Gama Amaral
 */

#include "Country.h"
#include "ConnectionCountryInfo.h"

ConnectionCountryInfo::ConnectionCountryInfo(Country* c, int z, float bR): country(c), zone(z), baseRate(bR){}

int ConnectionCountryInfo::getZone() const{
	return zone;
}

float ConnectionCountryInfo::getBaseRate() const{
	return baseRate;
}

Country* ConnectionCountryInfo::getCountry() const{
	return country;
}

std::string ConnectionCountryInfo::getName() const{
	return country->getName();
}


