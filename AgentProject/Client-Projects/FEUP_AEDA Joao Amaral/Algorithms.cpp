/*
 * Algorithms.cpp
 *
 *  Created on: 24/11/2017
 *      Author: Francisco Maria / João Gama Amaral
 */

#include "Algorithms.h"


// ----- PRINT CLIENTS INFO

void bubbleSort(std::vector<Client*>& clients_aux){

	for(unsigned int j=clients_aux.size()-1; j > 0; j--)
	{
		bool change = false;
		for(unsigned int i = 0; i < j; i++)
			if(clients_aux[i+1]->getName() < clients_aux[i]->getName()) {
				std::swap(clients_aux[i],clients_aux[i+1]);
				change = true;
			}
		if (!change) return;
	}
}


void selectionSort(std::vector<Client*> &c_aux )
{
	int j, i;
	std::vector<Client*>::iterator it;

	for(i = 0; i < c_aux.size(); i++){

		for(j = i+1; j < c_aux.size(); j++){
			if(c_aux[j]->getJoiningDate() < c_aux[i]->getJoiningDate()){
				Client* c = c_aux[i];
				c_aux[i] = c_aux[j];
				c_aux[j] = c;
			}
		}
	}
}

//  -- BINARY SEARCH
int binarySearch(const std::vector<Client*> &v, int x)
{
	int left = 0, right = v.size() - 1;

	while (left <= right)
	{
		int middle = (left + right) / 2;

		if (v[middle]->getId() < x)
			left = middle + 1;
		else if (x < v[middle]->getId())
			right = middle-1;
		else
			return middle; // encontrou
	}
	return -1; // não encontrou
}

int binarySearch(const std::vector<Client*> &v, std::string x)
{
	int left = 0, right = v.size() - 1;

	while (left <= right)
	{
		int middle = (left + right) / 2;

		if (v[middle]->getName() < x)
			left = middle + 1;
		else if (x < v[middle]->getName())
			right = middle-1;
		else
			return middle; // encontrou
	}
	return -1; // não encontrou
}




