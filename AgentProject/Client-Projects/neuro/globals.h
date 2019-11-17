#ifndef GLOBALS_H
#define GLOBALS_H

#include <vector>
#include <chrono>
#include <random>
#include <string>
#include <iostream>

using namespace std;

extern default_random_engine generator;
extern normal_distribution<double> normalDistribution;
extern uniform_real_distribution<double> uniformDistribution;

extern vector<vector<vector<double>>> images;
extern vector<int> labels;
extern vector<vector<double>> input;
extern vector<vector<double>> output;

extern int maxImages;

void initializeGlobals();

bool getImages(string imagesFilename, string labelsFilename);

void saveImage(string filename, const vector<double>& input);
void saveImage(string filename, const vector<vector<double>>& input);

vector<double> readImage(string filename);



#endif