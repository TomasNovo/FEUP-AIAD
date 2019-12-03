/*
 * MovingCompany.cpp
 *
 *  Created on: 02/11/2017
 *      Author: Francisco Maria / João Gama Amaral
 */

#include "MovingCompany.h"
#include <algorithm>

MovingCompany::MovingCompany(std::string n, std::string d, std::string iban, std::string e, int fd, int fm, int fy): foundingDate(Date(fd,fm,fy)),
	servicesBills(ServiceBill()){
	this->name = n;
	this->description = d;
	this->IBAN = iban;
	this->Entity = e;
}

std::string MovingCompany::getName() const{
	return name;
}

std::string MovingCompany::getDescription() const{
	return description;
}

const Date& MovingCompany::getFoundingDate() const{
	return foundingDate;
}

std::vector<Client*> MovingCompany::getClients() const{
	return clients;
}

std::vector<Client*> MovingCompany::getParticularClients() const{

	unsigned int i;
	std::vector<Client*> particulars_aux;

	for(i = 0; i < clients.size(); i++){
		if(clients[i]->isParticular()){
			particulars_aux.push_back(clients[i]);
		}
	}
	return particulars_aux;
}

std::vector<Client*> MovingCompany::getCompaniesClients() const{
	unsigned int i;
	std::vector<Client*> companies_aux;

	for(i = 0; i < clients.size(); i++){
		if(!clients[i]->isParticular()){
			companies_aux.push_back(clients[i]);
		}
	}
	return companies_aux;
}

tabHCli MovingCompany::getNonActiveClients() const{
	return nonActiveClients;
}

vector<Vehicle*> MovingCompany::getVehicles() const{
	return allVehicles;
}

std::priority_queue<Vehicle*> MovingCompany::getAvailableVehicles() const{
	return availableVehicles;
}

std::queue<ServiceRequest*> MovingCompany::getServicesRequested() const{
	return servicesWaiting;
}

Country* MovingCompany::getCountry(std::string name) const{

	std::vector<Country*>::const_iterator it;

	for(it = countriesToOperate.begin(); it != countriesToOperate.end(); it++){
		if((*it)->getName() == name)
			return *it;
	}

	return NULL;
}

bool MovingCompany::existsClients() const{
	return (clients.size() != 0);
}

void MovingCompany::addClient(Client* c){
	clients.push_back(c);
}

void MovingCompany::addServiceBill(Client* c, Service* s){

	ServiceBill sb(c,s);
	servicesBills.insert(sb);
}

void MovingCompany::addNonActiveClient(Client* c){
	nonActiveClients.insert(c);
}

void MovingCompany::addServiceWaiting(ServiceRequest* sr){
	servicesWaiting.push(sr);
}

void MovingCompany::addCountry(Country* c){
	countriesToOperate.push_back(c);
}

void MovingCompany::addVehicle(Vehicle* v){
	allVehicles.push_back(v);

	//inserts it in the priority queue of the vehicles
	if(v->isAvailable())
		availableVehicles.push(v);
}

std::vector<Country*> MovingCompany::getCountriesToOperate() const{
	return countriesToOperate;
}

void MovingCompany::printAllCountriesToOperate() const{

	for(unsigned int i = 0; i < countriesToOperate.size(); i++){
		std::cout << "\t\t\t\t\t\t\t" << i+1 << " - " << countriesToOperate[i] << std::endl;
	}
}

void MovingCompany::printCountriesToOperateFrom(Country* c){
	c->printCountriesTo();
}

ConnectionCountryInfo& MovingCompany::getCountryDestination(Country* c, int idDestination){
	return c->getDestination(idDestination);
}

std::string MovingCompany::getIBAN() const{
	return IBAN;
}

std::string MovingCompany::getEntity() const{
	return Entity;
}

void MovingCompany::removeClientByID(int id){

	int index = binarySearch(clients, id);

	if(index == -1){
		throw NonExistingClient(id);
	}

	clients[index]->deleteServices();
	clients.erase(clients.begin()+index);
}

void MovingCompany::removeClientByName(std::string name){
	bool found = false;
	unsigned int i;

	for(i = 0; i < clients.size(); i++){
		if(clients[i]->getName() == name){
			found = true;
			break;
		}
	}

	if(found){
		clients.erase(clients.begin()+i);
		return;
	}

	throw NonExistingClient(name);
}


void MovingCompany::removeClientByJoiningDate(int d, int m, int y){

	unsigned int i;
	Date date(d, m, y);

	for(i = 0; i < clients.size(); i++){
		if(clients[i]->getJoiningDate() == date){
			clients.erase(clients.begin()+i);
			return;
		}
	}
	throw NonExistingDate(d,m,y);
}

void MovingCompany::printBill(Client* c, Service* s){

	BSTItrIn<ServiceBill> it(servicesBills);

	while(!it.isAtEnd()){
		if((it.retrieve().getClient() == c) && (it.retrieve().getService() == s)){
			std::cout << "\n\t\t" << it.retrieve();
			return;
		}
		it.advance();
	}
}

void MovingCompany::printClient(std::string name) const{

	int index = binarySearch(clients, name);

	if(index == -1){
		throw NonExistingClient(name);
	}

	std::cout << *clients[index];
}

void MovingCompany::printClient(int id) const{

	int index = binarySearch(clients, id);

	if(index == -1){
		throw NonExistingClient(id);
	}

	std::cout << *clients[index];
}

//  GENERAL PRINT
void MovingCompany::printByID(std::vector<Client*>& clients_aux) const{
	unsigned int i;

	for(i = 0; i < clients_aux.size(); i++){
		std::cout << *clients_aux[i];
	}
}

// Uses Bubble Sort
void MovingCompany::printByName(std::vector<Client*>& clients_aux) const{

	bubbleSort(clients_aux);

	for(unsigned int k = 0; k < clients_aux.size(); k++){
		std::cout << *clients_aux[k];
	}
}

// Uses Selection Sort
void MovingCompany::printByJoiningDate(std::vector<Client*>& clients_aux) const{

	selectionSort(clients_aux);

	for(unsigned int i = 0; i < clients_aux.size(); i++){
		std::cout << *clients_aux[i];
	}
}


// ---- ALL CLIENTS ----- //

void MovingCompany::printClientsByID() const{

	std::vector<Client*> clients_aux = clients;

	printByID(clients_aux);
}


void MovingCompany::printClientsByName() const{

	std::vector<Client*> clients_aux = clients;

	printByName(clients_aux);
}

void MovingCompany::printClientsByJoiningDate() const{

	std::vector<Client*> clients_aux = clients;

	printByJoiningDate(clients_aux);

}

// ----- PARTICULAR CLIENTS ------- //

void MovingCompany::printParticularClientsByID() const{

	std::vector<Client*> particulars_aux = getParticularClients();

	printByID(particulars_aux);
}

void MovingCompany::printParticularClientsByName() const{

	std::vector<Client*> particulars_aux = getParticularClients();

	printByName(particulars_aux);
}

void MovingCompany::printParticularClientsByJoiningDate() const{

	std::vector<Client*> particulars_aux = getParticularClients();

	printByJoiningDate(particulars_aux);
}

// ----- COMPANIES CLIENTS ------ //

void MovingCompany::printCompanyClientsByID() const{

	std::vector<Client*> companies_aux = getCompaniesClients();

	printByID(companies_aux);
}

void MovingCompany::printCompanyClientsByName() const{

	std::vector<Client*> companies_aux = getCompaniesClients();

	printByName(companies_aux);
}

void MovingCompany::printCompanyClientsByJoiningDate() const{

	std::vector<Client*> companies_aux = getCompaniesClients();

	printByJoiningDate(companies_aux);
}

void MovingCompany::printNonActiveClients() const{

	tabHCli::const_iterator it;

	for(it = nonActiveClients.begin(); it != nonActiveClients.end(); it++){
		std::cout << "\t\t\t\t\t" << *(*it) << std::endl;
	}
}

void MovingCompany::printAllVehicles() const{

	for(unsigned int i = 0; i < allVehicles.size(); i++){
		std::cout << *allVehicles[i];
	}
}

void MovingCompany::printAvailableVehicles() const{

	std::priority_queue<Vehicle*> aux = availableVehicles;

	if(aux.empty()){
		std::cout << "\n\t\t\t\t\tThere are no vehicles available to transport" << std::endl;
		return;
	}

	while(!aux.empty()){
		Vehicle* v = aux.top();

		std::cout << *v;

		aux.pop();
	}
}

void MovingCompany::printAllServicesWaiting() const{

	std::queue<ServiceRequest*> aux = servicesWaiting;

	while(!aux.empty()){

		std::cout << *(aux.front());

		aux.pop();
	}
}

void MovingCompany::printClientServices(int index) const{
	clients[index]->printServices();
}

int MovingCompany::checkClientServiceStatus(int index){

	clients[index]->printServices();

	int sID;

	std::cout << "\t\t\t\tSelect the service: ";
	std::cin >> sID;

	if(std::cin.fail()){
		std::cout << "\t\t\t\tNot a valid option." << std::endl;
		return 0;
	}

	if(sID == 0) return 0;
	else if(sID == -1) return -1;

	clients[index]->checkServiceStatus(sID);

	return 0;
}

int MovingCompany::validateClientService(int index){

	clients[index]->printServices();

	int sID;

	std::cout << "\t\t\t\tSelect the service to validate payment: ";
	std::cin >> sID;

	if(std::cin.fail()){
		std::cout << "Not a valid option." << std::endl;
		return 0;
	}

	if(sID == 0) return 0;
	else if(sID == -1) return -1;

	clients[index]->validatePayment(sID);

	return 0;
}

bool MovingCompany::existsAvailableCarsToTransport(int weight, std::list<Vehicle*>& vehiclesToTransport){

	int leftWeight = weight, cont = 0;
	std::priority_queue<Vehicle*> auxVehicles = availableVehicles;

	while(!auxVehicles.empty()){
		Vehicle* v = auxVehicles.top();

		if(leftWeight <= v->getMaxWeight()){
			vehiclesToTransport.push_back(v);
			cont++;
			break;
		}
		else{
			leftWeight -= v->getMaxWeight();
			vehiclesToTransport.push_back(v);
			cont++;
		}
		auxVehicles.pop();
	}

	if(leftWeight > 0) return false;

	while(!availableVehicles.empty() && cont > 0){
		availableVehicles.top()->changeAvailability(false);
		availableVehicles.pop();
		cont--;
	}
	return true;
}

void MovingCompany::checkNonActiveClients(Client* c){

	tabHCli::iterator it = nonActiveClients.find(c);

	if(it == nonActiveClients.end())
		return;

	nonActiveClients.erase(it);
}

void MovingCompany::deleteClients(){

	unsigned int i;

	for(i = 0; i < clients.size(); i++){
		for(unsigned int j = 0; j < clients[i]->getServicesRequested().size(); j++){
			delete(clients[i]->getServicesRequested()[j]);
		}
		delete(clients[i]);
	}
}

void MovingCompany::deleteCountries(){

	for(unsigned int i = 0; i < countriesToOperate.size(); i++){
		delete(countriesToOperate[i]);
	}
}

void MovingCompany::deleteVehicles(){

	for(unsigned int i = 0; i < allVehicles.size(); i++){
		delete(allVehicles[i]);
	}
}

void MovingCompany::freeMemory(){

	deleteClients();
	deleteCountries();
	deleteVehicles();
}

