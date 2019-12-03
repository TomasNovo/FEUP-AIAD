/*
 * Interface.cpp
 *
 *  Created on: 02/11/2017
 *      Author: Francisco Maria / João Gama Amaral
 */

#include "Interface.h"

void run(MovingCompany& company){
	bool exit = false;

	std::cout << "\t\t\t\t\t\t   Welcome to Company Helping Software.\n" << std::endl;

	while(!exit){
		int option = showMenu(company);

		switch(option){
			case 1:
				exit = showClientsMenu(company);
				break;
			case 2:
				exit = showServicesMenu(company);
				break;
			case 3:
				exit = showVehiclesMenu(company);
				break;
			case -1:
				exit = true;
				break;
			default:
				std::cout << "Please insert a valid option.\n";
				break;
		}

		if(exit) break;
	}
}

int showMenu(MovingCompany& company){
	int option;

	std::cout << "\t\t\t\t\t\t\t\tMENU\n" << std::endl;
	std::cout << "\t\t\t\t\t\t\t1 - Clients" << std::endl;
	std::cout << "\t\t\t\t\t\t\t2 - Services" << std::endl;
	std::cout << "\t\t\t\t\t\t\t3 - Vehicles" << std::endl;
	std::cout << "\n\t\t\t\t\t\t       -1 - Exit Program\n\n" << std::endl;
	std::cout << "\n\t\t\t\t\tPlease enter an option: ";

	std::cin >> option;
	return option;
}

bool showClientsMenu(MovingCompany& company){
	int option;

	while(option != -1){
		std::cout <<"\n\n\t\t\t\t\t\t\t\tCLIENTS\n" << std::endl;
		std::cout << "\t\t\t\t\t\t\t1 - Check client" << std::endl;
		std::cout << "\t\t\t\t\t\t\t2 - Add client" << std::endl;
		std::cout << "\t\t\t\t\t\t\t3 - Remove client" << std::endl;
		std::cout << "\t\t\t\t\t\t\t4 - Print particular clients" << std::endl;
		std::cout << "\t\t\t\t\t\t\t5 - Print company clients" << std::endl;
		std::cout << "\t\t\t\t\t\t\t6 - Print all clients" << std::endl;
		std::cout << "\t\t\t\t\t\t\t7 - Print non active clients" << std::endl;
		std::cout << "\t\t\t\t\t\t\t8 - Update Client's Info\n" << std::endl;
		std::cout << "\t\t\t\t\t\t\t0 - Go back" << std::endl;
		std::cout << "\t\t\t\t\t\t       -1 - Exit program.\n" << std::endl;

		int instruction;

		std::cout << "\n\t\t\t\t\tPlease enter an option: ";
		std::cin >> option;

		switch(option){
			case 1:
				instruction = checkClient(company);
				break;
			case 2:
				instruction = addNewClient(company);
				break;
			case 3:
				instruction = removeClient(company);
				break;
			case 4:
				instruction = printParticulars(company);
				break;
			case 5:
				instruction = printCompanies(company);
				break;
			case 6:
				instruction = printClients(company);
				break;
			case 7:
				instruction = printNonActiveClients(company);
				break;
			case 8:
				instruction = updateClientsInfo(company);
				break;
			case 0:
				return false;
			case -1:
				instruction = -1;
				break;
			default:
				std::cout << "Please insert a valid option.";
				break;
		}

		if(instruction == -1) return true;
		else if(instruction == 0) continue;
	}
	return false;
}


bool showServicesMenu(MovingCompany& company){
	int option;

	while(option != -1){

		std::cout << "\n\n\t\t\t\t\t\t\t\tSERVICES\n" << std::endl;
		std::cout << "\t\t\t\t\t\t\t1 - Request New Service" << std::endl;
		std::cout << "\t\t\t\t\t\t\t2 - Check Service Status" << std::endl;
		std::cout << "\t\t\t\t\t\t\t3 - Print Client's Services History" << std::endl;
		std::cout << "\t\t\t\t\t\t\t4 - Validate Payment" << std::endl;
		std::cout << "\t\t\t\t\t\t\t5 - Show service bill" << std::endl;
		std::cout << "\t\t\t\t\t\t\t6 - Print Requested Services\n" << std::endl;
		std::cout << "\t\t\t\t\t\t\t0 - Go back" << std::endl;
		std::cout << "\t\t\t\t\t\t       -1 - Exit program.\n" << std::endl;

		int instruction;

		std::cout << "\n\t\t\t\t\tPlease enter an option: ";
		std::cin >> option;

		switch(option){
			case 1:
				instruction = newService(company);
				break;
			case 2:
				instruction = checkClientsServiceStatus(company);
				break;
			case 3:
				instruction = printClientsServices(company);
				break;
			case 4:
				instruction = validateClientsPayment(company);
				break;
			case 5:
				instruction = printServicesBill(company);
				break;
			case 6:
				instruction = printServicesRequests(company);
				break;
			case 0:
				return false;
			case -1:
				return true;
			default:
				std::cout << "Please insert a valid option.";
				break;
		}

		if(instruction == 0) continue;
		if(instruction == -1) return true;
	}

	return true;
}

bool showVehiclesMenu(MovingCompany& company){
	int option;

	while(option != -1){
		std::cout << "\n\n\t\t\t\t\t\t\t\tVEHICLES" << std::endl;
		std::cout << "\n\t\t\t\t\t\t\t1 - Print all vehicles" << std::endl;
		std::cout << "\t\t\t\t\t\t\t2 - Print only available vehicles" << std::endl;
		std::cout << "\n\t\t\t\t\t\t\t0 - Go back" << std::endl;
		std::cout << "\t\t\t\t\t\t       -1 - Exit program" << std::endl;

		int instruction;

		std::cout << "\n\t\t\t\t\tPlease enter an option: ";
		std::cin >> option;

		switch(option){
			case 1:
				instruction = printVehicles(company);
				break;
			case 2:
				instruction = printAvailableVehicles(company);
				break;
			case 0:
				return false;
			case -1:
				return true;
			default:
				std::cout << "\n\t\t\tPlease insert a valid option.";
				break;
		}

		if(instruction == 0) continue;
		if(instruction == -1) return true;
	}

	return true;
}


