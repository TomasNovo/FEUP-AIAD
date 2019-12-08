/*
 * Client.h
 *
 *  Created on: 31/10/2017
 *      Author: Francisco Maria / João Gama Amaral
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include "Libraries.h"
#include "Date.h"
#include "Address.h"
#include "Service.h"

/**
 * 	@brief Class that stores all of the client related information.
 */
class Client{
	int id;
	long int NIF;
	std::string name;
	Address address;
	Date joiningDate;
	std::vector<Service*> servicesRequested;
	Date lastService;
	static int numberOfClients;
public:
	/**
	 * @brief Default Constructor
	 */
	Client(){};

	/**
	 * @brief Default Destructor
	 */
	~Client(){};

	/**
	 * @brief Constructor to new Client
	 */
	Client(std::string name, long int nif, std::string address, std::string zipCode, std::string city, std::string country, int firstDay, int firstMonth, int firstYear, int hour, int minute);

	/**
	 * @brief Client constructor w/ ID (already existing clients)
	 */
	Client(int ID, std::string name, long int nif, std::string address, std::string zipCode, std::string city, std::string country, int firstDay, int firstMonth, int firstYear, int hour, int minute);

	/**
	 * @brief Gets client ID
	 * @return ID number
	 */
	int getId() const;

	/**
	 * @brief Gets client NIF
	 * @return NIF number
	 */
	long int getNIF() const;

	/**
	 * @brief Gets client name
	 * @return string with name
	 */
	std::string getName() const;

	/**
	 * @brief Gets client address
	 * @return address
	 */
	const Address& getAddress() const;

	/**
	 * @brief Gets zip code address
	 * @return zip code
	 */
	std::string getZipCode() const;

	/**
	 * @brief Checks if clients are equal
	 * @param c1 another client
	 * @return true or false
	 */
	bool operator ==(const Client& c1);

	/**
	 * @brief Gets client's joining date to the company
	 * @return joining date
	 */
	const Date& getJoiningDate() const;

	/**
	 * @brief Gets client's last service date
	 * @return last service date
	 */
	const Date& getLastService() const;

	/**
	 * @brief Gets all clients services requested
	 * @return vector of services requested by the client
	 */
	std::vector<Service*> getServicesRequested();

	/**
	 * @brief Adds new service to the clients service requested
	 * @param s service pointer
	 */
	void addNewService(Service* s);

	/**
	 * @brief Updates client Address
	 * @param a new address
	 */
	void updateAddress(Address& a);

	/**
	 * @brief Updates client's NIF
	 * @param nif new nif
	 */
	void updateNIF(long int nif);

	/**
	 * @brief Updated client's last service date
	 * @param d date of the last service
	 */
	void updateLastService(Date& d);

	/**
	 * @brief Prints all services requested by the client
	 */
	void printServices() const;

	/**
	 * @brief Prints all services resumed
	 */
	void printServicesResume() const;

	/**
	 * @brief Prints the status of the clients service passed as parameter by ID
	 * @param sID service ID to check service status
	 */
	void checkServiceStatus(int sID) const;

	/**
	 * @brief Validates client service
	 * @param sID represents the service ID to validate its payment
	 */
	void validatePayment(int sID);

	/**
	 * @brief Deletes all of the services associated w/ the client
	 */
	void deleteServices();

	/**
	 * @brief Checks if two clients are the same
	 * @return true or false
	 */
	bool operator ==(Client& c);

	/**
	 * @brief Checks if a client is particular
	 * @return true or false if is or not a particular client
	 */
	virtual bool isParticular() {};

	/**
	 * @brief Gets client age if particular
	 * @return client's age
	 */
	virtual int getAge() {}

	/**
	 * @brief Gets the total amount of clients registered in the company
	 * @return total amount
	 */
	static int getNumberOfClients();

	/**
	 * @brief Prints a client
	 * @param o ostream
	 * @param c1 client
	 * @return ostream
	 */
	friend std::ostream& operator<<(std::ostream& o, const Client & c1){
		o << "Client's Info:\n\t" << "Name: " << c1.getName() << "\n\tID: " << c1.getId()
				<< "\n\tRegistered in: " << c1.getJoiningDate() << "\n\t" << c1.getAddress() << "\n" << std::endl;
		return o;
	}
};

/**
 * 	@brief Class that represents a company client.
 */
class Company: public Client{
	static int numberOfCompanies;
public:
	/**
	 * @brief Constructor to the Company client
	 */
	Company(std::string name, long int nif, std::string address, std::string zipCode, std::string city, std::string country, int firstDay, int firstMonth, int firstYear, int hour, int minute);

	/**
	 * @brief Constructor to the Company Client
	 */
	Company(int id, std::string name, long int nif, std::string address, std::string zipCode, std::string city, std::string country, int firstDay, int firstMonth, int firstYear, int hour, int minute);

	/**
	 * @brief gets the total amount of company clients registered in the company
	 * @return total amount of companies
	 */
	static int getNumberOfCompanies();

	/**
	 * @brief Check if is or not a particular client
	 * @return false
	 */
	bool isParticular();
};

/**
 * 	@brief Class that represents a particular client.
 */
class Particular: public Client{
	int age;
	static int numberOfParticulars;
public:

	/**
	 * @brief Constructor to Particular Client
	 */
	Particular(std::string name, int age, long int nif, std::string address, std::string zipCode, std::string city, std::string country, int firstDay, int firstMonth, int firstYear, int hour, int minute);

	/**
	 * @brief Constructor to Particular Client
	 */
	Particular(int id, std::string name, int age, long int nif, std::string address, std::string zipCode, std::string city, std::string country, int firstDay, int firstMonth, int firstYear, int hour, int minute);

	/**
	 * @brief gets particular client age
	 * @return age
	 */
	int getAge();

	/**
	 * @brief checks if it is or not a particular client
	 * @return true;
	 */
	bool isParticular();

	/**
	 * @brief get total number of particulars
	 * @return amount of particular clients
	 */
	static int getNumberOfParticulars();
};

#endif /* CLIENT_H_ */
