#include "Destroy.h"

using namespace std;

Destroy_Form::Destroy_Form(Bike *bk, Date dt): scheduled_destruction(dt)
{
	bike_to_destroy = bk;
	Destroyed = false;
}

Date Destroy_Form::getDate() const
{
	return scheduled_destruction;
}

Bike* Destroy_Form::getBike() const
{
	return bike_to_destroy;
}

void Destroy_Form::setDestroyed()
{
	Destroyed = true;
}

bool Destroy_Form::isDestroyed() const
{
	return Destroyed;
}

bool Destroy_Form::operator==(const Destroy_Form &df1) const
{
	return (scheduled_destruction == df1.getDate()) && (bike_to_destroy->getID() == df1.getBike()->getID());
}