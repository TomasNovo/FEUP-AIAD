#ifndef AEDA_P1_FUNCS_H
#define AEDA_P1_FUNCS_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "Date.h"
#include "Bike.h"
#include "HQ.h"

using namespace std;

template <class T>
int find_element(vector<T *> vt, T *element)
{
	for (unsigned int i = 0; i < vt.size(); i++)
		if (*vt[i] == *element)
			return i;

	return -1;
}

void InvalidInput(int n_op, int &op);
double calc_distance(int x1, int y1, int x2, int y2);
Date read_date();
void write_date(Date global_date);

#endif