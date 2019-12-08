#include "Conference.h"
#include "Association.h"
#include "Associate.h"
using namespace std;

//Constructors
Conference::Conference() {
}

Conference::Conference(vector<Associate *> event_request,
		vector<Associate *> event_organizers, string date, string local,
		string theme, int phase, Association * association, int estimative) :
		Event(event_request, event_organizers, date, local, theme, phase,
				association) {
	this->estimative = estimative;
	//The given support, in the conference type event, will not take in consideration more people than the organizers
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

	if (this->association->getFund() < total_support)
		throw InvalidRequest(counter, total);

}

Conference::Conference(std::vector<Associate *> event_request,
		std::vector<Associate *> event_organizers, std::string date,
		std::string local, std::string theme, int phase, Association * association,
		int estimative, long double money) :
		Event(event_request, event_organizers, date, local, theme, phase, association), estimative(
				estimative), given_support(money) {
}
;

//Destructors

Conference::~Conference() {
	// TODO Auto-generated destructor stub
}

//Get Methods

int Conference::getEstimative() const {

	return this->estimative;

}

string Conference::getType() const {
	return this->type;
}

long double Conference::getSupport() const {
	return this->given_support;
}

list<Trainer *> Conference::getTrainers() const {
	list<Trainer *> trainers;

	return trainers;
}

//General Methods

string Conference::showInfo() const {
	string info = "";
	info += "Conference Type Event: \n";
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
	info += "\t Estimativa de participantes: " + to_string(this->estimative)
			+ "\n";

	return info;
}

