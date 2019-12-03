/*
 * ServiceRequest.cpp
 *
 *  Created on: 05/01/2018
 *      Author: Francisco Maria / João Gama Amaral
 */

#include "ServiceRequest.h"

ServiceRequest::ServiceRequest(int cID, Service* s): clientID(cID), service(s){}

int ServiceRequest::getClientID() const{
	return clientID;
}

Service* ServiceRequest::getService() const{
	return service;
}




