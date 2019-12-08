#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Line.h"
#include "Driver.h"
#include "Header.h"


using namespace std;

class Company {
private:
	vector<Driver> drivers;
	vector<Line> lines;
	string fileDrivers;
	string fileLines;

public:
	Company(string fileDrivers, string fileLines);

	//			METODOS GET
	vector<Driver> getDrivers() const;
	vector<Line> getLines() const;
	string getFileDrivers() const;
	string getFileLines() const;
	int getDriverIndice(unsigned int id) const;
	int getLineIndice(unsigned int id) const;

	//			METODOS SET
	void setDrivers(vector<Driver> newDrivers);
	void setLines(vector<Line> newLines);

	// 
	//			   OUTROS
	//
	void saveFiles() const;
	void distribuiServico(); // funcao que implementa a afectacao de servico
	//			METODOS DRIVER
	void addDriver(Company &c);
	void removeDriver(Company &c);
	void changeDriver(Company &c);
	void changeDriverName(int indice, Company &c);
	void changeDriverMaxHours(int indice, Company &c);
	void changeDriverMaxWeekWorkingTime(int indice, Company &c);
	void changeDriverMinRestTime(int indice, Company &c);
	void showDrivers(Company &c);
	void sortDrivers();

	//			METODOS LINE
	void addLine(Company &c);
	void removeLine(Company &c);
	void changeLine(Company &c);
	void changeLineFreq(int indice, Company &c);
	void changeLineStops(int indice, Company &c);
	void changeLineTimes(int indice, Company &c);
	int totalLineStops(int indice) const;
	void showLines(Company &c);
	void sortLines();
};