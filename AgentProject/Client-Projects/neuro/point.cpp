#include "point.h"

#include <cmath>

Point::Point(int dimSize)
{
	this->dimentionSize = dimSize;
	coords = vector<double>(0.0, dimSize);
}

Point::Point(vector<double> coords)
{
	this->dimentionSize = coords.size();
	this->coords = coords;
}

Point::Point(vector<double> coords, int classification)
{
	this->dimentionSize = coords.size();
	this->coords = coords;
	this->classification = classification;
}


double Point::euclideanDistance(const Point& point)
{
	double distance = 0.0;

	if (coords.size() != point.coords.size())
		return -1;

	double dif;
	for (int i = 0; i < coords.size(); ++i)
	{
		dif = coords[i] - point.coords[i];
		dif *= dif;

		distance += dif;
	}

	return sqrt(distance);
}
