#include "Line.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <iomanip>
#include <cctype>

Line::Line() {
	id = 0;
	freq = 0;
	vector <string> busStop(0);
	vector <int> times_between_stops(0);
}

Line::Line(int id, int freq, vector<string> paragens, vector <int> times_between_stops) {
	this->id = id;
	this->freq = freq;
	this->busStops = paragens;
	this->times_between_stops = times_between_stops;
	int total = 0;
	for (size_t t = 0; t < times_between_stops.size(); t++) {
		total += times_between_stops.at(t);
	}

	NumberBusNeeded = ((2 * total) / freq) + 1;
}

vector <string> Line::getBusStopsFromString(string busStops) {
	vector<string> paragens;
	while (true) {
		size_t pos = busStops.find_first_of(','); //sempre que ha uma virgula, existe pelo menos uma paragem
		string encontrou;
		if (pos != string::npos)
		{
			encontrou = busStops.substr(0, pos);  //a paragem que estavamos a procura
			paragens.push_back(encontrou);
			busStops = busStops.substr(pos + 2);//removendo a paragem ja guardada no vetor da string original para assim repetir o algoritmo, soma dois para ignorar o caracter ',' e o espaco
		}
		else
		{
			encontrou = busStops.substr(pos + 1, string::npos); //quando nao encontra mais nenhuma virgula e porque chegou a ultima paragem, sendo esta tambem adicionada ao vetor
			paragens.push_back(encontrou);
			break;
		}
	}
	return paragens;
}

vector <int> Line::getTimingsFromString(string Timings) {
	vector<int> lista_horarios;
	istringstream temp;
	temp.str(Timings);
	string lixo; //usada para descartar as virgulas que separam os numeros
	while (temp.good() && !temp.eof()) {
		int n;

		temp >> n >> lixo;
		lista_horarios.push_back(n);
	}
	return lista_horarios;
}

Line::Line(string one_line) {
	istringstream cada_linha(one_line);
	string temp, temp_stops, temp_times;
	string lixo; //para descartar os ';' de cada linha
	cada_linha >> id >> lixo >> freq >> lixo;
	getline(cada_linha, temp);
	size_t pos = temp.find(';');
	if (pos != string::npos) // ; e o que separa as busStop dos seus respetivos intervalos
	{
		temp_stops = temp.substr(1, pos - 1);
		temp_times = temp.substr(pos + 1);
	}
	busStops = getBusStopsFromString(temp_stops);
	times_between_stops = getTimingsFromString(temp_times);
	int total = 0;
	for (size_t t = 0; t < times_between_stops.size(); t++) {
		total += times_between_stops.at(t);
	}
	NumberBusNeeded = ((2 * total) / freq) + 1;
}

void Line::setID(int id) {
	this->id = id;
}
void Line::setFreq(int freq) {
	this->freq = freq;
}
void Line::setBusStops(vector<string> busStops) {
	this->busStops = busStops;
}
void Line::setTimings(vector <int> times_between_stops) {
	this->times_between_stops = times_between_stops;
}

int Line::getID() const {
	return id;
}
int Line::getFreq() const {
	return freq;
}
vector <string> Line::getBusStops() const {
	return busStops;
}
vector <int> Line::getTimings() const{
	return times_between_stops;
}
int Line::getNumberBusNeeded() const {
	return NumberBusNeeded;
}

//display
void Line::showInfo() const {
	cout << "LINHA: " << id << endl;
	cout << '\t' << "Frequencia: " << freq << endl;
	cout << '\t' << "Paragens: ";
	for (size_t posp = 0; posp < busStops.size(); posp++) //posp percorre o vetor de busStop em cada linha
	{
		if (posp == busStops.size() - 1)
			cout << busStops.at(posp) << '.';
		else cout << busStops.at(posp) << ", ";
	}
	cout << endl << '\t' << "Tempo de viagem entre paragens: ";
	for (size_t posh = 0; posh < times_between_stops.size(); posh++)//posh percorre o vetor dos intervalos de tempo entre busStop
	{
		if (posh == times_between_stops.size() - 1)
			cout << times_between_stops.at(posh) << '.';
		else cout << times_between_stops.at(posh) << ", ";
	}
	cout << endl;
	cout << '\t' << "Numero de autocarros necessarios: " << NumberBusNeeded;
	cout << endl;
}