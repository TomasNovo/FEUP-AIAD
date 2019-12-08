/*
 * Event.cpp
 *
 *  Created on: Nov 14, 2017
 */

#include "Event.h"
#include "Association.h"
#include "Associate.h"
#include <sstream>

using namespace std;

//Constructors

Event::Event() {
}

Event::Event(vector<Associate *> event_request,
		vector<Associate *> event_organizers, string date, string local,
		string theme, int phase, Association * association) {
	this->association = association;
	this->date = date;
	this->event_organizers = event_organizers;
	this->event_request = event_request;
	this->local = local;
	this->theme = theme;
	this->phase = phase;
}

//Destructors

Event::~Event() {

	// TODO Auto-generated destructor stub

}

//Set Methods


void Event::setDate(std::string date){
	this->date = date;
}

void Event::setLocal(std::string local){
	this->local = local;
}

void Event::setTheme(std::string theme){
	this->theme = theme;
}

void Event::setPhase(int phase){
	this->phase = phase;
}



//Get Methods

vector<Associate *> Event::getRequest() const {

	return this->event_request;

}

vector<Associate *> Event::getOrganizers() const {

	return this->event_organizers;

}

string Event::getDate() const {

	return this->date;

}

string Event::getLocal() const {

	return this->local;

}

string Event::getTheme() const {

	return this->theme;

}

int Event::getPhase() const {

	return this->phase;

}

bool Event::operator < (Event* ev1) const{


	//+ contributor = +

	int contributor1, contributor2;
	int subscriber1, subscriber2;

	for (size_t i = 0; i < this->getOrganizers().size(); i++) {

		if (this->getOrganizers().at(i)->getStatus() == "contributor")
			contributor1++;
		else if (this->getOrganizers().at(i)->getStatus() == "subscriber")
			subscriber1++;
	}

	for (size_t i = 0; i < ev1->getOrganizers().size(); i++) {

		if (ev1->getOrganizers().at(i)->getStatus() == "contributor")
			contributor2++;
		else if (ev1->getOrganizers().at(i)->getStatus() == "subscriber")
			subscriber2++;
	}

	if(contributor1 == contributor2){
		if(subscriber1 == subscriber2)
			return(this->getOrganizers().size() < ev1->getOrganizers().size());
		else
			return(subscriber1 < subscriber2);
	}
	else
		return(contributor1 < contributor2);
}


