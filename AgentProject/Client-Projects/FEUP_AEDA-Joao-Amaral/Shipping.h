/*
 * Shipping.h
 *
 *  Created on: 15/11/2017
 *      Author: Francisco
 */

#ifndef SHIPPING_H_
#define SHIPPING_H_

#include "Libraries.h"
#include "Date.h"

const float TAX_SHIPPING = 0.075;

/**
 * @brief Class that stores all information of shipping service
 */
class Shipping{
	float cost;
	Date beggining;
	Date end;
	float weight;
public:
	/**
	 * @brief Shipping constructor
	 */
	Shipping(Date& b, Date& e, float w, int id);

	/**
	 * @brief Shipping Destructor
	 */
	~Shipping(){};

	/**
	 * @brief gets beggining shipping date
	 * @return date
	 */
	Date& getBeggining();

	/**
	 * @brief gets ending shipping date
	 * @return date
	 */
	Date& getEnd();

	/**
	 * @brief gets cost of the shipping service
	 * @return shipping cost
	 */
	float getCost() const;
};


#endif /* SHIPPING_H_ */
