/*
 * Client.cpp
 *
 *  Created on: 01/11/2017
 *      Author: Francisco Maria / João Gama Amaral
 */

#include "Client.h"

int Client::numberOfClients = 0;

/************************************************/
/************  CLIENT CONSTRUCTOR  **************/
/************************************************/

Client::Client(std::string name, long int nif, std::string address, std::string zipCode, std::string city, std::string country, int firstDay, int firstMonth, int firstYear, int hour, int minute):
				address(Address(address, zipCode, city, country)),
				joiningDate(Date(firstDay, firstMonth, firstYear, hour, minute)),
				lastService(Date(0,0,0,0,0)){
	numberOfClients++;
	this->id = numberOfClients;
	this->name = name;
	this->NIF = nif;
}

Client::Client(int ID, std::string name, long int nif, std::string address, std::string zipCode, std::string city, std::string country, int firstDay, int firstMonth, int firstYear, int hour, int minute):
				address(Address(address, zipCode, city, country)),
				joiningDate(Date(firstDay, firstMonth, firstYear, hour, minute)),
				lastService(Date(0,0,0,0,0)){
	numberOfClients++;
	this->id = ID;
	this->name = name;
	this->NIF = nif;
}

int Client::getId() const{
	return id;
}

long int Client::getNIF() const{
	return NIF;
}

std::string Client::getName() const{
	return name;
}

const Address& Client::getAddress() const{
	return address;
}

std::string Client::getZipCode() const{
	return address.getZipCode();
}

bool Client::operator ==(const Client& c1){
	if(this->id == c1.getId() && this->name == c1.getName()) return true;
	return false;
}

const Date& Client::getJoiningDate() const{
	return joiningDate;
}

const Date& Client::getLastService() const{
	return lastService;
}

std::vector<Service*> Client::getServicesRequested(){
	return servicesRequested;
}

void Client::updateAddress(Address& a){
	address = a;
}

void Client::updateNIF(long int nif){
	NIF = nif;
}

void Client::updateLastService(Date& d){
	lastService = d;
}

void Client::addNewService(Service* s){
	servicesRequested.push_back(s);
}

int Client::getNumberOfClients(){
	return numberOfClients;
}

void Client::printServices() const{

	unsigned int i;

	for(i = 0; i < servicesRequested.size(); i++){
		std::cout << *servicesRequested[i];
	}
}

void Client::printServicesResume() const{

	unsigned int i;

	for(i = 0; i < servicesRequested.size(); i++){
		std::cout << "\n\t\t" << i+1 << " -";
		servicesRequested[i]->printResume();
	}
}

void Client::checkServiceStatus(int sID) const{

	std::cout << "\n\n\t\t\t\t\tSTATUS: " << servicesRequested[sID-1]->getPayment()->getPaymentStatus();
}

void Client::validatePayment(int sID){

	servicesRequested[sID-1]->validatePayment();
}

void Client::deleteServices(){

	for(unsigned int i = 0; i < servicesRequested.size(); i++){
		delete(servicesRequested[i]);
	}
}

bool Client::operator ==(Client& c){

	if(NIF == c.getNIF())
		return true;
	return false;
}

/************************************************/
/*****************  COMPANY  ********************/
/************************************************/

int Company::numberOfCompanies = 0;

Company::Company(std::string name, long int nif, std::string address, std::string zipCode, std::string city, std::string country, int firstDay, int firstMonth, int firstYear, int hour, int minute)
: Client(name, nif, address, zipCode, city, country, firstDay, firstMonth, firstYear, hour, minute){
	numberOfCompanies++;
}

Company::Company(int id, std::string name, long int nif, std::string address, std::string zipCode, std::string city, std::string country, int firstDay, int firstMonth, int firstYear, int hour, int minute)
: Client(id, name, nif, address, zipCode, city, country, firstDay, firstMonth, firstYear, hour, minute){
	numberOfCompanies++;
}

int Company::getNumberOfCompanies(){
	return numberOfCompanies;
}

bool Company::isParticular(){
	return false;
}

/************************************************/
/****************  PARTICULAR  ******************/
/************************************************/

int Particular::numberOfParticulars = 0;

Particular::Particular(std::string name, int age, long int nif, std::string address, std::string zipCode, std::string city, std::string country, int firstDay, int firstMonth, int firstYear, int hour, int minute)
: Client(name, nif, address, zipCode, city, country, firstDay, firstMonth, firstYear, hour, minute){
	this->age = age;
	numberOfParticulars++;
}

Particular::Particular(int id, std::string name, int age, long int nif, std::string address, std::string zipCode, std::string city, std::string country, int firstDay, int firstMonth, int firstYear, int hour, int minute)
: Client(id, name, nif, address, zipCode, city, country, firstDay, firstMonth, firstYear, hour, minute){
	this->age = age;
	numberOfParticulars++;
}

int Particular::getAge(){
	return age;
}

bool Particular::isParticular(){
	return true;
}

int Particular::getNumberOfParticulars(){
	return numberOfParticulars;
}









