/*
 * Delivery.cpp
 *
 *  Created on: 15/11/2017
 *      Author: Francisco Maria / João Gama Amaral
 */

#include "Delivery.h"

Delivery::Delivery(Date& b, Date& e, float w, int id): beggining(b), end(e), weight(w){
	cost = w * TAX_DELIVERY;
}

Date& Delivery::getBeggining(){
	return beggining;
}

Date& Delivery::getEnd(){
	return end;
}

float Delivery::getCost() const{
	return cost;
}

