/*
 * MovingCompany.h
 *
 *  Created on: 02/11/2017
 *      Author: Francisco Maria / João Gama Amaral
 */

#ifndef MOVINGCOMPANY_H_
#define MOVINGCOMPANY_H_

#include "Libraries.h"
#include "Client.h"
#include "Country.h"
#include "Exceptions.h"
#include "Algorithms.h"
#include "ServiceBill.h"
#include "BST.h"
#include "ServiceRequest.h"
#include <unordered_set>
#include <queue>

/**
 * @brief Struct that handles the hash table operators
 */
struct cliHash{

	int operator()(Client* const& c) const{
		return c->getName().size();
	}

	int operator()(Client const* c1, Client const* c2) const{
		if(c1->getNIF() == c2->getNIF())
			return true;
		return false;
	}
};

typedef std::unordered_set<Client*, cliHash, cliHash> tabHCli;

/**
 * @brief Class that is the "Mother of all others". It represents a company.
 */
class MovingCompany{
	std::string name;
	std::string description;
	std::string IBAN;
	std::string Entity;
	Date foundingDate;
	std::vector<Client*> clients;
	std::vector<Country*> countriesToOperate;
	BST<ServiceBill> servicesBills;
	tabHCli nonActiveClients;
	std::vector<Vehicle*> allVehicles;
	std::priority_queue<Vehicle*> availableVehicles;
	std::queue<ServiceRequest*> servicesWaiting;

	// This next three funtions are private because they shall be accessed from the outside as they are critical to the good
	//function of the program.
	/**
	 * @brief deletes all clients and its associated services from the program (frees memory)
	 */
	void deleteClients();

	/**
	 * @brief deletes all countries associated with the company (frees memory)
	 */
	void deleteCountries();

	/**
	 * @brief deletes all vehicles associated with the company (frees memory)
	 */
	void deleteVehicles();

public:

	/**
	 * @brief Moving Company Constructor
	 */
	MovingCompany(std::string n, std::string d, std::string iban, std::string e, int fd, int fm, int fy);

	/**
	 * @brief gets the company name
	 * @return company name
	 */
	std::string getName() const;

	/**
	 * @brief gets the company's description
	 * @return company description
	 */
	std::string getDescription() const;

	/**
	 * @brief get company founding date
	 * @return founding date
	 */
	const Date& getFoundingDate() const;

	/**
	 * @brief gets all company clients
	 * @return clients
	 */
	std::vector<Client*> getClients() const;

	/**
	 * @brief gets all company's particular clients
	 * @return particular clients
	 */
	std::vector<Client*> getParticularClients() const;

	/**
	 * @brief gets all company's companies clients
	 * @return companies clients
	 */
	std::vector<Client*> getCompaniesClients() const;

	/**
	 * @brief gets all non active clients
	 * @return non active clients
	 */
	tabHCli getNonActiveClients() const;

	/**
	 * @brief gets all vehicles which belong to the company
	 * @return vehicles of the company
	 */
	vector<Vehicle*> getVehicles() const;

	/**
	 * @brief gets all vehicles available in the company to start a new transport
	 * @return available vehicles to start transportation
	 */
	std::priority_queue<Vehicle*> getAvailableVehicles() const;

	/**
	 * @brief gets all services on "stand-by"
	 * @return services requested
	 */
	std::queue<ServiceRequest*> getServicesRequested() const;

	/**
	 * @brief gets countries to which the company operate
	 * @return countries
	 */
	std::vector<Country*> getCountriesToOperate() const;

	/**
	 * @brief gets a specific country searching it by name
	 * @param country name
	 * @return country
	 */
	Country* getCountry(std::string) const;

	/**
	 * @brief Checks if there are clients registered in the company
	 * @return true or false depending on the existence of clients
	 */
	bool existsClients() const;

	/**
	 * @brief adds a new country to operate to the company
	 * @param c country to add to the company
	 */
	void addCountry(Country* c);

	/**
	 * @brief adds a new vehicle to the company
	 * @param v new vehicle to add to the country
	 */
	void addVehicle(Vehicle* v);

	/**
	 * @brief prints all countries to which the company operates
	 */
	void printAllCountriesToOperate() const;

	/**
	 * @briefs given a certain country gets all of the countries to which it operates
	 * @param c country
	 */
	void printCountriesToOperateFrom(Country* c);

	/**
	 * @brief gets the ConnectionCountryInfo object with information of the destination country
	 * @param c country of origin
	 * @param idDestination destination country ID
	 * @return ConnectionCountryInfo object representing the country destination info
	 */
	ConnectionCountryInfo& getCountryDestination(Country* c, int idDestination);

	/**
	 * @brief gets the IBAN of the company
	 * @return company's IBAN
	 */
	std::string getIBAN() const;

	/**
	 * @brief gets the entity representing the company
	 * @return entity of the company
	 */
	std::string getEntity() const;

	/**
	 * @brief adds a new client to the company
	 * @param c new client
	 */
	void addClient(Client* c);

	/**
	 * @brief adds a new service bill
	 * @param c client to add bill
	 * @param s service of the bill
	 */
	void addServiceBill(Client* c, Service* s);

	/**
	 * @brief adds a non active client to the hash table
	 * @param c non active client
	 */
	void addNonActiveClient(Client* c);

	/**
	 * @brief adds a new service request to the company
	 * @param sr service request
	 */
	void addServiceWaiting(ServiceRequest* sr);

	/**
	 * @brief removes client given a certain ID
	 * @param id ID of the client to be removed
	 */
	void removeClientByID(int id);
	/**
	 * @brief removes client given a certain name
	 * @param name name of the client to be removed
	 */
	void removeClientByName(std::string name);

	/**
	 * @brief removes client given a certain date (joining date)
	 * @param d day of the date
	 * @param m month of the date
	 * @param y year of the date
	 */
	void removeClientByJoiningDate(int d, int m, int y);

	/**
	 * @brief prints bill of a service associated with the given client (searches through the BST)
	 * @param c client which has the bill
	 * @param s service of the client to print bill
	 */
	void printBill(Client* c, Service* s);

	/**
	 * @brief prints client given a certain name using binary search
	 * @param name name of the client to print
	 */
	void printClient(std::string name) const;

	/**
	 * @brief print client given a certain ID
	 * @param id id of the client to print
	 */
	void printClient(int id) const;

	/**
	 * @brief print clients of a vector
	 * @param v clients vector
	 */
	void printByID(std::vector<Client*>& v) const;

	/**
	 * @brief print clients of a vector sorting them by name using bubble sort
	 * @param v clients vector
	 */
	void printByName(std::vector<Client*>& v) const;

	/**
	 * @brief print clients of a vector sorting them by joining date using selection sort
	 * @param v clients vector
	 */
	void printByJoiningDate(std::vector<Client*>& v) const;

	/**
	 * @brief print all clients by ID
	 */
	void printClientsByID() const;

	/**
	 * @brief print all client by name
	 */
	void printClientsByName() const;

	/**
	 * @brief print all clients by joining date
	 */
	void printClientsByJoiningDate() const;

	/**
	 * @brief print all particular clients by ID
	 */
	void printParticularClientsByID() const;

	/**
	 * @brief print all particular clients by name
	 */
	void printParticularClientsByName() const;

	/**
	 * @brief print all particular clients by joining date
	 */
	void printParticularClientsByJoiningDate() const;

	/**
	 * @brief print all company clients by ID
	 */
	void printCompanyClientsByID() const;

	/**
	 * @brief print all company clients by ID
	 */
	void printCompanyClientsByName() const;

	/**
	 * @brief print all company clients by ID
	 */
	void printCompanyClientsByJoiningDate() const;

	/**
	 * @brief prints all non active members
	 */
	void printNonActiveClients() const;

	/**
	 * @brief prints all services from a client of a given ID
	 * @param id id of the client to print its services
	 */
	void printClientServices(int index) const;

	/**
	 * @brief prints all vehicles
	 */
	void printAllVehicles() const;

	/**
	 * @brief prints all the vehicles ready to transport cargo
	 */
	void printAvailableVehicles() const;

	/**
	 * @brief prints all services that were requested by clients
	 */
	void printAllServicesWaiting() const;

	/**
	 * @brief validates a service of a client given a certain id
	 * @param id id of the client to validate service
	 */
	int validateClientService(int index);

	/**
	 * @brief print client service status (pending/received)
	 * @param id id of the client to check the service
	 */
	int checkClientServiceStatus(int index);

	/**
	 * @brief checks if exists in the company available cars to transport the packages of the service
	 * @param weight weight of the packages
	 * @return true or false depending on the availability of the cars
	 */
	bool existsAvailableCarsToTransport(int weight, std::list<Vehicle*>& vehiclesToTransport);

	/**
	 * @brief checks in the hash table if a given client is a non active client
	 * @param c client
	 * @return true or false depending on the activity of the client
	 */
	void checkNonActiveClients(Client* c);

	/**
	 * @brief frees all memory allocated by the company
	 */
	void freeMemory();
};



#endif /* MOVINGCOMPANY_H_ */
