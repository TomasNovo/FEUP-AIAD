#include "Line.h"
#include <sstream>

Line::Line() {

}

Line::Line(string textLine){

	istringstream infLine;

	string busStopsStr;			 //string com a lista de paragens
	string timesStr;			 //string com a lista dos tempos entre paragens
	vector<string> stops;	     //vetor com as paragens de uma linha
	vector <unsigned int> times;     	 //vetor com os tempos entre paragens
	string lixo;				 //string para onde vao os ' ' e ';'	

	infLine.str(textLine);

	infLine >> id >> lixo >> freq;
	getline(infLine, lixo, ';');			//retira o ';' a seguir a freq
	getline(infLine, busStopsStr, ';');  	//guarda a string com as paragens
	getline(infLine, timesStr);			   //guarda a string com os tempos


	istringstream stopsList(busStopsStr);
	string stop;

	//ciclo para colocar cada paragem, sem as ',', no vetor
	while (getline(stopsList, stop, ',')) {
		string paragem_org = stop.substr(1, stop.size() - 1); //retira o espaco antes de cada paragem
		stops.push_back(paragem_org);
	}

	busStopList = stops;

	istringstream timesList(timesStr);
	int time;
	string temp;  //string temporaria com o valor do tempo

	//ciclo para colocar cada tempo , sem as ',', no vetor
	while (getline(timesList, temp, ',')) {
		istringstream isstemp(temp);
		isstemp >> time;
		times.push_back(time);
	}

	this->timesList = times;

	int totalLineTime = 0;
	for (size_t i = 0; i < times.size(); i++) {
		totalLineTime += times[i];
		totalLineTime += times[i];
	}

	numberOfBuses = totalLineTime / getFreq();

}

//			METODOS GET
unsigned int Line::getId() const{
  return id;
}
unsigned int Line::getFreq() const {
	return freq;
}
vector<string> Line::getBusStops() const{
  return busStopList;
}
vector<unsigned int> Line::getTimes() const{
  return timesList;
}

unsigned int Line::getNumberOfBuses() const {
	return numberOfBuses;
}

//			METODOS SET
void Line::setId(unsigned int newId) {
	id = newId;
}
void Line::setFreq(unsigned int newFreq) {
	freq = newFreq;
}
void Line::setBusStops(vector<string> newBusStops) {
	busStopList = newBusStops;
}
void Line::setTimesList(vector<unsigned int> newTimesList) {
	timesList = newTimesList;
}

void Line::getNumberOfBuses(unsigned int newNumber) {
	numberOfBuses = newNumber;
}