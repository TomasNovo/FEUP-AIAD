#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>

#include "knn.h"
#include "globals.h"

using namespace std;



// int trainNN()
// {
	// initializeGlobals();

// 	GA ga(50, 784, 10);
// 	ga.addLayer(1, 30);
// 	ga.addLayer(1, 16);

// 	ga.simulate(input, output, 50);

// 	neuralNetwork nn("output.txt");
// 	// getImages("images/t10k-images.idx3-ubyte", "images/t10k-labels.idx1-ubyte");
// 	nn.train(input, output);

// 	// input = {readImage("sss2.bmp")};
// 	// vector<vector<double>> input2(28, vector<double>(28, 0.0));
// 	// for (int i = 0; i < 28; ++i)
// 	// {
// 	// 	for (int j = 0; j < 28; ++j)
// 	// 	{
// 	// 		input2[j][i] = (input[0][i*28 + j]);
// 	// 	}
// 	// }
	
// 	// saveImage("sss.bmp", input2);

// 	// // Create input
// 	// input.clear();
// 	// input.push_back(vector<double>());
// 	// for (int i = 0; i < input2.size(); ++i)
// 	// {
// 	// 	for (int j = 0; j < input2[i].size(); ++j)
// 	// 	{
// 	// 		input[0].push_back(input2[i][j]);
// 	// 	}
// 	// }

// 	// nn.propagate(input[200]);

// 	// cout << "size = " << nn.layers.back().size() << "\n";
// 	// for (int i = 0; i < 10; ++i)
// 	// {
// 	// 	cout << nn.layers.back()[i].value << "\n";
// 	// }

// 	cout << "Average error rate = " << nn.cost << "\n";

// 	return 0;
// }


int trainKnn()
{
	Knn knn(1);

	knn.train(input, labels);

	// getImages("images/t10k-images.idx3-ubyte", "images/t10k-labels.idx1-ubyte");

	// int matches = 0;
	// int limit = 1000;
	// for (int i = 0; i < limit; ++i)
	// {
	// 	if (knn.classify(input[i]) == labels[i])
	// 		matches++;

	// 	// cout << knn.classify(input[i]) << ", should be " << labels[i] << "\n";
	// }

	// cout << "precision = " << (double)matches/limit << "\n";

	vector<double> input = readImage("my2.bmp");

	cout << "I predict " << knn.classify(input);

	saveImage("newmy2.bmp", input);

	return 0;
}

int main()
{
	input.clear();
	output.clear();

	getImages("images/train-images.idx3-ubyte", "images/train-labels.idx1-ubyte");

	trainKnn();

	return 0;
}