/*
 * Association.cpp
 *
 */
#include "Association.h"
#include "Area.h"
#include "SubArea.h"
#include "Event.h"
#include <math.h>
#include <algorithm>
#include <sstream>
#include <iostream>

using namespace std;

//===========================================SORT FUNCTIONS==============================================

//=======================================================================================================

//============================================ASSOCIATE ONLY=============================================
/* @brief Compares two associates, pointed by.
 * Useful to call in the sort method, defined by the stl library.
 * An associate is smaller than the other if his uniqueID is smaller.
 *
 *@param rhs - pointer to the right-hand side associate
 *@param lhs - pointer to the left-hand side associate
 */
bool cmpID(Associate * rhs, Associate * lhs) {
	return rhs->getUniqueID() < lhs->getUniqueID();
}
;

bool cmpMoney(Associate * rhs, Associate * lhs) {
	return rhs->getPersonalWallet() < lhs->getPersonalWallet();
}
;
template<class T>
bool cmpName(T * rhs, T * lhs) {
	return rhs->getName() < lhs->getName();
}
;

//=======================================================================================================

//===========================================EVENT ONLY====================================================
/* @brief Compares two (pointed by) events.
 * Useful to call in the sort method, defined by the stl library.
 * In this case, an event is smaller than the other if it was
 * made earlier (time-wise).
 *
 * Dates are in format day-month-year
 *
 *@param rhs - pointer to the right-hand side Event
 *@param lhs - pointer to the left-hand side Event
 */
bool cmpDate(Event * rhs, Event * lhs) {

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

/* @brief Compares two (pointed by) events.
 * Useful to call in the sort method, defined by the stl library.
 * In this case, an event is smaller than the other if it's local is
 * alphabetically smaller than the other
 *
 *
 *@param rhs - pointer to the right-hand side Event
 *@param lhs - pointer to the left-hand side Event
 */
bool cmpLocal(Event * rhs, Event * lhs) {
	return rhs->getLocal() < lhs->getLocal();
}

/* @brief Compares two (pointed by) events.
 * Useful to call in the sort method, defined by the stl library.
 * In this case, an event is smaller than the other if it's theme is alphabetically
 * smaller than the other.
 *
 *@param rhs - pointer to the right-hand side Event
 *@param lhs - pointer to the left-hand side Event
 */
bool cmpTheme(Event * rhs, Event * lhs) {
	return rhs->getTheme() < lhs->getTheme();
}

/* @brief Compares two (pointed by) events.
 * Useful to call in the sort method, defined by the stl library.
 * In this case, an event is smaller than the other if it's phase is smaller than the other.
 *
 *@param rhs - pointer to the right-hand side Event
 *@param lhs - pointer to the left-hand side Event
 */
bool cmpPhase(Event * rhs, Event * lhs) {
	return rhs->getPhase() < lhs->getPhase();
}

//=======================================================================================================

float Association::currentYear = 0.0;

Association::Association() {
}

Association::Association(string name) :
		name(name) {
}
;

Association::Association(string file, Network * rede) {

	istringstream input(file);

	string name;
	long double fund;
	float annualPay;
	char garbage;
	float year;

	getline(input, name, '/');
	input >> fund;
	input >> garbage;
	input >> annualPay;
	input >> garbage;

	input >> year;
	Association::currentYear = year;

	this->name = name;
	this->fund = fund;
	this->annualPay = annualPay;
	this->network = rede;

}

Association::~Association() {
	// TODO Auto-generated destructor stub
}

//Set Methods

void Association::setName(string name) {
	this->name = name;
}

void Association::setFund(long double fund) {
	this->fund = fund;
}

void Association::setAnnualPay(float annualPay) {
	this->annualPay = annualPay;
}

void Association::setEvents(vector<Event *> all_events) {
	this->events = all_events;
}

//Get Methods

string Association::getName() const {
	return this->name;
}

long double Association::getFund() const {
	return this->fund;
}

float Association::getAnnualPay() const {
	return this->annualPay;
}

int Association::getCurrentYear() {
	return Association::currentYear / 1;
}

float Association::getCurrentSemester() {
	return fmod(Association::currentYear, 1);
}

set<Associate *> Association::getAssociates() const {
	return this->associates_set;
}

vector<Event *> Association::getEvents() const {
	return this->events;
}

HashTabInactiveAssociate Association::getInactiveAssociates() const {
	return this->inactiveAssociates;

}

priority_queue<Event *> Association::getQueue1() const {
	return this->queue1;
}

priority_queue<Event *> Association::getQueue2() const {
	return this->queue2;
}

void Association::pushToQueue(Event * evento) {

	if (evento->getPhase() == 1)
		this->queue1.push(evento);
	else
		this->queue2.push(evento);
}

//Associate Type Functions

void Association::addAssociate(Associate * newAsso) {

	int currentYear = Association::currentYear / 1;

	if ((currentYear - newAsso->getPaidYears().back()) >= 5)
		inactiveAssociates.insert(newAsso);
	else
		this->associates_set.insert(newAsso);
}

void Association::removeAssociate(int uniqueID) {

	auto it_set =
			find_if(this->associates_set.begin(), this->associates_set.end(),
					[uniqueID](Associate * obj) {return obj->getUniqueID() == uniqueID;});

	if (it_set != this->associates_set.end()) {

		this->associates_set.erase(it_set);

	} else {

		Associate * temp = new Associate(uniqueID);
		auto it_un = this->inactiveAssociates.find(temp);

		if (it_un != this->inactiveAssociates.end()) {
			this->inactiveAssociates.erase(it_un);
			delete (temp);
		} else {
			delete (temp);
			throw NoSuchID(uniqueID);
		}

	}

}

void Association::updateAllAssociates() {
	for (Associate * elem : this->associates_set)
		elem->updateStatus();

	for (Associate * elem : this->inactiveAssociates)
		elem->updateStatus();

	moveAssociates();
}

Associate * Association::getAssoById(int uniqueID) {

	auto it_set =
			find_if(this->associates_set.begin(), this->associates_set.end(),
					[uniqueID](Associate * obj) {return obj->getUniqueID() == uniqueID;});

	if (it_set != this->associates_set.end()) {

		return (*it_set);

	} else {

		Associate * temp = new Associate(uniqueID);
		auto it_un = this->inactiveAssociates.find(temp);

		if (it_un != this->inactiveAssociates.end()) {
			delete (temp);
			return (*it_un);
		} else
			throw NoSuchID(uniqueID);

	}

}

//Association Type Functions

void Association::updateSemester() {
	Association::currentYear += 0.5;
}

void Association::addToFund(float income) {
	this->fund += income;
}

string Association::updatePayment() {

	int yearToBePaid = Association::currentYear / 1;

	string log = "";

	for (auto it = this->associates_set.begin();
			it != this->associates_set.end(); it++) {

		try {
			(*it)->payYear(yearToBePaid);
			log += "Pagamento do Associado " + (*it)->getName() + " com o ID "
					+ to_string((*it)->getUniqueID())
					+ " efetuado com sucesso!\n";
		} catch (const NotEnoughMoney & e) {

			log += "Nao foi possivel efetuar o pagamento do  Associado "
					+ getAssoById(e.getID())->getName() + " com o ID "
					+ to_string(e.getID())
					+ " pois nao tem dinheiro suficiente.\n";

		} catch (const NotUpToDate & e) {

			log += "Nao foi possivel efetuar o pagamento do Associado "
					+ getAssoById(e.getID())->getName() + " com o ID "
					+ to_string(e.getID())
					+ " pois tentou efetuar o pagamento do ano "
					+ to_string(e.getYear()) + " quando o ultimo pago foi "
					+ to_string(e.getLast()) + ".\n";

		} catch (const AlreadyPaid & e) {

			log +=
					"Nao foi possivel efetuar o pagamento do Associado "
							+ getAssoById(e.getID())->getName() + " com o ID "
							+ to_string(e.getID())
							+ " pois tentou efetuar o pagamento de um ano ja pago previamente.\n";

		}

	}

	for (Associate * elem : this->inactiveAssociates) {

		try {
			elem->payYear(yearToBePaid);
			log += "Pagamento do Associado " + elem->getName() + " com o ID "
					+ to_string(elem->getUniqueID())
					+ " efetuado com sucesso!\n";
		} catch (const NotEnoughMoney & e) {

			log += "Nao foi possivel efetuar o pagamento do  Associado "
					+ getAssoById(e.getID())->getName() + " com o ID "
					+ to_string(e.getID())
					+ " pois nao tem dinheiro suficiente.\n";

		} catch (const NotUpToDate & e) {

			log += "Nao foi possivel efetuar o pagamento do Associado "
					+ getAssoById(e.getID())->getName() + " com o ID "
					+ to_string(e.getID())
					+ " pois tentou efetuar o pagamento do ano "
					+ to_string(e.getYear()) + " quando o ultimo pago foi "
					+ to_string(e.getLast()) + ".\n";

		} catch (const AlreadyPaid & e) {

			log +=
					"Nao foi possivel efetuar o pagamento do Associado "
							+ getAssoById(e.getID())->getName() + " com o ID "
							+ to_string(e.getID())
							+ " pois tentou efetuar o pagamento de um ano ja pago previamente.\n";

		}

	}

	moveAssociates();

	return log;
}

string Association::showAllAssociates() {
	string allInfo = "";

	allInfo += "Contributors and Subscribers:\n";
	for (auto it = this->associates_set.begin();
			it != this->associates_set.end(); it++) {
		allInfo += (*it)->showInfo();
	}

	allInfo += "\n Others:\n";

	for (auto it = this->inactiveAssociates.begin();
			it != this->inactiveAssociates.end(); it++) {
		allInfo += (*it)->showInfo();
	}

	return allInfo;
}

vector<Associate *> Association::sortAssociates(string type) {

	vector<Associate*> toReturn(this->associates_set.begin(),
			this->associates_set.end());

	if (type == "name")
		sort(toReturn.begin(), toReturn.end(), cmpName<Associate>);
	else if (type == "id")
		sort(toReturn.begin(), toReturn.end(), cmpID);
	else if (type == "money")
		sort(toReturn.begin(), toReturn.end(), cmpMoney);

	return toReturn;
}

void Association::moveAssociates() {

	Associate * keep_it = new Associate();

	for (auto it = this->associates_set.begin();
			it != this->associates_set.end();) {

		if ((*it)->getStatus() == "normal") {

			(*keep_it) = (**it);

			it = this->associates_set.erase(it);

			this->inactiveAssociates.insert(keep_it);

		} else

			it++;

	}

	for (auto it = this->inactiveAssociates.begin();
			it != this->inactiveAssociates.end();) {

		if ((*it)->getStatus() == "contributor"
				|| (*it)->getStatus() == "subscriber") {

			(*keep_it) = (**it);

			it = this->inactiveAssociates.erase(it);

			this->associates_set.insert(keep_it);

		} else

			it++;

	}

}

//Area Type Functions

vector<Area*> Association::getAreas() const {
	return this->areas;
}

void Association::addArea(Area * newArea) {
	this->areas.push_back(newArea);
}

string Association::showAreas() const {
	string info = "";
	for (size_t t = 0; t < this->areas.size(); t++) {
		info += to_string(t) + ": " + this->areas.at(t)->getName() + "\n";
		for (size_t k = 0; k < this->areas.at(t)->getSubAreas().size(); k++) {
			info += "\t " + this->areas.at(t)->getSubAreas().at(k)->getName()
					+ " "
					+ this->areas.at(t)->getSubAreas().at(k)->getInitials()
					+ "\n";
		}
	}

	return info;
}

//Event Type Functions

void Association::addEvent(Event * newEvent) {
	this->events.push_back(newEvent);
}

void Association::acceptEvents() {

	float maxSupportPerPhase = 5000;
	int maxEventsPerPhase = 3;

	float supportCounter = 0;
	int eventCounter = 0;

	if (this->getCurrentSemester() == 0.0) {

		priority_queue<Event *> first_queue = this->getQueue1();

		while (!first_queue.empty()) {

			if (eventCounter < maxEventsPerPhase) {	//did not create too many events
				if ((supportCounter + first_queue.top()->getSupport())
						< maxSupportPerPhase) {  //did not spend too much money
					if (this->getFund() > first_queue.top()->getSupport()) { //did not spend money the association didn't have

							//if the function reaches here, this event will happen
						this->events.push_back(first_queue.top());
						eventCounter++;
						supportCounter += first_queue.top()->getSupport();

						//if event is successful each requester receives 200
						for (size_t i = 0;
								i < first_queue.top()->getRequest().size();
								i++) {

							first_queue.top()->getRequest().at(i)->addToWallet(
									200);
						}
						this->fund -= first_queue.top()->getSupport();
					}
				}
			}

			first_queue.pop();
		}

		this->queue1 = first_queue;

	} else if (this->getCurrentSemester() == 0.5) {

		priority_queue<Event *> second_queue = this->getQueue2();

		while (!second_queue.empty()) {

			if (eventCounter < maxEventsPerPhase) {	//did not create too many events
				if ((supportCounter + second_queue.top()->getSupport())
						< maxSupportPerPhase) {  //did not spend too much money
					if (this->getFund() > second_queue.top()->getSupport()) { //did not spend money the association didn't have

							//if the function reaches here, this event will happen
						this->events.push_back(second_queue.top());
						eventCounter++;
						supportCounter += second_queue.top()->getSupport();

						//if event is successful each requester receives 200
						for (size_t i = 0;
								i < second_queue.top()->getRequest().size();
								i++) {

							second_queue.top()->getRequest().at(i)->addToWallet(
									200);
						}
						this->fund -= second_queue.top()->getSupport();
					}
				}
			}

			second_queue.pop();
		}

		this->queue2 = second_queue;
	}
}

string Association::showEvents() const {
	string info = "";

	for (size_t t = 0; t < this->events.size(); t++) {
		info += this->events.at(t)->showInfo() + "\n";
	}

	return info;
}

string Association::showRequests() const {

	string info = "";

	priority_queue<Event *> queue_one = this->queue1;
	priority_queue<Event *> queue_two = this->queue2;

	info += "Pedidos de eventos da Primeira Fase:\n";

	while (!queue_one.empty()) {

		Event * evento = queue_one.top();

		info += evento->showInfo() + '\n';

		queue_one.pop();

	}

	info += "\nPedidos de eventos da Segunda Fase:\n";

	while (!queue_two.empty()) {

		Event * evento = queue_two.top();

		info += evento->showInfo() + '\n';

		queue_two.pop();

	}

	return info;

}

void Association::removeEvent(string date, int phase) {

	priority_queue<Event *> temp;
	bool found = false;

	if (phase == 1) {

		priority_queue<Event *> first_queue = this->getQueue1();

		while (!first_queue.empty()) {

			if (first_queue.top()->getDate() == date) {
				found = true;
			} else
				temp.push(first_queue.top());

			first_queue.pop();
		}
		this->queue1 = temp;
	} else {

		priority_queue<Event *> second_queue = this->getQueue2();

		while (!second_queue.empty()) {

			if (second_queue.top()->getDate() == date)
				found = true;
			else
				temp.push(second_queue.top());

			second_queue.pop();
		}
		this->queue2 = temp;
	}

	if (!found)
		throw NoSuchDate(date);
}

vector<Event *> Association::getEventByDate(string date) {


	vector<Event *> temp;

	for(size_t i = 0; i < this->events.size(); i++){

		if(this->events.at(i)->getDate() == date)
			temp.push_back(this->events.at(i));
	}

	return temp;
}

Event * Association::getEventByDatePhase(string date, int phase) {

	priority_queue<Event *> temp;
	bool found = false;
	Event * retorno;

	if (phase == 1) {
		priority_queue<Event *> first_queue = this->getQueue1();

		while (!first_queue.empty()) {

			if (first_queue.top()->getDate() == date) {
				retorno = first_queue.top();
				found = true;
			}

			temp.push(first_queue.top());
			first_queue.pop();
		}
		this->queue1 = temp;
		if (found)
			return retorno;
		else
			throw NoSuchDate(date);
	} else {
		priority_queue<Event *> second_queue = this->getQueue2();

		while (!second_queue.empty()) {

			if (second_queue.top()->getDate() == date) {
				retorno = second_queue.top();
				found = true;
			}

			temp.push(second_queue.top());
			second_queue.pop();
		}
		this->queue2 = temp;

		if (found)
			return retorno;
		else
			throw NoSuchDate(date);
	}
}

void Association::sortEvents(std::string type) {

	if (type == "local")
		sort(this->events.begin(), this->events.end(), cmpLocal);
	else if (type == "date")
		sort(this->events.begin(), this->events.end(), cmpDate);
	else if (type == "theme")
		sort(this->events.begin(), this->events.end(), cmpTheme);
	else
		sort(this->events.begin(), this->events.end(), cmpPhase);
}

