/*
 * ImportInfo.h
 *
 *  Created on: 14/11/2017
 *      Author: Francisco Maria / João Gama Amaral
 */

#ifndef IMPORTINFO_H_
#define IMPORTINFO_H_

#include "Libraries.h"
#include "Interface.h"
#include "Algorithms.h"
#include <fstream>
#include <ctime>
#include <cstdio>

/**
 * @brief import clients from .txt file
 * @param company company itself
 */
void importClients(MovingCompany& company);

/**
 * @brief import countries from .txt file
 * @param company company itself
 */
void importCountries(MovingCompany& company);

/**
 * @brief import countries zones from .txt file
 * @param company company itself
 */
void importCountriesZones(MovingCompany& company);

/**
 * @brief import services from .txt file
 * @param company company itself
 */
void importServices(MovingCompany& company);

/**
 * @brief import vehicles from .txt file
 * @param company company itself
 */
void importVehicles(MovingCompany& company);

/**
 * @brief adds non active clients to the hash table
 * @param company company itself
 */
void addNonActiveClients(MovingCompany& company);


#endif /* IMPORTINFO_H_ */
