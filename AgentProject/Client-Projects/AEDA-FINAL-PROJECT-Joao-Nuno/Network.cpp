/*
 * Network.cpp
 *
 *  Created on: Nov 10, 2017
 *      Author: jubas
 */

#include "Network.h"
#include "Mail.h"
#include <algorithm>
#include <sstream>

using namespace std;

//===========================================SORT FUNCTIONS==============================================

//=======================================================================================================

/*
 * @brief Compares two mails, pointed by.
 * Useful to call in the sort method, defined by the stl library.
 * A Mail is smaller than the other if his title is smaller.
 *
 *@param rhs - pointer to the right-hand side associate
 *@param lhs - pointer to the left-hand side associate
 */
bool cmpTitle(Mail * rhs, Mail * lhs) {
	return rhs->getTitle() < lhs->getTitle();
}
;

bool cmpDate(Mail * rhs, Mail * lhs) {
	stringstream date1(rhs->getDate());
	stringstream date2(lhs->getDate());

	int year1, year2, month1, month2, day1, day2;
	char garbage;

	date1 >> day1 >> garbage >> month1 >> garbage >> year1;
	date2 >> day2 >> garbage >> month2 >> garbage >> year2;

	if (year1 != year2)
		return year1 < year2;
	else if (month1 != month2)
		return month1 < month2;
	return day1 < day2;
}
;

//Constructors
Network::Network() {
	// TODO Auto-generated constructor stub

}

//Destructors

Network::~Network() {
	// TODO Auto-generated destructor stub
}

//Set Methods

void Network::setMails(vector<Mail*> mails) {
	this->mails = mails;
}

//Get Methods

vector<Mail *> Network::getMails() const {
	return this->mails;
}

//General

void Network::addMail(Mail * newMail) {

	this->mails.push_back(newMail);
	sort(this->mails.begin(), this->mails.end(), cmpTitle);

}

void Network::sortMails(string type) {

	if (type == "title")
		sort(this->mails.begin(), this->mails.end(), cmpTitle);
	else if (type == "date")
		sort(this->mails.begin(), this->mails.end(), cmpDate);

}

