/*
 * Associate.cpp
 */

#include "Associate.h"
#include "Area.h"
#include "SubArea.h"
#include "Association.h"
#include <sstream>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int Associate::id_provider = 0;

//Constructors
Associate::Associate() {

	this->name = "";

}

Associate::Associate(int uniqueID) {
	this->uniqueID = uniqueID;
}

Associate::Associate(Association * asso, string name, string institution,
		vector<Area *> interests) :
		uniqueID(++id_provider) {
	this->association = asso;
	this->name = name;
	this->institution = institution;
	this->interestAreas = interests;
	this->personalWallet = 500.0;  //DEFAULT FOR EVERY ASSOCIATE
	this->divulgations = 0;
	this->paidYears.push_back(asso->getCurrentYear()); //THE ASSOCIATE DOES NOT NEED TO PAY THE FIRST YEAR, IT IS GIVEN
}

Associate::Associate(Association * asso, std::string name,
		std::string institution, vector<Area*> interests, float personalWallet,
		string status, vector<int> paidYears, int uniqueID, int divulgations) {
	this->association = asso;
	this->name = name;
	this->institution = institution;
	this->interestAreas = interests;
	this->personalWallet = personalWallet;
	this->divulgations = divulgations;
	this->paidYears = paidYears;
	this->uniqueID = uniqueID;
	this->status = status;

}

Associate::Associate(Association * association, string file_string) {

	/*
	 * ID/Name/Instituion/[Interest Areas]/Wallet/[Years Paid]/Divulgations
	 *
	 * */

	this->association = association;

	istringstream infoAssociate(file_string);

	string name, institution, interest;
	int id, years, divulgation;
	float wallet;
	char garbage;

	infoAssociate >> id;

	this->uniqueID = id;

	infoAssociate >> garbage;

	getline(infoAssociate, name, '/');

	this->name = name;

	getline(infoAssociate, institution, '/');

	this->institution = institution;

	infoAssociate >> garbage;

	while (infoAssociate.peek() != ']') {

		getline(infoAssociate, interest, '/');

		for (size_t t = 0; t < this->association->getAreas().size(); t++) {

			if (interest == this->association->getAreas().at(t)->getName())
				this->interestAreas.push_back(
						this->association->getAreas().at(t));

		}

	}

	infoAssociate >> garbage;

	infoAssociate >> garbage;

	infoAssociate >> wallet;

	this->personalWallet = wallet;

	infoAssociate >> garbage;

	infoAssociate >> garbage;

	while (infoAssociate.peek() != ']') {
		infoAssociate >> years;
		this->paidYears.push_back(years);
		infoAssociate >> garbage;

	}

	infoAssociate >> garbage;

	infoAssociate >> divulgation;

	this->divulgations = divulgation;

	this->status = "contributor";

	/*When reading associates from the file
	 * we must ensure that the id_provider static variable will be updated
	 * accordingly, in order to maintain the add Associate function viable
	 */
	if (this->uniqueID > Associate::id_provider)
		Associate::id_provider = uniqueID;

}

//Destructors
Associate::~Associate() {
	// TODO Auto-generated destructor stub
}

//Get Methods

string Associate::getName() const {
	return name;
}

int Associate::getUniqueID() const {
	return this->uniqueID;
}

string Associate::getStatus() const {
	return this->status;
}

vector<int> Associate::getPaidYears() const {
	return this->paidYears;
}

float Associate::getPersonalWallet() const {
	return this->personalWallet;
}

string Associate::getInstitution() const {
	return this->institution;
}

vector<Area *> Associate::getInterestAreas() const {
	return this->interestAreas;
}

int Associate::getDivulgations() const {
	return this->divulgations;
}

//Set Methods

void Associate::setInterestAreas(vector<Area *> interest) {
	this->interestAreas = interest;
}

void Associate::setStatus(string newStatus) {
	this->status = newStatus;
}

void Associate::setPaidYears(vector<int> paid) {
	this->paidYears = paid;
}

void Associate::setPersonallWallet(float money) {
	this->personalWallet = money;
}

void Associate::setInstitution(string inst) {
	this->institution = inst;
}

void Associate::setDivulgations(int divulgation) {
	this->divulgations = divulgation;
}

//General Methods

void Associate::addToWallet(float more_money) {
	this->personalWallet += more_money;
}

void Associate::payFromWallet(float less_money) {
	this->personalWallet -= less_money;
}

void Associate::addPaidYear(int year) {
	this->paidYears.push_back(year);
}

void Associate::payYear(int year) {

	int lastYearPaid = this->paidYears.back();

	if (find(this->paidYears.begin(), this->paidYears.end(), year)
			!= this->paidYears.end())
		throw AlreadyPaid(year, this->uniqueID);

	if (lastYearPaid == Association::getCurrentYear() && year > lastYearPaid //if he has paid everything so far, he can pay upfront if he wants
	&& this->personalWallet >= this->association->getAnnualPay()) {

		this->addPaidYear(year);

		this->payFromWallet(this->association->getAnnualPay()); //Makes the payment from the associate wallet

		this->association->addToFund(this->association->getAnnualPay()); //Adds the payment to the fund

		this->updateStatus();

		sort(this->paidYears.begin(), this->paidYears.end());

		return;

	}

	if (lastYearPaid < (Association::getCurrentYear() - 1)

	&& year > (lastYearPaid + 1)) //if his payments are not up to date, he has to strictly pay the year after the last one paid

		throw NotUpToDate(year, this->uniqueID, lastYearPaid);

	else if (this->personalWallet < this->association->getAnnualPay())
		throw NotEnoughMoney(this->uniqueID);
	else {
		this->addPaidYear(year);

		sort(this->paidYears.begin(), this->paidYears.end());

		this->payFromWallet(this->association->getAnnualPay()); //Makes the payment from the associate wallet

		this->association->addToFund(this->association->getAnnualPay()); //Adds the payment to the fund

		this->updateStatus();

		this->association->moveAssociates();

	}
}

void Associate::updateStatus() {

	int lastYearPaid = this->paidYears.back();

	string statustemp = this->status;

	int currentYear = Association::getCurrentYear();

	if (lastYearPaid >= currentYear - 1) //if the last year he paid is the current last year or if he paid ahead
		this->status = "contributor";
	else if (lastYearPaid > (currentYear - 5))
		this->status = "subscriber";
	else
		this->status = "normal";

//	Associate * temp = new Associate(this->association, this->name,
//			this->institution, this->interestAreas, this->personalWallet,
//			this->status, this->paidYears, this->uniqueID, this->divulgations);
//
//	if (statustemp == "normal") {
//		if ((this->status == "subscriber") || (this->status == "contributor")) {
//
//			this->association->removeAssociate(this->uniqueID);
//			this->association->addAssociate(temp);
//		}
//	} else if ((statustemp == "subscriber") || (statustemp == "contributor")) {
//		if (this->status == "normal") {
//
//			this->association->removeAssociate(this->uniqueID);
//			this->association->addAssociate(temp);
//		}
//	}

}

void Associate::incDivulgations() {

	this->divulgations++;

}

bool Associate::accessNetwork() {

	return !(this->status == "normal"); //can always see except when its a normal associate

}

bool Associate::shareNetwork() {

	return this->status == "contributor"; //can only share if it is a contributor

}

string Associate::showInfo() const {

	string info = "";

	info += "Associado nº " + to_string(this->uniqueID) + ":\n" + "\t -Nome: "
			+ this->name + "\n" + "\t -Instituicao: " + this->institution + "\n"
			+ "\t -Status: " + this->status + "\n" + "\t -Wallet: "
			+ to_string(this->personalWallet) + "\n" + "\t -Divulgations: "
			+ to_string(this->divulgations) + "\n" + "\t -Interest Areas: ";

	for (size_t t = 0; t < this->interestAreas.size(); t++) {

		if (t == (this->interestAreas.size() - 1)) {
			info += this->interestAreas.at(t)->getName();
			break;
		}
		info += this->interestAreas.at(t)->getName() + ", ";

	}

	info += "\n\t -Paid Years: ";

	for (size_t t = 0; t < this->paidYears.size(); t++) {

		if (t == (this->paidYears.size() - 1)) {
			info += to_string(this->paidYears.at(t));
			break;
		}
		info += to_string(this->paidYears.at(t)) + ", ";
	}

	info += "\n";

	return info;
}

//Operators

bool Associate::operator<(const Associate & lhs) const {
	//return this->uniqueID < lhs.uniqueID;

	if (this->status == lhs.status)
		return this->name < lhs.name;

	int this_number;
	int lhs_number;

	if (this->status == "contributor")
		this_number = 0;
	else if (this->status == "subscriber")
		this_number = 1;
	else
		this_number = 2;

	if (lhs.status == "contributor")
		lhs_number = 0;
	else if (lhs.status == "subscriber")
		lhs_number = 1;
	else
		lhs_number = 2;

	return this_number < lhs_number;

}

Associate & Associate::operator=(const Associate & lhs) {

	this->association = lhs.association;
	this->divulgations = lhs.divulgations;
	this->institution = lhs.institution;
	this->interestAreas = lhs.interestAreas;
	this->name = lhs.name;
	this->paidYears = lhs.paidYears;
	this->personalWallet = lhs.personalWallet;
	this->status = lhs.status;
	this->uniqueID = lhs.uniqueID;

	return *this;

}
