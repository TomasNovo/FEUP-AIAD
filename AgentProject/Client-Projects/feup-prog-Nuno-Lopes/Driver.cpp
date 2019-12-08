#include "Driver.h"
#include <fstream>
#include <ostream>
#include <sstream>
#include <algorithm>

Driver::Driver() {
	id = 0;
	name = "";
	maxDayWorkingTime = 0;
	maxWeekWorkingTime = 0;
	minRestTime = 0;
}

Driver::Driver(int id, string name) {
	this->id = id;
	this->name = name;
	maxDayWorkingTime = 0;
	maxWeekWorkingTime = 0;
	minRestTime = 0;

	//Null Shift to initialize the vector
	vector <DriverWork> Null_Shifts(0);

	//initialization of the DriverShifts vector, it will always have 7 elements (from 0 to 6)
	for (int t = 0; t < 7; t++) {
		DriverShifts.push_back(make_pair(t, Null_Shifts));
	}
	maxWeekWorkingTimeConst = maxWeekWorkingTime;
}

Driver::Driver(int id, string name, int maxDayWorkingTime, int maxWeekWorkingTime, int minRestTime) {
	this->id = id;
	this->name = name;
	maxWeekWorkingTimeConst = maxWeekWorkingTime;
	this->maxDayWorkingTime = maxDayWorkingTime * 60;
	this->maxWeekWorkingTime = maxWeekWorkingTime * 60;
	this->minRestTime = minRestTime * 60;

	//Null Shift to initialize the vector
	vector <DriverWork> Null_Shifts(0);

	//initialization of the DriverShifts vector, it will always have 7 elements (from 0 to 6), representing the days
	for (int t = 0; t < 7; t++) {
		DriverShifts.push_back(make_pair(t,Null_Shifts));
	}
	
}

Driver::Driver(string one_driver)
{
	istringstream cada_condutor, cada_condutor2;
	cada_condutor.str(one_driver);
	string lixo, temp;
	cada_condutor >> id >> lixo;

	getline(cada_condutor, temp);
	temp = temp.substr(1);                 //eliminando assim o espaco entre ';' e o name
	cada_condutor2.str(temp);

	getline(cada_condutor2, name, ';');

	name = name.substr(0, name.size() - 1);   //eliminar o ultimo espaco
	cada_condutor2 >> maxDayWorkingTime >> lixo >> maxWeekWorkingTime  >> lixo >> minRestTime ;   //o lixo serve para descartar os ';'
	maxWeekWorkingTimeConst = maxWeekWorkingTime;
	maxDayWorkingTime = maxDayWorkingTime * 60;
	maxWeekWorkingTime = maxWeekWorkingTime * 60;
	minRestTime = minRestTime * 60;

	//Null Shift to initialize the vector
	vector <DriverWork> Null_Shifts(0);

	//initialization of the DriverShifts vector, it will always have 7 elements (from 0 to 6)
	for (int t = 0; t < 7; t++) {
		DriverShifts.push_back(make_pair(t, Null_Shifts));
	}
}

void Driver::setName(string name) {
	this->name = name;
}
void Driver::setID(int id) {
	this->id = id;
}
void Driver::setMaxHours(int maxDayWorkingTime) {
	this->maxDayWorkingTime = maxDayWorkingTime;
}
void Driver::setMaxWeekWorkingTime(int maxWeekWorkingTime) {
	this->maxWeekWorkingTime = maxWeekWorkingTime;
}
void Driver::setMinRestTime(int minRestTime) {
	this->minRestTime = minRestTime;
}
void Driver::addShift(pair <int, DriverWork> Turno) {
	DriverShifts.at(Turno.first).second.push_back(Turno.second);
}
bool operator==(const DriverWork& Turno1, const DriverWork& Turno2) {
	if (Turno1.getStartTime() == Turno2.getStartTime() && Turno1.getEndTime() == Turno2.getEndTime())
		return true;
	else
		return false;
}

void Driver::removeShift(pair <int, DriverWork> Turno) {
	DriverShifts.at(Turno.first).second.erase(std::remove(DriverShifts.at(Turno.first).second.begin(), DriverShifts.at(Turno.first).second.end(), Turno.second), DriverShifts.at(Turno.first).second.end());
}


int Driver::getID() const {
	return id;
}
string Driver::getName() const {
	return name;
}
int Driver::getMaxHours() const {
	return maxDayWorkingTime;
}
int Driver::getMaxWeekWorkingTime() const {
	return maxWeekWorkingTime;
}
int Driver::getMaxWeekWorkingTimeConst() const {
	return maxWeekWorkingTimeConst;
}
int Driver::getMinRestTime() const {
	return minRestTime;
}

vector <int> Driver::getStartTimes(int day) {
	vector <int> StartTimes;
	for (size_t t = 0; t < DriverShifts.at(day).second.size(); t++)
		StartTimes.push_back(DriverShifts.at(day).second.at(t).getStartTime());

	return StartTimes;
}

vector <int> Driver::getEndTimes(int day) {
	vector <int> EndTimes;
	for (size_t t = 0; t < DriverShifts.at(day).second.size(); t++)
		EndTimes.push_back(DriverShifts.at(day).second.at(t).getEndTime());

	return EndTimes;
}

vector <Shift *> Driver::getShifts(int day) {
	vector <Shift *> DayShifts;
	for (size_t t = 0; t < DriverShifts.at(day).second.size(); t++)
		for (size_t k = 0; k < DriverShifts.at(day).second.at(t).getWorkShifts().size(); k++)
			DayShifts.push_back(DriverShifts.at(day).second.at(t).getWorkShifts().at(k));
	return DayShifts;
}

vector <pair <int,vector < DriverWork>>> Driver::getAllDriverShifts()  {
	vector <pair <int, vector < DriverWork>>> Shifts;
	for (size_t t = 0; t < DriverShifts.size(); t++) {
		if (!DriverShifts.at(t).second.empty())
			Shifts.push_back(make_pair(t, DriverShifts.at(t).second));
	}

	return Shifts;
}

vector <DriverWork> Driver::getDayWork(int day){
	vector <DriverWork> Works;
	for (size_t t = 0; t < DriverShifts.at(day).second.size(); t++) {
		Works.push_back(DriverShifts.at(day).second.at(t));
	}
	return Works;
}

void Driver::showInfo() const {
	cout << "CONDUTOR: " << name << endl;
	cout << '\t' << "ID: " << id << endl;
	cout << '\t' << "Duracao do turno: " << maxDayWorkingTime / 60 << endl;
	cout << '\t' << "Numero maximo de horas por semana: " << maxWeekWorkingTimeConst << endl;
	cout << '\t' << "Numero minimo de horas de descanso obrigatorio: " << minRestTime / 60 << endl;
}


