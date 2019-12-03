#include "Driver.h"
#include <sstream>

Driver::Driver() {

}

Driver::Driver(string textLine){

	istringstream infDriver(textLine);
	string tempName;			//string com o nome do condutor
	string lixo;			//string para onde vao os ' ' e ';'

	infDriver >> id;		//guarda o id
	getline(infDriver, lixo, ';');	//remove o " ;"
	getline(infDriver, tempName, ';');	//guarda o nome
	infDriver >> maxHours >> lixo >> maxWeekWorkingTime >> lixo >> minRestTime;	//guarda a info relativa as horas

	name = tempName.substr(1, tempName.size() - 2); //retira o ' ' inicial e final do 
}

//////////////
// get methods
//////////////

unsigned int Driver::getId() const{
  return id;
}

string Driver::getName() const{
  return name;
}

unsigned int Driver::getShiftMaxDuration() const{
  return maxHours;
}

unsigned int Driver::getMaxWeekWorkingTime() const{
  return maxWeekWorkingTime;
}

unsigned int Driver::getMinRestTime() const{
  return minRestTime;
}

vector<Shift> Driver::getShifts() const{
  return shifts;
}

//set methods

void Driver::setId(unsigned int newId){
	id = newId;
}
void Driver::setName(string newName){
	name = newName;
}
void Driver::setShiftMaxDuration(unsigned int newShiftMaxDuration) {
	maxHours = newShiftMaxDuration;
}
void Driver::setMaxWeekWorkingTime(unsigned int newMaxWeekWorkingTime) {
	maxWeekWorkingTime = newMaxWeekWorkingTime;
}
void Driver::setMinRestTime(unsigned int newMinRestTime) {
	minRestTime = newMinRestTime;
}