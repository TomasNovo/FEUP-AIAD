/*
 * Service.h
 *
 *  Created on: 02/11/2017
 *      Author: Francisco Maria / João Gama Amaral
 */

#ifndef SERVICE_H_
#define SERVICE_H_

#include "Libraries.h"
#include "Address.h"
#include "Date.h"
#include "Packaging.h"
#include "Shipping.h"
#include "Delivery.h"
#include "Payment.h"
#include "Vehicle.h"
#include <list>

const float TAX_WAREHOUSING_DAY = 0.01;		//  1%

/**
 * @brief Class that stores all service information
 */
class Service{
	int ID;
	Date beggining;
	Date end;
	Address origin;
	Address destination;
	float weight;
	Packaging* pack;
	Shipping* shipping;
	Delivery* delivery;
	Payment* payment;
	float totalCost;
	int zone;
	float baseRate;
	//int status;
	std::list<Vehicle*> vehiclesUsed;
	static int numberOfServices;
public:

	/**
	 * @brief Service Default Contructor
	 */
	Service(){}

	/**
	 * @brief Service Default Destructor
	 */
	~Service();

	/**
	 * @brief Service constructor to services with undefined ending date
	 */
	Service(Address& o, Address& d, float w, Date& b);

	/**
	 * @brief Service Constructor
	 */
	Service(Address& o, Address& d, float w, Date& b, Date& e);

	/**
	 * @brief adds base rate to service
	 * @param baseRate base rate of the country destination service
	 */
	void addBaseRate(float baseRate);

	/**
	 * @brief Adds zone of the service
	 * @param zone zone of the service
	 */
	void addZone(int zone);

	/**
	 * @brief Adds extra cost for extra services (warehousing, etc)
	 * @param cost cost to be added
	 */
	void addExtraCost(float cost);

	/**
	 * @brief Adds a new vehicle to the service
	 * @param v new vehicle used by the service
	 */
	void addVehicle(Vehicle* v);

	/**
	 * @return service ID
	 */
	int getID();

	/**
	 * @brief sets ID
	 * @param id ID to be set
	 */
	void setID(int id);

	/**
	 * @brief gets service request date
	 * @return date
	 */
	Date& getBeggining();

	/**
	 * @brief gets service ending date
	 * @return date
	 */
	Date& getEnd();

	/**
	 * @brief gets origin address
	 * @return address
	 */
	Address& getOrigin();

	/**
	 * @brief gets destination address
	 * @return address
	 */
	Address& getDestination();

	/**
	 * @brief gets payment
	 * @return payment
	 */
	Payment* getPayment() const;

	/**
	 * @brief Gets total weight of the packages
	 * @return weight of the package
	 */
	float getWeight() const;

	/**
	 * @brief Gets the total cost of the packages
	 * @return total cost of the service
	 */
	float getTotalCost() const;

	/**
	 * @brief Gets base rate of the service
	 * @return base rate
	 */
	float getBaseRate() const;

	/**
	 * @brief Gets zone of the service (1/2)
	 * @return zone
	 */
	int getZone() const;

	/**
	 * @brief Gets the list of vehicles used in the transport of the service
	 * @return list of vehicles used
	 */
	std::list<Vehicle*> getVehiclesUsed() const;

	/**
	 * @brief Gets the total number of services
	 * @return total amount of services
	 */
	static int getNumberOfServices();

	/**
	 * @brief sets packaging info
	 * @param p packaging
	 */
	void setPackaging(Packaging* p);

	/**
	 * @brief sets shipping info
	 * @param s shipping
	 */
	void setShipping(Shipping* s);

	/**
	 * @brief sets delivery info
	 * @param d delivery
	 */
	void setDelivery(Delivery* d);

	/**
	 * @brief sets payment
	 * @param pay payment
	 */
	void setPayment(Payment* pay);

	/**
	 * @brief sets last day of th service
	 * @param e ending date
	 */
	void setEndingDate(Date& e);

	/**
	 * @brief sets vehicles used to transport the cargo
	 * @param list of vehicles
	 */
	void setVehiclesUsed(std::list<Vehicle*> vehicles);

	/**
	 * @brief gets packaging beggining date
	 * @return date
	 */
	Date& getPackagingBegginingDate() const;

	/**
	 * @brief gets packaging ending date
	 * @return date
	 */
	Date& getPackagingEndDate() const;

	/**
	 * @brief gets packaging cost
	 * @return packaging cost
	 */
	float getPackagingCost() const;

	/**
	 * @brief gets shipping beginning date
	 * @return date
	 */
	Date& getShippingBegginingDate() const;

	/**
	 * @brief gets shipping ending date
	 * @return date
	 */
	Date& getShippingEndDate() const;

	/**
	 * @brief gets shipping cost
	 * @return shipping cost
	 */
	float getShippingCost() const;

	/**
	 * @brief gets delivery beginning date
	 * @return date
	 */
	Date& getDeliveryBegginingDate() const;

	/**
	 * @brief gets delivery ending date
	 * @return date
	 */
	Date& getDeliveryEndDate() const;

	/**
	 * @brief gets delivery cost
	 * @return delivery cost
	 */
	float getDeliveryCost() const;

	/**
	 * @brief prints a little resume of the service
	 */
	void printResume() const;

	/**
	 * @brief confirms/validate payment
	 */
	void validatePayment();

	/**
	 * @brief returns if it is or not a warehousing service
	 */
	virtual bool isWarehousing(){};

	/**
	 * @brief Checks if two services are the same
	 * @return true or false
	 */
	bool operator ==(Service& s);

	/**
	 * @brief prints a service
	 * @param o ostream
	 * @param s service to be printed
	 * @return ostream
	 */
	friend std::ostream& operator <<(std::ostream& o, const Service& s){
		o << "\n\t\t\t\tSERVICE INFO:\n" << "\t\t\tOrigin: " << s.origin.getCity() << "\t\tDestination: " << s.destination.getCity() <<
				"\n\t\t\tRequested on: " << s.beggining << "\tDelivered on: " << s.end << "\n\n\t\tDETAILED INFO:\n\n\t\t\t" <<
				"Packaging started on: "<< s.getPackagingBegginingDate() << "\tPackaging ended on: " << s.getPackagingEndDate() <<
				"\n\t\t\tShipping started on: " << s.getShippingBegginingDate() << "\tShipping ended on: " << s.getShippingEndDate() <<
				"\n\t\t\tDelivery started on: " << s.getDeliveryBegginingDate() << "\tDelivery ended on " << s.getDeliveryEndDate() <<
				"\n\t\t\tType of Payment: " << s.getPayment()->getPaymentType() << "\t\tPayment status: " << s.getPayment()->getPaymentStatus() <<
			    "\n\t\t\tTotal Price: " << s.getTotalCost();
		return o;
	}
};

/**
 * @brief Class that stores transport service information
 */
class Transport: public Service{
public:

	/**
	 * @brief Transport constructor to service with undefined ending date
	 */
	Transport(Address& o, Address& d, float w, Date& b);

	/**
	 * @brief Transport Constructor
	 */
	Transport(Address& o, Address& d, float w, Date& b, Date& e);

	/**
	 * @brief Checks if service has or not warehousing option
	 * @return false
	 */
	bool isWarehousing(){ return false; }
};

/**
 * @brief Class that stores warehousing service information
 */
class Warehousing: public Transport{
	int daysWarehouse;
	float warehousingCost;
public:

	/**
	 * @brief Warehousing constructor to service with undefined ending date
	 */
	Warehousing(Address& o, Address& d, float w, Date& b, int daysWarehouse);

	/**
	 * @brief Warehousing constructor
	 */
	Warehousing(Address& o, Address& d, float w, Date& b, Date& e, int daysWarehouse);

	/*
	 * @brief gets number of days in the warehouse
	 * @return warehouse days
	 */
	int getDaysWarehouse() const;

	/**
	 * @brief gets the cost of keeping the packages in warehouse
	 * @return warehousing cost
	 */
	float getWarehousingCost() const;

	/**
	 * @brief Checks if service has or not warehousing option
	 * @return true
	 */
	bool isWarehousing(){ return true; }
};



#endif /* SERVICE_H_ */
