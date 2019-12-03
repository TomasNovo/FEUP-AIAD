#include <iomanip>
#include <sstream>
#include "extras.h"
#pragma warning(disable: 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

                      /////                                            /////
                     /////               EXTRAS . CPP                 /////
                    /////                                            /////

// Definition of class: Time

Time::Time(){}

Time::Time(unsigned int min, unsigned int h, unsigned int d, unsigned int m, unsigned int y): minutes(min), hours(h), day(d), month(m), year(y){}

Time::Time(const Time &t1):
		minutes(t1.minutes),
		hours(t1.hours),
		day(t1.day),
		month(t1.month),
		year(t1.year)
{}

Time::Time(string time){
	stringstream ss;
	char slash;
	char double_point;
	ss << time;
	ss >> this->year >> slash >> this->month >> slash >> this->day >> this->hours >> double_point >> this->minutes;
}

RealTime::RealTime():Time(0, 0, 0, 0, 0){
	time_t theTime = time(NULL);
	struct tm *aTime = localtime(&theTime);
	this->minutes = aTime->tm_min;
	this->hours = aTime->tm_hour;
	this->day = aTime->tm_mday;
	this->month = aTime ->tm_mon;
	this->year = aTime->tm_year;
}

void Time::printTime(ostream & os){
	os << year << "/" << month << "/" << day << " " << hours << ":" << minutes;
}

ostream & operator<<(ostream & os, Time & t){
	t.printTime(os);
	return os ;
}

unsigned int Time::getMinutes(){
	return this->minutes;
}

unsigned int Time::getHours(){
	return this->hours;
}

unsigned int Time::getDay() {
	return this->day;
}

unsigned int Time::getMonth() {
	return month;
}

unsigned int Time::getYear() {
	return year;
}


bool Time::operator==(Time t2){
	return (this->getDay() == t2.getDay() && t2.getMonth() == this->getMonth() && this->getYear() == t2.getYear());

}

bool Time::operator<( Time  t2){
	if(this->getYear() < t2.getYear())
		return true;
	else if(this->getYear() == t2.getYear()){
		if(this->getMonth() < t2. getMonth()){
			return true;
		}
		else if(this->getMonth() == t2.getMonth()){
			if(this->getDay() < t2.getDay()){
				return true;
			}
			else{
				return false;
			}
		}
		else{
			return false;
		}
	}
	else{
	return false;
	}
}

int Time::diferencaDias() {
	RealTime rt;
	int dias = 0;
	int realano = rt.getYear() - 100; // correção de um erro que estava a dar que apresentava o ano do rt como sendo 100 anos mais que o rt verdadeiro

	//se ano e m�s forem iguais
	if ((realano == getYear()) && (rt.getMonth() == getMonth()))
		dias = this->getDay() - rt.getDay();

	//se ano for igual mas mes for diferente
	else if ((realano == getYear()) && (rt.getMonth() != getMonth()))
	{
		if (getMonth() - rt.getMonth() == 1)
		{
			switch (getMonth()) {
			case 1: //Janeiro
				dias = (31 - rt.getDay()) + getDay();
			case 2: //Fevereiro
				if (getYear() % 4 == 0 && getYear() % 10 == 0 && getYear() % 400 == 0)
					dias = (29 - rt.getDay()) + getDay();
				else
					dias = (28 - rt.getDay()) + getDay();
			case 3: //Marco
				dias = (31 - rt.getDay()) + getDay();
			case 4: //Abril
				dias = (30 - rt.getDay()) + getDay();
			case 5: //Maio
				dias = (31 - rt.getDay()) + getDay();
			case 6: //Junho
				dias = (30 - rt.getDay()) + getDay();
			case 7: //Julho
				dias = (31 - rt.getDay()) + getDay();
			case 8: //Agosto
				dias = (31 - rt.getDay()) + getDay();
			case 9: //Setembro
				dias = (30 - rt.getDay()) + getDay();
			case 10: //Outubro
				dias = (31 - rt.getDay()) + getDay();
			case 11: //Novembro (nao ha dezembro ja que, para haver uma diferenca de 1 mes positiva para Dezembro, o ano teria de ser diferente)
				dias = (30 - rt.getDay()) + getDay();
			default:
				dias = -1;
			}
		}
		else
		{
			dias = 50;
			return dias;
		}
	}

	else if (!(realano == getYear()))
	{
		if (getYear() - realano == 1)
		{
			if (rt.getMonth() == 12 && getMonth() == 1)
				dias = (31 - rt.getDay()) + getDay();
			else
				dias = -1;
		}
		else
			dias = 50;
	}
	

	if (dias == 2)
	{
		if (rt.getHours() * 60 + rt.getMinutes() < getHours() * 60 + getMinutes())
		{
			return dias;
		}
		else return 1;
	}
	/*
	return abs(rt.getDay() - this->getDay()) + abs(rt.getMonth - this->getMonth()) * 30 + abs(realano - this->getYear()) * 365;*/
	return dias;
}

string toUpperCase(string input)
{
	for (unsigned int i = 0; i < input.length(); i++)
	{
		if (input[i] >= 'a' && input[i] <= 'z')
			input[i] += 'A' - 'a';
	}
	return input;
}
