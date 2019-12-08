/*
 * SubArea.cpp
 *
 */

#include "SubArea.h"

using namespace std;

SubArea::SubArea() {
	// TODO Auto-generated constructor stub

}

SubArea::SubArea(string name, string initials) :
		name(name), initials(initials) {
}

SubArea::~SubArea() {
	// TODO Auto-generated destructor stub
}

//Get Methods
string SubArea::getName() const {
	return this->name;
}

string SubArea::getInitials() const {
	return this->initials;
}
