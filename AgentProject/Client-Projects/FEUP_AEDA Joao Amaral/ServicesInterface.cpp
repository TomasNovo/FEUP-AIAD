/*
 * ServicesInterface.cpp
 *
 *  Created on: 12/11/2017
 *      Author: Francisco Maria / João Gama Amaral
 */

#include "ServicesInterface.h"

void getClientIndex(int& index, MovingCompany& company, int idClient){

	index = binarySearch(company.getClients(), idClient);

	if(index == -1)
		throw NonExistingClient(idClient);
}

void getActualDateService(Date& actualDate){

	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, sizeof(buffer), "%d %m %y %H %M", timeinfo);

	int day_now, month_now, year_now, hour_now, minute_now;
	std::string bufs(buffer);
	std::stringstream aux;

	aux << bufs;

	aux >> day_now;
	aux >> month_now;
	aux >> year_now;
	year_now += 2000;
	aux >> hour_now;
	aux >> minute_now;

	actualDate.setDay(day_now); actualDate.setMonth(month_now);
	actualDate.setYear(year_now); actualDate.setHour(hour_now);
	actualDate.setMinute(minute_now);
}

int getOriginInfo(MovingCompany& company, int& weight, Address& origin){

	std::cout << "\t\t\t\t    ORIGIN INFO:\n";
	std::cout << "\n\t\t\t\tEnter the total weight of the volumes (KG): ";
	std::cin >> weight;

	if(weight == 0) return 0;
	else if(weight == -1) return -1;

	std::cout << "\n\t\t\tSelect from the list of Countries the one where the package will be sent.\n\n";
	company.printAllCountriesToOperate();

	int idOrigin;
	std::cout << "\n\t\t\t\tCountry: ";
	std::cin.ignore();
	std::cin >> idOrigin;

	std::cout << "\n\t\t\t\tCity: ";
	std::string city;
	std::cin.ignore();
	std::getline(std::cin, city);

	std::cout << "\n\t\t\t\tStreet Address: ";
	std::string address;
	std::getline(std::cin, address);

	std::cout << "\n\t\t\t\tZip Code: ";
	std::string zipCode;
	std::getline(std::cin, zipCode);

	origin.setStreet(address);
	origin.setCity(city);
	origin.setZipCode(zipCode);
	origin.setCountry(company.getCountriesToOperate()[idOrigin-1]->getName());

	return idOrigin;
}

int getDestinationInfo(MovingCompany& company, int idOrigin, Address& destination){

	std::cout << "\n\n\t\t\t\t\t     DESTINATION INFO:\n";

	std::cout << "\n\t\t\tSelect from the list of Countries the one where the package will be received.\n\n";
	company.printCountriesToOperateFrom(company.getCountriesToOperate()[idOrigin-1]);

	int idDestination;
	std::cout << "\n\n\t\t\t\tCountry: ";
	std::cin >> idDestination;

	std::cout << "\n\t\t\t\tCity: ";
	std::string city;
	std::cin.ignore();
	std::getline(std::cin, city);

	std::cout << "\n\t\t\t\tStreet Address: ";
	std::string address;
	std::getline(std::cin, address);

	std::cout << "\n\t\t\t\tZip Code: ";
	std::string zipCode;
	std::getline(std::cin, zipCode);

	destination.setStreet(address);
	destination.setZipCode(zipCode);
	destination.setCity(city);
	destination.setCountry(company.getCountryDestination(company.getCountriesToOperate()[idOrigin-1], idDestination));

	return idDestination;
}

int getBeginningServiceDate(Date& beginningDate){

	int day, month, year, hour, minutes;

	std::cout << "\n\n\t\t\t\t\t\tDATE INFO:" << std::endl;

	std::cout << "\n\n\t\t\t\tDay: ";
	std::cin >> day;
	if(day < 1 || day > 31){
		std::cout << "\n\t\t\t\t\tThe day you entered is not valid." << std::endl;
		return 0;
	}

	std::cout << "\n\n\t\t\t\tMonth: ";
	std::cin >> month;
	if(month < 1 || month > 12){
		std::cout << "\n\t\t\t\t\tThe month you entered is not valid." << std::endl;
		return 0;
	}

	std::cout << "\n\n\t\t\t\tYear: ";
	std::cin >> year;
	std::cout << "\n\n\t\t\t\tHour: ";
	std::cin >> hour;
	if(hour < 0 || hour > 24){
		std::cout << "\n\t\t\t\t\tThe year you have entered is not valid." << std::endl;
		return 0;
	}

	std::cout << "\n\n\t\t\t\tMinute: ";
	std::cin >> minutes;
	if(minutes < 0 || minutes > 60){
		std::cout << "\n\t\t\t\t\tThe minute you have entered is not valid." << std::endl;
		return 0;
	}

	beginningDate.setDay(day); beginningDate.setMonth(month);
	beginningDate.setYear(year); beginningDate.setHour(hour);
	beginningDate.setMinute(minutes);
}

int getRandomNumberBetweenValues(int minValue, int maxValue){
	return rand()%(maxValue - minValue + 1)+minValue;
}

int getRandomHour(){			//Só trabalha das 8h as 19h
	return getRandomNumberBetweenValues(8, 19);
}

int getRandomMinute(){
	return getRandomNumberBetweenValues(0, 59);
}

int getShippingZone1Duration(){
	return getRandomNumberBetweenValues(5, 8);
}

int getShippingZone2Duration(){
	return getRandomNumberBetweenValues(14, 20);
}

void setPackagingDates(Date& packagingBeginning, Date& packagingEnding, Date& beginningDate){

	packagingBeginning = beginningDate;

	packagingBeginning.setHour(beginningDate.getHour()+2);

	packagingEnding.setHour(getRandomHour());
	packagingEnding.setMinute(getRandomMinute());

	if(packagingBeginning.getDay() < 31){
		packagingEnding.setDay(beginningDate.getDay()+1);
		packagingEnding.setMonth(beginningDate.getMonth());
		packagingEnding.setYear(beginningDate.getYear());
	}
	else{
		packagingEnding.setDay(1);

		if(packagingBeginning.getMonth() >= 12){
			packagingEnding.setMonth(1);
			packagingEnding.setYear(beginningDate.getYear()+1);
		}else{
			packagingEnding.setMonth(beginningDate.getMonth()+1);
			packagingEnding.setYear(beginningDate.getYear());
		}
	}
}

void setShippingDates(Date& shippingBeginning, Date& shippingEnding, Date& beginningDate, int zone){

	int endingDay, shippingDays;

	shippingBeginning = beginningDate;
	shippingBeginning.setHour(beginningDate.getHour()+2);
	shippingBeginning.setMinute(getRandomMinute());

	if(zone == 1){
		shippingDays = getShippingZone1Duration();				// 5 to 7 days
	}
	else{
		shippingDays = getShippingZone2Duration();				// 14 to 20 days
	}

	endingDay = shippingBeginning.getDay() + shippingDays;

	if(endingDay > 31){
		shippingEnding.setDay((endingDay%31) + 1);
		if(beginningDate.getMonth() == 12){
			shippingEnding.setMonth(1);
			shippingEnding.setYear(beginningDate.getYear()+1);
		}else{
			shippingEnding.setMonth(beginningDate.getMonth()+1);
			shippingEnding.setYear(beginningDate.getYear());
		}
	}else{
		shippingEnding.setDay(endingDay); shippingEnding.setMonth(beginningDate.getMonth());
		shippingEnding.setYear(beginningDate.getYear());
	}

	shippingEnding.setHour(getRandomHour()); shippingEnding.setMinute(getRandomMinute());
}

void setDeliveryDates(Date& deliveryBeginning, Date& deliveryEnding, Date& beginningDate){

	deliveryBeginning = beginningDate;
	deliveryBeginning.setHour(beginningDate.getHour()+2);
	deliveryBeginning.setMinute(getRandomMinute());

	int endingDate = deliveryBeginning.getDay()+1;

	if(endingDate <= 31){
		deliveryEnding.setDay(deliveryBeginning.getDay()+1);
		deliveryEnding.setMonth(deliveryBeginning.getMonth());
		deliveryEnding.setYear(deliveryBeginning.getYear());
	}else{
		deliveryEnding.setDay(1);
		if(deliveryBeginning.getMonth() == 12){
			deliveryEnding.setMonth(1);
			deliveryEnding.setYear(deliveryBeginning.getYear()+1);
		}else{
			deliveryEnding.setMonth(deliveryBeginning.getMonth()+1);
			deliveryEnding.setYear(deliveryBeginning.getYear());
		}
	}
	deliveryEnding.setHour(getRandomHour()); deliveryEnding.setMinute(getRandomMinute());
}

void setDeliveryDates(Date& deliveryBeginning, Date& deliveryEnding, Date& beginningDate, int daysWarehouse){

	Date warehousingEnd = beginningDate;
	int warehouseFinalDay = beginningDate.getDay()+daysWarehouse;

	if(warehouseFinalDay > 31){
		warehousingEnd.setDay(warehouseFinalDay%31);

		if(beginningDate.getMonth() == 12){
			warehousingEnd.setMonth(1);
			warehousingEnd.setYear(beginningDate.getYear()+1);
		}
		else{
			warehousingEnd.setMonth(beginningDate.getMonth()+1);
		}
	}
	else
		warehousingEnd.setDay(warehouseFinalDay);

	warehousingEnd.setHour(12);			//o Warehousing acaba sempre no último dia às 12h
	warehousingEnd.setMinute(0);

	setDeliveryDates(deliveryBeginning, deliveryEnding, warehousingEnd);
}
void setATMPayment(MovingCompany& company, Service* s, bool show){

	ATM* atm = new ATM(company.getEntity());
	s->setPayment(atm);

	if(show){
		std::cout << "\n\t\t\t\t\tPAYMENT DETAILS:\n" << std::endl;
		std::cout << "\n\t\t\t\t    Entity: ";
		std::cout << atm->getEntity();
		std::cout << "\n\t\t\t\t    Reference: ";
		std::cout << atm->getReference();
		std::cout << "\n\t\t\t\t    Montant: ";
		std::cout << s->getTotalCost() << "€";
	}
}

void setCreditCardPayment(MovingCompany& company, Service* s, bool show){

	int month;
	std::string ccNumber;

	if(show){
		std::cout << "\n\t\t\t\t\tPAYMENT DETAILS:\n" << std::endl;
		std::cout << "\n\t\t\t\t Credit Card Number: ";
		std::cin >> ccNumber;
		std::cout << "\n\t\t\t\t Validation month: ";
		std::cin >> month;
		std::cout << "\n\t\t\t\t Montant: " << s->getTotalCost() << "€";
	}
}

void setBankTransferPayment(MovingCompany& company, Service* s, bool show){

	BankTransfer* bt = new BankTransfer(company.getIBAN());
	s->setPayment(bt);

	if(show){
		std::cout << "\n\t\t\t\t\tPAYMENT DETAILS:\n" << std::endl;
		std::cout << "\n\t\t\t\t   IBAN: " << bt->getIBAN();
		std::cout << "\n\t\t\t\t   Montant: " << s->getTotalCost() << "€";
	}
}

void setEndOfMonthPayment(MovingCompany& company, Service* s, bool show){

	EndOfMonth* eom = new EndOfMonth();
	s->setPayment(eom);

	if(show){
		std::cout << "\n\t\t\t\tThis service has been added to client's debt. It is payable until the end of the month.";
		std::cout << "\n\t\t\t\t\t   Montant: " << s->getTotalCost() << "€" << std::endl;
		std::cout << s->getPayment()->getPaymentType();
	}
}

// Returns 0 or -1 depending on user input or 1 if succeeded.
int setTypeOfPaymentParticular(MovingCompany& company, Service* s, bool show){

	std::cout << "\n\t\t\t\tChoose the type of payment:\n" << std::endl;
	std::cout << "\t\t\t\t\t\t1 - ATM" << std::endl;
	std::cout << "\t\t\t\t\t\t2 - Bank Transfer\n" << std::endl;
	std::cout << "\t\t\t\t\t\t   Option: ";

	int option;
	std::cin >> option;

	while(std::cin.fail()){
		std::cout << "\t\t\t\t\t\tNot a valid option.";
		std::cout << "\t\t\t\t\t\t    Option: ";
		std::cin >> option;
	}

	switch(option){
		case 1:
			setATMPayment(company, s, show);
			break;
		case 2:
			setBankTransferPayment(company, s, show);
			break;
		case 0:
			return 0;
		case -1:
			return -1;
		default:
			break;
	}
	return 1;
}

// Returns 0 or -1 depending on user input or 1 if succeeded.
int setTypeOfPaymentCompany(MovingCompany& company, Service* s, bool show){

	std::cout << "\n\t\t\t\tChoose the type of payment:\n" << std::endl;
	std::cout << "\t\t\t\t\t\t1 - ATM" << std::endl;
	std::cout << "\t\t\t\t\t\t2 - Credit Card" << std::endl;
	std::cout << "\t\t\t\t\t\t3 - Bank Transfer" << std::endl;
	std::cout << "\t\t\t\t\t\t4 - End of the Month\n" << std::endl;

	int option;
	std::cin >> option;

	while(std::cin.fail()){
		std::cout << "\t\t\t\t\t\tNot a valid option.";
		std::cout << "\t\t\t\t\t\t    Option: ";
		std::cin >> option;
	}

	switch(option){
		case 1:
			setATMPayment(company, s, show);
			break;
		case 2:
			setCreditCardPayment(company, s, show);
			break;
		case 3:
			setBankTransferPayment(company, s, show);
			break;
		case 4:
			setEndOfMonthPayment(company, s, show);
			break;
		case 0:
			return 0;
		case -1:
			return -1;
		default:
			break;
	}
	return 1;
}

int newRegisteredClientService(MovingCompany& company){

	int idClient;

	std::cout << "\n\n\t\t\t\t\t     REQUEST SERVICE TO REGISTERED CLIENT\n" << std::endl;

	std::cout << "\t\t\t\t    Enter the ID of the client to add a new service: ";
	std::cin >> idClient;

	if(idClient == 0) return 0;
	else if(idClient == -1) return -1;

	int index;

	try{
		getClientIndex(index, company, idClient);
	}
	catch(NonExistingClient& c){
		std::cout << "\n\t\t\t\t\t There is no client with the ID: " << c.getID() << std::endl;
		return 0;
	}

	std::cout << "\n\n\t\t\t\t    Fill out this form in order to create a new service.\n" << std::endl;

	int weight, idOrigin, idDestination;
	Address origin, destination;

	idOrigin = getOriginInfo(company, weight, origin);
	idDestination = getDestinationInfo(company, idOrigin, destination);

	Date beginningDate;
	int check = getBeginningServiceDate(beginningDate);

	if(check == 0) return 0;
	else if(check == -1) return -1;

	Date actualDate;
	getActualDateService(actualDate);

	if(beginningDate < actualDate){
		std::cout << "\t\t\t\t\tYou have entered a non valid date (this date is before today).";
		return 0;
	}

	std::string response;
	std::cin.ignore();
	std::cout << "\n\t\t\t\t\tDo the volumes need warehousing? [y | n] : ";
	std::getline(std::cin, response);

	srand(time(NULL));

	std::list<Vehicle*> vehiclesToTransport;

	// This service does not require warehousing so it is a "Transport service"
	if(response == "n" || response == "N"){				//TRANSPORT

		if(!company.existsAvailableCarsToTransport(weight, vehiclesToTransport)){

			Transport* waitingT= new Transport(origin, destination, weight, actualDate);
			int checkReturn;

			if(company.getClients()[index]->isParticular())					// PARTICULAR CLIENT
				checkReturn = setTypeOfPaymentParticular(company, waitingT, false);
			else															// COMPANY  CLIENT
				checkReturn = setTypeOfPaymentCompany(company, waitingT, false);

			ServiceRequest* transportR = new ServiceRequest(company.getClients()[index]->getId(), waitingT);

			company.addServiceWaiting(transportR);

			std::cout << "\t\t\tWARNING: At the moment there are no vehicles available for transport."
					"\n\t\t\tYour service will be on hold until "
					"vehicles are freed." << std::endl;
			return 0;
		}

		Date packagingB, packagingE, shippingB,
				shippingE, deliveryB, deliveryE;

		setPackagingDates(packagingB, packagingE, beginningDate);
		setShippingDates(shippingB, shippingE, packagingE, destination.getCountry().getZone());
		setDeliveryDates(deliveryB, deliveryE, shippingE);

		Date endingDate = deliveryE;
		endingDate.setHour(deliveryE.getHour() + getRandomNumberBetweenValues(1, 3));
		endingDate.setMinute(getRandomMinute());

		Transport* svcT = new Transport(origin, destination, weight, beginningDate, endingDate);
		int idT = svcT->getID();

		Packaging* p = new Packaging(packagingB, packagingE, weight, idT);
		Shipping* s = new Shipping(shippingB, shippingE, weight, idT);
		Delivery* d = new Delivery(deliveryB, deliveryE, weight, idT);

		svcT->setPackaging(p);
		svcT->setShipping(s);
		svcT->setDelivery(d);
		svcT->setVehiclesUsed(vehiclesToTransport);

		if(company.getCountryDestination(company.getCountriesToOperate()[idOrigin-1], idDestination).getZone() == 1){
			svcT->addZone(ZONE_1);
			svcT->addBaseRate(company.getCountryDestination(company.getCountriesToOperate()[idOrigin-1], idDestination).getBaseRate());
		}
		else{
			svcT->addZone(ZONE_2);
			svcT->addBaseRate(company.getCountryDestination(company.getCountriesToOperate()[idOrigin-1], idDestination).getBaseRate());
		}

		int checkReturn;

		if(company.getClients()[index]->isParticular())					// PARTICULAR CLIENT
			checkReturn = setTypeOfPaymentParticular(company, svcT, true);
		else															//   COMPANY  CLIENT
			checkReturn = setTypeOfPaymentCompany(company, svcT, true);

		if(checkReturn == 0) return 0;
		else if(checkReturn == -1) return -1;

		company.checkNonActiveClients(company.getClients()[index]);
		company.addServiceBill(company.getClients()[index], svcT);
		company.getClients()[index]->addNewService(svcT);

	}
	else if(response == "y" || response == "Y"){					//WAREHOUSING

		int daysWarehouse;

		std::cout << "\n\t\t\t\tHow many days will the volumes be in the warehouse? ";
		std::cin >> daysWarehouse;

		if(!company.existsAvailableCarsToTransport(weight, vehiclesToTransport)){

			Warehousing* waitingW = new Warehousing(origin, destination, weight, actualDate, daysWarehouse);

			int checkReturn;

			if(company.getClients()[index]->isParticular())					// PARTICULAR CLIENT
				checkReturn = setTypeOfPaymentParticular(company, waitingW, false);
			else															// COMPANY  CLIENT
				checkReturn = setTypeOfPaymentCompany(company, waitingW, false);

			ServiceRequest* warehousingR = new ServiceRequest(company.getClients()[index]->getId(), waitingW);
			company.addServiceWaiting(warehousingR);

			std::cout << "\t\t\tWARNING: At the moment there are no vehicles available for transport."
					"\n\t\t\tYour service will be on hold until "
					"vehicles are freed." << std::endl;
			return 0;
		}

		Date packagingB, packagingE, shippingB,
				shippingE, deliveryB, deliveryE, warehousingE;

		setPackagingDates(packagingB, packagingE, beginningDate);
		setShippingDates(shippingB, shippingE, packagingE, destination.getCountry().getZone());
		setDeliveryDates(deliveryB, deliveryE, shippingE, daysWarehouse);

		Date endingDate = deliveryE;
		endingDate.setHour(deliveryE.getHour() + getRandomNumberBetweenValues(1, 3));		//O serviço acaba quando funcionário concluir
		endingDate.setMinute(getRandomMinute());											//o serviço (entre 1 a 3 horas após a entrega)

		Warehousing* svcW = new Warehousing(origin, destination, weight, beginningDate, endingDate, daysWarehouse);
		int idW = svcW->getID();

		Packaging* p = new Packaging(packagingB, packagingE, weight, idW);
		Shipping* s = new Shipping(shippingB, shippingE, weight, idW);
		Delivery* d = new Delivery(deliveryB, deliveryE, weight, idW);

		svcW->setPackaging(p);
		svcW->setShipping(s);
		svcW->setDelivery(d);

		if(company.getCountryDestination(company.getCountriesToOperate()[idOrigin-1], idDestination).getZone() == 1){
			svcW->addZone(ZONE_1);
			svcW->addBaseRate(company.getCountryDestination(company.getCountriesToOperate()[idOrigin-1], idDestination).getBaseRate());
		}
		else{
			svcW->addZone(ZONE_2);
			float zone2Increase = company.getCountryDestination(company.getCountriesToOperate()[idOrigin-1], idDestination).getBaseRate();
			svcW->addBaseRate(zone2Increase);
		}

		int checkReturn;

		if(company.getClients()[index]->isParticular())					// PARTICULAR CLIENT
			checkReturn = setTypeOfPaymentParticular(company, svcW, true);
		else															// COMPANY  CLIENT
			checkReturn = setTypeOfPaymentCompany(company, svcW, true);

		company.checkNonActiveClients(company.getClients()[index]);
		company.addServiceBill(company.getClients()[index], svcW);
		company.getClients()[index]->addNewService(svcW);
	}

	else if(response == "0") return 0;
	else if(response == "-1") return -1;
	else{
		std::cout << "\n\t\t\t\tNot a valid entry." << std::endl;
		return 0;
	}
	return 0;
}

int newUnregisteredClientService(MovingCompany& company){

	std::cout << "\n\t\t\t\t\tREQUEST SERVICE TO NEW UNREGISTERED CLIENT\n" << std::endl;
	std::cout << "\t\t\t\t\tPlease fill out this form in order to create a new service." << std::endl;

	int weight, idOrigin, idDestination;
	Address origin, destination;

	idOrigin = getOriginInfo(company, weight, origin);

	if(idOrigin == 0) return 0;
	else if(idOrigin == -1) return -1;

	idDestination = getDestinationInfo(company, idOrigin, destination);

	std::list<Vehicle*> vehiclesToBeUsed;

	if(!company.existsAvailableCarsToTransport(weight, vehiclesToBeUsed)){
		std::cout << "\n\t\t\t\tWe're sorry to inform you that we have no capacity to transport your cargo\n\t\t\t\t and due to"
				"the fact that you are not a client for the company we may not put you on hold." << std::endl;
		return 0;
	}

	Date beginningDate;
	int check = getBeginningServiceDate(beginningDate);

	if(check == 0) return 0;
	else if(check == -1) return -1;

	Date actualDate;
	getActualDateService(actualDate);

	if(beginningDate < actualDate){
		std::cout << "\t\t\t\t\tYou have entered a non valid date (this date is before today).";
		return 0;
	}

	std::string response;
	std::cin.ignore();
	std::cout << "\n\t\t\t\tDo the volumes need warehousing? [y | n] : ";
	std::getline(std::cin, response);

	srand(time(NULL));

	if(response == "n" || response == "N"){

		Date packagingB, packagingE, shippingB,
				shippingE, deliveryB, deliveryE;

		setPackagingDates(packagingB, packagingE, beginningDate);
		setShippingDates(shippingB, shippingE, packagingE, destination.getCountry().getZone());
		setDeliveryDates(deliveryB, deliveryE, shippingE);

		Date endingDate = deliveryE;
		endingDate.setHour(deliveryE.getHour() + getRandomNumberBetweenValues(1, 3));
		endingDate.setMinute(getRandomMinute());

		Transport* svcT = new Transport(origin, destination, weight, beginningDate, endingDate);
		int idT = svcT->getID();

		Packaging* p = new Packaging(packagingB, packagingE, weight, idT);
		Shipping* s = new Shipping(shippingB, shippingE, weight, idT);
		Delivery* d = new Delivery(deliveryB, deliveryE, weight, idT);

		svcT->setPackaging(p);
		svcT->setShipping(s);
		svcT->setDelivery(d);

		if(company.getCountryDestination(company.getCountriesToOperate()[idOrigin-1], idDestination).getZone() == 1){
			svcT->addZone(ZONE_1);
			svcT->addBaseRate(company.getCountryDestination(company.getCountriesToOperate()[idOrigin-1], idDestination).getBaseRate());
		}
		else{
			svcT->addZone(ZONE_2);
			svcT->addBaseRate(company.getCountryDestination(company.getCountriesToOperate()[idOrigin-1], idDestination).getBaseRate());

		}

		std::cout << "\n\t\t\t\tChoose the type of payment:\n" << std::endl;

		int checkReturn;

		checkReturn = setTypeOfPaymentParticular(company, svcT, true);

		if(checkReturn == 0) return 0;
		else if(checkReturn == -1) return -1;


	}
	else if(response == "y" || response == "Y"){
		int daysWarehouse;

		std::cout << "\n\t\t\t\tHow many days will the volumes be in the warehouse? ";
		std::cin >> daysWarehouse;

		Date packagingB, packagingE, shippingB,
				shippingE, deliveryB, deliveryE, warehousingE;

		setPackagingDates(packagingB, packagingE, beginningDate);
		setShippingDates(shippingB, shippingE, packagingE, destination.getCountry().getZone());
		setDeliveryDates(deliveryB, deliveryE, shippingE, daysWarehouse);

		std::cout << packagingB << std::endl << shippingE << std::endl << deliveryB;
		Date endingDate = deliveryE;
		endingDate.setHour(deliveryE.getHour() + getRandomNumberBetweenValues(1, 3));		//O serviço acaba quando funcionário concluir
		endingDate.setMinute(getRandomMinute());											//o serviço (entre 1 a 3 horas após a entrega)


		Warehousing* svcW = new Warehousing(origin, destination, weight, beginningDate, endingDate, daysWarehouse);
		int idW = svcW->getID();

		Packaging* p = new Packaging(packagingB, packagingE, weight, idW);
		Shipping* s = new Shipping(shippingB, shippingE, weight, idW);
		Delivery* d = new Delivery(deliveryB, deliveryE, weight, idW);

		svcW->setPackaging(p);
		svcW->setShipping(s);
		svcW->setDelivery(d);

		if(company.getCountryDestination(company.getCountriesToOperate()[idOrigin-1], idDestination).getZone() == 1){
			svcW->addZone(ZONE_1);
			svcW->addBaseRate(company.getCountryDestination(company.getCountriesToOperate()[idOrigin-1], idDestination).getBaseRate());
		}
		else{
			svcW->addZone(ZONE_2);
			float zone2Increase = company.getCountryDestination(company.getCountriesToOperate()[idOrigin-1], idDestination).getBaseRate();
			svcW->addBaseRate(zone2Increase);
		}

		std::cout << "\n\t\t\t\tChoose the type of payment:\n" << std::endl;

		int checkReturn;

		checkReturn = setTypeOfPaymentParticular(company, svcW, true);
	}

	else if(response == "0") return 0;

	else if(response == "-1") return -1;

	return 0;
}

int newService(MovingCompany& company){

	int option;

	while(option != -1){
		int instruction;

		std::cout << "\n\n\t\t\t\t\t\t\tREQUEST NEW SERVICE FORM\n" << std::endl;
		std::cout << "\t\t\tPlease enter if you want to request a service to an already REGISTERED client or to an UNREGISTERED client." << std::endl;
		std::cout << "\n\t\t\t\t\t\t\t1 - Registered Client" << std::endl;
		std::cout << "\t\t\t\t\t\t\t2 - Unregistered Client\n" << std::endl;
		std::cout << "\t\t\t\t\t\t\t0 - Go back" << std::endl;
		std::cout << "\t\t\t\t\t\t       -1 - Exit Program\n" << std::endl;

		std::cout << "\n\t\t\t\t\tPlease enter an option: ";
		std::cin >> option;

		switch(option){
			case 1:
				instruction = newRegisteredClientService(company);
				break;
			case 2:
				instruction = newUnregisteredClientService(company);
				break;
			case 0:
				return 0;
			case -1:
				return -1;
			default:
				std::cout << "\n\t\t\t\t\tPlease insert a valid option.";
				break;
		}
		if(!instruction) continue;
		if(instruction == -1) return -1;
	}
	return -1;
}

int printClientsServices(MovingCompany& company){

	int id;

	std::cout << "\n\n\t\t\t\t\t\t\tPRINT CLIENT SERVICES\n" << std::endl;
	std::cout << "\t\tEnter the ID of the client to check the services: ";

	std::cin >> id;

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

	if(std::cin.fail()){
		std::cout << "Not a valid option." << std::endl;
		return 0;
	}

	company.printClientServices(index);

	return 0;
}

int checkClientsServiceStatus(MovingCompany& company){

	int id;

	std::cout << "\n\n\t\t\t\t\t\t\tCHECK CLIENT PAYMENT STATUS\n" << std::endl;
	std::cout << "\t\tEnter the ID of the client to check the client's service payment status: ";

	std::cin >> id;

	if(id == 0) return 0;
	else if(id == -1) return -1;

	int index;

	if(std::cin.fail()){
		std::cout << "Not a valid option." << std::endl;
		return 0;
	}

	try{
		index = binarySearch(company.getClients(), id);
		if(index == -1)
			throw NonExistingClient(id);
	}
	catch(NonExistingClient& c){
		std::cout << "\n\t\t\t\t\t There is no client with the ID: " << c.getID() << std::endl;
		return 0;
	}

	if(company.getClients()[index]->getServicesRequested().size() == 0){
		std::cout << "\t\t\t\tThis client hans't requested any services." << std::endl;
		return 0;
	}

	return company.checkClientServiceStatus(index);
}

int validateClientsPayment(MovingCompany& company){

	int id;

	std::cout << "\n\n\t\t\t\t\t\t\tVALIDATE CLIENT PAYMENT\n" << std::endl;
	std::cout << "\t\tEnter the ID of the client to validate service payment: ";

	std::cin >> id;

	if(id == 0) return 0;
	else if(id == -1) return -1;

	if(std::cin.fail()){
		std::cout << "Not a valid option." << std::endl;
		return 0;
	}

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

	return company.validateClientService(index);
}

int printServicesBill(MovingCompany& company){

	int id;

	std::cout << "\n\t\t\t\t\t\t\tPRINT SERVICE BILL\n" << std::endl;
	std::cout << "\t\t\t\t\tEnter the ID of the client to print service bill: ";

	std::cin >> id;

	if(id == 0) return 0;
	else if(id == -1) return -1;

	if(std::cin.fail()){
		std::cout << "Not a valid option." << std::endl;
		return 0;
	}

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

	if(company.getClients()[index]->getServicesRequested().size() == 0){
		std::cout << "\n\t\t\t\t\t\tThere are no services associated with this client." << std::endl;
		return 0;
	}

	company.getClients()[index]->printServicesResume();

	int serviceOption;

	std::cout << "\n\t\t\tChoose the service you'd like to get the bill: ";
	std::cin >> serviceOption;

	if((std::cin.fail()) || (serviceOption < -1) || (serviceOption > (int)company.getClients()[index]->getServicesRequested().size())){
		std::cout << "Not a valid option." << std::endl;
		return 0;
	}

	if(serviceOption == 0) return 0;
	else if(serviceOption == -1) return -1;

	company.printBill(company.getClients()[index], company.getClients()[index]->getServicesRequested()[serviceOption-1]);
	return 0;
}

int printServicesRequests(MovingCompany& company){

	std::cout << "\n\t\t\t\t\t\t\tPRINT SERVICES REQUESTED\n\t\t\t\t\t\t      (waiting for available vehicles)";
	std::cout << "\n\n\t\t\t\t\t\t1 - Print all services requested" << std::endl;
	std::cout << "\n\t\t\t\t\t\t\t0 - Go back" << std::endl;
	std::cout << "\t\t\t\t\t\t       -1 - Exit program" << std::endl;

	int option;

	while(option != -1){

		std::cout << "\n\t\t\t\t\tEnter your option: ";
		std::cin >> option;

		switch(option){
			case 1:
				company.printAllServicesWaiting();
				break;
			case 0:
				return 0;
			case -1:
				return -1;
			default:
				std::cout << "\n\t\t\t\tPlease insert a valid option.";
				break;
		}
	}
	return 0;
}
