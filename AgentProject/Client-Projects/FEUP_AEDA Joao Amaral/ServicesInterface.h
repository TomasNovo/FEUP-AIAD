/*
 * ServicesInterface.h
 *
 *  Created on: 10/11/2017
 *      Author: Francisco Maria / João Gama Amaral
 */

#ifndef SERVICESINTERFACE_H_
#define SERVICESINTERFACE_H_

#include "MovingCompany.h"
#include <cstdlib>
#include <ctime>

const int ZONE_1 = 1;
const int ZONE_2 = 2;

/**
 * @brief creates new service
 * @param company company itself
 * @return 0 or -1 depending on the user input
 */
int newService(MovingCompany& company);

/**
 * @brief creates new service to a registered client
 * @param company company itself
 * @return 0 or -1 depending on the user input
 */
int newRegisteredClientService(MovingCompany& company);

/**
 * @brief creates new service to an unregistered client
 * @param company company itself
 * @return 0 or -1 depending on the user input
 */
int newUnregisteredClientService(MovingCompany& company);

/**
 * @brief prints all services of a certain client
 * @param company company itself
 * @return 0 or -1 depending on the user input
 */
int printClientsServices(MovingCompany& company);

/**
 * @brief print service status of some client
 * @param company company itself
 * @return 0 or -1 depending on the user input
 */
int checkClientsServiceStatus(MovingCompany& company);

/**
 * @brief validates certain client service payment
 * @param company company itself
 * @return 0 or -1 depending on the user input
 */
int validateClientsPayment(MovingCompany& company);

/**
 * @brief prints service bill
 * @param company company itself
 * @return 0 or -1 depending on the user input
 */
int printServicesBill(MovingCompany& company);

/**
 * @brief prints all services that are waiting for available vehicles
 * @param company company itself
 * @return 0 or -1 depending on the user input
 */
int printServicesRequests(MovingCompany& company);


#endif /* SERVICESINTERFACE_H_ */
