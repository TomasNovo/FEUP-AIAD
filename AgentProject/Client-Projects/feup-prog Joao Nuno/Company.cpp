#include "Company.h"
#include <algorithm>
#include <fstream>

string organizarString(string s);
void end(Company &c);
void addStop(int i, Company &c);
void removeStop(int i, Company &c);
void changeStop(int i, Company &c);

Company::Company(string fileDrivers, string fileLines){

	this->fileDrivers = fileDrivers;
	this->fileLines = fileLines;
	ifstream fLines;	
	fLines.open(fileLines);

	vector <Line> lines; 
	string info;
	//ciclo para ler e organizar a informacao de cada linha do ficheiro
	while (getline(fLines, info)) {
		Line line(info);
		lines.push_back(line);
	}
	this->lines = lines;
	fLines.close();

	ifstream fDrivers;
	fDrivers.open(fileDrivers);

	vector <Driver> drivers;
	//ciclo para ler e organizar a informacao de cada condutor do ficheiro
	while (getline(fDrivers, info)) {
		Driver driver(info);
		drivers.push_back(driver);
	}
	this->drivers = drivers;
	fDrivers.close();
}

//			METODOS GET
vector<Driver> Company::getDrivers() const{
	return drivers;
}
vector<Line> Company::getLines() const{
	return lines;
}
string Company::getFileDrivers() const {
	return fileDrivers;
}
string Company::getFileLines() const {
	return fileLines;
}
int Company::getDriverIndice(unsigned int id) const{
	vector<Driver> drivers = getDrivers();
	int indice = -1;

	for (size_t i = 0; i < drivers.size(); i++) {
		if (drivers[i].getId() == id) {
			indice = i;
			break;
		}
	}
	return indice;
}
int Company::getLineIndice(unsigned int id) const {
	vector<Line> lines = getLines();
	int indice = -1;

	for (size_t i = 0; i < lines.size(); i++) {
		if (lines[i].getId() == id) {
			indice = i;
			break;
		}
	}
	return indice;
}

//			METODOS SET
void Company::setDrivers(vector<Driver> newDrivers) {
	drivers = newDrivers;
}
void Company::setLines(vector<Line> newLines) {
	lines = newLines;
}

//				OUTROS
void Company::distribuiServico(){
}

void Company::saveFiles() const {

	ofstream fLines;
	fLines.open(getFileLines());	//ficheiro onde guarda a informacao

	vector<Line> lines = getLines();

									
	for (size_t i = 0; i < lines.size(); i++) {
		fLines << lines[i].getId() << " ; " << lines[i].getFreq() << " ; ";
		//loop para as paragens
		vector<string> busStops = lines[i].getBusStops();
		for (size_t j = 0; j < busStops.size(); j++) {
			if (j == busStops.size() - 1)
				fLines << busStops[j] << "; ";
			else
				fLines << busStops[j] << ", ";
		}
		//loop para os tempos entre viagens
		vector<unsigned int> timesList = lines[i].getTimes();
		for (size_t k = 0; k < timesList.size(); k++) {

			// se for o ultimo elemento nao faz newl no fim
			if (i == lines.size() - 1) {
				if (k == timesList.size() - 1)
					fLines << timesList[k];
				else
					fLines << timesList[k] << ", ";
			}
			else {
				if (k == timesList.size() - 1)
					fLines << timesList[k] << endl;
				else
					fLines << timesList[k] << ", ";
			}
		}
	}
	fLines.close();

	ofstream fDrivers;
	fDrivers.open(getFileDrivers());	//ficheiro onde guarda a informacao

	//loop para cada elemento do vetor
	vector<Driver> drivers = getDrivers();
	for (size_t i = 0; i < drivers.size(); i++) {
		if (i == drivers.size() - 1)
			fDrivers << drivers[i].getId() << " ; " << drivers[i].getName() << " ; " << drivers[i].getShiftMaxDuration() << " ; " << drivers[i].getMaxWeekWorkingTime() << " ; " << drivers[i].getMinRestTime();
		else
			fDrivers << drivers[i].getId() << " ; " << drivers[i].getName() << " ; " << drivers[i].getShiftMaxDuration() << " ; " << drivers[i].getMaxWeekWorkingTime() << " ; " << drivers[i].getMinRestTime() << endl;
	}
	fDrivers.close();
}

void Company::addDriver(Company &c) {
	clearScreen();

	Driver newdriver;
	vector<Driver> drivers = c.getDrivers();

	cout << "+-------------------------------+\n";
	cout << "| Adicionar Condutor            |\n";
	cout << "+-------------------------------+\n";

	unsigned int id;			//id do novo condutor
	string name;	//nome do novo condutor
	unsigned int times = 0;	//horas relativas ao novo condutor

	while (true) {
		cout << "Numero Identificador: "; cin >> id;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		else
			break;
	}
	//verifica se o id introduzido ja existe no vetor global
	for (size_t i = 0; i < drivers.size(); i++) {
		if (id == drivers[i].getId()) {
			cout << "\nO condutor " << id << " ja existe!...\n";
			system("pause");
			return;
		}
	}
	newdriver.setId(id);

	//nome
	cin.ignore(1, '\n');
	cout << "Nome: "; getline(cin, name, '\n');

	newdriver.setName(organizarString(name));

	//numero de horas por turno
	while (true) {
		cout << "Numero horas por turno: "; cin >> times;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		else if (times > 0)
			break;
	}
	newdriver.setShiftMaxDuration(times);

	//numero de horas por semana
	while (true) {
		cout << "Numero horas por semana: "; cin >> times;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		else if (times > 0)
			break;
	}
	newdriver.setMaxWeekWorkingTime(times);

	//numero minimo de horas de descanso
	while (true) {
		cout << "Numero minimo de horas de descanso: "; cin >> times;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		else if (times > 0)
			break;
	}
	newdriver.setMinRestTime(times);
	drivers.push_back(newdriver);

	cout << "\nCondutor Adicionado!\n";

	c.setDrivers(drivers);
	c.sortDrivers();

	//fim
	int opcao = 0;

	cout << "8 - Voltar\n";
	cout << "9 - Sair\n\n";

	while (true) {
		cout << "Opcao: "; cin >> opcao;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		switch (opcao) {
		case 8:
			return;
		case 9:
			end(c);
			break;
		}
	}
}
void Company::removeDriver(Company &c) {
	clearScreen();
	vector<Driver> drivers = c.getDrivers();

	cout << "+-------------------------------+\n";
	cout << "| Remover Condutor              |\n";
	cout << "+-------------------------------+\n";

	unsigned int id;

	cout << "\nCondutor a remover ? "; cin >> id;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	int indice = -1;

	//verifica se o condutor escolhido esta guardado no vetor
	for (size_t i = 0; i < drivers.size(); i++) {
		if (drivers[i].getId() == id) {
			indice = c.getDriverIndice(id);
		}
	}

	if (indice == -1) {
		cout << "\nCondutor nao encontrado!...\n";
		system("pause");
		return;
	}

	drivers.erase(drivers.begin() + indice);
	c.setDrivers(drivers);
	cout << "\nCondutor removido!\n";

	//fim
	int opcao = 0;
	cout << "8 - Voltar\n";
	cout << "9 - Sair\n\n";

	while (true) {
		cout << "Opcao: "; cin >> opcao;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		switch (opcao) {
		case 8:
			return;
		case 9:
			end(c);
			break;
		}
	}
}
void Company::changeDriver(Company &c) {
	clearScreen();

	unsigned int id;
	cout << "+-------------------------------+\n";
	cout << "| Modificar Condutor            |\n";
	cout << "+-------------------------------+\n";
	cout << "Condutor a modificar: "; cin >> id;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}

	//verifica se o condutor introduzido existe
	int indice = c.getDriverIndice(id);

	if (indice == -1) {
		cout << "Condutor nao encontrado!...\n";
		system("pause");
		return;
	}

	while (true) {
		int opcao = 0;

		clearScreen();
		cout << "+--------------------------------------+\n";
		cout << "| Modificar Condutor " << setw(3) << id << "               |\n";
		cout << "+--------------------------------------+\n";
		cout << "| Selecione uma opcao :                |\n";
		cout << "+--------------------------------------+\n";
		cout << "| 1. Nome                              |\n";
		cout << "| 2. Numero de horas por turno         |\n";
		cout << "| 3. Numero de horas por semana        |\n";
		cout << "| 4. Numero min de horas de descanso   |\n";
		cout << "|                                      |\n";
		cout << "| 8. Voltar                            |\n";
		cout << "+--------------------------------------+\n";
		cout << "\nOpcao: "; cin >> opcao;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}

		switch (opcao) {
		case 1:
			c.changeDriverName(indice, c);
			break;
		case 2:
			c.changeDriverMaxHours(indice, c);
			break;
		case 3:
			c.changeDriverMaxWeekWorkingTime(indice, c);
			break;
		case 4:
			c.changeDriverMinRestTime(indice, c);
			break;
		case 8:
			return;
		}
	}
}
void Company::changeDriverName(int i, Company &c) {
	clearScreen();
	vector<Driver> drivers = c.getDrivers();

	cout << "Condutor " << drivers[i].getId() << endl;

	cout << "+-------------------------------+\n";
	cout << "| Alterar Nome                  |\n";
	cout << "+-------------------------------+\n";
	cout << endl;

	string newName;  //string com o novo nome

	cin.ignore(1, '\n');
	cout << "Nome Atual: " << drivers[i].getName() << endl;
	cout << "Novo Nome ? "; getline(cin, newName, '\n');
	drivers[i].setName(organizarString(newName));
	c.setDrivers(drivers);

	cout << "\nNome Alterado!\n";
	int opcao = 0;
	cout << "8 - Voltar\n";
	cout << "9 - Sair\n\n";

	//fim
	while (true) {
		cout << "Opcao: "; cin >> opcao;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		switch (opcao) {
		case 8:
			return;
		case 9:
			end(c);
			break;
		}
	}
}
void Company::changeDriverMaxHours(int i, Company &c) {
	vector<Driver> drivers;
	while (true) {
		clearScreen();

		cout << "Condutor " << drivers[i].getId() << endl;

		cout << "+------------------------------------------------+\n";
		cout << "| Alterar Numero Maximo de Horas por Turno       |\n";
		cout << "+------------------------------------------------+\n";
		cout << endl;

		int newShiftMaxDuration = 0;  //novas horas

		cout << "Valor Atual: " << drivers[i].getShiftMaxDuration() << endl;
		cout << "Novo Valor ? "; cin >> newShiftMaxDuration;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		else if (newShiftMaxDuration > 0) {
			drivers[i].setShiftMaxDuration(newShiftMaxDuration);
			c.setDrivers(drivers);
			break;
		}
	}

	cout << "\nValor Alterado!\n";

	//fim
	int opcao = 0;
	cout << "8 - Voltar\n";
	cout << "9 - Sair\n\n";

	while (true) {
		cout << "Opcao: "; cin >> opcao;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		switch (opcao) {
		case 8:
			return;
		case 9:
			end(c);
			break;
		}
	}
}
void Company::changeDriverMaxWeekWorkingTime(int i, Company &c) {

	vector<Driver> drivers;
	while (true) {
		clearScreen();

		cout << "Condutor " << drivers[i].getId() << endl;

		cout << "+------------------------------------------------+\n";
		cout << "| Alterar Numero Maximo de Horas por Semana      |\n";
		cout << "+------------------------------------------------+\n";
		cout << endl;

		int newMaxWeekWorkingTime = 0;	//novas horas

		cout << "Valor Atual: " << drivers[i].getMaxWeekWorkingTime() << endl;
		cout << "Novo Valor ? "; cin >> newMaxWeekWorkingTime;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		else if (newMaxWeekWorkingTime > 0) {
			drivers[i].setMaxWeekWorkingTime(newMaxWeekWorkingTime);
			c.setDrivers(drivers);
			break;
		}
	}

	cout << "\nValor Alterado!\n";

	//fim
	int opcao = 0;
	cout << "8 - Voltar\n";
	cout << "9 - Sair\n\n";

	while (true) {
		cout << "Opcao: "; cin >> opcao;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		switch (opcao) {
		case 8:
			return;
		case 9:
			end(c);
			break;
		}
	}
}
void Company::changeDriverMinRestTime(int i, Company &c) {
	vector<Driver> drivers;
	while (true) {
		clearScreen();

		cout << "Condutor " << drivers[i].getId() << endl;

		cout << "+------------------------------------------------+\n";
		cout << "| Alterar Numero Minimo de Horas de Descanso     |\n";
		cout << "+------------------------------------------------+\n";
		cout << endl;

		int newMinRestTime = 0;	//novas horas

		cout << "Valor Atual: " << drivers[i].getMinRestTime() << endl;
		cout << "Novo Valor ? "; cin >> newMinRestTime;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		else if (newMinRestTime > 0) {
			drivers[i].setMinRestTime(newMinRestTime);
			c.setDrivers(drivers);
			break;
		}
	}

	cout << "\nValor Alterado!\n";

	//fim
	int opcao = 0;
	cout << "8 - Voltar\n";
	cout << "9 - Sair\n\n";

	while (true) {
		cout << "Opcao: "; cin >> opcao;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		switch (opcao) {
		case 8:
			return;
		case 9:
			end(c);
			break;
		}
	}
}
void Company::showDrivers(Company &c) {

	vector<Driver> drivers = getDrivers();
	while (true) {
		clearScreen();
		//ciclo para cada condutor do vetor
		for (size_t i = 0; i < drivers.size(); i++) {
			cout << "Condutor " << drivers[i].getId() << endl;
			cout << "Nome: " << drivers[i].getName() << endl;
			cout << "Numero horas por turno: " << drivers[i].getShiftMaxDuration() << endl;
			cout << "Numero horas por semana: " << drivers[i].getMaxWeekWorkingTime() << endl;
			cout << "Numero minimo de horas de descanso : " << drivers[i].getMinRestTime() << endl;
			cout << endl;
		}

		//fim
		int opcao = 0;

		cout << "8 - Voltar\n";
		cout << "9 - Sair\n";
		cout << "\nOpcao: "; cin >> opcao;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		switch (opcao) {
		case 8:
			return;
		case 9:
			end(c);
			break;
		}
	}
}
void Company::showLines(Company &c) {
	vector<Line> lines = getLines();
	while (true) {
		clearScreen();

		for (size_t i = 0; i < lines.size(); i++) {
			cout << "Linha " << lines[i].getId() << endl;
			cout << "Frequencia: " << lines[i].getFreq() << " min\n";
			cout << "Paragens: ";
			//ciclo para as paragens
			vector<string> busStops = lines[i].getBusStops();
			for (size_t j = 0; j < busStops.size(); j++) {
				if (j == 0)
					cout << busStops[j];
				else
					cout << ", " << busStops[j];
			}
			cout << "\nTempo de viagem entre paragens: ";
			//ciclo para os tempos
			vector<unsigned int> times = lines[i].getTimes();
			for (size_t j = 0; j < times.size(); j++) {
				if (j == 0)
					cout << times[j] << " min";
				else
					cout << ", " << times[j] << " min";
			}
			cout << "\n\n";
		}

		//fim
		int opcao = 0;

		cout << "8 - Voltar\n";
		cout << "9 - Sair\n";
		cout << "\nOpcao: "; cin >> opcao;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		switch (opcao) {
		case 8:
			return;
		case 9:
			end(c);
			break;
		}
	}
}

// ordenar os condutores
bool compareDriver(const Driver& d1, const Driver &d2) {
	return d1.getId() < d2.getId();
}
void Company::sortDrivers() {
	sort(drivers.begin(), drivers.end(), compareDriver);
}
// ordenar as linhas
bool compareLines(const Line& l1, const Line &l2) {
	return l1.getId() < l2.getId();
}
void Company::sortLines() {
	sort(lines.begin(), lines.end(), compareLines);
}

void Company::addLine(Company &c) {
	clearScreen();

	Line newLine;
	vector<Line> lines = c.getLines();

	unsigned int id;						//id da nova linha
	unsigned int freq = 0;					//freq da nova linha
	int numStops = 0;						//numero de paragens da nova linha
	vector <string> stops;			    //vetor com as paragens da nova linha
	vector <unsigned int> times;			//vetor com os tempos da nova linha

	cout << "+-------------------------------+\n";
	cout << "| Adicionar Linha               |\n";
	cout << "+-------------------------------+\n";
	//id
	while (true) {
		cout << "Numero Identificador: "; cin >> id;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		else
			break;
	}
	//verifica se o id introduzido ja existe no vetor global
	for (size_t i = 0; i < lines.size(); i++) {
		if (id == lines[i].getId()) {
			cout << "\nA linha " << id << " ja existe!...\n";
			system("pause");
			return;
		}
	}
	newLine.setId(id);

	cout << endl;
	//freq
	while (true) {
		cout << "Frequencia: "; cin >> freq;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		else if (freq > 0)
			break;
	}

	newLine.setFreq(freq);

	cout << endl;
	//paragens
	while (true) {
		cout << "Quantas paragens ? "; cin >> numStops;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		else if (numStops > 1)
			break;
	}
	cin.ignore(1, '\n');
	for (size_t i = 0; i < numStops; i++) {
		string paragem;
		cout << "Paragem " << i + 1 << ": "; getline(cin, paragem);
		string paragem_org = organizarString(paragem);
		stops.push_back(paragem_org);
	}
	newLine.setBusStops(stops);

	//tempos
	cout << endl;
	for (size_t i = 0; i < numStops - 1; i++) {
		int time = 0;
		while (true) {
			cout << "Tempo entre a paragem " << i + 1 << " e " << i + 2 << ": "; cin >> time;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
			else if (time > 0)
				break;
		}
		times.push_back(time);
	}
	newLine.setTimesList(times);
	lines.push_back(newLine);
	c.setLines(lines);
	c.sortLines();

	cout << "\nLinha Adicionada!\n";

	//fim

	int opcao = 0;

	cout << "8 - Voltar\n";
	cout << "9 - Sair\n\n";

	while (true) {
		cout << "Opcao: "; cin >> opcao;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		switch (opcao) {
		case 8:
			return;
		case 9:
			end(c);
			break;
		}
	}
}
void Company::removeLine(Company &c) {
	clearScreen();
	vector<Line> lines = c.getLines();

	cout << "+-------------------------------+\n";
	cout << "| Remover Linha                 |\n";
	cout << "+-------------------------------+\n";

	unsigned int id;

	cout << "Linha a remover ? "; cin >> id;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	int indice = -1;

	//verifica se a linha pedida esta guardada no vetor

	for (size_t i = 0; i < lines.size(); i++) {
		if (lines[i].getId() == id) {
			indice = c.getLineIndice(id);
		}
	}

	if (indice == -1) {
		cout << "\nLinha nao encontrada!...\n";
		system("pause");
		return;
	}

	lines.erase(lines.begin() + indice);
	c.setLines(lines);
	cout << "\nLinha removida!\n";

	//fim
	int opcao = 0;
	cout << "8 - Voltar\n";
	cout << "9 - Sair\n\n";

	while (true) {
		cout << "Opcao: "; cin >> opcao;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		switch (opcao) {
		case 8:
			return;
		case 9:
			end(c);
			break;
		}
	}
}
void Company::changeLine(Company &c) {

	clearScreen();

	unsigned int id;
	cout << "+-------------------------------+\n";
	cout << "| Modificar Linha               |\n";
	cout << "+-------------------------------+\n";
	cout << "Linha a modificar: "; cin >> id;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}

	//verifica se a linha introduzida existe
	int indice = c.getLineIndice(id);

	if (indice == -1) {
		cout << "\nLinha nao encontrada!...\n";
		system("pause");
		return;
	}

	while (true) {
		int opcao = 0;

		clearScreen();
		cout << "+-------------------------------+\n";
		cout << "| Modificar Linha " << setw(3) << id << "           |\n";
		cout << "+-------------------------------+\n";
		cout << "| Selecione uma opcao :         |\n";
		cout << "+-------------------------------+\n";
		cout << "| 1. Frequencia                 |\n";
		cout << "| 2. Paragens                   |\n";
		cout << "| 3. Tempos                     |\n";
		cout << "|                               |\n";
		cout << "| 8. Voltar                     |\n";
		cout << "+-------------------------------+\n";
		cout << "\nOpcao: "; cin >> opcao;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}

		switch (opcao) {
		case 1:
			changeLineFreq(indice, c);
			break;
		case 2:
			changeLineStops(indice, c);
			break;
		case 3:
			changeLineTimes(indice, c);
			break;
		case 8:
			return;
		}
	}
}
void Company::changeLineFreq(int i, Company &c) {

	vector<Line> lines = c.getLines();
	while (true) {
		clearScreen();

		cout << "Linha " << lines[i].getId() << endl;

		cout << "+-------------------------------+\n";
		cout << "| Alterar Frequencia            |\n";
		cout << "+-------------------------------+\n";
		cout << endl;

		int newFreq = 0;

		cout << "Frequencia Atual: " << lines[i].getFreq() << " min\n";
		cout << "Nova Frequencia ? "; cin >> newFreq;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		else if (newFreq > 0) {
			lines[i].setFreq(newFreq);
			break;
		}
	}

	c.setLines(lines);

	cout << "\nFrequencia Alterada!\n";

	//fim
	int opcao = 0;
	cout << "8 - Voltar\n";
	cout << "9 - Sair\n\n";

	while (true) {
		cout << "Opcao: "; cin >> opcao;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		switch (opcao) {
		case 8:
			return;
		case 9:
			end(c);
			break;
		}
	}
}
void Company::changeLineStops(int i, Company &c) {
	
	vector<Line> lines = c.getLines();
	while (true) {
		int opcao = 0;

		clearScreen();
		cout << "Linha " << lines[i].getId() << endl << "*os tempos afetados sao colocados a 0*\n";
		cout << "+-------------------------------+\n";
		cout << "| Modificar Paragens            |\n";
		cout << "+-------------------------------+\n";
		cout << "| Selecione uma opcao :         |\n";
		cout << "+-------------------------------+\n";
		cout << "| 1. Adicionar                  |\n";
		cout << "| 2. Remover                    |\n";
		cout << "| 3. Alterar                    |\n";
		cout << "|                               |\n";
		cout << "| 8. Voltar                     |\n";
		cout << "+-------------------------------+\n";
		cout << "\nOpcao: "; cin >> opcao;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}

		switch (opcao) {
		case 1:
			addStop(i, c);
			return;
		case 2:
			removeStop(i, c);
			return;
		case 3:
			changeStop(i, c);
			return;
		case 8:
			return;
		}
	}
}
int Company::totalLineStops(int i) const{
	vector<Line> lines = getLines();
	vector<string> stops = lines[i].getBusStops();
	int total = 0;
	for (size_t j = 0; j < stops.size(); j++) {
		total++;
	}
	return total;
}

void addStop(int i, Company &c) {
	vector<Line> lines = c.getLines();
	vector<string> stops = lines[i].getBusStops();
	vector<unsigned int> times = lines[i].getTimes();

	int total = c.totalLineStops(i) - 1;  //numero total de posicoes entre outras 2 paragens
	int opcao;
	int counter;		//contador para o display

	while (true) {
		//escolha da posicao da nova paragem
		counter = 2;

		clearScreen();
		cout << "+-------------------------------+\n";
		cout << "| Adicionar Paragem             |\n";
		cout << "+-------------------------------+\n\n";
		//display de todas as opcoes
		cout << "1. No inicio\n";
		for (int j = 0; j < total; j++) {
			cout << counter << ". Entre " << stops[j] << " e " << stops[j + 1] << endl;
			counter++;
		}
		cout << counter << ". No fim\n";

		cout << "\nOpcao: "; cin >> opcao;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		else if (opcao >= 1 && opcao <= counter)
			break;
	}

	int indice = opcao - 1;     //indice da nova paragem
	int indice2 = indice - 1;	//indice do tempo correspondente
	string newStop;			//string com a nova paragem

								//adicionar paragem ao vetor
	clearScreen();
	cout << "+-------------------------------+\n";
	cout << "| Adicionar Paragem             |\n";
	cout << "+-------------------------------+\n";
	cin.ignore(1, '\n');
	//display da escolha
	if (opcao == 1)
		cout << "1. No inicio\n";
	else if (opcao == counter)
		cout << counter << ". No fim\n";
	else
		cout << opcao << ". Entre " << stops[indice] << " e " << stops[indice + 1] << endl;
	cout << "\nNova Paragem ? "; getline(cin, newStop, '\n');

	newStop = organizarString(newStop);

	//adicionar ao vetor e alterar tempos para 0
	stops.insert(stops.begin() + indice, newStop);
	if (opcao == 1) {
		times.insert(times.begin() + indice, 0);
	}
	else if (opcao == counter) {
		times.insert(times.begin() + indice2, 0);
	}
	else {
		times.insert(times.begin() + indice2, 0);
		times[indice2 + 1] = 0;
	}

	lines[i].setBusStops(stops);
	lines[i].setTimesList(times);
	c.setLines(lines);

	cout << "\nParagem Adicionada!\n";

	//fim
	opcao = 0;
	cout << "8 - Voltar\n";
	cout << "9 - Sair\n\n";

	while (true) {
		cout << "Opcao: "; cin >> opcao;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		switch (opcao) {
		case 8:
			return;
		case 9:
			end(c);
			break;
		}
	}
}
void removeStop(int i, Company &c) {
	vector<Line> lines = c.getLines();
	vector<string> stops = lines[i].getBusStops();
	vector<unsigned int> times = lines[i].getTimes();

	int total = c.totalLineStops(i);  //total de paragens
	int opcao;

	while (true) {

		clearScreen();
		cout << "+-------------------------------+\n";
		cout << "| Remover Paragem               |\n";
		cout << "+-------------------------------+\n\n";

		//display de todas as paragens da linha
		for (int j = 0; j < total; j++) {
			cout << j + 1 << ". " << stops[j] << endl;
		}
		cout << "\nOpcao: "; cin >> opcao;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		else if (opcao >= 1 && opcao <= total)
			break;
	}

	int indice = opcao - 1;		//indice da paragem escolhida
	int indice2 = opcao - 2;	//indice do tempo a remover se for escolhida a ultima paragem para remover

	stops.erase(stops.begin() + indice);  //remove paragem


																	//remove o tempo correspondente
	if (opcao == total)
		times.erase(times.begin() + indice2);
	else
		times.erase(times.begin() + indice);

	cout << "\nParagem Removida!\n";

	lines[i].setBusStops(stops);
	lines[i].setTimesList(times);
	c.setLines(lines);

	//fim
	opcao = 0;
	cout << "8 - Voltar\n";
	cout << "9 - Sair\n\n";

	while (true) {
		cout << "Opcao: "; cin >> opcao;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		switch (opcao) {
		case 8:
			return;
		case 9:
			end(c);
			break;
		}
	}
}
void changeStop(int i, Company &c) {
	vector<Line> lines = c.getLines();
	vector<string> stops = lines[i].getBusStops();
	vector<unsigned int> times = lines[i].getTimes();

	int total = c.totalLineStops(i);  //numero total de paragens
	int opcao;

	while (true) {
		//escolha da paragem
		clearScreen();
		cout << "+-------------------------------+\n";
		cout << "| Alterar Paragem               |\n";
		cout << "+-------------------------------+\n\n";
		//display de todas as paragens
		for (int j = 0; j < total; j++) {
			cout << j + 1 << ". " << stops[j] << endl;
		}
		cout << "\nOpcao: "; cin >> opcao;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		else if (opcao >= 1 && opcao <= total)
			break;
	}

	int indice = opcao - 1;		//indice da paragem escolhida
	int indice2 = indice - 1;	//indice do tempo correspondente
	string newStop;			//string com o nome da nova paragem

								//altera nome paragem
	clearScreen();
	cout << "+-------------------------------+\n";
	cout << "| Alterar Paragem               |\n";
	cout << "+-------------------------------+\n";
	cin.ignore(1, '\n');
	cout << opcao << ". " << stops[indice] << endl;
	cout << "\nNova paragem ? "; getline(cin, newStop, '\n');
	string novaParagem_org = organizarString(newStop);

	stops[indice] = novaParagem_org;  //altera o nome da paragem

												   //alterar tempos
	if (opcao == 1) {
		times[0] = 0;
	}
	else if (opcao == total) {
		times[indice2] = 0;
	}
	else {
		times[indice2] = 0;
		times[indice2 + 1] = 0;
	}

	lines[i].setBusStops(stops);
	lines[i].setTimesList(times);
	c.setLines(lines);

	cout << "\nParagem Alterada!\n";

	//fim
	opcao = 0;
	cout << "8 - Voltar\n";
	cout << "9 - Sair\n\n";

	while (true) {
		cout << "Opcao: "; cin >> opcao;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		switch (opcao) {
		case 8:
			return;
		case 9:
			end(c);
			break;
		}
	}
}

void Company::changeLineTimes(int i, Company &c) {
	vector<Line> lines = c.getLines();
	vector<string> stops = lines[i].getBusStops();
	vector<unsigned int> times = lines[i].getTimes();

	int total = c.totalLineStops(i) - 1; //numero total de tempos
	int opcao;

	while (true) {
		//escolha do tempo a alterar
		clearScreen();
		cout << "+-------------------------------+\n";
		cout << "| Alterar Tempo entre Paragens  |\n";
		cout << "+-------------------------------+\n\n";
		//display de todos os tempos
		for (int j = 0; j < total; j++) {
			cout << j + 1 << ". Entre " << stops[j] << " e " << stops[j + 1] << endl;
		}
		cout << "\nOpcao: "; cin >> opcao;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		else if (opcao >= 1 && opcao <= total)
			break;
	}

	int indice = opcao - 1;  //indice correspondente ao tempo escolhido

	while (true) {
		//alterar tempo escolhido
		int newTime = 0;

		clearScreen();
		cout << "+-------------------------------+\n";
		cout << "| Alterar Tempo                 |\n";
		cout << "+-------------------------------+\n";

		cout << opcao << ". Entre " << stops[indice] << " e " << stops[indice + 1] << endl;
		cout << "Tempo atual: " << times[indice] << " min" << endl;
		cout << "\nNovo Tempo ? "; cin >> newTime;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		else if (newTime > 0) {
			times[indice] = newTime;
			break;
		}
	}

	lines[i].setTimesList(times);
	c.setLines(lines);

	cout << "\nTempo Alterado!\n";

	//fim
	opcao = 0;
	cout << "8 - Voltar\n";
	cout << "9 - Sair\n\n";

	while (true) {
		cout << "Opcao: "; cin >> opcao;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		switch (opcao) {
		case 8:
			return;
		case 9:
			end(c);
			break;
		}
	}
}