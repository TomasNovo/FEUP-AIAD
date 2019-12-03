/*
 * Shipping.cpp
 *
 *  Created on: 15/11/2017
 *      Author: Francisco Maria / João Gama Amaral
 */

#include "Shipping.h"

Shipping::Shipping(Date& b, Date& e, float w, int id): beggining(b), end(e), weight(w){
	cost = w * TAX_SHIPPING;
}

Date& Shipping::getBeggining(){
	return beggining;
}

Date& Shipping::getEnd(){
	return end;
}

float Shipping::getCost() const{
	return cost;
}


