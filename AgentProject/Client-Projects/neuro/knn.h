#ifndef KNN_H
#define KNN_H

#include <vector>
#include <string>

#include "point.h"

using namespace std;

class Knn
{
public:
	int k;
	vector<Point> dataSet;

	Knn(int k);

	void train(vector<vector<double>> input, vector<int> output);

	int classify(vector<double> input);

};


class pointComparison
{
public:
	
	bool reverse;

	pointComparison(bool reverse)
	{
		this->reverse = reverse;
	}

	bool operator() (const pair<int, double>& lhs, const pair<int, double>&rhs) const
	{
		return reverse ? (lhs.second > rhs.second) : (lhs.second < rhs.second);
	}
};

#endif