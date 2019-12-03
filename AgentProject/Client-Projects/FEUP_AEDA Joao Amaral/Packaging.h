/*
 * Packaging.h
 *
 *  Created on: 15/11/2017
 *      Author: Francisco
 */

#ifndef PACKAGING_H_
#define PACKAGING_H_

#include "Libraries.h"
#include "Date.h"

const float TAX_PACKAGING = 0.045; 	//4.5%

/**
 * @brief Class that stores all packaging information
 */
class Packaging{
	float cost;
	Date beggining;
	Date end;
	float weight;
public:
	/**
	 * @brief Packaging constructor
	 */
	Packaging(Date& b, Date& e, float w, int id);

	/**
	 * @brief gets begginning packaging date
	 * @return date
	 */
	Date& getBeggining();

	/**
	 * @brief gets ending packaging date
	 * @return date
	 */
	Date& getEnd();

	/**
	 * @brief gets cost of the packaging service
	 * @return packaging cost
	 */
	float getCost() const;
};




#endif /* PACKAGING_H_ */
