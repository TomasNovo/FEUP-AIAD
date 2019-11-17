#include "knn.h"

#include <queue>
#include <unordered_map>

Knn::Knn(int k)
{
	this->k = k;
	dataSet = vector<Point>();
}

void Knn::train(vector<vector<double>> input, vector<int> output)
{
	for (int i = 0; i < input.size(); ++i)
	{
		Point point(input[i], output[i]);

		dataSet.push_back(point);
	}
}


int Knn::classify(vector<double> input)
{
	Point point(input);
	priority_queue<pair<int, double>, vector<pair<int, double>>, pointComparison> kNearest(pointComparison(false));
	double distance;

	for (int i = 0; i < dataSet.size(); ++i)
	{
		distance = dataSet[i].euclideanDistance(point);
	
		if (kNearest.size() < k)
		{
			kNearest.push(pair<int, double>(i, distance));
		}
		else if (distance < kNearest.top().second)
		{
			kNearest.pop();
			kNearest.push(pair<int, double>(i, distance));
		}
	}

	// Convert amount of times each classification appears to a map
	unordered_map<int, int> table;
	while (kNearest.size() != 0)
	{
		int classification = dataSet[kNearest.top().first].classification;
		kNearest.pop();

		if (table.find(classification) == table.end())
			table[classification] = 1;
		else
			table[classification]++;
	}

	// Retrieve max classification
	int maxClassification = -1;
	int maxClassificationCount = 0;
	for (auto& it: table) 
	{
		if (it.second > maxClassificationCount)
		{
			maxClassificationCount = it.second;
			maxClassification = it.first;
		}
	}

	return maxClassification;
}



