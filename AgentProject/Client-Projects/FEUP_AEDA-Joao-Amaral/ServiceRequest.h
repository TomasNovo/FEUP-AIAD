/*
 * ServiceRequest.h
 *
 *  Created on: 05/01/2018
 *      Author: Francisco Maria / João Gama Amaral
 */

#ifndef SERVICEREQUEST_H_
#define SERVICEREQUEST_H_

#include "Libraries.h"
#include "Service.h"

/**
 * @brief This class represents a service that was requested by a certain client but there weren't any
 * vehicles in the company to begin the transportation of the cargo. Serves to represent a service on
 * hold until there is another vehicle(s) available.
 */
class ServiceRequest{
	int clientID;
	Service* service;
public:
	/**
	 * @brief Service Request constructor
	 */
	ServiceRequest(int cID, Service* s);

	/**
	 * @brief Gets the ID of the client
	 * @return client's ID
	 */
	int getClientID() const;

	/**
	 * @brief Gets the service on hold
	 * @return service
	 */
	Service* getService() const;

	/**
	 * @brief prints a service request
	 * @param o ostream
	 * @param sr service request to be printed
	 * @return o ostream
	 */
	friend std::ostream& operator <<(std::ostream& o, const ServiceRequest& sr){
		std::cout << "\n\t\t\t\t\t\t\tSERVICE REQUEST INFO\n\t\t\t\t\tClient ID: " << sr.clientID <<
				"\n\t\t\t\t\t\tService request date: " << sr.getService()->getBeggining() << std::endl;
		return o;
	}
};



#endif /* SERVICEREQUEST_H_ */
