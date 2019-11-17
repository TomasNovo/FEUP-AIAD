#ifndef POINT_H
#define POINT_H

#include <vector>

using namespace std;

class Point
{
public:
	int dimentionSize;
	vector<double> coords;
	int classification;

	Point(int dimSize);
	Point(vector<double> coords);
	Point(vector<double> coords, int classification);

	double euclideanDistance(const Point& point);

};



#endif