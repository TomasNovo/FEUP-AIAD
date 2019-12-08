/*
 * Interface.h
 *
 *  Created on: 02/11/2017
 *      Author: Francisco
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "MovingCompany.h"
#include "ClientsInterface.h"
#include "ServicesInterface.h"

/**
 * @brief runs program
 * @param company company itself
 */
void run(MovingCompany& company);

/**
 * @brief prints main menu
 * @param company company itself
 */
int showMenu(MovingCompany& company);

/**
 * @brief prints clients menu
 * @param company company itself
 */
bool showClientsMenu(MovingCompany& company);

/**
 * @brief prints services menu
 * @param company company itself
 */
bool showServicesMenu(MovingCompany& company);

/**
 * @brief prints clients menu
 * @param company company itself
 */
bool showVehiclesMenu(MovingCompany& company);


#endif /* INTERFACE_H_ */
