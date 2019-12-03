/*
 * ClientsInterface.cpp
 *
 *  Created on: 11/11/2017
 *      Author: Francisco Maria / João Gama Amaral
 */

#include "ClientsInterface.h"

int checkClient(MovingCompany& company){
	int option, instruction;

	while(option != -1){

		std::cout << "\n\n\t\t\t\t\t\tSearch Client:" << std::endl;
		std::cout << "\t\t\t\t\t   How would you like to search the client?" << std::endl;
		std::cout << "\n\t\t\t\t\t\t1 - By Name" << std::endl;
		std::cout << "\t\t\t\t\t\t2 - By ID" << std::endl;
		std::cout << "\n\t\t\t\t\t\t0 - Go Back" << std::endl;
		std::cout << "\t\t\t\t\t       -1 - Exit Program" << std::endl;

		std::cout << "\n\t\t\t\t\tPlease enter an option: ";
		std::cin >> option;

		switch(option){
			case 1:
				instruction = searchClientByName(company);
				break;
			case 2:
				instruction = searchClientByID(company);
				break;
			case 0:
				return 0;
			case -1:
				return -1;
			default:
				std::cout <<"Please insert a valid option.\n" << std::endl;
				break;
			}
		if(instruction == 0) continue;
		if(instruction == -1) return -1;
		}

	return 1;
}

int searchClientByName(MovingCompany& company){

	std::string name;

	std::cout << "\n\t\t\t\t\t\t0 - Go Back" << std::endl;
	std::cout << "\t\t\t\t\t       -1 - Exit Program\n" << std::endl;
	std::cout << "\t\t\t\t\tPlease enter the client's name." <<std::endl;
	std::cout << "\t\t\t\t\tName: " << std::endl;

	std::cin.ignore();
	std::getline(std::cin, name);

	if(name == "0") return 0;
	if(name == "-1") return -1;

	try{
		company.printClient(name);
	}
	catch(NonExistingClient& nc){
		std::cout << "\t\t\t\tThere is no client with the name " << nc.getName();
	}
	return 0;
}

int searchClientByID(MovingCompany& company){

	int id;

	std::cout << "\t\t\t\t\t\t0 - Go Back" << std::endl;
	std::cout << "\t\t\t\t\t       -1 - Exit Program\n" << std::endl;
	std::cout << "\t\t\t\t\tPlease enter the client's ID." <<std::endl;
	std::cout << "\t\t\t\t\t\tID: ";

	std::cin >> id;

	if(id == 0) return 0;
	if(id == -1) return -1;

	int index;

	try{
		index = binarySearch(company.getClients(), id);
		if(index == -1)
			throw NonExistingClient(id);
	}
	catch(NonExistingClient& c){
		std::cout << "\n\t\t\t\t\t There is no client with the ID: " << c.getID() << std::endl;
		return 0;
	}

	std::cout << *company.getClients()[index];
	return 0;
}

int newParticularClient(MovingCompany& company){

	std::cout << "\n\t\t\t\t\t\t     NEW PARTICULAR CLIENT FORM\n" << std::endl;
	std::cout << "\t\t\t\t\t\t0 - Cancel\t-1 - Exit program\n" << std::endl;
	std::cout <<"\t\t\t\t\tPlease fill out this form in order to add the new client.\n\t\t\t\t\tYou can cancel or exit the "
			"program at any time just enter 0 to cancel or -1 to exit.\n\n"<< std::endl;

	std::string input;
	std::stringstream ss;

	std::cin.ignore();

		//-- NAME
	std::cout << "\t\t\t\tFull Name: ";
	std::getline(std::cin, input);

	if(input == "-1") return -1;
	else if(input == "0") return 0;

	std::string name = input;

	input.clear();

		// -- AGE
	int age;
	std::cout << "\n\t\t\t\tAge: ";
	std::cin >> age;

	if(age == -1) return -1;
	else if(age == 0) return 0;

		//-- NIF
	long int nif;
	std::cout << "\n\t\t\t\tNIF: ";
	std::cin >> nif;

	if(std::cin.fail()){
		std::cout << "Not a number.";
		return 0;
	}

	if(nif == -1) return -1;
	else if(nif == 0) return 0;

	input.clear();

		//-- ADDRESS
	std::cout << "\n\t\t\t\tStreet Adress: ";
	std::cin.ignore();
	std::getline(std::cin, input);

	if(input == "-1") return -1;
	else if(input == "0") return 0;

	std::string address = input;

	input.clear();

		//-- ZIPCODE
	std::cout << "\n\t\t\t\tZip Code: ";
	//std::cin.ignore();
	std::getline(std::cin, input);

	if(input == "-1") return -1;
	else if(input == "0") return 0;

	std::string zipCode = input;

	input.clear();

	//-- City
	std::cout << "\n\t\t\t\tCity: ";
	std::getline(std::cin, input);

	std::string city = input;

	input.clear();

	// -- Country
	std::cout << "\n\t\t\t\tCountry: ";
	std::getline(std::cin, input);

	std::string country = input;

		//-- DATE
	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, sizeof(buffer), "%d %m %y %H %M", timeinfo);

	int day, month, year, hour, minute;
	std::string bufs(buffer);
	std::stringstream aux;

	aux << bufs;

	aux >> day;
	aux >> month;
	aux >> year;
	aux >> hour;
	aux >> minute;

	year += 2000;

	int index = company.getClients().size()-1;
	Particular* c = new Particular(company.getClients()[index]->getId()+1,name, age, nif, address, zipCode, city, country, day, month, year, hour, minute);
	company.addClient(c);

	std::cout << "\n\n\t\t\t\t" << name << " has been added to the company." << std::endl;

	return 0;
}

int newCompanyClient(MovingCompany& company){

	std::cout << "\n\t\t\t\t\t\t     NEW COMPANY CLIENT FORM\n" << std::endl;
	std::cout << "\t\t\t\t\t\t0 - Cancel\t-1 - Exit program\n" << std::endl;
	std::cout <<"\t\t\t\t\tPlease fill out this form in order to add the new client.\n\t\t\t\t\tYou can cancel or exit the "
			"program at any time just enter 0 to cancel or -1 to exit.\n\n"<< std::endl;

	std::string input;
	std::stringstream ss;

	std::cin.ignore();

		//-- COMPANY NAME
	std::cout << "\t\t\t\tCompany Name: ";
	std::getline(std::cin, input);

	if(input == "-1") return -1;
	else if(input == "0") return 0;

	std::string name = input;

		//-- NIF
	long int nif;
	std::cout << "\n\t\t\t\tNIF: ";
	std::cin >> nif;//input;

	if(nif == -1) return -1;
	else if(nif == 0) return 0;

	input.clear();

		//-- ADDRESS
	std::cout << "\n\t\t\t\tStreet Adress: ";
	std::cin.ignore();
	std::getline(std::cin, input);

	if(input == "-1") return -1;
	else if(input == "0") return 0;

	std::string address = input;

	input.clear();

		//-- ZIPCODE
	std::cout << "\n\t\t\t\tZip Code: ";
	std::getline(std::cin, input);

	if(input == "-1") return -1;
	else if(input == "0") return 0;

	std::string zipCode = input;

	input.clear();

		// -- City
	std::cout << "\n\t\t\t\tCity: ";
	std::getline(std::cin, input);

	if(input == "-1") return -1;
	else if(input == "0") return 0;

	std::string city = input;

		// -- Country
	std::cout << "\n\t\t\t\tCountry: ";
	std::getline(std::cin, input);

	std::string country = input;

	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, sizeof(buffer), "%d %m %y %H %M", timeinfo);

	int day, month, year, hour, minute;
	std::string bufs(buffer);
	std::stringstream aux;

	aux << bufs;

	aux >> day;
	aux >> month;
	aux >> year;
	aux >> hour;
	aux >> minute;

	year += 2000;

	int index = company.getClients().size()-1;
	Company* c = new Company(company.getClients()[index]->getId()+1 ,name, nif, address, zipCode, city, country, day, month, year, hour, minute);

	company.addClient(c);

	std::cout << "\n\n\t\t\t\t" << name << " has been added to the company." << std::endl;

}

int addNewClient(MovingCompany& company){

	int option, instruction;

	while(option != -1){
		std::cout << "\n\n\t\t\t\t\t\t\t      NEW CLIENT FORM\n" << std::endl;
		std::cout << "\t\t\t\t\t\t\t1 - Add new Particular Client" << std::endl;
		std::cout << "\t\t\t\t\t\t\t2 - Add new Company Client\n" << std::endl;
		std::cout << "\t\t\t\t\t\t\t0 - Go back" << std::endl;
		std::cout << "\t\t\t\t\t\t       -1 - Exit Program\n" << std::endl;

		std::cout << "\n\t\t\t\t\tPlease enter an option: ";
		std::cin >> option;

		switch(option){
			case 1:
				instruction = newParticularClient(company);
				if(!instruction) continue;
				break;
			case 2:
				instruction = newCompanyClient(company);
				break;
			case 0:
				return 0;
			case -1:
				return -1;
		}
		if(instruction == 0 || instruction == -1) return instruction;
	}
	return -1;
}

int removeClientByID(MovingCompany& company){

	int enteredID;

	std::cout << "\t\t\t\t\t0 - Go Back and Cancel" << std::endl;
	std::cout << "\t\t\t\t\t-1 - Exit Program\n" << std::endl;
	std::cout << "\t\t\t\tID of the client you would like to remove: " << std::endl;

	std::cin >> enteredID;

	if(enteredID == 0 || enteredID == -1) return enteredID;

	try{
		company.removeClientByID(enteredID);
		std::cout << "\t\t\t\t\tClient successfully removed." << std::endl;
	}
	catch(NonExistingClient& nc){
		std::cout << "\n\t\t\t\tThere is no client with the ID: " << nc.getID() << std::endl;
	}

	return 0;
}


int removeClientByName(MovingCompany& company){

	std::string enteredName;

	std::cout << "\t\t\t\t0 - Go Back and Cancel\t\t\t\t-1 - Exit Program" << std::endl;
	std::cout << "\n\t\t\t\tPlease enter the name of the client you would like to remove: ";

	std::cin.ignore();
	std::getline(std::cin, enteredName);

	if(enteredName == "0") return 0;
	if(enteredName == "-1") return -1;

	try{
		company.removeClientByName(enteredName);
		std::cout << "\t\t\t\t\tClient successfully removed." << std::endl;
	}
	catch(NonExistingClient& nc){
		std::cout << "\n\t\t\t\tThere is no client with the name: " << nc.getName() << std::endl;
	}

	return 0;
}

int removeClientByJoiningDate(MovingCompany& company){

	int day, year, month;

	std::cout << "\n\t\t\t\tEnter the joining date of the client you would like to remove:" << std::endl;
	std::cout << "\t\t\t\t\tDay: ";
	std::cin >> day;

	if(day > 31){
		std::cout << "\n\t\t\t\tInvalid Day." << std::endl;
		return 0;
	}
	else if(day == -1) return -1;

	std::cout << "\t\t\t\t\tMonth: ";
	std::cin >> month;

	if(month < 1 || month > 12){
		std::cout << "Invalid Month." << std::endl;
		return 0;
	}
	else if(month == -1) return -1;

	std::cout << "\t\t\t\t\tYear: ";
	std::cin >> year;

	if(year == -1) return -1;
	else if(year < company.getFoundingDate().getYear())
		std::cout << "Invalid year." << std::endl;

	try{
		company.removeClientByJoiningDate(day, month, year);
		std::cout << "\t\t\t\t\tClient successfully removed.";
	}
	catch(NonExistingDate& nd){
		std::cout << "\t\t\tThere is no client with first registration date: " << nd.getDay() << "/" << nd.getMonth()
			<< "/" << nd.getYear() << std::endl;
	}
	return 0;
}

int removeClient(MovingCompany& company){
	int option, instruction;

	while(option != -1){
			std::cout << "\n\n\t\t\t\t\t\t    Remove Client Form\n" << std::endl;
			std::cout << "\t\t\t\t\t   How would you like to remove the client?\n" << std::endl;
			std::cout << "\t\t\t\t\t\t\t1 - By ID" << std::endl;
			std::cout << "\t\t\t\t\t\t\t2 - By Name" << std::endl;
			std::cout << "\t\t\t\t\t\t\t3 - By Joining Date\n" << std::endl;
			std::cout << "\t\t\t\t\t\t\t0 - Go Back" << std::endl;
			std::cout << "\t\t\t\t\t\t       -1 - Exit Program" << std::endl;

			std::cout << "\n\t\t\t\t\tPlease insert your option: ";
			std::cin >> option;

			switch(option){
				case 1:
					instruction = removeClientByID(company);		//Binary Search algorithm
					break;
				case 2:
					instruction = removeClientByName(company);		//Sequential Search algorithm
					break;
				case 3:
					instruction = removeClientByJoiningDate(company);	//Sequential Search algorithm
					break;
				case 0:
					return 0;
				case -1:
					return -1;
				default:
					std::cout << "\t\t\t\t\tPlease insert a valid option.";
					break;
			}
			if(instruction == 0) continue;
			if(instruction == 1) return -1;
		}
}


int printParticulars(MovingCompany& company){

	int option;

	while(option != -1){

		if(company.getParticularClients().size() == 0){
			std::cout << "\t\t\t\t\tThere are no particular clients registered." << std::endl;
			break;
		}

		std::cout << "\n\t\t\t\t\t\tPrint Particular Clients" << std::endl;
		std::cout << "\n\t\t\t\t\tHow would you like to print the particular clients?\n" << std::endl;
		std::cout << "\t\t\t\t\t\t1 - By ID" << std::endl;
		std::cout << "\t\t\t\t\t\t2 - By Name" << std::endl;
		std::cout << "\t\t\t\t\t\t3 - By joining date\n" << std::endl;
		std::cout << "\t\t\t\t\t\t0 - Go back" << std::endl;
		std::cout << "\t\t\t\t\t       -1 - Exit program.\n" << std::endl;

		std::cout << "\t\t\t\tPlease insert your option: ";
		std::cin >> option;

		switch(option){
			case 1:
				company.printParticularClientsByID();
				break;
			case 2:
				company.printParticularClientsByName();
				break;
			case 3:
				company.printParticularClientsByJoiningDate();
				break;
			case 0:
				return 0;
			case -1:
				return -1;
			default:
				std::cout << "\nPlease insert a valid option." << std::endl;
				break;
		}
	}

	return 0;

}

int printCompanies(MovingCompany& company){
	int option;

	while(option != -1){

		if(company.getCompaniesClients().size() == 0){
			std::cout << "\t\t\t\tThere are no company clients registered." << std::endl;
			break;
		}

		std::cout << "\n\t\t\t\t\t\tPrint Company Clients" << std::endl;
		std::cout << "\n\t\t\t\t\tHow would you like to print the company clients?\n" << std::endl;
		std::cout << "\t\t\t\t\t\t1 - By ID" << std::endl;
		std::cout << "\t\t\t\t\t\t2 - By Name" << std::endl;
		std::cout << "\t\t\t\t\t\t3 - By joining date\n" << std::endl;
		std::cout << "\t\t\t\t\t\t0 - Go back" << std::endl;
		std::cout << "\t\t\t\t\t       -1 - Exit program.\n" << std::endl;

		std::cout << "\t\t\t\t\tPlease insert your option: ";
		std::cin >> option;

		switch(option){
			case 1:
				company.printCompanyClientsByID();
				break;
			case 2:
				company.printCompanyClientsByName();
				break;
			case 3:
				company.printCompanyClientsByJoiningDate();
				break;
			case 0:
				return 0;
			case -1:
				return -1;
			default:
				std::cout << "\nPlease insert a valid option.\n" << std::endl;
				break;
		}
	}

	return 0;
}

int printClients(MovingCompany& company){

	int option;

	while(option != -1){

		if(company.getClients().size() == 0){
			std::cout << "\t\t\t\t\tThere are no clients registered." << std::endl;
			break;
		}

		std::cout << "\n\t\t\t\t\t\t\tPrint All Clients" << std::endl;
		std::cout << "\t\t\t\t\t\tHow would you like to print the clients?\n" << std::endl;
		std::cout << "\t\t\t\t\t\t\t1 - By ID" << std::endl;
		std::cout << "\t\t\t\t\t\t\t2 - By Name" << std::endl;
		std::cout << "\t\t\t\t\t\t\t3 - By joining date\n" << std::endl;
		std::cout << "\t\t\t\t\t\t\t0 - Go back" << std::endl;
		std::cout << "\t\t\t\t\t\t       -1 - Exit program.\n" << std::endl;

		std::cout << "\t\t\t\tPlease insert your option: ";
		std::cin >> option;

		switch (option){
			case 1:
				company.printClientsByID();
				break;
			case 2:								//This function prints clients by name using BUBBLE SORT!
				company.printClientsByName();
				break;
			case 3:								//This function prints clients by joining date using SELECTION SORT!
				company.printClientsByJoiningDate();
				break;
			case 0:
				return 0;
			case -1:
				return -1;
			default:
				std::cout << "\t\t\t\t\tPlease insert a valid option.\n" << std::endl;
				break;
		}
	}
	return 0;
}

int printVehicles(MovingCompany& company){

	std::cout << "\t\t\t\t\t\t      PRINT VEHICLES INFORMATION\n" << std::endl;

	if(company.getVehicles().size() == 0){
		std::cout << "\t\t\t\t\tThere are no vehicles associated with the company.\n" << std::endl;
		return 0;
	}

	company.printAllVehicles();
	return 0;
}

int printAvailableVehicles(MovingCompany& company){

	std::cout << "\t\t\t\t\t\t      PRINT AVAILABLE VEHICLES INFORMATION\n" << std::endl;

	company.printAvailableVehicles();
	return 0;
}

int printNonActiveClients(MovingCompany& company){

	if(!company.existsClients()){
		std::cout << "\t\t\t\t\tThere are no clients registered." << std::endl;
		return 0;
	}

	if(company.getNonActiveClients().size() == 0){
		std::cout << "\t\t\t\t\tThere are no non active clients registered." << std::endl;
		return 0;
	}

	std::cout << "\t\t\t\t\t\tPRINT ALL NON ACTIVE CLIENTS" << std::endl;

	company.printNonActiveClients();
	return 0;
}

int updateClientInfoAddress(MovingCompany& company, int index){

	std::cin.ignore();

	std::cout << "\n\n\t\t\t\tUPDATE " << company.getClients()[index]->getName() << " ADDRESS" << std::endl;
	std::cout << "\t\t\t\tPlease insert the new information:\n\t\t\t\tStreet: ";

	std::string newStreet;
	std::getline(std::cin, newStreet);

	std::string newCity;
	std::cout << "\n\t\t\t\tCity: ";
	std::getline(std::cin, newCity);

	std::string newZipCode;
	std::cout << "\n\t\t\t\tZip Code: ";
	std::getline(std::cin, newZipCode);

	std::string newCountry;
	std::cout << "\n\t\t\t\tCountry: ";
	std::getline(std::cin, newCountry);

	Address newAddress(newStreet, newZipCode, newCity, newCountry);

	company.getClients()[index]->updateAddress(newAddress);

	std::cout << "\n\t\t\t\tAddress was successful updated." << std::endl;

	return 0;
}

int updateClientInfoNIF(MovingCompany& company, int index){

	std::cout << "\n\t\t\t\tUPDATE " << company.getClients()[index]->getName() << " NIF" << std::endl;
	std::cout << "\n\t\t\t\tPlease insert the new information.\n\n\t\t\t\tNIF: ";

	long int newNif;

	std::cin >> newNif;
	company.getClients()[index]->updateNIF(newNif);

	std::cout << "\n\t\t\t\tNIF was successful updated." << std::endl;

	return 0;
}

int updateClientInfo(MovingCompany& company, int clientID){

	int index;

	try{
		index = binarySearch(company.getClients(), clientID);
		if(index == -1)
			throw NonExistingClient(clientID);
	}
	catch(NonExistingClient& c){
		std::cout << "\n\t\t\t\t\t There is no client with the ID: " << c.getID() << std::endl;
		return 0;
	}

	std::cout << "\t\t\t\t\tWhat would you like to update?\n" << std::endl;
	std::cout << "\t\t\t\t\t\t1 - Address" << std::endl;
	std::cout << "\t\t\t\t\t\t2 - NIF" << std::endl;
	std::cout << "\t\t\t\tInsert the option you would like to update: ";

	int option;

	while(option != -1){
		std::cin >> option;

		switch(option){
			case 1:
				return updateClientInfoAddress(company, index);
			case 2:
				return updateClientInfoNIF(company, index);
			case 0:
				return 0;
			case -1:
				return -1;
			default:
				std::cout << "\t\t\t\tPlease insert a valid option: ";
				break;
		}
	}

	return 0;
}

int updateClientsInfo(MovingCompany& company){

	if(!company.existsClients()){
		std::cout << "There are no client registered in the company." << std::endl;
		return 0;
	}

	int enteredID;

	std::cout << "\n\t\t\t\t\t\t\tUPDATE CLIENT INFO\n" << std::endl;
	std::cout << "\t\t\t\tInsert the client ID you would like to update info: ";
	std::cin >> enteredID;

	if(enteredID == 0) return 0;
	if(enteredID == -1) return -1;

	try{
		company.printClient(enteredID);
	}
	catch(NonExistingClient& nc){
		std::cout << "There is no client with the ID: " << nc.getID() << std::endl;
		return 0;
	}

	return updateClientInfo(company, enteredID);
}


