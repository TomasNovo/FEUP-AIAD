#include "SummerSchool.h"
#include "Association.h"
#include "Associate.h"
#include <sstream>
using namespace std;

//Constructors
SummerSchool::SummerSchool() {
}

SummerSchool::SummerSchool(vector<Associate *> event_request,
		vector<Associate *> event_organizers, string date, string local,
		string theme, int phase, Association * association,
		list<Trainer *> trainers) :
		Event(event_request, event_organizers, date, local, theme, phase,
				association) {
	this->trainers = trainers;

	int counter = 0;
	int total = event_organizers.size();
	for (size_t t = 0; t < event_organizers.size(); t++) {
		if ((event_organizers.at(t)->getStatus() == "normal")
				|| (event_organizers.at(t)->getStatus() == "subscriber"))
			counter++;
	}

	int total_support = 0;
	float ratio = counter / (total * 1.0);
	if (ratio >= 2.0 / 3) //if two thirds or more of the organizers havent got their payments up to date, the association will not give payment
		throw InvalidRequest(counter, total);
	else if (ratio >= 1.0 / 3) //will be given a monetary support of 10% the total association fund
		this->given_support = 1000 + event_request.size() * 200;
	else if (ratio < 1.0 / 3 && ratio > 0)  //15 percent
		this->given_support = 2000 + event_request.size() * 200;
	else
		//if everyone has his payments up to date,
		this->given_support = 3500 + event_request.size() * 200;

	//if an event is successfully created, each of its creators will receive a small income

	if (this->association->getFund() < this->given_support)
		throw InvalidRequest(counter, total);

}

SummerSchool::SummerSchool(std::vector<Associate *> event_request,
		std::vector<Associate *> event_organizers, std::string date,
		std::string local, std::string theme, int phase, Association * association,
		std::list<Trainer *> trainers, long double given_support) :
		Event(event_request, event_organizers, date, local, theme, phase, association), given_support(
				given_support), trainers(trainers){
}
;

SummerSchool::~SummerSchool() {
	// TODO Auto-generated destructor stub
}

//Get Methods

long double SummerSchool::getSupport() const {
	return this->given_support;
}

string SummerSchool::getType() const {
	return this->type;
}

list<Trainer *> SummerSchool::getTrainers() const {
	return this->trainers;
}

int SummerSchool::getEstimative() const {
	return 0;
}


//General Methods
string SummerSchool::showInfo() const {
	string info = "";

	info += "SummerSchool Type Event: \n";
	info += string(this->theme) + "\n";
	info += "\t Local: " + string(this->local);
	info += "\n\t Data: " + string(this->date);
	info += "\n\t Fase: " + to_string(this->phase);
	info += "\n\t Criadores: ";

	for (size_t t = 0; t < this->event_request.size(); t++)
		info += this->event_request.at(t)->getName() + "("
				+ to_string(this->event_request.at(t)->getUniqueID()) + ")"
				+ " ";

	info += "\n\t Organizadores: ";
	for (size_t t = 0; t < this->event_organizers.size(); t++)
		info += this->event_organizers.at(t)->getName() + "("
				+ to_string(this->event_organizers.at(t)->getUniqueID()) + ")"
				+ " ";

	info += "\n\t Suporte dado: " + to_string(this->given_support) + "\n";

	info += "\t Formadores: ";

	for (auto it = trainers.begin(); it != trainers.end(); it++) {
		info += (*it)->getName() + "/" + (*it)->getInstitution() + "  ";
	}

	info += "\n";

	return info;

}

