/*
 * Delivery.h
 *
 *  Created on: 15/11/2017
 *      Author: Francisco Maria / João Gama Amaral
 */

#ifndef DELIVERY_H_
#define DELIVERY_H_

#include "Libraries.h"
#include "Date.h"

const float TAX_DELIVERY = 0.01;		// 1%

/**
 * @brief Class that stores all delivery information.
 */
class Delivery{
	float cost;
	Date beggining;
	Date end;
	float weight;
public:
	/**
	 * @brief Delivery Constructor
	 */
	Delivery(Date& b, Date& e, float w, int id);

	/**
	 * @brief gets begginning delivery date
	 * @return date
	 */
	Date& getBeggining();

	/**
	 * @brief gets ending delivery date
	 * @return date
	 */
	Date& getEnd();

	/**
	 * @brief gets cost of the delivery service
	 * @return delivery cost
	 */
	float getCost() const;
};



#endif /* DELIVERY_H_ */
