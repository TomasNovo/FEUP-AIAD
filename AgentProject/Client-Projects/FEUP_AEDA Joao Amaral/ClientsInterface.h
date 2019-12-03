/*
 * ClientsInterface.h
 *
 *  Created on: 11/11/2017
 *      Author: Francisco Maria / João Gama Amaral
 */

#ifndef CLIENTSINTERFACE_H_
#define CLIENTSINTERFACE_H_

#include "MovingCompany.h"
#include <ctime>

/**
 * 	@brief Prints a client
 * 	@param company The company object itself.
 * 	@return 0 or -1 depending on the input.
 */
int checkClient(MovingCompany& company);

/**
 * 	@brief Searches a client thats belongs to the company by name.
 * 	@param company The company object itself.
 * 	@return 0 or -1 depending on the input.
 */
int searchClientByName(MovingCompany& company);

/**
 * 	@brief Searches a client that belongs to the company by ID.
 * 	@param company The company object itself.
 * 	@return 0 or -1 depending on the input.
 */
int searchClientByID(MovingCompany& company);


/**
 * 	@brief Searches a client that belongs to the company by NIF.
 * 	@param company The company object itself.
 * 	@return 0 or -1 depending on the input.
 */
int searchClientByNIF(MovingCompany& company);

/**
 * 	@brief Adds a new company to the company.
 * 	@param company The company object itself.
 * 	@return 0 or -1 depending on the input.
 */
int addNewClient(MovingCompany& company);

/**
 * 	@brief Removes a client of the company.
 * 	@param company The company object itself.
 * 	@return 0 or -1 depending on the input.
 */
int removeClient(MovingCompany& company);

/**
 * 	@brief Prints only particulars clients.
 * 	@param company The company object itself.
 * 	@return 0 or -1 depending on the input.
 */
int printParticulars(MovingCompany& company);

/**
 * 	@brief Prints only companies clients.
 * 	@param company The company object itself.
 * 	@return 0 or -1 depending on the input.
 */
int printCompanies(MovingCompany& company);


/**
 * 	@brief Prints all clients of the company
 * 	@param company The company object itself
 * 	@return 0 or -1 depending on the input
 */
int printClients(MovingCompany& company);

/**
 * @brief Prints all vehicles of the company.
 * @param company The company object itself
 * @return 0 or -1 depending on the input
 */
int printVehicles(MovingCompany& company);

/**
 * @brief Prints all available vehicles of the company
 * @param company company itself
 * @return 0 or -1 depending on the input
 */
int printAvailableVehicles(MovingCompany& company);

/**
 * @brief Prints all non active clients
 * @param The company object itself
 * @return 0 or -1 depending on the input.
 */
int printNonActiveClients(MovingCompany& company);

/**
 * @brief Updates a certain client information
 * @param company The company object itself
 * @return 0 or -1 depending on the input.
 */
int updateClientsInfo(MovingCompany& company);


#endif /* CLIENTSINTERFACE_H_ */
