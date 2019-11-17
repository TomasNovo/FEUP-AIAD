#include "data.h"

using namespace std;

data::data()
{}

data::data(unsigned int dia, unsigned int mes, unsigned int ano) : dia(dia), mes(mes), ano(ano)
{}

data::~data()
{}


unsigned int data::getDia() const {
	return this->dia;
}

unsigned int data::getMes() const {
	return this->mes;
}

unsigned int data::getAno() const {
	return this->ano;
}

std::string data::getInfo() const {
	string info;

	info = to_string(dia) + "/" + to_string(mes) + "/" + to_string(ano);

	return info; 
}

void data::setDia(unsigned int dia) {
	this->dia = dia;
}

void data::setMes(unsigned int mes) {
	this->mes = mes;
}

void data::setAno(unsigned int ano) {
	this->ano = ano;
}


bool data::operator==(const data& data1) const {
	return (this->dia  == data1.getDia() && this->mes == data1.getMes() && this->ano == data1.getAno());
}

bool data::operator<(const data& data1) const {
	if (this->ano != data1.getAno())
		return (this->ano < data1.getAno());

	else if (this->mes != data1.getMes())
		return (this->mes < data1.getMes());

	else if (this->dia != data1.getDia())
		return (this->dia < data1.getDia());
}


std::ostream& operator<<(std::ostream& os, const data& data1) {
	return (os << data1.getInfo());
}