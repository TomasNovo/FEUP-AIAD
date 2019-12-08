/*
 * Packaging.cpp
 *
 *  Created on: 15/11/2017
 *      Author: Francisco Maria / João Gama Amaral
 */

#include "Packaging.h"

Packaging::Packaging(Date& b, Date& e, float w, int id): beggining(b), end(e), weight(w){
	cost = w * TAX_PACKAGING;
}

Date& Packaging::getBeggining(){
	return beggining;
}

Date& Packaging::getEnd(){
	return end;
}

float Packaging::getCost() const{
	return cost;
}


