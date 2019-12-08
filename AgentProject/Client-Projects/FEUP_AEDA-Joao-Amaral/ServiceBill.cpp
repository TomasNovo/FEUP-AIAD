/*
 * ServiceBill.cpp
 *
 *  Created on: 21/12/2017
 *      Author: Francisco Maria / João Gama Amaral
 */

#include "ServiceBill.h"

ServiceBill::ServiceBill(){}

ServiceBill::ServiceBill(Client* c, Service* s): client(c), service(s){}

Client* ServiceBill::getClient() const{
	return client;
}

Service* ServiceBill::getService() const{
	return service;
}

bool ServiceBill::operator <(const ServiceBill& sb) const{

	if(client->getName() == sb.getClient()->getName()){
		return service->getBeggining() < sb.getService()->getBeggining();
	}
	return client->getName() < sb.getClient()->getName();
}

bool ServiceBill::operator ==(const ServiceBill& sb) const{

	if((client == sb.getClient()) && (service == sb.getService()))
		return true;
	return false;
}

