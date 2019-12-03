/*
 * Vehicle.h
 *
 *  Created on: 26/12/2017
 *      Author: Francisco Maria / João Gama Amaral
 */

#ifndef VEHICLE_H_
#define VEHICLE_H_

#include "Libraries.h"

/**
 * @brief Class that handles all vehicle information
 */
class Vehicle{
	int id;
	int maintenanceDays;
	float maxWeight;
	bool available;
	static int numberOfVehicles;
public:
	/**
	 * @brief Vehicle Constructor
	 * @param ID id of the vehicle
	 * @param maxW max weight of the vehicle
	 */
	Vehicle(int ID, int mDays, float maxW, bool a);

	/**
	 * @brief Gets vehicle ID
	 * @return ID of the vehicle
	 */
	int getID() const;

	/**
	 * @brief Gets total days of maintenance the car has to have after a service
	 * @return Maintenance days
	 */
	int getMaintenanceDays() const;

	/**
	 * @brief Gets max weight of cargo of the vehicle
	 * @return Max weight of the vehicle
	 */
	float getMaxWeight() const;

	/**
	 * @brief Gets number of vehicles
	 * @rturn Number of vehicles
	 */
	static int getNumberOfVehicles();

	/**
	 * @brief Changes availability of the vehicle (this means it can not be used for transortation)
	 * @param a availability (true or false)
	 */
	void changeAvailability(bool a);

	/**
	 * @brief Checks if vehicle is available to transport
	 * @return true or false depending on its availability
	 */
	bool isAvailable() const;

	/**
	 * @brief Checks if two vehicles are the same
	 * @param v Vehicle to be compared with
	 * @return True or false depending on the conditions
	 */
	bool operator ==(const Vehicle& v);

	/**
	 * @brief Checks which of the two vehicles is less than the other
	 * @param v Vehicle to be compared with
	 * @return True or false depending on the conditions
	 */
	bool operator <(const Vehicle& v);

	/**
	 * @brief Prints a vehicle
	 * @param o ostream
	 * @param v vehicle to be printed
	 * @return o ostream
	 */
	friend std::ostream& operator <<(std::ostream& o, const Vehicle& v){
		std::cout << "\n\t\t\t\t\t\t\t\tVEHICLE INFO\n\n\t\t\t\t\t\t\tID: " << v.getID()
				<< "\n\t\t\t\t\t\t\tMax Cargo Supported: " << v.getMaxWeight()
				<< "\n\n\t\t\t\t\t\t\t( Maintenance Days: " << v.getMaintenanceDays() <<
				" )" << std::endl;
		return o;
	}
};



#endif /* VEHICLE_H_ */
