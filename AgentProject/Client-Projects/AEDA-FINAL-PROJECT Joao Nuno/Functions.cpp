/*
 * Functions.cpp
 *
 *  Created on: 14/11/2017
 *      Author: nl
 */

#include "Functions.h"
#include "Associate.h"
#include "Area.h"
#include "Association.h"
#include "SubArea.h"
#include "Event.h"
#include "SummerSchool.h"
#include "Conference.h"
#include "Mail.h"
#include "Network.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sstream>
#include <list>
#include <algorithm>
#include <iomanip>

using namespace std;

//PROTOTYPE
void lerficheiroAreas();

//=======================USEFUL FUNCTIONS================================
//=======================================================================

bool is_number(const std::string& s) {
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it))
		++it;
	return !s.empty() && it == s.end();
}

//=======================================================================

Association * Associacao;
Network * Rede = new Network();

void initialize() {
	lerficheiroAssociacao();
	lerficheiroAreas();
	lerficheiroAssociados();
	lerficheiroEventos();
	lerficheiroMails();

}

void initialize2() {
	Associacao = new Association(
			"ASSOCIACAO PORTUGUESA INVESTIGACAO CIENTIFICA");
	limparficheiros();
	lerficheiroAreas();
}

void ano() {
	cout << endl << endl;
	cout << "--------------------------------------------- " << endl;
	cout << "ASSOCIACAO PORTUGUESA INVESTIGACAO CIENTIFICA" << endl;
	cout << "--------------------------------------------- " << endl;
	cout << endl << endl;

	char opcao;
	cout << "Ano atual: " << Associacao->getCurrentYear()
			<< "\t Semestre Atual: " << fixed << setprecision(1)
			<< Associacao->getCurrentSemester() << "\nFundo Atual: "
			<< Associacao->getFund() << endl;
	cout << "\nIncrementar um semestre? (S/N): ";
	while (opcao != 's' && opcao != 'S' && opcao != 'n' && opcao != 'N') {
		cin >> opcao;
		switch (opcao) {
		case 's':
			Associacao->acceptEvents();
			Associacao->updateSemester();

			if (Associacao->getCurrentSemester() == 0)
				Associacao->updateAllAssociates();
			break;
		case 'S':
			Associacao->acceptEvents();
			Associacao->updateSemester();
			if (Associacao->getCurrentSemester() == 0)
				Associacao->updateAllAssociates();
			break;
		case 'n':
			break;
		case 'N':
			break;
		default:
			cout << "Opcao invalida. Introduza uma nova opcao: ";
		}
	}
}

//-----------------------FILES--------------------------//

void lerficheiroAreas() {
	ifstream file;
	string line;
	file.open("areas.txt");
	while (getline(file, line)) {
		Area * newArea = new Area(line);
		Associacao->addArea(newArea);
	}
	file.close();
}

void lerficheiroAssociacao() {
	ifstream file;
	string line;
	file.open("association.txt");
	while (getline(file, line)) {
		Associacao = new Association(line, Rede);
	}
	file.close();
}

void lerficheiroAssociados() {
	ifstream file;
	string line;
	file.open("associates.txt");
	while (getline(file, line)) {
		Associate * newAsso = new Associate(Associacao, line);
		Associacao->addAssociate(newAsso);
	}

	Associacao->updateAllAssociates();

	file.close();

}

void lerficheiroEventos() {

	ifstream file;
	string line;
	file.open("events.txt");
	while (getline(file, line)) {

		stringstream infoEvent(line);
		string type_of_event;
		getline(infoEvent, type_of_event, '/');

		if (type_of_event == "SummerSchool") {
			string type, date, local, theme;
			int phase;

			int requester, organizer;

			long double money;

			char garbage;

			string former_name, former_inst;

			getline(infoEvent, date, '/');
			getline(infoEvent, local, '/');
			getline(infoEvent, theme, '/');

			infoEvent >> phase;
			infoEvent >> garbage;		// '/'
			infoEvent >> garbage;		// '['

			vector<Associate *> event_request;

			vector<Associate *> event_organizers;

			while (infoEvent.peek() != ']') {

				infoEvent >> requester;

				for (Associate * elem : Associacao->getAssociates()) {

					if (requester == elem->getUniqueID()) {
						event_request.push_back(elem);
						event_organizers.push_back(elem);
					}

				}

				for (Associate * elem : Associacao->getInactiveAssociates()) {

					if (requester == elem->getUniqueID()) {
						event_request.push_back(elem);
						event_organizers.push_back(elem);
					}

				}

				infoEvent >> garbage;
			}

			infoEvent >> garbage;		// ']'
			infoEvent >> garbage;		// '/'
			infoEvent >> garbage;		// '['

			while (infoEvent.peek() != ']') {

				infoEvent >> organizer;

				for (Associate * elem : Associacao->getAssociates()) {

					if (organizer == elem->getUniqueID()) {
						event_organizers.push_back(elem);

					}

				}

				for (Associate * elem : Associacao->getInactiveAssociates()) {

					if (organizer == elem->getUniqueID()) {
						event_organizers.push_back(elem);
					}

				}
				infoEvent >> garbage;
			}

			infoEvent >> garbage;		// ']'
			infoEvent >> garbage;		// '/'

			infoEvent >> money;

			infoEvent >> garbage;		// '/'

			infoEvent >> garbage;		// '['

			list<Trainer *> trainers;

			while (infoEvent.peek() != ']') {

				getline(infoEvent, former_name, '/');
				getline(infoEvent, former_inst, '/');
				Trainer * newTrainer = new Trainer(former_name, former_inst);
				trainers.push_back(newTrainer);
			}

			infoEvent >> garbage;

			SummerSchool * newSummer = new SummerSchool(event_request,
					event_organizers, date, local, theme, phase, Associacao,
					trainers, money);
			Associacao->addEvent(newSummer);

		} else {

			string date, local, theme;
			int requester, organizer;
			long double money;
			int phase;
			char garbage;

			int predicted_participants;

			getline(infoEvent, date, '/');
			getline(infoEvent, local, '/');
			getline(infoEvent, theme, '/');

			infoEvent >> phase;
			infoEvent >> garbage;		// '/'
			infoEvent >> garbage;		// '['

			vector<Associate *> event_request;

			vector<Associate *> event_organizers;

			while (infoEvent.peek() != ']') {

				infoEvent >> requester;

				for (Associate * elem : Associacao->getAssociates()) {

					if (requester == elem->getUniqueID()) {
						event_request.push_back(elem);
						event_organizers.push_back(elem);
					}

				}

				for (Associate * elem : Associacao->getInactiveAssociates()) {

					if (requester == elem->getUniqueID()) {
						event_request.push_back(elem);
						event_organizers.push_back(elem);
					}

				}
				infoEvent >> garbage;
			}
			infoEvent >> garbage;		// ']'
			infoEvent >> garbage;		// '/'
			infoEvent >> garbage;		// '['

			while (infoEvent.peek() != ']') {

				infoEvent >> organizer;

				set<Associate *> associates_set = Associacao->getAssociates();
				for (auto it = associates_set.begin();
						it != associates_set.end(); it++) {

					if (organizer == (*it)->getUniqueID()) {
						event_organizers.push_back((*it));
					}
				}
				infoEvent >> garbage;
			}
			infoEvent >> garbage;		// ']'
			infoEvent >> garbage;		// '/'

			infoEvent >> money;

			infoEvent >> garbage;		// '/'

			infoEvent >> predicted_participants;
			Conference * newConf = new Conference(event_request,
					event_organizers, date, local, theme, phase, Associacao,
					predicted_participants, money);
			Associacao->addEvent(newConf);
		}

	}
	file.close();
}

void lerficheiroMails() {
	ifstream file;
	string line;
	file.open("mails.txt");
	vector<Mail *> all_mails;
	while (getline(file, line)) {

		stringstream infoMail(line);
		string title, content;
		int id;
		char garbage;
		string date;

		infoMail >> id;
		infoMail >> garbage;
		getline(infoMail, title, '/');
		getline(infoMail, content, '/');
		getline(infoMail, date, '/');

		for (Associate * elem : Associacao->getAssociates()) {

			if (id == elem->getUniqueID()) {
				Mail * newMail = new Mail(elem, title, content, date);
				all_mails.push_back(newMail);
				break;
			}
		}

		for (Associate * elem : Associacao->getInactiveAssociates()) {

			if (id == elem->getUniqueID()) {
				Mail * newMail = new Mail(elem, title, content, date);
				all_mails.push_back(newMail);
				break;
			}
		}

	}
	Rede->setMails(all_mails);
	file.close();
}

void guardarficheiroAreas() {
	ofstream file("areas.txt");

	vector<Area *> areas_vector = Associacao->getAreas();
	for (size_t i = 0; i < areas_vector.size(); i++) {

		file << areas_vector.at(i)->getName() << "/";

		vector<SubArea *> subareas_vector = areas_vector.at(i)->getSubAreas();
		for (size_t t = 0; t < subareas_vector.size(); t++) {

			if (t == (subareas_vector.size() - 1)) {
				file << subareas_vector.at(t)->getName() << "/"
						<< subareas_vector.at(t)->getInitials();

				if (i != areas_vector.size() - 1)
					file << endl;
			} else
				file << subareas_vector.at(t)->getName() << "/"
						<< subareas_vector.at(t)->getInitials() << "/";
		}
	}

	file.close();
}

void guardarficheiroAssociacao() {
	ofstream file("association.txt");

	file << Associacao->getName() << "/";
	file << Associacao->getFund() << "/";
	file << Associacao->getAnnualPay() << "/";
	file << Associacao->getCurrentYear();

	file.close();
}

void guardarficheiroAssociados() {
	ofstream file("associates.txt");

	vector<Associate *> associates_vector;

	for (Associate * elem : Associacao->getAssociates()) {
		associates_vector.push_back(elem);
	}

	for (Associate * elem : Associacao->getInactiveAssociates()) {
		associates_vector.push_back(elem);
	}
	//in order to keep them organized by ID in the txt file
	sort(associates_vector.begin(), associates_vector.end(), cmpID);

	for (size_t i = 0; i < associates_vector.size(); i++) {
		file << associates_vector.at(i)->getUniqueID() << "/";
		file << associates_vector.at(i)->getName() << "/";
		file << associates_vector.at(i)->getInstitution() << "/[";

		vector<Area *> areas_interest =
				associates_vector.at(i)->getInterestAreas();
		for (size_t t = 0; t < areas_interest.size(); t++) {

			file << areas_interest.at(t)->getName() << "/";
		}
		file << "]" << "/" << associates_vector.at(i)->getPersonalWallet()
				<< "/[";

		vector<int> years_vector = associates_vector.at(i)->getPaidYears();
		for (size_t t = 0; t < years_vector.size(); t++) {

			file << years_vector.at(t) << "/";
		}

		file << "]" << "/" << associates_vector.at(i)->getDivulgations();

		if (i != associates_vector.size() - 1)
			file << endl;

	}
	file.close();
}

void guardarficheiroEventos() {
	ofstream file("events.txt");

	vector<Event *> event_vector = Associacao->getEvents();

	for (size_t i = 0; i < event_vector.size(); i++) {

		if (event_vector.at(i)->getType() == "SummerSchool") {
			file << event_vector.at(i)->getType() << "/";
			file << event_vector.at(i)->getDate() << "/";
			file << event_vector.at(i)->getLocal() << "/";
			file << event_vector.at(i)->getTheme() << "/";
			file << event_vector.at(i)->getPhase() << "/[";

			vector<Associate *> requesters_vector =
					event_vector.at(i)->getRequest();

			vector<int> used_ids;

			for (size_t t = 0; t < requesters_vector.size(); t++) {

				file << requesters_vector.at(t)->getUniqueID() << "/";
				used_ids.push_back(requesters_vector.at(t)->getUniqueID());
			}

			file << "]/[";
			vector<Associate *> organizers_vector =
					event_vector.at(i)->getOrganizers();
			for (size_t t = 0; t < organizers_vector.size(); t++) {
				if (find(used_ids.begin(), used_ids.end(),
						organizers_vector.at(t)->getUniqueID())
						== used_ids.end())
					file << organizers_vector.at(t)->getUniqueID() << "/";
			}

			file << "]/" << event_vector.at(i)->getSupport() << "/[";

			list<Trainer *> trainers = event_vector.at(i)->getTrainers();

			for (auto it = trainers.begin(); it != trainers.end(); it++) {
				file << (*it)->getName() << "/" << (*it)->getInstitution()
						<< "/";
			}

			file << "]";

		} else {
			file << event_vector.at(i)->getType() << "/";
			file << event_vector.at(i)->getDate() << "/";
			file << event_vector.at(i)->getLocal() << "/";
			file << event_vector.at(i)->getTheme() << "/";
			file << event_vector.at(i)->getPhase() << "/[";

			vector<Associate *> requesters_vector =
					event_vector.at(i)->getRequest();

			vector<int> used_ids;

			for (size_t t = 0; t < requesters_vector.size(); t++) {

				file << requesters_vector.at(t)->getUniqueID() << "/";
				used_ids.push_back(requesters_vector.at(t)->getUniqueID());
			}

			file << "]/[";

			vector<Associate *> organizers_vector =
					event_vector.at(i)->getOrganizers();
			for (size_t t = 0; t < organizers_vector.size(); t++) {
				if (find(used_ids.begin(), used_ids.end(),
						organizers_vector.at(t)->getUniqueID())
						== used_ids.end())
					file << organizers_vector.at(t)->getUniqueID() << "/";
			}

			file << "]/" << event_vector.at(i)->getSupport() << "/";
			file << event_vector.at(i)->getEstimative();

		}

		if (i != event_vector.size() - 1)
			file << endl;
	}

	file.close();
}

void guardarficheiroMails() {

	ofstream file("mails.txt");

	vector<Mail *> mails_vector = Rede->getMails();
	for (size_t i = 0; i < mails_vector.size(); i++) {

		file << mails_vector.at(i)->getAuthor()->getUniqueID() << "/";
		file << mails_vector.at(i)->getTitle() << "/";
		file << mails_vector.at(i)->getBody() << "/";
		file << mails_vector.at(i)->getDate();

		if (i != mails_vector.size() - 1)
			file << endl;
	}

	file.close();
}

void limparficheiros() {
	ofstream file;
	file.open("associates.txt", ofstream::out | ofstream::trunc);
	file.close();
	file.open("association.txt", ofstream::out | ofstream::trunc);
	file.close();
	file.open("events.txt", ofstream::out | ofstream::trunc);
	file.close();
	file.open("mails.txt", ofstream::out | ofstream::trunc);
	file.close();
}

//----------------------ASSOCIATES---------------------//

void adicionarAssociado() {
	string nome, instituicao;
	cout << endl << endl;
	cout << "--------------------------------------------- " << endl;
	cout << "ASSOCIACAO PORTUGUESA INVESTIGACAO CIENTIFICA" << endl;
	cout << "--------------------------------------------- " << endl;
	cout << endl << endl;
	cin.clear();
	cin.ignore(10000, '\n');
	cout << "Introduza o nome do Associado: ";
	getline(cin, nome);
	cout << "\nIntroduza a instituicao do Associado: ";
	getline(cin, instituicao);

	//agora dar cout das areas da associacao numeradas...
	cout << "\nIndique quais as areas de interesse do Associado: " << endl;

	vector<Area *> areas = Associacao->getAreas();
	for (size_t t = 0; t < areas.size(); t++) {
		cout << t << ": " << areas.at(t)->getName() << endl;
	}

	string list;
	cout << "\nIntroduza as opcoes separadas por espacos: ";
	getline(cin, list);

	stringstream numbers(list);

	vector<Area *> newInterest; //O VETOR QUE IRA CONTER AS AREAS DE INTERESSE DO ASSOCIADO

	while (!numbers.eof()) {
		size_t selected = 0;
		if (!(numbers >> selected))
			cout << "\nUm dos valores introduzidos nao foi um inteiro.\n"
					<< endl;
		if (selected >= areas.size() || selected < 0) { //SE UM DOS INDICES ESCOLHIDOS NAO CORRESPONDE A NENHUM DOS APRESENTADOS
			cout << "\nNao existe a opcao " << selected << endl;
			sleep(1);
			return;
		}

		newInterest.push_back(areas.at(selected));
	}

	Associate * newAsso = new Associate(Associacao, nome, instituicao,
			newInterest);

	Associacao->addAssociate(newAsso);
	Associacao->updateAllAssociates();

	cout << "\nAssociado adicionado com sucesso!" << endl << endl;

	sleep(1);
}

void removerAssociado() {

	cout << endl << endl;
	cout << "--------------------------------------------- " << endl;
	cout << "ASSOCIACAO PORTUGUESA INVESTIGACAO CIENTIFICA" << endl;
	cout << "--------------------------------------------- " << endl;
	cout << endl << endl;
	cout << "Introduza o Identificador Unico do Associado a remover: ";
	cin.clear();
	int uniqueID;
	string tempID;
	cin.ignore(10000, '\n');
	getline(cin, tempID);

	if (!is_number(tempID)) {
		cout << "O valor introduzido nao e um inteiro.\n" << endl;
		return;
	}

	uniqueID = stoi(tempID);

	try {
		Associacao->removeAssociate(uniqueID);
	} catch (NoSuchID & e) {
		cout << "\nNao existe nenhum associado com o ID: " << e.getID() << endl;
		sleep(1);
		return;
	}

	cout << "\nAssociado removido com sucesso!" << endl;

	sleep(1);
}

void alterarAssociado() {
	string tempID;
	int uniqueID;
	cout << endl << endl;
	cout << "--------------------------------------------- " << endl;
	cout << "ASSOCIACAO PORTUGUESA INVESTIGACAO CIENTIFICA" << endl;
	cout << "--------------------------------------------- " << endl;
	cout << endl << endl;
	cout << "Introduza o Identificador Unico do Associado: ";
	cin.clear();
	cin.ignore(10000, '\n');
	getline(cin, tempID);

	if (!is_number(tempID)) {
		cout << "O valor introduzido nao e um inteiro.\n" << endl;
		return;
	}

	uniqueID = stoi(tempID);

	Associate * alterar;
	try {
		alterar = Associacao->getAssoById(uniqueID);
	} catch (const NoSuchID & e) {
		cout << "\nNao existe nenhum associado com o ID: " << e.getID() << endl;
		sleep(1);
		return;
	}

	cout << "\nQual o atributo que pretende mudar: " << endl;

	cout << "\t0: Areas de Interesse" << endl;
	cout << "\t1: Instituicao" << endl;

	cout << "\nInsira uma opcao: ";
	string opcao;
	getline(cin, opcao);

	if (!is_number(opcao)) {
		cout << "O valor introduzido nao e um inteiro.\n" << endl;
		return;
	}

	int escolha = stoi(opcao);

	switch (escolha) {
	case 0: {
		cout
				<< "\nTodas as areas de interesse do associado foram eliminadas. Escolha as novas areas de interesse.\n";
		vector<Area *> areas = Associacao->getAreas();
		for (size_t t = 0; t < areas.size(); t++) {
			cout << t << ": " << areas.at(t)->getName() << endl;
		}

		string list;
		cout << "\nIntroduza as opcoes separadas por espacos: ";
		getline(cin, list);

		stringstream numbers(list);

		vector<Area *> newInterest; //O VETOR QUE IRA CONTER AS AREAS DE INTERESSE DO ASSOCIADO

		while (!numbers.eof()) {
			size_t selected = 0;
			if (!(numbers >> selected))
				cout << "\nUm dos valores introduzidos nao foi um inteiro.\n"
						<< endl;
			if (selected >= areas.size() || selected < 0) { //SE UM DOS INDICES ESCOLHIDOS NAO CORRESPONDE A NENHUM DOS APRESENTADOS
				cout << "\nNao existe a opcao " << selected << endl;
				sleep(1);
				return;
			}

			newInterest.push_back(areas.at(selected));
		}

		alterar->setInterestAreas(newInterest);

		cout << "Areas de Interesse alteradas com sucesso!\n";
		return;
		break;
	}
	case 1: {
		cout << "Qual a nova Instituicao do associado? ";
		string institution;
		getline(cin, institution);
		alterar->setInstitution(institution);
		cout << "Instituicao alterada com sucesso!\n";
		return;
		break;

	}
	default:
		cout << "Opcao Invalida" << endl;
		return;
	}

}

void verInfoAssociado() {
	cout << endl << endl;
	cout << "--------------------------------------------- " << endl;
	cout << "ASSOCIACAO PORTUGUESA INVESTIGACAO CIENTIFICA" << endl;
	cout << "--------------------------------------------- " << endl;
	cout << endl << endl;
	cout << " Como deseja ver a informacao dos associados?" << endl;
	cout << " 1 - Procurar por Identificador Unico" << endl;
	cout << " 2 - Procurar por interesse numa área" << endl;
	cout << " 3 - Mostrar todos" << endl;
	cout << " 4 - Mostrar por ordem alfabetica de nome" << endl;
	cout << " 5 - Listagem parcial em funcao do ID" << endl;
	cout << " 6 - Listagem parcial em funcao do dinheiro disponivel" << endl;

	int opcao = 0;
	cout << endl;
	cout << "Introduza uma opcao: ";
	while (opcao < 1 || opcao > 6) {
		cin >> opcao;
		switch (opcao) {
		case 1: {
			cout << "Introduza o Identificador Unico do Associado: ";
			int uniqueID;
			string tempID;
			cin.ignore(10000, '\n');
			getline(cin, tempID);

			if (!is_number(tempID)) {
				cout << "O valor introduzido nao e um inteiro.\n" << endl;
				return;
			}

			uniqueID = stoi(tempID);

			Associate * associado;
			try {
				associado = Associacao->getAssoById(uniqueID);
			} catch (NoSuchID & e) {
				cout << "\nNao existe nenhum associado com o ID: " << e.getID()
						<< endl;
				return;
			}

			string associadoinfo = associado->showInfo();
			cout << endl << associadoinfo;

			break;
		}
		case 2: {
			cout
					<< "\nIndique qual a area de interesse dos Associados a procurar: "
					<< endl;

			vector<Area *> areas = Associacao->getAreas();
			for (size_t t = 0; t < areas.size(); t++) {
				cout << t << ": " << areas.at(t)->getName() << endl;
			}

			unsigned int opcao;
			cout << "\nIntroduza uma opcao: ";
			cin >> opcao;
			cin.clear();
			if (cin.fail() || opcao > (areas.size() - 1) || opcao < 0) {
				cout << "\nO valor introduzido nao e valido.\n";
				return;
			}

			int counter = 0;

			for (auto it = Associacao->getAssociates().begin();
					it != Associacao->getAssociates().end(); it++) {

				for (size_t t = 0; t < (*it)->getInterestAreas().size(); t++) {
					if ((*it)->getInterestAreas().at(t) == areas.at(opcao)) {
						cout << endl;
						counter++;
						cout << (*it)->showInfo();
					}
				}

			}

			if(counter == 0){
				cout << "\nNao ha Associados interessados na area " << areas.at(opcao)->getName() << "." << endl;
			}

			break;
		}
		case 3: {
			cout << endl;
			string output = Associacao->showAllAssociates();
			cout << output;
			break;
		}
		case 4:{
			string ordem;
			cout << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Ordem crescente ou decrescente? ";
			getline(cin, ordem);

			vector<Associate *> associados;

			for (Associate * elem : Associacao->getAssociates()) {
				associados.push_back(elem);
			}

			for (Associate * elem : Associacao->getInactiveAssociates()) {
				associados.push_back(elem);
			}

			if (ordem == "crescente") {
				sort(associados.begin(), associados.end(), cmpName<Associate>);
			} else if (ordem == "decrescente") {
				sort(associados.begin(), associados.end(), cmpName<Associate>);
				reverse(associados.begin(), associados.end());
			} else {
				cout << "Opcao inválida";
				break;
			}
			if (associados.empty()) {
				cout
						<< "Nao existem associados que cumpram esses requisitos.\n";
			} else {
				for (size_t i = 0; i < associados.size(); i++) {
					cout << endl;
					string retorno = associados.at(i)->showInfo();
					cout << retorno;
				}
			}
			break;
		}
		case 5: {
			int maximo, minimo;
			string ordem;
			cout << endl;
			cout << "Introduza os valores minimo e maximo de ID: " << endl;
			cout << "Minimo: ";
			cin >> minimo;
			cin.clear();
			cin.ignore(10000, '\n');

			cout << "Maximo: ";
			cin >> maximo;
			cin.clear();
			cin.ignore(10000, '\n');
			if (minimo > maximo) {
				cout << "O minimo e superior ao maximo" << endl;
				return;
			}
			cout << "Ordem crescente ou decrescente? ";
			getline(cin, ordem);

			vector<Associate *> associados;

			for (Associate * elem : Associacao->getAssociates()) {

				int id = elem->getUniqueID();

				if ((id <= maximo) && (id >= minimo))
					associados.push_back(elem);

			}

			for (Associate * elem : Associacao->getInactiveAssociates()) {

				int id = elem->getUniqueID();

				if ((id <= maximo) && (id >= minimo))
					associados.push_back(elem);

			}

			if (ordem == "crescente" || ordem == "Crescente") {
				sort(associados.begin(), associados.end(), cmpID);
			} else if (ordem == "decrescente" || ordem == "Descrescente") {
				sort(associados.begin(), associados.end(), cmpID);
				reverse(associados.begin(), associados.end());
			} else {
				cout << "Opcao inválida";
				break;
			}

			if (associados.empty()) {
				cout
						<< "Nao existem associados que cumpram esses requisitos.\n";
			} else {
				for (size_t i = 0; i < associados.size(); i++) {
					cout << endl;
					string retorno = associados.at(i)->showInfo();
					cout << retorno;
				}
			}
			break;
		}
		case 6: {
			float maximo, minimo;
			string ordem;
			cout << endl;
			cout
					<< "Introduza os valores minimo e maximo do dinheiro disponivel: "
					<< endl;
			cout << "Minimo: ";
			cin >> minimo;
			cout << "Maximo: ";
			cin >> maximo;
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Ordem crescente ou decrescente? ";
			getline(cin, ordem);

			vector<Associate *> associados;

			for (Associate * elem : Associacao->getAssociates()) {

				float wallet = elem->getPersonalWallet();

				if ((wallet <= maximo) && (wallet >= minimo))
					associados.push_back(elem);

			}

			for (Associate * elem : Associacao->getInactiveAssociates()) {

				float wallet = elem->getPersonalWallet();

				if ((wallet <= maximo) && (wallet >= minimo))
					associados.push_back(elem);

			}

			if (ordem == "crescente") {
				sort(associados.begin(), associados.end(), cmpMoney);
			} else if (ordem == "decrescente") {
				sort(associados.begin(), associados.end(), cmpMoney);
				reverse(associados.begin(), associados.end());
			} else {
				cout << "Opcao inválida";
				break;
			}
			if (associados.empty()) {
				cout
						<< "Nao existem associados que cumpram esses requisitos.\n";
			} else {
				for (size_t i = 0; i < associados.size(); i++) {
					cout << endl;
					string retorno = associados.at(i)->showInfo();
					cout << retorno;
				}
			}
			break;
		}
		default:
			cout << "Opcao invalida. Introduza uma nova opcao: ";
		}
	}
}

//-----------------------EVENTOS----------------------//

void criarEvento() {
	int uniqueID, numAsso;
	cout << endl << endl;
	cout << "--------------------------------------------- " << endl;
	cout << "ASSOCIACAO PORTUGUESA INVESTIGACAO CIENTIFICA" << endl;
	cout << "--------------------------------------------- " << endl;
	cout << endl << endl;
	Associate * associado;
	vector<Associate *> event_request, event_organizers;
	cin.clear();
	cin.ignore(10000, '\n');

	int phase;
	cout << "Indique a fase do evento (1 ou 2): ";
	cin >> phase;
	if (phase < 1 || phase > 2) {
		cout << "\nNao existe essa opcao\n";
		return;
	}

	cin.clear();
	cin.ignore(10000, '\n');

	string type;
	cout << "\nIndique o tipo de evento (Summer School ou Conference): ";
	getline(cin, type);

	bool typeevento; //true se for summer school e false se for conference
	if (type == "Summer School" || type == "summer school")
		typeevento = true;
	else if (type == "Conference" || type == "conference")
		typeevento = false;
	else {
		cout << "\nNao existe essa opcao\n";
		return;
	}

	cout << "\nIntroduza o numero de Associados que querem criar o Evento: ";
	cin >> numAsso;
	if (numAsso < 3) {
		cout
				<< "O numero de Associados que querem criar o evento deve ser superior a 3.";
		return;
	}

	for (int i = 0; i < numAsso; i++) {
		cout << "Introduza o Identificador Unico do " << i + 1
				<< "º Associado que quer criar um Evento: ";
		cin >> uniqueID;
		try {
			associado = Associacao->getAssoById(uniqueID);
		} catch (NoSuchID & e) {
			cout << "\nNao existe nenhum associado com o ID: " << e.getID()
					<< endl;
			sleep(1);
			return;
		}
		event_request.push_back(associado);
	}

	event_organizers = event_request;
	cout
			<< "\nIntroduza o numero de Associados que vao ajudar a organizar o Evento: ";
	cin >> numAsso;
	for (int i = 0; i < numAsso; i++) {
		cout << "Introduza o Identificador Unico do " << i + 1
				<< "º Associado que quer ajudar a organizar o Evento: ";
		cin >> uniqueID;
		try {
			associado = Associacao->getAssoById(uniqueID);
		} catch (NoSuchID & e) {
			cout << "\nNao existe nenhum associado com o ID: " << e.getID()
					<< endl;
			sleep(1);
			return;
		}
		event_organizers.push_back(associado);
	}

	cin.clear();
	cin.ignore(10000, '\n');

	string date, local, theme;
	cout << "\nIntroduza a data do evento (dd-mm-a): ";
	getline(cin, date);
	stringstream check_date(date);
	int temp_day, temp_month, temp_year;
	char garbage;
	check_date >> temp_day >> garbage >> temp_month >> garbage >> temp_year;
	if (check_date.fail()) {
		cout << "Nao introduziu a data no formato correto.\n";
		return;
	}
	cout << "\nIntroduza o local do evento: ";
	getline(cin, local);
	cout << "\nIntroduza o tema do evento: ";
	getline(cin, theme);

	if (typeevento) {
		int numFormadores;
		cout << "\nIntroduza o numero de formadores do evento: ";
		cin >> numFormadores;
		list<Trainer *> trainers;
		cin.clear();
		cin.ignore(10000, '\n');
		for (int i = 0; i < numFormadores; i++) {
			string nome, instituicao;
			cout << "\nIntroduza o nome do " << i + 1 << "º Formador: ";
			getline(cin, nome);
			cout << "Introduza o nome da sua intituicao: ";
			getline(cin, instituicao);
			Trainer * trainer = new Trainer(nome, instituicao);
			trainers.push_back(trainer);
		}
		SummerSchool * escola;
		try {
			escola = new SummerSchool(event_request, event_organizers, date,
					local, theme, phase, Associacao, trainers);
		} catch (const InvalidRequest & e) {
			cout << "\nEm " << e.getTotal() << " associados, " << e.getLate()
					<< " tem pagamentos em atraso. Impossivel criar evento!\n\n";
			sleep(1);
			return;
		}

		Associacao->pushToQueue(escola);
		cout << endl;
	}

	else {
		int numEsperado;
		cout << "\nIntroduza um numero esperado de Participantes: ";
		cin >> numEsperado;
		Conference * conferencia;
		try {
			conferencia = new Conference(event_request, event_organizers, date,
					local, theme, phase, Associacao, numEsperado);
		} catch (const InvalidRequest & e) {
			cout << "\nEm " << e.getTotal() << " associados, " << e.getLate()
					<< " tem pagamentos em atraso. Impossivel criar evento!\n\n";
			sleep(1);
			return;
		}

		Associacao->pushToQueue(conferencia);
		cout << endl;
	}

	cout << "\nPedido de Evento criado com sucesso!\n";
	sleep(1);
}

void removerEvento() {
	cout << endl << endl;
	cout << "--------------------------------------------- " << endl;
	cout << "ASSOCIACAO PORTUGUESA INVESTIGACAO CIENTIFICA" << endl;
	cout << "--------------------------------------------- " << endl;
	cout << endl << endl;

	cin.clear();
	cin.ignore(10000, '\n');
	int fase;
	cout << "Introduza a fase do evento a remover (1 ou 2): ";
	cin >> fase;
	if ((fase < 1) || (fase > 2)) {
		cout << "Nao introduziu uma fase válida.\n";
		return;
	}
	cin.clear();
	cin.ignore(10000, '\n');

	string data;
	cout << "Introduza a data do evento a remover (dd-mm-a): ";
	getline(cin, data);
	stringstream check_date(data);
	int temp_day, temp_month, temp_year;
	char garbage;
	check_date >> temp_day >> garbage >> temp_month >> garbage >> temp_year;
	if (check_date.fail()) {
		cout << "Nao introduziu a data no formato correto.\n";
		return;
	}

	try {
		Associacao->removeEvent(data, fase);
	} catch (const NoSuchDate & e) {
		cout << "\nNao existe nenhum evento com a data " << e.getDate() << endl;
		sleep(1);
		return;
	}

	cout << "\nEvento removido com sucesso!\n";
	sleep(1);
}

void alterarEvento() {
	cout << endl << endl;
	cout << "--------------------------------------------- " << endl;
	cout << "ASSOCIACAO PORTUGUESA INVESTIGACAO CIENTIFICA" << endl;
	cout << "--------------------------------------------- " << endl;
	cout << endl << endl;
	cin.clear();
	cin.ignore(10000, '\n');

	int fase;
	cout << "Introduza a fase do evento a alterar (1 ou 2): ";
	cin >> fase;
	if ((fase < 1) || (fase > 2)) {
		cout << "Nao introduziu uma fase válida.\n";
		return;
	}
	cin.clear();
	cin.ignore(10000, '\n');

	string data;
	cout << "Introduza a data do evento a alterar (dd-mm-a): ";
	getline(cin, data);
	stringstream check_date(data);
	int temp_day, temp_month, temp_year;
	char garbage;
	check_date >> temp_day >> garbage >> temp_month >> garbage >> temp_year;
	if (check_date.fail()) {
		cout
				<< "Nao introduziu a data no formato correto.\n Voltando ao menu principal...";
		return;
	}

	Event * alterar;
	try {
		alterar = Associacao->getEventByDatePhase(data, fase);
	} catch (const NoSuchDate & e) {
		cout << "\nNao existe nenhum evento com a data " << e.getDate() << endl;
		sleep(1);
		return;
	}

	string type = alterar->getType();
	bool typeevento; //true se for summer school e false se for conference
	if (type == "SummerSchool")
		typeevento = true;
	else if (type == "Conference")
		typeevento = false;

	cout << "\nQual o atributo que pretende mudar: " << endl;

	cout << "\t0: Data" << endl;
	cout << "\t1: Local" << endl;
	cout << "\t2: Tema" << endl;
	if (typeevento)
		cout << "\t3: Formadores" << endl;
	else
		cout << "\t3: Numero esperado de Participantes" << endl;

	cout << "\nInsira uma opcao: ";
	string opcao;
	getline(cin, opcao);

	if (!is_number(opcao)) {
		cout << "O valor introduzido nao e um inteiro.\n" << endl;
		return;
	}

	int escolha = stoi(opcao);

	switch (escolha) {
	case 0: {
		cout << "\nQual a nova data do evento? ";
		string data;
		getline(cin, data);
		stringstream check_date(data);
		int temp_day, temp_month, temp_year;
		char garbage;
		check_date >> temp_day >> garbage >> temp_month >> garbage >> temp_year;
		if (check_date.fail()) {
			cout << "Nao introduziu a data no formato correto.\n";
			return;
		}
		alterar->setDate(data);
		cout << "\nData alterada com sucesso!\n";
		break;
	}
	case 1: {
		cout << "\nQual o novo local do evento? ";
		string local;
		getline(cin, local);
		alterar->setLocal(local);
		cout << "\nLocal alterado com sucesso!\n";
		break;
	}
	case 2: {
		cout << "\nQual o novo tema do evento? ";
		string tema;
		getline(cin, tema);
		alterar->setTheme(tema);
		cout << "\nTema alterado com sucesso!\n";
		break;
	}
	case 3: {
		if (typeevento) {
			int numFormadores;
			cout << "\nIntroduza o numero de novos formadores do evento: ";
			cin >> numFormadores;
			list<Trainer *> trainers;
			cin.clear();
			cin.ignore(10000, '\n');
			for (int i = 0; i < numFormadores; i++) {
				string nome, instituicao;
				cout << "\nIntroduza o nome do " << i + 1 << "º Formador: ";
				getline(cin, nome);
				cout << "Introduza o nome da sua intituicao: ";
				getline(cin, instituicao);
				Trainer * trainer = new Trainer(nome, instituicao);
				trainers.push_back(trainer);
			}
			SummerSchool * novo = new SummerSchool(alterar->getRequest(),
					alterar->getOrganizers(), alterar->getDate(),
					alterar->getLocal(), alterar->getTheme(),
					alterar->getPhase(), Associacao, trainers);
			Associacao->removeEvent(alterar->getDate(), alterar->getPhase());
			Associacao->addEvent(novo);
			cout << "\nFormadores alterados com sucesso!\n";
			break;
		} else {
			int numEsperado;
			cout << "\nIntroduza o novo numero esperado de Participantes: ";
			cin >> numEsperado;
			Conference * novo = new Conference(alterar->getRequest(),
					alterar->getOrganizers(), alterar->getDate(),
					alterar->getLocal(), alterar->getTheme(),
					alterar->getPhase(), Associacao, numEsperado);
			Associacao->removeEvent(alterar->getDate(), alterar->getPhase());
			Associacao->addEvent(novo);
			cout
					<< "\nNumero esperado de Participantes alterado com sucesso!\n";
			break;
		}
	}
	default:
		cout << "Opcao Invalida" << endl;
		return;
	}

}

void verInfoEvento() {
	cout << endl << endl;
	cout << "--------------------------------------------- " << endl;
	cout << "ASSOCIACAO PORTUGUESA INVESTIGACAO CIENTIFICA" << endl;
	cout << "--------------------------------------------- " << endl;
	cout << endl << endl;
	cout << " Como deseja ver a informacao dos eventos?" << endl;
	cout << " 1 - Procurar pela Data" << endl;
	cout << " 2 - Procurar pela Fase" << endl;
	cout << " 3 - Mostrar todos" << endl;
	cout << " 4 - Listagem parcial em funcao da data" << endl;
	cout << " 5 - Listagem parcial em funcao do tipo de evento" << endl;
	cout << " 6 - Mostrar Pedidos de Eventos" << endl;

	int opcao = 0;
	cout << endl;
	cout << "Introduza uma opcao: ";
	while (opcao < 1 || opcao > 6) {
		if (cin >> opcao) {
			switch (opcao) {
			case 1: {
				cin.clear();
				cin.ignore(10000, '\n');

				string data;
				cout << "Introduza a data do evento (dd-mm-a): ";
				getline(cin, data);
				stringstream check_date(data);
				int temp_day, temp_month, temp_year;
				char garbage;
				check_date >> temp_day >> garbage >> temp_month >> garbage
						>> temp_year;
				if (check_date.fail()) {
					cout << "Nao introduziu a data no formato correto.\n";
					return;
				}

				vector<Event *> eventos;
				try {
					eventos = Associacao->getEventByDate(data);
				} catch (const NoSuchDate & e) {
					cout << "\nNao existe nenhum evento com a data "
							<< e.getDate() << endl;
					sleep(1);
					return;
				}

				cout << endl;
				for(size_t i = 0; i < eventos.size(); i++){
					cout << eventos.at(i)->showInfo();
				}

				if(eventos.size() == 0)
					cout << "\nNao existem eventos para essa data.\n";

				cout << endl;
				break;
			}
			case 2: {
				cin.clear();
				cin.ignore(10000, '\n');

				int phase;
				cout << "Introduza a fase dos eventos (1 ou 2): ";
				cin >> phase;
				if (phase < 1 || phase > 2) {
					cout << "Nao introduziu uma fase possivel.\n";
					return;
				}

				vector<Event *> eventos;
				for (size_t i = 0; i < Associacao->getEvents().size(); i++) {
					if (Associacao->getEvents().at(i)->getPhase() == phase)
						eventos.push_back(Associacao->getEvents().at(i));
				}
				if (eventos.empty()) {
					cout << "Nenhum evento cumpre os requisitos pedidos.\n";
				} else {
					for (size_t i = 0; i < eventos.size(); i++) {
						cout << endl;
						cout << eventos.at(i)->showInfo();
					}
				}
				break;
			}
			case 3: {
				for (size_t i = 0; i < Associacao->getEvents().size(); i++) {
					cout << endl;
					cout << Associacao->getEvents().at(i)->showInfo();
				}
				break;
			}
			case 4: {
				string inicial, final, ordem;
				cin.clear();
				cin.ignore(10000, '\n');
				cout << endl;
				cout << "Introduza a data inicial e data final: " << endl;
				cout << "Inicial: ";
				getline(cin, inicial);
				stringstream check_date(inicial);
				int temp_day, temp_month, temp_year;
				char garbage;
				check_date >> temp_day >> garbage >> temp_month >> garbage
						>> temp_year;
				if (check_date.fail()) {
					cout << "Nao introduziu a data no formato correto.\n";
					return;
				}
				cout << "Final: ";
				getline(cin, final);
				stringstream check_date2(final);
				check_date2 >> temp_day >> garbage >> temp_month >> garbage
						>> temp_year;
				if (check_date2.fail()) {
					cout << "Nao introduziu a data no formato correto.\n";
					return;
				}
				cout << "Ordem crescente ou decrescente? ";
				getline(cin, ordem);
				vector<Event *> eventos;

				for (Event * handle : Associacao->getEvents()) {

					stringstream date1(inicial);
					stringstream date2(final);
					stringstream date3(handle->getDate());

					int year1, year2, year3, month1, month2, month3, day1, day2,
							day3;
					char garbage;

					date1 >> day1 >> garbage >> month1 >> garbage >> year1;
					date2 >> day2 >> garbage >> month2 >> garbage >> year2;
					date3 >> day3 >> garbage >> month3 >> garbage >> year3;

					int inicialDate = (year1 * 10000) + (month1 * 100) + day1;
					int endDate = (year2 * 10000) + (month2 * 100) + day2;
					int eventDate = (year3 * 10000) + (month3 * 100) + day3;

					if (eventDate >= inicialDate && eventDate <= endDate) {
						eventos.push_back(handle);
					}

				}

				if (eventos.empty()) {
					cout << "Nenhum evento cumpre os requisitos pedidos.\n";
				}

				if (ordem == "crescente") {
					sort(eventos.begin(), eventos.end(), cmpDate);
				} else if (ordem == "decrescente") {
					sort(eventos.begin(), eventos.end(), cmpDate);
					reverse(eventos.begin(), eventos.end());
				} else {
					cout << "Opcao inválida";
					break;
				}

				for (size_t i = 0; i < eventos.size(); i++) {
					cout << endl;
					cout << eventos.at(i)->showInfo();
				}

				break;
			}
			case 5: {
				vector<Event *> eventos;
				string tipo;
				cin.clear();
				cin.ignore(10000, '\n');
				cout
						<< "\nIntroduza o tipo de eventos (SummerSchool/Conference): ";
				getline(cin, tipo);
				for (size_t i = 0; i < Associacao->getEvents().size(); i++) {
					if (Associacao->getEvents().at(i)->getType() == tipo)
						eventos.push_back(Associacao->getEvents().at(i));
				}
				if (eventos.empty()) {
					cout << "Nenhum evento cumpre os requisitos pedidos.\n";
				} else {
					for (size_t i = 0; i < eventos.size(); i++) {
						cout << endl;
						cout << eventos.at(i)->showInfo();
					}
				}
				break;
			}
			case 6: {

				cout << Associacao->showRequests() << endl;
				break;
			}
			default:
				cout << "Opcao invalida. Introduza uma nova opcao: ";
			}
		}

		else {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Opcao invalida. Introduza uma nova opcao: ";
		}
	}
}

void organizarEventos() {
	cout << endl << endl;
	cout << "--------------------------------------------- " << endl;
	cout << "ASSOCIACAO PORTUGUESA INVESTIGACAO CIENTIFICA" << endl;
	cout << "--------------------------------------------- " << endl;
	cout << endl << endl;
	cout << "Qual o criterio para organizar os eventos: " << endl;
	cout << "0 - Local\n";
	cout << "1 - Tema\n";
	cout << "2 - Data\n";
	cout << "3 - Fase\n";

	int opcao;
	cout << "\nIntroduza uma opcao: ";
	cin >> opcao;
	cin.clear();
	cin.ignore(1000, '\n');
	if (cin.fail() || opcao > 3 || opcao < 0) {
		cout << "\nO valor introduzido nao e valido.\n";
		return;
	}
	string type;

	if (opcao == 0)
		type = "local";
	else if (opcao == 1)
		type = "theme";
	else if (opcao == 2)
		type = "date";
	else
		type = "phase";

	Associacao->sortEvents(type);

	cout << "\nEventos organizados com sucesso!\n";

}

//-----------------------COTAS-------------------------//

void pagarCotas() {
	cout << endl << endl;
	cout << "--------------------------------------------- " << endl;
	cout << "ASSOCIACAO PORTUGUESA INVESTIGACAO CIENTIFICA" << endl;
	cout << "--------------------------------------------- " << endl;
	cout << endl << endl;
	string tempID;
	int uniqueID;
	cout << "Introduza o Identificador Unico do Associado: ";
	cin.clear();
	cin.ignore(10000, '\n');
	getline(cin, tempID);

	if (!is_number(tempID)) {
		cout << "O valor introduzido nao e um inteiro.\n" << endl;
		return;
	}

	uniqueID = stoi(tempID);

	Associate * associado;
	try {
		associado = Associacao->getAssoById(uniqueID);
	} catch (const NoSuchID & e) {
		cout << "\nNao existe nenhum associado com o ID: " << e.getID() << endl;
		sleep(1);
		return;
	}

	cout << "Qual o ano referente ao pagamento: ";
	int year;
	cin >> year;

	try {
		associado->payYear(year);
	} catch (const NotUpToDate & e) {

		cout << "\nNao foi possivel efetuar o pagamento referente ao ano "
				<< e.getYear()
				<< " dado que o ultimo pago por este associado e "
				<< e.getLast() << ".";
		return;
	} catch (const NotEnoughMoney & e) {
		cout
				<< "\nNao foi possivel efetuar o pagamento pois o associado nao possui dinheiro suficiente.\n";
		return;
	} catch (const AlreadyPaid & e) {
		cout << "\nO associado ja efetuou o pagamento do ano " << e.getYear()
				<< ".\n";
		return;
	}

	cout << "\nPagamente efetuado com sucesso.\n";
	return;
}

void pagarTodasCotas() {

	string info = "";

	info = Associacao->updatePayment();

	if (info.empty())
		cout << "Todos os pagamentos efetuados com sucesso.\n";
	else
		cout << endl << info;

	return;

}

void verAssociadosCotas() {
	cout << endl << endl;
	cout << "--------------------------------------------- " << endl;
	cout << "ASSOCIACAO PORTUGUESA INVESTIGACAO CIENTIFICA" << endl;
	cout << "--------------------------------------------- " << endl;
	cout << endl << endl;

	Associacao->updateAllAssociates();

	cout << "Ano Corrente: " << to_string(Associacao->getCurrentYear()) << endl;
	cout << "\nAssociados com as cotas em atraso: \n";

	for (auto it = Associacao->getAssociates().begin();
			it != Associacao->getAssociates().end(); it++) {

		if ((*it)->getStatus() != "contributor") {

			cout << "\t -" << (*it)->getName() << ", ID = "
					<< (*it)->getUniqueID() << ", ultimo ano pago: "
					<< to_string((*it)->getPaidYears().back()) << endl;

		}

	}

	return;

}

//-----------------------REDE--------------------------//

void divulgarEmail() {
	cout << endl << endl;
	cout << "--------------------------------------------- " << endl;
	cout << "ASSOCIACAO PORTUGUESA INVESTIGACAO CIENTIFICA" << endl;
	cout << "--------------------------------------------- " << endl;
	cout << endl << endl;
	cout << "Introduza o Identificador Unico do Associado a enviar o Mail: ";
	cin.clear();
	int uniqueID;
	string tempID;
	cin.ignore(10000, '\n');
	getline(cin, tempID);

	if (!is_number(tempID)) {
		cout << "O valor introduzido nao e um inteiro.\n" << endl;
		return;
	}

	uniqueID = stoi(tempID);
	Associate * associate;

	try {
		associate = Associacao->getAssoById(uniqueID);
	} catch (NoSuchID & e) {
		cout << "\nNao existe nenhum associado com o ID: " << e.getID() << endl;
		sleep(1);
		return;
	}

	if (!associate->shareNetwork()) {
		cout
				<< "\nO associado nao tem permissoes para partilhar mensagens na rede.\nPague as cotas em atraso para resolver\n";
		return;
	}

	string title, body, date;

	cout << "Titulo: ";
	getline(cin, title);
	cout << "\nMensagem: \n";
	getline(cin, body);
	cout << "\nData: ";
	getline(cin, date);
	cout << endl;
	stringstream check_date(date);
	int temp_day, temp_month, temp_year;
	char garbage;
	check_date >> temp_day >> garbage >> temp_month >> garbage >> temp_year;
	if (check_date.fail()) {
		cout << "\nNao introduziu a data no formato correto.\n";
		return;
	}
	Mail * newMail = new Mail(associate, title, body, date);

	Rede->addMail(newMail);

	cout << "\nMail enviado com sucesso!\n";
	sleep(1);
	return;

}

void verEmails() {
	cout << endl << endl;
	cout << "--------------------------------------------- " << endl;
	cout << "ASSOCIACAO PORTUGUESA INVESTIGACAO CIENTIFICA" << endl;
	cout << "--------------------------------------------- " << endl;
	cout << endl << endl;
	cout << "Introduza o seu Identificador Unico: ";
	cin.clear();
	int uniqueID;
	string tempID;
	cin.ignore(10000, '\n');
	getline(cin, tempID);

	if (!is_number(tempID)) {
		cout << "O valor introduzido nao e um inteiro.\n" << endl;
		return;
	}

	uniqueID = stoi(tempID);
	Associate * associate;

	try {
		associate = Associacao->getAssoById(uniqueID);
	} catch (NoSuchID & e) {
		cout << "\nNao existe nenhum associado com o ID: " << e.getID() << endl;
		sleep(1);
		return;
	}

	if (!associate->accessNetwork()) {
		cout
				<< "\nO associado nao tem permissoes para ver mensagens na rede.\nPague as cotas em atraso para resolver\n";
		return;
	}

	cout << "\nQual a mensagem que pretende ver:\n";

	for (size_t t = 0; t < Rede->getMails().size(); t++) {
		cout << "\t" << t << ": " << Rede->getMails().at(t)->getTitle() << endl;
	}

	cout << "\nInsira a sua opcao: ";

	size_t t = 0;
	cin >> t;

	if((t < 0) || (t > (Rede->getMails().size() - 1))){
		cout << "\nOpcao invalida.\n";
		return;
	}

	cout << "\nMensagem partilhada por "
			<< Rede->getMails().at(t)->getAuthor()->getName() << ": \n";
	cout << "Titulo: " << Rede->getMails().at(t)->getTitle() << endl;
	cout << "Mensagem: " << Rede->getMails().at(t)->getBody() << endl;
	cout << "Data: " << Rede->getMails().at(t)->getDate() << endl;

	return;

}

void organizarMails() {
	cout << endl << endl;
	cout << "--------------------------------------------- " << endl;
	cout << "ASSOCIACAO PORTUGUESA INVESTIGACAO CIENTIFICA" << endl;
	cout << "--------------------------------------------- " << endl;
	cout << endl << endl;
	cout << "Qual o criterio para organizar os emails: " << endl;
	cout << "0 - Titulo\n";
	cout << "1 - Data\n";

	int opcao;
	cout << "\nIntroduza uma opcao: ";
	cin >> opcao;
	if (cin.fail() || opcao > 1 || opcao < 0) {
		cout << "\nO valor introduzido nao e valido.\n";
		return;
	}

	string type;

	if (opcao == 0)
		type = "title";
	else if (opcao == 1)
		type = "date";

	Rede->sortMails(type);

	cout << "\nMails organizados com sucesso!\n";
}
