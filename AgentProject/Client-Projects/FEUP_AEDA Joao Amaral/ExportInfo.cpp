/*
 * ExportInfo.cpp
 *
 *  Created on: 16/11/2017
 *      Author: Francisco Maria / João Gama Amaral
 */

#include "ExportInfo.h"

std::string saveParticularClient(Client* c){

	std::string line;
	std::stringstream ss;
	std::string delimiter = "/";

	line = "P/";

	//ID
	std::string id;
	int auxID = c->getId();

	ss << auxID;
	ss >> id;

	ss.clear();
	ss.str(std::string());

	line.append(id).append(delimiter);

	// Name
	std::string name;
	name = c->getName();

	// Age
	std::string age;
	int auxAge = c->getAge();
	ss << auxAge;
	ss >> age;

	ss.clear();
	ss.str(std::string());

	// NIF
	std::string nif;
	int auxNif = c->getNIF();
	ss << auxNif;
	ss >> nif;

	ss.clear();
	ss.str(std::string());

	// Street Address
	std::string streetAddress;
	streetAddress = c->getAddress().getStreet();

	// Zip Code
	std::string zipCode;
	zipCode = c->getAddress().getZipCode();

	// City
	std::string city;
	city = c->getAddress().getCity();

	// Country
	std::string country;
	country = c->getAddress().getCountryAux();

	// Day
	std::string day;
	int auxDay = c->getJoiningDate().getDay();
	ss << auxDay;
	ss >> day;

	ss.clear();
	ss.str(std::string());

	// Month
	std::string month;
	int auxMonth = c->getJoiningDate().getMonth();
	ss << auxMonth;
	ss >> month;

	ss.clear();
	ss.str(std::string());

	// Year
	std::string year;
	int auxYear = c->getJoiningDate().getYear();
	ss << auxYear;
	ss >> year;

	ss.clear();
	ss.str(std::string());

	//Hour
	std::string hour;
	int auxHour = c->getJoiningDate().getHour();
	ss << auxHour;
	ss >> hour;

	ss.clear();
	ss.str(std::string());


	//Minute
	std::string min;
	int auxMin = c->getJoiningDate().getMinute();
	ss << auxMin;
	ss >> min;

	ss.clear();
	ss.str(std::string());

	line.append(name).append(delimiter).append(age).append(delimiter).append(nif).append(delimiter).append(streetAddress).
			append(delimiter).append(zipCode).append(delimiter).append(city).append(delimiter).append(country).append(delimiter).
			append(day).append(delimiter).append(month).append(delimiter).append(year).append(delimiter).append(hour).
			append(":").append(min).append("\n");

	return line;
}

std::string saveCompanyClient(Client* c){
	std::string line;
	std::stringstream ss;
	std::string delimiter = "/";

	line = "C/";

	//ID
	std::string id;
	int auxID = c->getId();

	ss << auxID;
	ss >> id;

	line.append(id).append(delimiter);

	ss.clear();
	ss.str(std::string());

	//Name
	std::string name;
	name = c->getName();

	//NIF
	std::string nif;
	int auxNif = c->getNIF();
	ss << auxNif;
	ss >> nif;

	ss.clear();
	ss.str(std::string());

	//Address
	std::string streetAddress;
	streetAddress = c->getAddress().getStreet();

	//ZipCode
	std::string zipCode;
	zipCode = c->getZipCode();

	//City
	std::string city;
	city = c->getAddress().getCity();

	//Country
	std::string country;
	country = c->getAddress().getCountryAux();

	// Day
	std::string day;
	int auxDay = c->getJoiningDate().getDay();
	ss << auxDay;
	ss >> day;

	ss.clear();
	ss.str(std::string());

	// Month
	std::string month;
	int auxMonth = c->getJoiningDate().getMonth();
	ss << auxMonth;
	ss >> month;

	ss.clear();
	ss.str(std::string());

	// Year
	std::string year;
	int auxYear = c->getJoiningDate().getYear();
	ss << auxYear;
	ss >> year;

	ss.clear();
	ss.str(std::string());

	//Hour
	std::string hour;
	int auxHour = c->getJoiningDate().getHour();
	ss << auxHour;
	ss >> hour;

	ss.clear();
	ss.str(std::string());

	//Minutes
	std::string min;
	int auxmin = c->getJoiningDate().getMinute();
	ss << auxmin;
	ss >> min;

	ss.clear();
	ss.str(std::string());

	line.append(name).append(delimiter).append(nif).append(delimiter).append(streetAddress).
		append(delimiter).append(zipCode).append(delimiter).append(city).append(delimiter).append(country).append(delimiter).
		append(day).append(delimiter).append(month).append(delimiter).append(year).append(delimiter).append(hour).
		append(":").append(min).append("\n");

	return line;
}

void saveClients(MovingCompany& company){

	int i;
	int clientsSize = company.getClients().size();

	std::ofstream clientsFile;
	clientsFile.open("InfoFiles/clients.txt", std::ios::trunc);

	for(i = 0; i < company.getClients().size(); i++){

		std::string infoClient;
		Client* c = company.getClients()[i];

		if(company.getClients()[i]->isParticular()){
			infoClient = saveParticularClient(c);
		}
		else{
			infoClient = saveCompanyClient(c);
		}

		clientsFile << infoClient;
	}

	clientsFile.close();
}

std::string saveTransportService(Transport* tService, int idC){

	std::string line;
	std::stringstream ss;
	std::string delimiter = "/", dateDelimiter = "-", hourDelimiter = ":", addressDelimiterB = "[", addressDelimiterE = "]";

	//------  CLIENT ID  -------//
	std::string idClient;
	ss << idC;
	ss >> idClient;

	ss.clear();
	ss.str(std::string());

	line.append(idClient).append(delimiter);

	//------  SERVICE TYPE  ------//
	std::string type = "T";

	line.append(type).append(delimiter);

	//------  SERVICE WEIGHT ------//
	int w = tService->getWeight();
	std::string weight;
	ss << w;
	ss >> weight;

	ss.clear();
	ss.str(std::string());

	line.append(weight).append(delimiter);

	//------  BEGGINING DATE  -------//
	std::string bDate;
	ss << tService->getBeggining().getDay() << dateDelimiter << tService->getBeggining().getMonth() << "-" << tService->getBeggining().getYear()
			<< dateDelimiter << tService->getBeggining().getHour() << hourDelimiter << tService->getBeggining().getMinute();
	ss >> bDate;

	ss.clear();
	ss.str(std::string());

	line.append(bDate).append(delimiter);

	//------  ENDING DATE  -------//
	std::string eDate;
	ss << tService->getEnd().getDay() << dateDelimiter << tService->getEnd().getMonth() << "-" << tService->getEnd().getYear()
			<< dateDelimiter << tService->getEnd().getHour() << hourDelimiter << tService->getEnd().getMinute();
	ss >> eDate;

	ss.clear();
	ss.str(std::string());

	line.append(eDate).append(addressDelimiterB);

	//-------  ORIGIN ADDRESS  -------//
	std::string originAddress;
	std::string originAddressStreet, originAddressCity, originAddressZipCode, originAddressCountry;

	originAddressStreet = tService->getOrigin().getStreet();
	originAddressCity = tService->getOrigin().getCity();
	originAddressZipCode = tService->getOrigin().getZipCode();
	originAddressCountry = tService->getOrigin().getCountryAux();

	originAddress = originAddressStreet.append(delimiter).append(originAddressZipCode).append(delimiter)
			.append(originAddressCity).append(delimiter).append(originAddressCountry);

	line.append(originAddress).append(addressDelimiterE);

	//-------  DESTINATION INFO -------//
	std::string destinationAddress;
	std::string destinationAddressStreet, destinationAddressCity, destinationAddressZipCode, destinationAddressCountry;

	destinationAddressStreet = tService->getDestination().getStreet();
	destinationAddressCity = tService->getDestination().getCity();
	destinationAddressZipCode = tService->getDestination().getZipCode();
	destinationAddressCountry = tService->getDestination().getCountryAux();

	destinationAddress = destinationAddressStreet.append(delimiter).append(destinationAddressZipCode).append(delimiter)
			.append(destinationAddressCity).append(delimiter).append(destinationAddressCountry);


	line.append(destinationAddress).append(addressDelimiterE);

	//------- PACKAGING INFO  --------//

	std::string packagingDateB;
	ss << tService->getPackagingBegginingDate().getDay() << dateDelimiter << tService->getPackagingBegginingDate().getMonth() << "-"
			<< tService->getPackagingBegginingDate().getYear()<< dateDelimiter << tService->getPackagingBegginingDate().getHour()
			<< hourDelimiter << tService->getPackagingBegginingDate().getMinute();
	ss >> packagingDateB;

	ss.clear();
	ss.str(std::string());

	std::string packagingDateE;

	ss << tService->getPackagingEndDate().getDay() << dateDelimiter << tService->getPackagingEndDate().getMonth() << "-"
			<< tService->getPackagingEndDate().getYear()<< dateDelimiter << tService->getPackagingEndDate().getHour()
			<< hourDelimiter << tService->getPackagingEndDate().getMinute();

	ss >> packagingDateE;

	ss.clear();
	ss.str(std::string());

	line.append("P/").append(packagingDateB).append(delimiter).append(packagingDateE).append(delimiter);


	//------- SHIPPING INFO  --------//

	std::string shippingDateB, shippingDateE;

	ss << tService->getShippingBegginingDate().getDay() << dateDelimiter << tService->getShippingBegginingDate().getMonth() << "-"
			<< tService->getShippingBegginingDate().getYear()<< dateDelimiter << tService->getShippingBegginingDate().getHour()
			<< hourDelimiter << tService->getShippingBegginingDate().getMinute();
	ss >> shippingDateB;

	ss.clear();
	ss.str(std::string());

	ss << tService->getShippingEndDate().getDay() << dateDelimiter << tService->getShippingEndDate().getMonth() << "-"
			<< tService->getShippingEndDate().getYear()<< dateDelimiter << tService->getShippingEndDate().getHour()
			<< hourDelimiter << tService->getShippingEndDate().getMinute();
	ss >> shippingDateE;

	ss.clear();
	ss.str(std::string());
	line.append("S/").append(shippingDateB).append(delimiter).append(shippingDateE).append(delimiter);

	//------- DELIVERY INFO  --------//

	std::string deliveryDateB, deliveryDateE;

	ss << tService->getDeliveryBegginingDate().getDay() << dateDelimiter << tService->getDeliveryBegginingDate().getMonth() << "-"
			<< tService->getDeliveryBegginingDate().getYear()<< dateDelimiter << tService->getDeliveryBegginingDate().getHour()
			<< hourDelimiter << tService->getDeliveryBegginingDate().getMinute();
	ss >> deliveryDateB;

	ss.clear();
	ss.str(std::string());

	ss << tService->getDeliveryEndDate().getDay() << dateDelimiter << tService->getDeliveryEndDate().getMonth() << "-"
			<< tService->getDeliveryEndDate().getYear()<< dateDelimiter << tService->getDeliveryEndDate().getHour()
			<< hourDelimiter << tService->getDeliveryEndDate().getMinute();
	ss >> deliveryDateE;

	ss.clear();
	ss.str(std::string());
	line.append("D/").append(deliveryDateB).append(delimiter).append(deliveryDateE).append(delimiter);

	//-------  PAYMENT TYPE  -------//
	std::string payType;
	std::string typePayment = tService->getPayment()->getPaymentType();

	if(typePayment == "Bank Transfer")
		payType = "BT";
	else if(typePayment == "Payable until the end of month")
		payType = "EOM";
	else if(typePayment == "Credit Card")
		payType = "CC";
	else
		payType = "ATM";

	line.append(payType).append(delimiter);

	//------- PAYMENT STATUS ------//
	std::string payStatus = tService->getPayment()->getPaymentStatus();
	line.append(payStatus).append("\n");

	return line;
}

std::string saveWarehousingService(Warehousing* wService, int idClient){

	std::string line;
	std::stringstream ss;
	std::string delimiter = "/", dateDelimiter = "-", hourDelimiter = ":", addressDelimiterB = "[", addressDelimiterE = "]";

	//------- CLIENT ID ------//
	std::string idC;
	ss << idClient;
	ss >> idC;

	ss.clear();
	ss.str(std::string());

	line.append(idC).append(delimiter);

	//-------SERVICE TYPE---------//

	std::string type = "W";
	line.append(type).append(delimiter);

	//------ WAREHOUSING DAYS ------//

	int daysWarehouse = wService->getDaysWarehouse();
	std::string daysW;

	ss << daysWarehouse;
	ss >> daysW;

	ss.clear();
	ss.str(std::string());

	line.append(daysW).append(delimiter);

	//--------SERVICE WEIGHT---------//

	int w = wService->getWeight();
	std::string weight;
	ss << w;
	ss >> weight;

	ss.clear();
	ss.str(std::string());

	line.append(weight).append(delimiter);

	//--------------BEGGINING DATE-------------//
	std::string bDate;
	ss << wService->getBeggining().getDay() << dateDelimiter << wService->getBeggining().getMonth() << "-" << wService->getBeggining().getYear()
			<< dateDelimiter << wService->getBeggining().getHour() << hourDelimiter << wService->getBeggining().getMinute();
	ss >> bDate;

	ss.clear();
	ss.str(std::string());

	line.append(bDate).append(delimiter);

	//-------------ENDING DATE------------//

	std::string eDate;
	ss << wService->getEnd().getDay() << dateDelimiter << wService->getEnd().getMonth() << "-" << wService->getEnd().getYear()
			<< dateDelimiter << wService->getEnd().getHour() << hourDelimiter << wService->getEnd().getMinute();

	ss >> eDate;

	ss.clear();
	ss.str(std::string());

	line.append(eDate).append(addressDelimiterB);

	//------------ORIGIN ADDRESS--------------//
	std::string originAddress;
	std::string originAddressStreet , originAddressCity, originAddressZipCode, originAddressCountry;

	originAddressStreet = wService->getOrigin().getStreet();
	originAddressCity = wService->getOrigin().getCity();
	originAddressZipCode = wService->getOrigin().getZipCode();
	originAddressCountry = wService->getOrigin().getCountryAux();

	originAddress = originAddressStreet.append(delimiter).append(originAddressZipCode).append(delimiter)
			.append(originAddressCity).append(delimiter).append(originAddressCountry);

	line.append(originAddress).append(addressDelimiterE);

	//------------DESTINATION INFO-----------//

	std::string destinationAddress;
	std::string destinationAddressStreet, destinationAddressCity, destinationAddressZipCode, destinationAddressCountry;

	destinationAddressStreet = wService->getDestination().getStreet();
	destinationAddressCity = wService->getDestination().getCity();
	destinationAddressZipCode = wService->getDestination().getZipCode();
	destinationAddressCountry = wService->getDestination().getCountryAux();

	destinationAddress = destinationAddressStreet.append(delimiter).append(destinationAddressZipCode).append(delimiter)
		.append(destinationAddressCity).append(delimiter).append(destinationAddressCountry);

	line.append(destinationAddress).append(addressDelimiterE);

	//---------------------PACKAGING INFO---------------//

	std::string packagingDateB;
	ss << wService->getPackagingBegginingDate().getDay() << dateDelimiter << wService->getPackagingBegginingDate().getMonth() << "-"
			<< wService->getPackagingBegginingDate().getYear() << dateDelimiter << wService->getPackagingBegginingDate().getHour()
			<< hourDelimiter << wService->getPackagingBegginingDate().getMinute();
	ss >> packagingDateB;

	ss.clear();
	ss.str(std::string());

	std::string packagingDateE;

	ss << wService->getPackagingEndDate().getDay() << dateDelimiter << wService->getPackagingEndDate().getMonth() << "-"
			<< wService->getPackagingEndDate().getYear()<< dateDelimiter << wService->getPackagingEndDate().getHour()
			<< hourDelimiter << wService->getPackagingEndDate().getMinute();

	ss >> packagingDateE;

	ss.clear();
	ss.str(std::string());

	line.append("P/").append(packagingDateB).append(delimiter).append(packagingDateE).append(delimiter);

	//------- SHIPPING INFO  --------//

	std::string shippingDateB, shippingDateE;

	ss << wService->getShippingBegginingDate().getDay() << dateDelimiter << wService->getShippingBegginingDate().getMonth() << "-"
			<< wService->getShippingBegginingDate().getYear()<< dateDelimiter << wService->getShippingBegginingDate().getHour()
			<< hourDelimiter << wService->getShippingBegginingDate().getMinute();
	ss >> shippingDateB;

	ss.clear();
	ss.str(std::string());

	ss << wService->getShippingEndDate().getDay() << dateDelimiter << wService->getShippingEndDate().getMonth() << "-"
			<< wService->getShippingEndDate().getYear()<< dateDelimiter << wService->getShippingEndDate().getHour()
			<< hourDelimiter << wService->getShippingEndDate().getMinute();
	ss >> shippingDateE;

	ss.clear();
	ss.str(std::string());

	line.append("S/").append(shippingDateB).append(delimiter).append(shippingDateE).append(delimiter);


	//------- DELIVERY INFO  --------//

	std::string deliveryDateB, deliveryDateE;

	ss << wService->getDeliveryBegginingDate().getDay() << dateDelimiter << wService->getDeliveryBegginingDate().getMonth() << "-"
			<< wService->getDeliveryBegginingDate().getYear()<< dateDelimiter << wService->getDeliveryBegginingDate().getHour()
			<< hourDelimiter << wService->getDeliveryBegginingDate().getMinute();
	ss >> deliveryDateB;

	ss.clear();
	ss.str(std::string());

	ss << wService->getDeliveryEndDate().getDay() << dateDelimiter << wService->getDeliveryEndDate().getMonth() << "-"
			<< wService->getDeliveryEndDate().getYear()<< dateDelimiter << wService->getDeliveryEndDate().getHour()
			<< hourDelimiter << wService->getDeliveryEndDate().getMinute();
	ss >> deliveryDateE;

	ss.clear();
	ss.str(std::string());
	line.append("D/").append(deliveryDateB).append(delimiter).append(deliveryDateE).append(delimiter);

	//-------  PAYMENT TYPE  -------//

	std::string payType;
	std::string typePayment = wService->getPayment()->getPaymentType();

	line.append(typePayment).append(delimiter);

	std::string payStatus = wService->getPayment()->getPaymentStatus();
	line.append(payStatus).append("\n");

	return line;
}

std::string saveServiceRequestTransport(int idClient, Service* service){

	Transport* tService = (Transport*)service;

	std::string line;
	std::stringstream ss;
	std::string delimiter = "/", dateDelimiter = "-", hourDelimiter = ":", addressDelimiterB = "[", addressDelimiterE = "]";

	//-------SERVICE TYPE--------//
	std::string type = "R";
	line.append(type).append(delimiter);


	//-------CLIENT ID------//
	std::string idC;
	ss << idClient;
	ss >> idC;

	ss.clear();
	ss.str(std::string());

	line.append(idC).append(delimiter);

	//---------TYPE OF SERVICE----------//

	std::string t = "T";
	line.append(t).append(delimiter);

	//--------- WEIGHT
	int w = tService->getWeight();
	std::string weight;
	ss << w;
	ss >> weight;

	ss.clear();
	ss.str(std::string());

	line.append(weight).append(delimiter);

	//----------BEGINNING DATE------------//

	std::string bDate;
	ss << tService->getBeggining().getDay() << dateDelimiter << tService->getBeggining().getMonth() << "-" << tService->getBeggining().getYear()
			<< dateDelimiter << tService->getBeggining().getHour() << hourDelimiter << tService->getBeggining().getMinute();
	ss >> bDate;

	ss.clear();
	ss.str(std::string());

	line.append(bDate).append(addressDelimiterB);

	//------------ORIGIN ADDRESS--------------//
	std::string originAddress;
	std::string originAddressStreet , originAddressCity, originAddressZipCode, originAddressCountry;

	originAddressStreet = tService->getOrigin().getStreet();
	originAddressCity = tService->getOrigin().getCity();
	originAddressZipCode = tService->getOrigin().getZipCode();
	originAddressCountry = tService->getOrigin().getCountryAux();

	originAddress = originAddressStreet.append(delimiter).append(originAddressZipCode).append(delimiter)
			.append(originAddressCity).append(delimiter).append(originAddressCountry);

	line.append(originAddress).append(addressDelimiterE);

	//------------DESTINATION INFO-----------//

	std::string destinationAddress;
	std::string destinationAddressStreet, destinationAddressCity, destinationAddressZipCode, destinationAddressCountry;

	destinationAddressStreet = tService->getDestination().getStreet();
	destinationAddressCity = tService->getDestination().getCity();
	destinationAddressZipCode = tService->getDestination().getZipCode();
	destinationAddressCountry = tService->getDestination().getCountryAux();

	destinationAddress = destinationAddressStreet.append(delimiter).append(destinationAddressZipCode).append(delimiter)
		.append(destinationAddressCity).append(delimiter).append(destinationAddressCountry);

	line.append(destinationAddress).append(addressDelimiterE);

	//-------  PAYMENT TYPE  -------//

	line.append(tService->getPayment()->getPaymentType()).append(delimiter);

	//------- PAYMENT STATUS ------//
	std::string payStatus = tService->getPayment()->getPaymentStatus();
	line.append(payStatus).append("\n");

	return line;
}

std::string saveServiceRequestWarehousing(int idClient, Service* service){

	Warehousing* wService = (Warehousing*)service;

	std::string line;
	std::stringstream ss;
	std::string delimiter = "/", dateDelimiter = "-", hourDelimiter = ":", addressDelimiterB = "[", addressDelimiterE = "]";

	//-------SERVICE TYPE--------//
	std::string type = "R";
	line.append(type).append(delimiter);

	//-------CLIENT ID------//
	std::string idC;
	ss << idClient;
	ss >> idC;

	ss.clear();
	ss.str(std::string());

	line.append(idC).append(delimiter);

	//---------TYPE OF SERVICE----------//

	std::string t = "W";
	line.append(t).append(delimiter);

	//--------- WEIGHT
	int w = wService->getWeight();
	std::string weight;
	ss << w;
	ss >> weight;

	ss.clear();
	ss.str(std::string());

	line.append(weight).append(delimiter);

	//----------BEGINNING DATE------------//

	std::string bDate;
	ss << wService->getBeggining().getDay() << dateDelimiter << wService->getBeggining().getMonth() << "-" << wService->getBeggining().getYear()
			<< dateDelimiter << wService->getBeggining().getHour() << hourDelimiter << wService->getBeggining().getMinute();
	ss >> bDate;

	ss.clear();
	ss.str(std::string());

	line.append(bDate).append(addressDelimiterB);

	//------------ORIGIN ADDRESS--------------//
	std::string originAddress;
	std::string originAddressStreet , originAddressCity, originAddressZipCode, originAddressCountry;

	originAddressStreet = wService->getOrigin().getStreet();
	originAddressCity = wService->getOrigin().getCity();
	originAddressZipCode = wService->getOrigin().getZipCode();
	originAddressCountry = wService->getOrigin().getCountryAux();

	originAddress = originAddressStreet.append(delimiter).append(originAddressZipCode).append(delimiter)
			.append(originAddressCity).append(delimiter).append(originAddressCountry);

	line.append(originAddress).append(addressDelimiterE);

	//------------DESTINATION INFO-----------//

	std::string destinationAddress;
	std::string destinationAddressStreet, destinationAddressCity, destinationAddressZipCode, destinationAddressCountry;

	destinationAddressStreet = wService->getDestination().getStreet();
	destinationAddressCity = wService->getDestination().getCity();
	destinationAddressZipCode = wService->getDestination().getZipCode();
	destinationAddressCountry = wService->getDestination().getCountryAux();

	destinationAddress = destinationAddressStreet.append(delimiter).append(destinationAddressZipCode).append(delimiter)
		.append(destinationAddressCity).append(delimiter).append(destinationAddressCountry);

	line.append(destinationAddress).append(addressDelimiterE);

	//-------  PAYMENT TYPE  -------//

	line.append(wService->getPayment()->getPaymentType()).append(delimiter);

	//------- PAYMENT STATUS ------//
	std::string payStatus = wService->getPayment()->getPaymentStatus();
	line.append(payStatus).append(delimiter);

	int days = wService->getDaysWarehouse();
	std::string daysWarehouse;
	ss << days;
	ss >> daysWarehouse;

	line.append(daysWarehouse).append("\n");

	return line;
}

void saveServices(MovingCompany& company){

	std::ofstream servicesFile;
	servicesFile.open("InfoFiles/services.txt", std::ios::trunc);

	int i, j;
	int clientsSize = company.getClients().size();
	std::queue<ServiceRequest*> aux = company.getServicesRequested();

	for(i = 0; i < clientsSize; i++){

		for(j = 0; j < (int)company.getClients()[i]->getServicesRequested().size(); j++){

			std::string infoService;

			if(!company.getClients()[i]->getServicesRequested()[j]->isWarehousing()){
				infoService = saveTransportService((Transport*)company.getClients()[i]->getServicesRequested()[j], company.getClients()[i]->getId());
			}
			else{
				infoService = saveWarehousingService((Warehousing*)company.getClients()[i]->getServicesRequested()[j], company.getClients()[i]->getId());
			}

			servicesFile << infoService;
		}
	}

	while(!aux.empty()){

		std::string infoServiceRequest;
		ServiceRequest* sr = aux.front();

		if(!sr->getService()->isWarehousing()){
			infoServiceRequest = saveServiceRequestTransport(sr->getClientID(), sr->getService());
		}
		else{
			infoServiceRequest = saveServiceRequestWarehousing(sr->getClientID(), sr->getService());
		}

		servicesFile << infoServiceRequest;
		aux.pop();
	}

	servicesFile.close();
}


