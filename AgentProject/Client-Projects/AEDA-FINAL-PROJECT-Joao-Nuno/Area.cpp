/*
 * Area.cpp
 *
 */

#include "Area.h"
#include "SubArea.h"
#include <sstream>
#include <iostream>

using namespace std;

Area::Area() {
	this->name = "";

}

void Area::addSubarea(SubArea * newSub) {

	this->subareas.push_back(newSub);

}

Area::Area(string file_string) {

	string areaName, subAreaName, subAreaInitials;
	string garbage;
	istringstream infoArea(file_string);
	getline(infoArea, areaName, '/');
	this->name = areaName;
	while (!infoArea.eof()) {  //num xei shié eofê
		getline(infoArea, subAreaName, '/');
		getline(infoArea, subAreaInitials, '/');
		SubArea * subarea = new SubArea(subAreaName, subAreaInitials);
		this->addSubarea(subarea);
	}

}

Area::~Area() {
	// TODO Auto-generated destructor stub
}

//Get Methods

string Area::getName() const {
	return this->name;
}

vector<SubArea *> Area::getSubAreas() const {
	return this->subareas;
}



//General


