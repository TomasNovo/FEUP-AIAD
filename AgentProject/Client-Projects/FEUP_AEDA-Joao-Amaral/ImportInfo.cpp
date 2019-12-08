/*
 * ImportInfo.cpp
 *
 *  Created on: 14/11/2017
 *      Author: Francisco Maria / João Gama Amaral
 */

#include "ImportInfo.h"


void getActualDate(Date& actualDate){
	std::stringstream ss;

	int actualDay, actualMonth, actualYear;
	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, sizeof(buffer), "%d %m %y", timeinfo);

	std::string buf(buffer);

	ss << buf;
	ss >> actualDay;
	ss >> actualMonth;
	ss >> actualYear;

	actualYear += 2000;

	actualDate.setDay(actualDay);
	actualDate.setMonth(actualMonth);
	actualDate.setYear(actualYear);
}

void importClients(MovingCompany& company){

	std::ifstream clientsFile;
	clientsFile.open("InfoFiles/clients.txt");

	if(!clientsFile.good())
		std::cout << "Couldn't access clients.txt file. Error reading from File." << std::endl;

	int fDay, fMonth, fYear, fHour, fMinute, age;
	long int nif;
	std::string name, zipCode, address, line, city, country, clientType;

	while(std::getline(clientsFile, line)){

		std::stringstream ss(line);
		std::string aux;
		std::stringstream auxSS;

		std::getline(ss, clientType, '/');

		if(clientType == "P"){				//PARTICULAR

			int id;
			std::getline(ss, aux, '/');
			auxSS << aux;
			auxSS >> id;

			aux.clear();
			auxSS.clear();
			auxSS.str(std::string());

			// Name
			std::getline(ss, name, '/');

			// Age
			std::getline(ss, aux, '/');
			auxSS << aux;
			auxSS >> age;

			aux.clear();
			auxSS.clear();
			auxSS.str(std::string());

			// NIF
			std::getline(ss, aux, '/');
			auxSS << aux;
			auxSS >> nif;

			aux.clear();
			auxSS.clear();
			auxSS.str(std::string());

			// Address
			std::getline(ss, address, '/');

			// Zip Code
			std::getline(ss, zipCode, '/');

			// City
			std::getline(ss, city, '/');

			// Country
			std::getline(ss, country, '/');

			// Day
			std::getline(ss, aux, '/');
			auxSS << aux;
			auxSS >> fDay;

			aux.clear();
			auxSS.clear();
			auxSS.str(std::string());

			// Month
			std::getline(ss, aux, '/');
			auxSS << aux;
			auxSS >> fMonth;

			aux.clear();
			auxSS.clear();
			auxSS.str(std::string());

			// Year
			std::getline(ss, aux, '/');
			auxSS << aux;
			auxSS >> fYear;

			aux.clear();
			auxSS.clear();
			auxSS.str(std::string());

			// Hour
			std::getline(ss, aux, ':');
			auxSS << aux;
			auxSS >> fHour;

			aux.clear();
			auxSS.clear();
			auxSS.str(std::string());

			// Minute
			std::getline(ss, aux, ':');
			auxSS << aux;
			auxSS >> fMinute;

			aux.clear();
			auxSS.clear();
			auxSS.str(std::string());

			Particular* p = new Particular(id, name, age, nif, address, zipCode, city, country, fDay, fMonth, fYear, fHour, fMinute);
			company.addClient(p);
		}
		else if(clientType == "C"){					//COMPANY

			int id;
			std::getline(ss, aux, '/');
			auxSS << aux;
			auxSS >> id;

			aux.clear();
			auxSS.clear();
			auxSS.str(std::string());

			//	Name
			std::getline(ss, name, '/');

			// NIF
			std::getline(ss, aux, '/');
			auxSS << aux;
			auxSS >> nif;

			aux.clear();
			auxSS.clear();
			auxSS.str(std::string());

			// Address
			std::getline(ss, address, '/');

			// ZipCode
			std::getline(ss, zipCode, '/');

			// City
			std::getline(ss, city, '/');

			// Country
			std::getline(ss, country, '/');

			// Day
			std::getline(ss, aux, '/');
			auxSS << aux;
			auxSS >> fDay;

			aux.clear();
			auxSS.clear();
			auxSS.str(std::string());

			// Month
			std::getline(ss, aux, '/');
			auxSS << aux;
			auxSS >> fMonth;

			aux.clear();
			auxSS.clear();
			auxSS.str(std::string());

			// Year
			std::getline(ss, aux, '/');
			auxSS << aux;
			auxSS >> fYear;

			aux.clear();
			auxSS.clear();
			auxSS.str(std::string());

			// Hour
			std::getline(ss, aux, ':');
			auxSS << aux;
			auxSS >> fHour;

			aux.clear();
			auxSS.clear();
			auxSS.str(std::string());

			// Minute
			std::getline(ss, aux);
			auxSS << aux;
			auxSS >> fMinute;

			aux.clear();
			auxSS.clear();
			auxSS.str(std::string());

			Company* c = new Company(id, name, nif, address, zipCode, city, country, fDay, fMonth, fYear, fHour, fMinute);
			company.addClient(c);
		}
	}

	clientsFile.close();
}

void importCountries(MovingCompany& company){

	std::ifstream countriesFile;
	countriesFile.open("InfoFiles/countries.txt");

	if(!countriesFile.good())
		std::cout << "Couldn't access countries.txt file. Error reading from File." << std::endl;

	std::string line;

	while(std::getline(countriesFile, line)){
		Country* c = new Country(line);
		company.addCountry(c);
	}

	countriesFile.close();
}

void importCountriesZones(MovingCompany& company){

	std::ifstream countriesZonesFile;
	countriesZonesFile.open("InfoFiles/countriesZones.txt");

	if(!countriesZonesFile.good())
		std::cout << "Couldn't access countriesZones.txt file. Error reading from File." << std::endl;

	int i = -1;
	unsigned int j;
	std::string line;

	while(std::getline(countriesZonesFile, line)){
		std::stringstream ss(line);
		std::string aux;

		std::getline(ss, aux, ' ');

		if(aux == "C"){
			i++;
		}
		else if(aux == "1"){
			//zone1
			std::string name;
			float baseRate;
			std::stringstream auxSS;

			std::getline(ss, name, ' ');
			aux.clear();

			std::getline(ss, aux, '\n');
			auxSS << aux;
			auxSS >> baseRate;


			for(j = 0; j < company.getCountriesToOperate().size(); j++){
				if(company.getCountriesToOperate()[j]->getName() == name){
					ConnectionCountryInfo ci(company.getCountriesToOperate()[j], 1, baseRate);
					company.getCountriesToOperate()[i]->addCountryConnection(ci);
				}
			}
		}
		else{
			//zone2
			std::string name;
			float baseRate;
			std::stringstream auxSS;

			std::getline(ss, name, ' ');
			aux.clear();

			std::getline(ss, aux, '\n');
			auxSS << aux;
			auxSS >> baseRate;

			for(j = 0; j < company.getCountriesToOperate().size(); j++){
				if(company.getCountriesToOperate()[j]->getName() == name){
					ConnectionCountryInfo ci(company.getCountriesToOperate()[j], 2, baseRate);
					company.getCountriesToOperate()[i]->addCountryConnection(ci);
				}
			}

		}
	}

	countriesZonesFile.close();
}

void readDate(std::stringstream& ss, Date& date){

	int day, month, year, hour, minute;
	std::string buffer;
	std::stringstream auxSS;

	std::getline(ss, buffer, '-');
	auxSS << buffer;
	auxSS >> day;

	buffer.clear();
	auxSS.clear();				//Clears Buffers
	auxSS.str(std::string());

	std::getline(ss, buffer, '-');
	auxSS << buffer;
	auxSS >> month;

	buffer.clear();
	auxSS.clear();				//Clears Buffers
	auxSS.str(std::string());

	std::getline(ss, buffer, '-');
	auxSS << buffer;
	auxSS >> year;

	buffer.clear();
	auxSS.clear();				//Clears Buffers
	auxSS.str(std::string());

	std::getline(ss, buffer, ':');
	auxSS << buffer;
	auxSS >> hour;

	buffer.clear();
	auxSS.clear();				//Clears Buffers
	auxSS.str(std::string());


	std::getline(ss, buffer);
	auxSS << buffer;
	auxSS >> minute;

	date.setDay(day);
	date.setMonth(month);
	date.setYear(year);
	date.setHour(hour);
	date.setMinute(minute);
}

int readAddress(MovingCompany& company, std::stringstream& auxSS, Address& address){

	std::string streetAddress, zipCode, city, countryName;

	std::getline(auxSS, streetAddress, '/');
	std::getline(auxSS, zipCode, '/');
	std::getline(auxSS, city, '/');
	std::getline(auxSS, countryName);

	address.setStreet(streetAddress);
	address.setZipCode(zipCode);
	address.setCity(city);
	address.setCountry(company.getCountry(countryName)->getName());

	for(unsigned int i = 0; i < company.getCountriesToOperate().size(); i++){
		if(countryName == company.getCountriesToOperate()[i]->getName())
			return i+1;
	}
}

int getRandomNumberBetweenValuesAux(int minValue, int maxValue){
	return rand()%(maxValue - minValue + 1)+minValue;
}

int getRandomHourAux(){			//Só trabalha das 8h as 19h
	return getRandomNumberBetweenValuesAux(8, 19);
}

int getRandomMinuteAux(){
	return getRandomNumberBetweenValuesAux(0, 59);
}

int getShippingZone1DurationAux(){
	return getRandomNumberBetweenValuesAux(5, 8);
}

int getShippingZone2DurationAux(){
	return getRandomNumberBetweenValuesAux(14, 20);
}

void setPackagingDatesAux(Date& packagingBeginning, Date& packagingEnding, Date& beginningDate){

	packagingBeginning = beginningDate;

	packagingBeginning.setHour(beginningDate.getHour()+2);

	packagingEnding.setHour(getRandomHourAux());
	packagingEnding.setMinute(getRandomMinuteAux());

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


void setShippingDatesAux(Date& shippingBeginning, Date& shippingEnding, Date& beginningDate, int zone){

	int endingDay, shippingDays;

	shippingBeginning = beginningDate;
	shippingBeginning.setHour(beginningDate.getHour()+2);
	shippingBeginning.setMinute(getRandomMinuteAux());

	if(zone == 1){
		shippingDays = getShippingZone1DurationAux();				// 5 to 7 days
	}
	else{
		shippingDays = getShippingZone2DurationAux();				// 14 to 20 days
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

	shippingEnding.setHour(getRandomHourAux()); shippingEnding.setMinute(getRandomMinuteAux());
}

void setDeliveryDatesAux(Date& deliveryBeginning, Date& deliveryEnding, Date& beginningDate){

	deliveryBeginning = beginningDate;
	deliveryBeginning.setHour(beginningDate.getHour()+2);
	deliveryBeginning.setMinute(getRandomMinuteAux());

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
	deliveryEnding.setHour(getRandomHourAux()); deliveryEnding.setMinute(getRandomMinuteAux());
}

void newTransportService(Transport* svcT, int zone){

	Date packagingB, packagingE, shippingB,
			shippingE, deliveryB, deliveryE, actualDate;

	getActualDate(actualDate);

	setPackagingDatesAux(packagingB, packagingE, actualDate);
	setShippingDatesAux(shippingB, shippingE, packagingE, zone);
	setDeliveryDatesAux(deliveryB, deliveryE, shippingE);

	Packaging* p = new Packaging(packagingB, packagingE, svcT->getWeight(), svcT->getID());
	Shipping* s = new Shipping(shippingB, shippingE, svcT->getWeight(), svcT->getID());
	Delivery* d = new Delivery(deliveryB, deliveryE, svcT->getWeight(), svcT->getID());

	svcT->setPackaging(p);
	svcT->setShipping(s);
	svcT->setDelivery(d);

	Date endingDate = deliveryE;
	endingDate.setHour(deliveryE.getHour() + getRandomNumberBetweenValuesAux(1, 3));
	endingDate.setMinute(getRandomMinuteAux());

	svcT->setEndingDate(endingDate);
}

void newWarehousingService(Warehousing* svcW, int zone){

	Date packagingB, packagingE, shippingB,
			shippingE, deliveryB, deliveryE, actualDate;

	getActualDate(actualDate);

	setPackagingDatesAux(packagingB, packagingE, actualDate);
	setShippingDatesAux(shippingB, shippingE, packagingE, zone);
	setDeliveryDatesAux(deliveryB, deliveryE, shippingE);

	Packaging* p = new Packaging(packagingB, packagingE, svcW->getWeight(), svcW->getID());
	Shipping* s = new Shipping(shippingB, shippingE, svcW->getWeight(), svcW->getID());
	Delivery* d = new Delivery(deliveryB, deliveryE, svcW->getWeight(), svcW->getID());

	svcW->setPackaging(p);
	svcW->setShipping(s);
	svcW->setDelivery(d);

	Date endingDate = deliveryE;
	endingDate.setHour(deliveryE.getHour() + getRandomNumberBetweenValuesAux(1, 3));
	endingDate.setMinute(getRandomMinuteAux());

	svcW->setEndingDate(endingDate);
}

void readServiceRequest(MovingCompany& company, std::stringstream& line){

	int clientID, weight;
	bool transportType = false;
	Date beginningDate;

	std::string aux;
	std::stringstream auxSS;

	std::getline(line, aux, '/');
	auxSS << aux;
	auxSS >> clientID;

	int index = binarySearch(company.getClients(), clientID);
	if(index == -1) return;

	aux.clear();			//Clears buffers
	auxSS.clear();
	auxSS.str(std::string());

	std::getline(line, aux, '/');

	if(aux == "T"){
		transportType = true;
	}

	aux.clear();			//Clears buffers
	auxSS.clear();
	auxSS.str(std::string());

	std::getline(line, aux, '/');
	auxSS << aux;
	auxSS >> weight;

	aux.clear();			//Clears buffers
	auxSS.clear();
	auxSS.str(std::string());

	std::getline(line, aux, '[');
	auxSS << aux;
	readDate(auxSS, beginningDate);

	aux.clear();			//Clears buffers
	auxSS.clear();
	auxSS.str(std::string());

	Address origin, destination;

	std::getline(line, aux, ']');
	auxSS << aux;
	int idOrigin = readAddress(company, auxSS, origin);

	aux.clear();			//Clears buffers
	auxSS.clear();
	auxSS.str(std::string());

	std::getline(line, aux, ']');
	auxSS << aux;
	int idDestination = readAddress(company, auxSS, destination);

	aux.clear();			//Clears buffers
	auxSS.clear();
	auxSS.str(std::string());

	std::string typePayment;

	std::getline(line, typePayment, '/');

	Payment* pay;

	if(typePayment == "ATM"){
		pay = new ATM(company.getEntity());
	}
	else if(typePayment == "CC"){
		pay = new CreditCard();
	}
	else if(typePayment == "BT"){
		pay = new BankTransfer(company.getIBAN());
	}
	else if(typePayment == "EOM"){
		int actualMonth;
		time_t rawtime;
		struct tm* timeinfo;
		char buffer[80];

		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(buffer, sizeof(buffer), "%m", timeinfo);

		std::string buf(buffer);

		line << buf;
		line >> actualMonth;

		pay = new EndOfMonth(actualMonth);
	}

	std::string paymentStatus;
	std::getline(line, paymentStatus);

	if(paymentStatus == "RECEIVED"){
		pay->validate();
	}

	int zone;
	if(company.getCountryDestination(company.getCountriesToOperate()[idOrigin-1], idDestination).getZone() == 1){
		zone = 1;
	}else{
		zone = 2;
	}
	std::list<Vehicle*> vehiclesToTransport;

	if(transportType){
		Transport* waitingT = new Transport(origin, destination, weight, beginningDate);
		waitingT->setPayment(pay);

		//There are sufficient vehicles in the company to realize the transportation
		if(company.existsAvailableCarsToTransport(weight,vehiclesToTransport)){
			waitingT->setVehiclesUsed(vehiclesToTransport);
			newTransportService(waitingT, zone);

			if(company.getCountryDestination(company.getCountriesToOperate()[idOrigin-1], idDestination).getZone() == 1){
				waitingT->addZone(ZONE_1);
				waitingT->addBaseRate(company.getCountryDestination(company.getCountriesToOperate()[idOrigin-1], idDestination).getBaseRate());
			}
			else{
				waitingT->addZone(ZONE_2);
				float zone2Increase = company.getCountryDestination(company.getCountriesToOperate()[idOrigin-1], idDestination).getBaseRate();
				waitingT->addBaseRate(zone2Increase);
			}

			company.checkNonActiveClients(company.getClients()[index]);
			company.addServiceBill(company.getClients()[index], waitingT);
			company.getClients()[index]->addNewService(waitingT);
		}else{
			ServiceRequest* sr = new ServiceRequest(clientID, waitingT);
			company.addServiceWaiting(sr);
		}
	}else{
		int daysWarehouse;

		std::getline(line, aux, '/');
		auxSS << aux;
		auxSS >> daysWarehouse;

		Warehousing* waitingW = new Warehousing(origin, destination, weight, beginningDate, daysWarehouse);
		waitingW->setPayment(pay);

		if(company.existsAvailableCarsToTransport(weight,vehiclesToTransport)){
			waitingW->setVehiclesUsed(vehiclesToTransport);
			newWarehousingService(waitingW, zone);

			if(company.getCountryDestination(company.getCountriesToOperate()[idOrigin-1], idDestination).getZone() == 1){
				waitingW->addZone(ZONE_1);
				waitingW->addBaseRate(company.getCountryDestination(company.getCountriesToOperate()[idOrigin-1], idDestination).getBaseRate());
			}
			else{
				waitingW->addZone(ZONE_2);
				float zone2Increase = company.getCountryDestination(company.getCountriesToOperate()[idOrigin-1], idDestination).getBaseRate();
				waitingW->addBaseRate(zone2Increase);
			}

			company.checkNonActiveClients(company.getClients()[index]);
			company.addServiceBill(company.getClients()[index], waitingW);
			company.getClients()[index]->addNewService(waitingW);
		}else{
			ServiceRequest* sr = new ServiceRequest(clientID, waitingW);
			company.addServiceWaiting(sr);
		}
	}
}

void importServices(MovingCompany& company){

	std::ifstream servicesFile;
	servicesFile.open("InfoFiles/services.txt");

	if(!servicesFile.good())
		std::cout << "Couldn't access services.txt file. Error reading from File." << std::endl;

	int idClient;
	std::string line;

	while(std::getline(servicesFile, line)){

		std::stringstream ss(line);
		std::string aux;
		std::stringstream auxSS;

		std::getline(ss, aux, '/');

		if(aux == "R"){
			readServiceRequest(company, ss);
			continue;
		}

		auxSS << aux;
		auxSS >> idClient;

		aux.clear();				//Clears buffers
		auxSS.clear();
		auxSS.str(std::string());

		int index = binarySearch(company.getClients(), idClient);
		if(index == -1) continue;

		std::getline(ss, aux, '/');

		int weight;

		if(aux == "T"){						//TRANSPORT
			aux.clear();
			std::getline(ss, aux, '/');
			auxSS << aux;					//WEIGHT
			auxSS >> weight;

			aux.clear();
			auxSS.clear();				//Clear buffers
			auxSS.str(std::string());

			Date begginingTransport;
			Date endTransport;

			std::getline(ss, aux, '/');
			auxSS << aux;
			readDate(auxSS, begginingTransport);			//beggining Date Transport

			aux.clear();
			auxSS.clear();				//Clear buffers
			auxSS.str(std::string());

			std::getline(ss, aux, '[');
			auxSS << aux;
			readDate(auxSS, endTransport);					//ending Date Transport

			aux.clear();
			auxSS.clear();				//Clear buffers
			auxSS.str(std::string());

			/************* ADDRESS ***************/
			std::getline(ss, aux, ']');
			auxSS << aux;
			Address origin;
			int idOrigin = readAddress(company, auxSS, origin);			// Origin Address

			aux.clear();
			auxSS.clear();				//Clear buffers
			auxSS.str(std::string());

			std::getline(ss, aux, ']');
			auxSS << aux;
			Address destination;// Destination Address
			int idDestination = readAddress(company, auxSS, destination);
			idDestination--;

			aux.clear();
			auxSS.clear();				//Clear buffers
			auxSS.str(std::string());

			/************ PACKAGING ***************/
			ss.ignore(line.length(), '/');
			std::getline(ss, aux, '/');
			auxSS << aux;

			Date packagingB, packagingE;
			readDate(auxSS, packagingB);

			aux.clear();
			auxSS.clear();				//Clear buffers
			auxSS.str(std::string());

			std::getline(ss, aux, '/');
			auxSS << aux;

			readDate(auxSS, packagingE);

			aux.clear();
			auxSS.clear();				//Clear buffers
			auxSS.str(std::string());

			/*********** SHIPPING ***********/
			ss.ignore(line.length(), '/');
			std::getline(ss, aux, '/');
			auxSS << aux;

			Date shippingB, shippingE;
			readDate(auxSS, shippingB);

			aux.clear();
			auxSS.clear();				//Clear buffers
			auxSS.str(std::string());

			std::getline(ss, aux, '/');
			auxSS << aux;

			readDate(auxSS, shippingE);

			aux.clear();
			auxSS.clear();				//Clear buffers
			auxSS.str(std::string());

			/*********** DELIVERY ***********/
			ss.ignore(line.length(), '/');
			std::getline(ss, aux, '/');
			auxSS << aux;

			Date deliveryB, deliveryE;
			readDate(auxSS, deliveryB);

			aux.clear();
			auxSS.clear();				//Clear buffers
			auxSS.str(std::string());

			std::getline(ss, aux, '/');
			auxSS << aux;

			readDate(auxSS, deliveryE);

			aux.clear();
			auxSS.clear();				//Clear buffers
			auxSS.str(std::string());

			std::string typePayment;

			std::getline(ss, typePayment, '/');

			Payment* pay;

			if(typePayment == "ATM"){
				pay = new ATM(company.getEntity());
			}
			else if(typePayment == "CC"){
				pay = new CreditCard();
			}
			else if(typePayment == "BT"){
				pay = new BankTransfer(company.getIBAN());
			}
			else if(typePayment == "EOM"){
				int actualMonth;
				time_t rawtime;
				struct tm* timeinfo;
				char buffer[80];

				time(&rawtime);
				timeinfo = localtime(&rawtime);
				strftime(buffer, sizeof(buffer), "%m", timeinfo);

				std::string buf(buffer);

				ss << buf;
				ss >> actualMonth;

				pay = new EndOfMonth(actualMonth);
			}

			std::string paymentStatus;
			std::getline(ss, paymentStatus);

			if(paymentStatus == "RECEIVED"){
				pay->validate();
			}

			Transport* svcT = new Transport(origin, destination, weight, begginingTransport, endTransport);
			int idT = svcT->getID();

			Packaging* p = new Packaging(packagingB, packagingE, weight, idT);
			Shipping* s = new Shipping(shippingB, shippingE, weight, idT);
			Delivery* d = new Delivery(deliveryB, deliveryE, weight, idT);

			svcT->setPackaging(p);
			svcT->setShipping(s);
			svcT->setDelivery(d);
			svcT->setPayment(pay);

			if(company.getCountryDestination(company.getCountriesToOperate()[idOrigin-1], idDestination).getZone() == 1){
				svcT->addZone(ZONE_1);
				svcT->addBaseRate(company.getCountryDestination(company.getCountriesToOperate()[idOrigin-1], idDestination).getBaseRate());
			}
			else{
				svcT->addZone(ZONE_2);
				float zone2Increase = company.getCountryDestination(company.getCountriesToOperate()[idOrigin-1], idDestination).getBaseRate();
				svcT->addBaseRate(zone2Increase);
			}

			if(company.getClients()[index]->getLastService() < begginingTransport){
				company.getClients()[index]->updateLastService(begginingTransport);
			}

			company.addServiceBill(company.getClients()[index], svcT);
			company.getClients()[index]->addNewService(svcT);
		}
		if(aux == "W"){

			aux.clear();
			int daysWarehousing;

			std::getline(ss, aux, '/');

			auxSS << aux;
			auxSS >> daysWarehousing;

			aux.clear();
			auxSS.clear();
			auxSS.str(std::string());

			std::getline(ss, aux, '/');
			auxSS << aux;					//WEIGHT
			auxSS >> weight;

			aux.clear();
			auxSS.clear();				//Clear buffers
			auxSS.str(std::string());

			/************** DATES *****************/
			Date begginingWarehousing;
			Date endWarehousing;

			std::getline(ss, aux, '/');
			auxSS << aux;
			readDate(auxSS, begginingWarehousing);			//beggining Date Transport

			aux.clear();
			auxSS.clear();				//Clear buffers
			auxSS.str(std::string());

			std::getline(ss, aux, '[');
			auxSS << aux;
			readDate(auxSS, endWarehousing);					//ending Date Transport

			aux.clear();
			auxSS.clear();				//Clear buffers
			auxSS.str(std::string());

			/************* ADDRESS ***************/
			std::getline(ss, aux, ']');
			auxSS << aux;
			Address origin;
			int idOrigin = readAddress(company, auxSS, origin);			// Origin Address

			aux.clear();
			auxSS.clear();				//Clear buffers
			auxSS.str(std::string());

			std::getline(ss, aux, ']');
			auxSS << aux;
			Address destination;							// Destination Address
			int idDestination = readAddress(company, auxSS, destination);
			idDestination--;

			aux.clear();
			auxSS.clear();				//Clear buffers
			auxSS.str(std::string());

			/************ PACKAGING ***************/
			ss.ignore(line.length(), '/');
			std::getline(ss, aux, '/');
			auxSS << aux;

			Date packagingB, packagingE;
			readDate(auxSS, packagingB);

			aux.clear();
			auxSS.clear();				//Clear buffers
			auxSS.str(std::string());

			std::getline(ss, aux, '/');
			auxSS << aux;

			readDate(auxSS, packagingE);

			aux.clear();
			auxSS.clear();				//Clear buffers
			auxSS.str(std::string());

			/*********** SHIPPING ***********/
			ss.ignore(line.length(), '/');
			std::getline(ss, aux, '/');
			auxSS << aux;

			Date shippingB, shippingE;
			readDate(auxSS, shippingB);

			aux.clear();
			auxSS.clear();				//Clear buffers
			auxSS.str(std::string());

			std::getline(ss, aux, '/');
			auxSS << aux;

			readDate(auxSS, shippingE);

			aux.clear();
			auxSS.clear();				//Clear buffers
			auxSS.str(std::string());

			/*********** DELIVERY ***********/
			ss.ignore(line.length(), '/');
			std::getline(ss, aux, '/');
			auxSS << aux;

			Date deliveryB, deliveryE;
			readDate(auxSS, deliveryB);

			aux.clear();
			auxSS.clear();				//Clear buffers
			auxSS.str(std::string());

			std::getline(ss, aux, '/');
			auxSS << aux;

			readDate(auxSS, deliveryE);

			aux.clear();
			auxSS.clear();				//Clear buffers
			auxSS.str(std::string());

			std::string typePayment;
			std::getline(ss, typePayment, '/');

			Payment* pay;

			if(typePayment == "ATM"){
				pay = new ATM(company.getEntity());
			}
			else if(typePayment == "Credit Card"){
				pay = new CreditCard();
			}
			else if(typePayment == "Bank Transfer"){
				pay = new BankTransfer(company.getIBAN());
			}
			else if(typePayment == "Payable until the end of month"){
				int actualMonth;
				time_t rawtime;
				struct tm* timeinfo;
				char buffer[80];

				time(&rawtime);
				timeinfo = localtime(&rawtime);
				strftime(buffer, sizeof(buffer), "%m", timeinfo);

				std::string buf(buffer);

				ss << buf;
				ss >> actualMonth;

				pay = new EndOfMonth(actualMonth);
			}

			//---- Payment Status
			std::string paymentStatus;
			std::getline(ss, paymentStatus);

			if(paymentStatus == "RECEIVED")
				pay->validate();

			Warehousing* svcW = new Warehousing(origin, destination, weight, begginingWarehousing, endWarehousing, daysWarehousing);
			int idW = svcW->getID();

			Packaging* p = new Packaging(packagingB, packagingE, weight, idW);
			Shipping* s = new Shipping(shippingB, shippingE, weight, idW);
			Delivery* d = new Delivery(deliveryB, deliveryE, weight, idW);

			svcW->setPackaging(p);
			svcW->setShipping(s);
			svcW->setDelivery(d);
			svcW->setPayment(pay);

			if(company.getCountryDestination(company.getCountriesToOperate()[idOrigin-1], idDestination).getZone() == 1){
				svcW->addZone(ZONE_1);
				svcW->addBaseRate(company.getCountryDestination(company.getCountriesToOperate()[idOrigin-1], idDestination).getBaseRate());
			}
			else{
				svcW->addZone(ZONE_2);
				float zone2Increase = company.getCountryDestination(company.getCountriesToOperate()[idOrigin-1], idDestination).getBaseRate();
				svcW->addBaseRate(zone2Increase);
			}

			if(company.getClients()[index]->getLastService() < begginingWarehousing){
				company.getClients()[index]->updateLastService(begginingWarehousing);
			}

			company.addServiceBill(company.getClients()[index], svcW);
			company.getClients()[index]->addNewService(svcW);
		}
	}

	addNonActiveClients(company);
}

void importVehicles(MovingCompany& company){

	std::ifstream vehiclesFile;
	vehiclesFile.open("InfoFiles/vehicles.txt");

	if(!vehiclesFile.good())
		std::cout << "Couldn't access vehicles.txt file. Error reading from File." << std::endl;

	std::string line;

	while(std::getline(vehiclesFile, line)){
		int vehicleID, maintenanceDays;
		float maxWeight;
		int availability;

		std::sscanf(line.c_str(), "%d %d %f %d", &vehicleID, &maintenanceDays, &maxWeight, &availability);

		Vehicle* v = new Vehicle(vehicleID, maintenanceDays, maxWeight, availability);
		company.addVehicle(v);
	}

	vehiclesFile.close();
}

bool isNonActiveClient(const Date& clientDate){

	Date actualDate;
	getActualDate(actualDate);

	if(clientDate.getYear() < actualDate.getYear()){
		if(actualDate.getYear() == (clientDate.getYear()+1)){
			int monthAux = actualDate.getMonth()+12;

			if((monthAux - clientDate.getMonth()) > 3)
				return true;

			return false;
		}
		return true;			// a diferença dos meses do ultimo serviço passa bem mais dos 3 meses
	}
	else if((clientDate.getYear() == actualDate.getYear())){
		int diffMonth = actualDate.getMonth() - clientDate.getMonth();

		if(diffMonth > 3)
			return true;

		return false;
	}
	else{
		return false;
	}
}

void addNonActiveClients(MovingCompany& company){

	unsigned int i;

	for(i = 0; i < company.getClients().size(); i++){
		if(isNonActiveClient(company.getClients()[i]->getLastService())){
			company.addNonActiveClient(company.getClients()[i]);
		}
	}
}
