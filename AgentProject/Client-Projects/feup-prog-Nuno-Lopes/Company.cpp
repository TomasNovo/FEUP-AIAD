#include "Company.h"
#include<vector>
#include <iostream>
#include <fstream>
#include <ostream>
#include <algorithm>
#include <climits>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>
#include <iomanip>
#include <cctype>

using namespace std;


bool is_number(const string& s);

int convert(const string& s);

string formatingCout(int to_format) {
	string tempostring;
	if (to_format % 60 == 0 && (to_format / 60) >= 24)
		tempostring = "0" + to_string(to_format / 60 - 24) + ":00";
	else if (to_format % 60 == 0 && (to_format / 60) < 24)
		tempostring = to_string(to_format / 60) + ":00";
	else if (to_format % 60 < 10 && (to_format / 60) >= 24)
		tempostring = "0" + to_string(to_format / 60 - 24) + ":0" + to_string(to_format % 60);
	else if (to_format % 60 < 10 && (to_format / 60) < 24)
		tempostring = to_string(to_format / 60) + ":0" + to_string(to_format % 60);
	else if ((to_format / 60) >= 24)
		tempostring = "0" + to_string(to_format / 60 - 24) + ":" + to_string(to_format % 60);
	else
		tempostring = to_string(to_format / 60) + ":" + to_string(to_format % 60);

	return tempostring;
}

bool sortLine(Line line1, Line line2) {
	return (line1.getID() < line2.getID());
}

bool sortDrivers(Driver Driver1, Driver Driver2) {
	return (Driver1.getID() < Driver2.getID());
}

string NumberToDay(int day) {
	switch (day)
	{
	case 0:
		return "Segunda-Feira";
		break;
	case 1:
		return "Terca-Feira";
		break;
	case 2:
		return "Quarta-Feira";
		break;
	case 3:
		return "Quinta-Feira";
		break;
	case 4:
		return "Sexta-Feira";
		break;
	case 5:
		return "Sabado";
		break;
	case 6:
		return "Domingo";
		break;
	default:
		return "invalid";
		break;
	}
}


bool is_file_empty(ifstream& pFile)
{
	return pFile.peek() == ifstream::traits_type::eof();
}

Company::Company()
{
	name = "";
}

Company::Company(string name, string LinesFile, string DriversFile, string ShiftsFile)
{
	ifstream input_linhas;
	input_linhas.open(LinesFile);
	if (input_linhas.fail())
	{
		cerr << LinesFile << " nao encontrado!" << endl;
		system("pause");
		exit(1);
	}
	ifstream input_drivers;
	input_drivers.open(DriversFile);
	if (input_drivers.fail())
	{
		cerr << DriversFile << " nao encontrado!" << endl;
		system("pause");
		exit(1);
	}
	ifstream input_shifts;
	input_shifts.open(ShiftsFile);
	if (input_shifts.fail())
	{
		cerr << ShiftsFile << " nao encontrado!" << endl;
		system("pause");
		exit(1);
	}
	this->name = name;
	this->LinesFile = LinesFile;
	this->DriversFile = DriversFile;
	this->ShiftsFile = ShiftsFile;
	
	CreateVectorDrivers();

	sort(Drivers.begin(), Drivers.end(), sortDrivers);

	CreateVectorLines();

	sort(Lines.begin(), Lines.end(), sortLine);

	CreateVectorAllShifts();

	
	if (input_shifts.peek() != 'E') {
		string shift;
		while (getline(input_shifts,shift)){
			ReadShiftsFromFile(shift);
		}
	}
	

	input_shifts.close();
}

string Company::getName() const {
	return name;
}

string Company::getLinesFile() const {
	return LinesFile;
}

string Company::getDriversFile() const {
	return DriversFile;
}

string Company::getShiftsFile() const {
	return ShiftsFile;
}

//=====================LINES===========




void Company::CreateVectorLines() {
	string line_to_organize;
	ifstream LinesFilestream;
	LinesFilestream.open(LinesFile);
	while (getline(LinesFilestream, line_to_organize))
		Lines.push_back(Line(line_to_organize));
	LinesFilestream.close();
}

void Company::rewriteFileLines(string FileName) {
	ofstream LinesFile;
	LinesFile.open(FileName);
	for (size_t j = 0; j < Lines.size(); j++) {
		LinesFile << Lines.at(j).getID() << " ; " << Lines.at(j).getFreq() << " ; ";
		for (size_t posp = 0; posp < Lines.at(j).getBusStops().size(); posp++) //posp = nr de busStops
		{
			if (posp == Lines.at(j).getBusStops().size() - 1)
				LinesFile << Lines.at(j).getBusStops().at(posp) << "; ";
			else LinesFile << Lines.at(j).getBusStops().at(posp) << ", ";
		}
		for (size_t posh = 0; posh < Lines.at(j).getTimings().size(); posh++)//posh times_between_stops de tempo entre busStops
		{
			if (posh == Lines.at(j).getTimings().size() - 1)
				LinesFile << Lines.at(j).getTimings().at(posh);
			else LinesFile << Lines.at(j).getTimings().at(posh) << ", ";
		}
		if (j != Lines.size() - 1)
			LinesFile << endl;
	}
	LinesFile.close();
}

void Company::showAllLines() const {
	for (size_t pos = 0; pos < Lines.size(); pos++) {
		Lines.at(pos).showInfo();
		cout << endl;
	}
}

void Company::removeLines(int id, ptrdiff_t j) {
	Lines.erase(Lines.begin() + j);
	sort(Lines.begin(), Lines.end(), sortLine);
}

bool Company::existsLines(int id) const {
	vector <int> lines_used_ids;
	for (size_t pos = 0; pos < Lines.size(); pos++) {
		lines_used_ids.push_back(Lines.at(pos).getID());
	}
	if (find(lines_used_ids.begin(), lines_used_ids.end(), id) != lines_used_ids.end())
		return true;
	else
		return false;
}

void Company::insertLines(Line line) {
	Lines.push_back(line);
	sort(Lines.begin(), Lines.end(), sortLine);
}

void Company::newLine(int id, int freq, vector<string> busStops, vector <int> times_between_stops) {
	Line newLine(id, freq, busStops, times_between_stops);
	insertLines(newLine);
}

vector<int> Company::lines_used_ids() {
	vector<int> vetor;
	for (size_t j = 0; j < Lines.size(); j++)
		vetor.push_back(Lines.at(j).getID());

	return vetor;
}

Line& Company::getLinhaById(int id) {
	for (size_t t = 0; t < Lines.size(); t++) {
		if (Lines.at(t).getID() == id)
			return Lines.at(t);
	}
}

vector <int> Company::getLinhaWithStop(string stop) const {
	vector<int> lines_id;
	for (size_t t = 0; t < Lines.size(); t++) {
		vector<string> busStops = Lines.at(t).getBusStops();
		if (find(busStops.begin(), busStops.end(), stop) != busStops.end())
			lines_id.push_back(Lines.at(t).getID());
	}
	return lines_id;
}

vector <int> Company::getLinhaWithBothStops(string Stop1, string Stop2) {
	vector<int> lines_id;
	for (size_t t = 0; t < Lines.size(); t++) {
		vector<string> busStops = Lines.at(t).getBusStops();
		if (find(busStops.begin(), busStops.end(), Stop1) != busStops.end() && find(busStops.begin(), busStops.end(), Stop2) != busStops.end())
			lines_id.push_back(Lines.at(t).getID());
	}
	return lines_id;
}

vector <pair<string, vector<int>>> Company::getTimesLineForward(int id, int minuto_inicial_global, int minuto_final_global) {
	vector <pair<string, vector<int>>> horario;
	Line line_to_analyze = getLinhaById(id);
	int minuto_da_final = minuto_final_global;
	for (size_t t = 0; t < line_to_analyze.getBusStops().size(); t++) {
		if (t == 0) {
			vector<int> minutos_da_paragem;
			int minuto_inicial_paragem = 0;
			minuto_inicial_paragem = minuto_inicial_global;
			while (minuto_inicial_paragem < minuto_final_global) {
				minutos_da_paragem.push_back(minuto_inicial_paragem);
				minuto_inicial_paragem += line_to_analyze.getFreq();
			}
			horario.push_back(make_pair(line_to_analyze.getBusStops().at(t), minutos_da_paragem));
		}
		else {
			vector<int> minutos_da_paragem;
			int minuto_inicial_paragem = 0;
			int minutos_a_somar = 0;
			for (size_t m = 0; m < t; m++)
				minutos_a_somar += line_to_analyze.getTimings().at(m);
			minuto_inicial_paragem = minuto_inicial_global + minutos_a_somar;
			while (minuto_inicial_paragem <= minuto_da_final + minutos_a_somar) {
				minutos_da_paragem.push_back(minuto_inicial_paragem);
				minuto_inicial_paragem += line_to_analyze.getFreq();
			}
			horario.push_back(make_pair(line_to_analyze.getBusStops().at(t), minutos_da_paragem));
		}
	}
	return horario;
}

vector <pair<string, vector<int>>> Company::getTimesLineBackward(int id, int minuto_inicial_global, int minuto_final_global) {

	vector <pair<string, vector<int>>> horario;

	Line line_to_analyze = getLinhaById(id);

	int minutos_a_somar_inicio = 0;

	for (size_t t = 0; t < line_to_analyze.getTimings().size(); t++)
		minutos_a_somar_inicio += line_to_analyze.getTimings().at(t);

	int minuto_inicial_contrario = minuto_inicial_global + minutos_a_somar_inicio;

	int minuto_da_final = minuto_final_global + minutos_a_somar_inicio;

	for (size_t t = line_to_analyze.getBusStops().size() - 1; t > 0; t--) {

		if (t == line_to_analyze.getBusStops().size() - 1) {
			vector<int> minutos_da_paragem;
			int minuto_inicial_paragem = minuto_inicial_contrario;
			while (minuto_inicial_paragem < minuto_da_final) {
				minutos_da_paragem.push_back(minuto_inicial_paragem);
				minuto_inicial_paragem += line_to_analyze.getFreq();
			}
			horario.push_back(make_pair(line_to_analyze.getBusStops().at(t), minutos_da_paragem));
		}

		else {
			vector<int> minutos_da_paragem;
			int minuto_inicial_paragem = 0;

			int minutos_a_somar = 0;
			for (size_t m = t; m < line_to_analyze.getTimings().size(); m++)
				minutos_a_somar += line_to_analyze.getTimings().at(m);

			minuto_inicial_paragem = minuto_inicial_contrario + minutos_a_somar;

			while (minuto_inicial_paragem <= minuto_da_final + minutos_a_somar) {
				minutos_da_paragem.push_back(minuto_inicial_paragem);
				minuto_inicial_paragem += line_to_analyze.getFreq();
			}
			horario.push_back(make_pair(line_to_analyze.getBusStops().at(t), minutos_da_paragem));
		}
	}

	vector<int> minutos_da_paragem;
	int minuto_inicial_paragem = 0;

	int minutos_a_somar = 0;
	for (size_t m = 0; m < line_to_analyze.getTimings().size(); m++)
		minutos_a_somar += line_to_analyze.getTimings().at(m);

	minuto_inicial_paragem = minuto_inicial_contrario + minutos_a_somar;

	while (minuto_inicial_paragem <= minuto_da_final + minutos_a_somar) {
		minutos_da_paragem.push_back(minuto_inicial_paragem);
		minuto_inicial_paragem += line_to_analyze.getFreq();
	}
	horario.push_back(make_pair(line_to_analyze.getBusStops().at(0), minutos_da_paragem));

	return horario;
}

vector <pair <int, vector <int>>> Company::getTimesStopForward(string Stop, int minuto_inicial_global, int minuto_final_global) {
	vector <int> lines_with_stop = getLinhaWithStop(Stop);

	vector <pair <int, vector<int>>> horario_da_linha;

	for (size_t t = 0; t < lines_with_stop.size(); t++) {

		Line line_to_analyze = getLinhaById(lines_with_stop.at(t));
		int minuto_da_final = minuto_final_global;
		for (size_t k = 0; k < line_to_analyze.getBusStops().size(); k++) {
			if (line_to_analyze.getBusStops().at(k) == Stop) {
				if (k == 0) {
					vector<int> minutos_da_paragem;
					int minuto_inicial_paragem = 0;
					minuto_inicial_paragem = minuto_inicial_global;
					while (minuto_inicial_paragem < minuto_final_global) {
						minutos_da_paragem.push_back(minuto_inicial_paragem);
						minuto_inicial_paragem += line_to_analyze.getFreq();
					}
					horario_da_linha.push_back(make_pair(lines_with_stop.at(t), minutos_da_paragem));
				}
				else {
					vector<int> minutos_da_paragem;
					int minuto_inicial_paragem = 0;
					int minutos_a_somar = 0;
					for (size_t m = 0; m < k; m++)
						minutos_a_somar += line_to_analyze.getTimings().at(m);
					minuto_inicial_paragem = minuto_inicial_global + minutos_a_somar;
					while (minuto_inicial_paragem < minuto_da_final + minutos_a_somar) {
						minutos_da_paragem.push_back(minuto_inicial_paragem);
						minuto_inicial_paragem += line_to_analyze.getFreq();
					}
					horario_da_linha.push_back(make_pair(lines_with_stop.at(t), minutos_da_paragem));
				}
			}
		}
	}
	return horario_da_linha;
}

vector <pair<int, vector<int>>> Company::getTimesStopBackward(string Stop, int minuto_inicial_global, int minuto_final_global) {

	vector <int> lines_with_stop = getLinhaWithStop(Stop);

	vector <pair <int, vector<int>>> horario_da_linha;


	for (size_t t = 0; t < lines_with_stop.size(); t++) {

		Line line_to_analyze = getLinhaById(lines_with_stop.at(t));

		int minutos_a_somar_inicio = 0;

		for (size_t i = 0; i < line_to_analyze.getTimings().size(); i++)
			minutos_a_somar_inicio += line_to_analyze.getTimings().at(i);

		int minuto_inicial_contrario = minuto_inicial_global + minutos_a_somar_inicio;

		int minuto_da_final = minuto_final_global + minutos_a_somar_inicio;

		for (int q = line_to_analyze.getBusStops().size() - 1; q >= 0; q--) {
			if (line_to_analyze.getBusStops().at(q) == Stop) {
				if (q == line_to_analyze.getBusStops().size() - 1) {
					vector<int> minutos_da_paragem;
					int minuto_inicial_paragem = minuto_inicial_contrario;
					while (minuto_inicial_paragem < minuto_da_final) {
						minutos_da_paragem.push_back(minuto_inicial_paragem);
						minuto_inicial_paragem += line_to_analyze.getFreq();
					}
					horario_da_linha.push_back(make_pair(lines_with_stop.at(t), minutos_da_paragem));
				}

				else
				{
					vector<int> minutos_da_paragem;
					int minuto_inicial_paragem = 0;

					int minutos_a_somar = 0;
					for (size_t m = q; m < line_to_analyze.getTimings().size(); m++)
						minutos_a_somar += line_to_analyze.getTimings().at(m);

					minuto_inicial_paragem = minuto_inicial_contrario + minutos_a_somar;

					while (minuto_inicial_paragem < minuto_da_final + minutos_a_somar) {
						minutos_da_paragem.push_back(minuto_inicial_paragem);
						minuto_inicial_paragem += line_to_analyze.getFreq();
					}
					horario_da_linha.push_back(make_pair(lines_with_stop.at(t), minutos_da_paragem));
				}

			}

		}
	}
	return horario_da_linha;
}

vector <pair <int, int>> Company::getTimeBetweenStops(string Stop1, string Stop2) {
	vector <int> lines_with_both = getLinhaWithBothStops(Stop1, Stop2);
	vector <pair <int, int>> final_vec;
	int Stop1_index, Stop2_index;

	if (lines_with_both.empty()) {
		return final_vec;
	}
	else {
		for (size_t i = 0; i < lines_with_both.size(); i++) {

			for (size_t j = 0; j < getLinhaById(lines_with_both.at(i)).getBusStops().size(); j++) {
				if (getLinhaById(lines_with_both.at(i)).getBusStops().at(j) == Stop1)
					Stop1_index = j;
				if (getLinhaById(lines_with_both.at(i)).getBusStops().at(j) == Stop2)
					Stop2_index = j;
			}
			int time_spent_in_minutes = 0;
			if (Stop1_index < Stop2_index) {
				for (Stop1_index; Stop1_index < Stop2_index; Stop1_index++) {
					time_spent_in_minutes += getLinhaById(lines_with_both.at(i)).getTimings().at(Stop1_index);
				}
				final_vec.push_back(make_pair(lines_with_both.at(i), time_spent_in_minutes));
			}
			else {
				for (Stop1_index; Stop1_index > Stop2_index; Stop1_index--) {
					time_spent_in_minutes += getLinhaById(lines_with_both.at(i)).getTimings().at(Stop1_index - 1);
				}
				final_vec.push_back(make_pair(lines_with_both.at(i), time_spent_in_minutes));
			}
		}
		return final_vec;
	}
}

vector <pair <int, vector <string>>> Company::getPathBetweenStops(string Stop1, string Stop2) {
	vector <int> lines_with_both = getLinhaWithBothStops(Stop1, Stop2);


	vector <pair <int, vector <string>>> final_vec;

	int Stop1_index, Stop2_index;

	for (size_t i = 0; i < lines_with_both.size(); i++) {
		vector <string> path;
		for (size_t j = 0; j < getLinhaById(lines_with_both.at(i)).getBusStops().size(); j++) {
			if (getLinhaById(lines_with_both.at(i)).getBusStops().at(j) == Stop1)
				Stop1_index = j;
			if (getLinhaById(lines_with_both.at(i)).getBusStops().at(j) == Stop2)
				Stop2_index = j;
		}
		string Stop;
		if (Stop1_index < Stop2_index) {
			for (Stop1_index; Stop1_index < Stop2_index; Stop1_index++) {
				Stop = getLinhaById(lines_with_both.at(i)).getBusStops().at(Stop1_index);
				path.push_back(Stop);
			}
		}
		else {
			for (Stop1_index; Stop1_index > Stop2_index; Stop1_index--) {
				Stop = getLinhaById(lines_with_both.at(i)).getBusStops().at(Stop1_index);
				path.push_back(Stop);
			}
		}
		final_vec.push_back(make_pair(lines_with_both.at(i), path));
	}
	return final_vec;
}

//=======================DRIVERS======================


void Company::CreateVectorDrivers()
{
	string FileName = getDriversFile();
	string driver_to_organize;
	ifstream DriversFile;
	DriversFile.open(FileName);
	while (getline(DriversFile, driver_to_organize)) {
		Drivers.push_back(Driver(driver_to_organize));
	}
	DriversFile.close();
}

void Company::rewriteFileDrivers(string FileName) {
	ofstream input_condutor;
	input_condutor.open(FileName);
	for (size_t j = 0; j < Drivers.size(); j++) {
		input_condutor << Drivers.at(j).getID() << " ; " << Drivers.at(j).getName() << " ; " << Drivers.at(j).getMaxHours() / 60 << " ; " << Drivers.at(j).getMaxWeekWorkingTimeConst() << " ; " << Drivers.at(j).getMinRestTime() / 60;
		if (j != Drivers.size() - 1)
			input_condutor << endl;
	}
}

void Company::showAllDrivers() const
{
	for (size_t pos = 0; pos < Drivers.size(); pos++) {
		Drivers.at(pos).showInfo();
		cout << endl;
	}
}

void Company::insertDrivers(Driver one_driver) {
	Drivers.push_back(one_driver);
	sort(Drivers.begin(), Drivers.end(), sortDrivers);
}

bool Company::existsDrivers(int id) const {
	vector <int> drivers_used_ids;
	for (size_t pos = 0; pos < Drivers.size(); pos++) {
		drivers_used_ids.push_back(Drivers.at(pos).getID());
	}

	if (find(drivers_used_ids.begin(), drivers_used_ids.end(), id) != drivers_used_ids.end())
		return true;
	else
		return false;
}

void Company::removeDrivers(int id, ptrdiff_t j) {
	Drivers.erase(Drivers.begin() + j);
	sort(Drivers.begin(), Drivers.end(), sortDrivers);
}

vector<int> Company::drivers_used_ids() {
	vector<int> vetor;
	for (size_t j = 0; j < Drivers.size(); j++)
		vetor.push_back(Drivers.at(j).getID());

	return vetor;
}

void Company::newCondutor(int id, string name, int maxDayWorkingTime, int maxWeekWorkingTime, int minRestTime) {
	Driver newDriver(id, name, maxDayWorkingTime, maxWeekWorkingTime, minRestTime);
	insertDrivers(newDriver);
}

Driver& Company::getDriverById(int id) {
	for (size_t t = 0; t < Drivers.size(); t++)
		if (Drivers.at(t).getID() == id)
			return Drivers.at(t);
}

Driver& Company::getDriverByName(string name) {
	for (size_t t = 0; t < Drivers.size(); t++)
		if (Drivers.at(t).getName() == name)
			return Drivers.at(t);
}

bool Company::addNewShiftToDriver(int day, int id, int line, int startTime) {
	bool ShiftExists = false;
	size_t t = 0;
	vector <Shift *> line_shifts = Pointers_To_Line_Shifts(line, day);

	for (t; t < line_shifts.size(); t++)
	{
		if ((*line_shifts.at(t)).getStartTime() == startTime && (*line_shifts.at(t)).getInUse() == false) {
			ShiftExists = true;
			break;
		}

	}

	if (!ShiftExists) {
		cout << "\nO turno nao existe ou ja esta atribuido.\n";
		return false;
	}
	else {
		if ((*line_shifts.at(t)).getDuration() > getDriverById(id).getMaxWeekWorkingTime()) {
			cout << "\nO condutor nao tem horas semanais restantes para fazer o turno.\n";
			return false;
		}
		else if ((*line_shifts.at(t)).getDuration() > getDriverById(id).getMaxHours()) {
			cout << "\nO condutor nao tem horas diarias restantes para fazer o turno.\n";
			return false;
		}
	}
	
	cout << "\nPretende que o Condutor acabe o turno quando: " << endl;
	int visu = 0;
	size_t s = t;
	vector <int> EndTimes;
	for (size_t temp = t; temp < line_shifts.size(); temp++) {
		if ((*line_shifts.at(t)).getBusOrderNumber() == (*line_shifts.at(temp)).getBusOrderNumber()) {
			if ((*line_shifts.at(temp)).getInUse() == false) {
				if (((*line_shifts.at(temp)).getEndTime() - (*line_shifts.at(t)).getStartTime()) <= getDriverById(id).getMaxHours()) {
					cout << "  " << ++visu << " - " << formatingCout((*line_shifts.at(temp)).getEndTime()) << endl;
					EndTimes.push_back((*line_shifts.at(temp)).getEndTime());
					++s;
				}

			}
		}
	}
	int opcao = 0;
	bool opcao_good = false;
	string opcaostr;
	while (!opcao_good)
	{
		cout << "\nInsira uma opcao: ";
		getline(cin, opcaostr);
		if (!is_number(opcaostr)) {
			cout << "Por favor, insira uma opcao valida. " << endl;
		}
		else if (convert(opcaostr) < 0 || convert(opcaostr) > visu)
			cout << "Por favor, insira uma opcao valida. " << endl;
		else {
			opcao = convert(opcaostr);
			opcao_good = true;
		}
	}

	opcao = opcao - 1;
	


	if (getDriverById(id).getShifts(day).empty())
	{
		vector <Shift *> ShiftsToDriverWork;
		for (size_t m = t; m < line_shifts.size(); m++) {
			if ((*line_shifts.at(t)).getBusOrderNumber() == (*line_shifts.at(m)).getBusOrderNumber()) {
				if ((*line_shifts.at(m)).getInUse() == false) {
					if (((*line_shifts.at(m)).getEndTime() - (*line_shifts.at(t)).getStartTime()) <= getDriverById(id).getMaxHours()) {
						if ((*line_shifts.at(m)).getEndTime() <= EndTimes.at(opcao)) {
							(*line_shifts.at(m)).setInUse(true);
							(*line_shifts.at(m)).setDriverId(getDriverById(id).getID());
							ShiftsToDriverWork.push_back(line_shifts.at(m));
						}
					}
				}
			}
		}
		getDriverById(id).setMaxWeekWorkingTime(getDriverById(id).getMaxWeekWorkingTime() - ((*ShiftsToDriverWork.at(ShiftsToDriverWork.size()-1)).getEndTime() - (*line_shifts.at(t)).getStartTime()));
		DriverWork toAdd((*line_shifts.at(t)).getStartTime(), (*ShiftsToDriverWork.at(ShiftsToDriverWork.size() - 1)).getEndTime(), ShiftsToDriverWork, line, (*line_shifts.at(t)).getBusOrderNumber());
		getDriverById(id).addShift(make_pair(day, toAdd));
		rewriteFileShifts(ShiftsFile);
		return true;
	}
	else
	{
		for (size_t k = 0; k < getDriverById(id).getEndTimes(day).size(); k++) {
			if ((*line_shifts.at(t)).getStartTime() < getDriverById(id).getEndTimes(day).at(k) && (*line_shifts.at(t)).getStartTime() > getDriverById(id).getStartTimes(day).at(k)) {
				cout << "\nO Condutor ainda nao acabou um turno previo" << endl;
				return false;
			}

			else if (EndTimes.at(opcao) < getDriverById(id).getEndTimes(day).at(k) && EndTimes.at(opcao) > getDriverById(id).getStartTimes(day).at(k)) {
				cout << "\nO Condutor ainda nao acabou um turno previo" << endl;
				return false;
			}

			else if ((*line_shifts.at(t)).getStartTime() < getDriverById(id).getStartTimes(day).at(k) && EndTimes.at(opcao) > getDriverById(id).getStartTimes(day).at(k)) {
				cout << "\nO Condutor ainda nao acabou um turno previo" << endl;
				return false;
			}
		}
		for (size_t k = 0; k < getDriverById(id).getEndTimes(day).size(); k++) {
			if (EndTimes.at(opcao) < getDriverById(id).getStartTimes(day).at(k)) {
				if (getDriverById(id).getStartTimes(day).at(k) - EndTimes.at(opcao) < getDriverById(id).getMinRestTime()) {
					cout << "\nO Condutor ainda esta em tempo de descanso" << endl;
					return false;
				}
			}

			else if ((*line_shifts.at(t)).getStartTime() > getDriverById(id).getEndTimes(day).at(k)) {
				if ((*line_shifts.at(t)).getStartTime() - getDriverById(id).getEndTimes(day).at(k) < getDriverById(id).getMinRestTime()) {
					cout << "\nO Condutor ainda esta em tempo de descanso" << endl;
					return false;
				}
			}
		}



		vector <Shift *> ShiftsToDriverWork;
		for (size_t m = t; m < line_shifts.size(); m++) {
			if ((*line_shifts.at(t)).getBusOrderNumber() == (*line_shifts.at(m)).getBusOrderNumber()) {
				if ((*line_shifts.at(m)).getInUse() == false) {
					if (((*line_shifts.at(m)).getEndTime() - (*line_shifts.at(t)).getStartTime()) <= getDriverById(id).getMaxHours()) {
						if ((*line_shifts.at(m)).getEndTime() <= EndTimes.at(opcao)) {
							(*line_shifts.at(m)).setInUse(true);
							(*line_shifts.at(m)).setDriverId(getDriverById(id).getID());
							ShiftsToDriverWork.push_back(line_shifts.at(m));
						}
					}
				}
			}
		}
		getDriverById(id).setMaxWeekWorkingTime(getDriverById(id).getMaxWeekWorkingTime() - ((*ShiftsToDriverWork.at(ShiftsToDriverWork.size() - 1)).getEndTime() - (*line_shifts.at(t)).getStartTime()));
		DriverWork toAdd((*line_shifts.at(t)).getStartTime(), (*ShiftsToDriverWork.at(ShiftsToDriverWork.size() - 1)).getEndTime(), ShiftsToDriverWork, line, (*line_shifts.at(t)).getBusOrderNumber());
		getDriverById(id).addShift(make_pair(day, toAdd));
		rewriteFileShifts(ShiftsFile);
		return true;
	}
}

bool Company::removeWorkFromDriver(int day, int id, int line, int startTime) {
	if (getDriverById(id).getDayWork(day).empty())
		return false;
	else {
		for (size_t t = 0; t < getDriverById(id).getDayWork(day).size(); t++) {
			if (getDriverById(id).getDayWork(day).at(t).getStartTime() == startTime && getDriverById(id).getDayWork(day).at(t).getLine() == line) {
			
				for (size_t k = 0; k < getDriverById(id).getDayWork(day).at(t).getWorkShifts().size(); k++) {
			
					(*getDriverById(id).getDayWork(day).at(t).getWorkShifts().at(k)).setInUse(false);
					(*getDriverById(id).getDayWork(day).at(t).getWorkShifts().at(k)).setDriverId(INT_MAX); //just a safety precaution
					
				}
				getDriverById(id).removeShift(make_pair(day, getDriverById(id).getDayWork(day).at(t)));
				rewriteFileShifts(ShiftsFile);
				return true;
			}
		}
		return false;
	}
}

vector <Driver *> Company::getDriversWithSpareTime() {
	vector <Driver *> Spare;
	for (size_t t = 0; t < Drivers.size(); t++) {
		if (Drivers.at(t).getMaxWeekWorkingTime() != 0)
			Spare.push_back(&Drivers.at(t));
	}
	return Spare;
}




//===================SHIFTS=============

void Company::CreateVectorAllShifts() {
	vector<int> lines_ids = lines_used_ids();
	for (int m = 0; m <= 7; m++) {
		vector<Shift> Temp_Shift;
		for (size_t t = 0; t < lines_ids.size(); t++) {
			//each line shift begins in the first stop of that line and ends there too
			int first_line_id = lines_ids.at(t);
			Line & line_to_analyze = getLinhaById(first_line_id);
			int repeat = 0;

			vector <pair <int, vector <int>>> Forward = getTimesStopForward(line_to_analyze.getBusStops().at(0), MINUTO_INICIAL, MINUTO_FINAL);   //getting the initial times in the initial stop (forward way)
			vector <pair <int, vector <int>>> Backward = getTimesStopBackward(line_to_analyze.getBusStops().at(0), MINUTO_INICIAL, MINUTO_FINAL);  //getting the end times in the initial stop    (backward way)
			for (size_t k = 0; k < Forward.size(); k++) {   //since both vectors have the same size....
				for (size_t l = 0; l < Forward.at(k).second.size(); l++) {  //going through all the different table times
					int startTime = Forward.at(k).second.at(l);
					int endTime = Backward.at(k).second.at(l);
					int busLineId = Forward.at(k).first;
					Temp_Shift.push_back(Shift(busLineId, startTime, endTime, repeat++ % line_to_analyze.getNumberBusNeeded() + 1));
				}
			}

		}
		All_Shifts.push_back(make_pair(m, Temp_Shift));
	}
}

Shift * Company::getShift(int day, int line, int startTime) {
	for (size_t t = 0; t < All_Shifts.at(day).second.size(); t++) {
		if (All_Shifts.at(day).second.at(t).getBusLineId() == line) {
			if (All_Shifts.at(day).second.at(t).getStartTime() == startTime)
				return &All_Shifts.at(day).second.at(t);
		}
	}
}

void Company::displayAllShifts() {
	for (size_t k = 0; k < lines_used_ids().size(); k++) {
		cout << "Turnos na linha " << lines_used_ids().at(k) << ": \n";
		for (size_t t = 0; t < All_Shifts.at(0).second.size(); t++) {
			{
				if (All_Shifts.at(0).second.at(t).getBusLineId() == lines_used_ids().at(k)) {
					cout << "Das " << setw(5) << formatingCout(All_Shifts.at(7).second.at(t).getStartTime()) << " ";
					cout << "as " << setw(5) << formatingCout(All_Shifts.at(7).second.at(t).getEndTime());
					cout << " no autocarro " << All_Shifts.at(7).second.at(t).getBusOrderNumber() << ". \n";
				}
			}
		}
		cout << "\n\n";
	}
	
}

vector<Shift> Company::Shifts_of_a_Line(int id) {

	vector <Shift> Line_Shifts;
	if (existsLines(id)) {
		Line & line_to_analyze = getLinhaById(id);
		int repeat = 0;
		vector <pair <int, vector <int>>> Forward = getTimesStopForward(line_to_analyze.getBusStops().at(0), MINUTO_INICIAL, MINUTO_FINAL);
		vector <pair <int, vector <int>>> Backward = getTimesStopBackward(line_to_analyze.getBusStops().at(0), MINUTO_INICIAL, MINUTO_FINAL);
		for (size_t k = 0; k < Forward.size(); k++) {   //dado que ambos os vetores têm o mesmo tamanho
			for (size_t l = 0; l < Forward.at(k).second.size(); l++) {  //percorrendo todos os tempos
				int startTime = Forward.at(k).second.at(l);
				int endTime = Backward.at(k).second.at(l);
				int busLineId = Forward.at(k).first;
				Line_Shifts.push_back(Shift(busLineId, startTime, endTime, repeat++ % line_to_analyze.getNumberBusNeeded() + 1));
			}
		}
	}
	return Line_Shifts;

}

vector <Shift *> Company::Pointers_To_Line_Shifts(int id, int day) {
	vector <Shift *> pointers;
	for (size_t t = 0; t < All_Shifts.at(day).second.size(); t++) {
		if (All_Shifts.at(day).second.at(t).getBusLineId() == id)
			pointers.push_back(&All_Shifts.at(day).second.at(t));
	}

	return pointers;
}

vector <pair <int, vector <Shift>>> Company::All_Shifts_inUse() {
	vector <pair <int, vector <Shift>>> Shifts_inUse;
	for (size_t t = 0; t < All_Shifts.size(); t++) {
		vector <Shift> Temp;
		for (size_t k = 0; k < All_Shifts.at(t).second.size(); k++) {
			if (All_Shifts.at(t).second.at(k).getInUse() == true)
				Temp.push_back(All_Shifts.at(t).second.at(k));
		}
		if (!Temp.empty())
			Shifts_inUse.push_back(make_pair(t, Temp));
	}

	return Shifts_inUse;
}


void Company::ReadShiftsFromFile(string one_shift) {
	unsigned int LineID;
	unsigned int Driver_ID;
	unsigned int ShiftStartTime;
	unsigned int ShiftEndTime;
	int day;
	istringstream each_shift(one_shift);
	string lixo; //para descartar os ';' de cada linha
	each_shift >> day >> lixo >> Driver_ID >> lixo >> LineID >> lixo >> ShiftStartTime >> lixo >> ShiftEndTime;


	size_t t = 0;
	vector <Shift *> line_shifts = Pointers_To_Line_Shifts(LineID, day);

	for (t; t < line_shifts.size(); t++)
	{
		if ((*line_shifts.at(t)).getStartTime() == ShiftStartTime && (*line_shifts.at(t)).getInUse() == false) {
			break;
		}

	}

	vector <Shift *> ShiftsToDriverWork;
	for (size_t m = t; m < line_shifts.size(); m++) {
		if ((*line_shifts.at(t)).getBusOrderNumber() == (*line_shifts.at(m)).getBusOrderNumber()) {
			if ((*line_shifts.at(m)).getInUse() == false) {
				if (((*line_shifts.at(m)).getEndTime() - (*line_shifts.at(t)).getStartTime()) <= getDriverById(Driver_ID).getMaxHours()) {
					if ((*line_shifts.at(m)).getEndTime() <= ShiftEndTime) {
						(*line_shifts.at(m)).setInUse(true);
						(*line_shifts.at(m)).setDriverId(getDriverById(Driver_ID).getID());
						ShiftsToDriverWork.push_back(line_shifts.at(m));
					}
				}
			}
		}
	}

	getDriverById(Driver_ID).setMaxWeekWorkingTime(getDriverById(Driver_ID).getMaxWeekWorkingTime() - ((*ShiftsToDriverWork.at(ShiftsToDriverWork.size() - 1)).getEndTime() - (*line_shifts.at(t)).getStartTime()));
	DriverWork toAdd((*line_shifts.at(t)).getStartTime(), (*ShiftsToDriverWork.at(ShiftsToDriverWork.size() - 1)).getEndTime(), ShiftsToDriverWork, LineID, (*line_shifts.at(t)).getBusOrderNumber());
	getDriverById(Driver_ID).addShift(make_pair(day, toAdd));
}

void Company::rewriteFileShifts(string FileName) {
	ofstream output_shifts;
	output_shifts.open(FileName);

	vector <int> DriverIDs = drivers_used_ids();

	for (size_t d = 0; d < DriverIDs.size(); d++) {
		vector <pair <int, vector <DriverWork>>> Shifts_in_Use = getDriverById(DriverIDs.at(d)).getAllDriverShifts();
		for (size_t t = 0; t < Shifts_in_Use.size(); t++) {
			for (size_t k = 0; k < Shifts_in_Use.at(t).second.size(); k++) {
				output_shifts << Shifts_in_Use.at(t).first << " ; " << DriverIDs.at(d) << " ; " << Shifts_in_Use.at(t).second.at(k).getLine() << " ; " << Shifts_in_Use.at(t).second.at(k).getStartTime() << " ; " << Shifts_in_Use.at(t).second.at(k).getEndTime() << endl;
				if (t != (Shifts_in_Use.size() - 1) || k != (Shifts_in_Use.at(t).second.size() - 1))
					output_shifts << endl;

			}
		}
	}
}

vector <Shift * > Company::Line_Shifts_Use(int id, int day){
	vector <Shift *> pointers;
	for (size_t t = 0; t < All_Shifts.at(day).second.size(); t++) {
		if (All_Shifts.at(day).second.at(t).getBusLineId() == id && All_Shifts.at(day).second.at(t).getInUse() == true)
			pointers.push_back(&All_Shifts.at(day).second.at(t));
	}

	return pointers;
}

vector < pair < int, vector <int> > > Company::BusWithoutDriver(int day) {
	vector <int> UsedLines = lines_used_ids();

	vector < pair <int, vector < int> > > toReturn; 

	for (size_t t = 0; t < UsedLines.size(); t++) {
		vector <Shift*> UseShifts = Line_Shifts_Use(UsedLines.at(t), day);
		vector <int> noUseBus;
		for (int m = 1; m <= getLinhaById(UsedLines.at(t)).getNumberBusNeeded(); m++) {
			noUseBus.push_back(m);
		}
		for (size_t k = 0; k < UseShifts.size(); k++) {
				noUseBus.erase(remove(noUseBus.begin(), noUseBus.end(), (*UseShifts.at(k)).getBusOrderNumber()), noUseBus.end());
		}
		toReturn.push_back(make_pair(UsedLines.at(t), noUseBus));
	}
	return toReturn;
}
