#ifndef AEDA_P1_DESTROY_H
#define AEDA_P1_DESTROY_H

#include "Bike.h"

class Destroy_Form
{
	Bike *bike_to_destroy;
	Date scheduled_destruction;
	bool Destroyed;

public:
	Destroy_Form(Bike *bk, Date dt);
	Date getDate() const;
	Bike* getBike() const;
	void setDestroyed();
	bool isDestroyed() const;
	bool operator==(const Destroy_Form &df1) const;
};

#endif