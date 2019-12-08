/*
 * Vehicle.cpp
 *
 *  Created on: 27/12/2017
 *      Author: Francisco Maria / João Gama Amaral
 */

#include "Vehicle.h"

int Vehicle::numberOfVehicles = 0;

Vehicle::Vehicle(int ID, int mDays, float maxW, bool a): id(ID), maintenanceDays(mDays), maxWeight(maxW), available(a){
	numberOfVehicles++;
}

int Vehicle::getID() const{
	return id;
}

int Vehicle::getMaintenanceDays() const{
	return maintenanceDays;
}

float Vehicle::getMaxWeight() const{
	return maxWeight;
}

int Vehicle::getNumberOfVehicles(){
	return numberOfVehicles;
}

void Vehicle::changeAvailability(bool a){
	available = a;
}

bool Vehicle::isAvailable() const{
	return available;
}

bool Vehicle::operator ==(const Vehicle& v){
	if(id == v.getID())
		return true;
	return false;
}

bool Vehicle::operator <(const Vehicle& v){
	if(maintenanceDays == v.getMaintenanceDays()){
		return maxWeight > v.getMaxWeight();
	}
	return maintenanceDays < v.getMaintenanceDays();
}

