#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <iomanip>
#include "Driver.h"
#include "Line.h"
#include "Company.h"
#include <cctype>
#include "Constants.h"

using namespace std;

vector<string> Iniciar();


vector <string> iniciar = Iniciar();


Company Empresa(iniciar.at(0), iniciar.at(1), iniciar.at(2), iniciar.at(3));



//================= USEFUL FUNCTIONS =====================
string NumberToDay(int day);

string formatingCout(int number);

bool is_number(const string& s)
{
	string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

int convert(const string& s) {
	return stoi(s);
}

string company_name_capitalized() {
	int i = 0;
	string str = iniciar.at(0);
	while (i < iniciar.at(0).size()) {
		str[i] = toupper(str[i]);
		i++;
	}
	return str;
}

//=========================================================





//===================FUNCOES REFERENTES A LINHAS====================


//funcao sem parametros que serve para dar display de todas as Lines presentes no vetor
void displayLinhas() {
	Empresa.showAllLines();
}

//funcao sem parametros que tem como finalidade adicionar uma nova linha (struct) ao vetor com todas as Lines 
void adicionarLinha() {
	Line novaLinha;                  //a nova linha a ser criada
	vector<string> novas_paragens;    //o vetor que ira conter as novas paragens da linha a criar
	vector<int> lines_used_ids = Empresa.lines_used_ids();                     //este vetor tem como funcionalidade testar se o id escolhido para a nova linha já está em uso

	vector<int> intervalos_novos;     //o vetor que ira conter os novos intervalos da linha a criar
	int id, freq, numero_de_paragens, intervalo;
	string paragem;
	bool id_good = false;
	bool freq_good = false;
	bool paragens_good = false;
	bool intervalos_good = false;
	while (!id_good) {        //loop com a finalidade de obrigar o utilizador a inserir um valor valido
		cout << "\n===================================" << endl;
		cout << "Qual o novo ID da linha: " << endl;
		cin >> id;
		cin.ignore();
		if (find(lines_used_ids.begin(), lines_used_ids.end(), id) != lines_used_ids.end())
			cout << "ID ja usado por outra linha. Por favor escolha outro." << endl;
		else id_good = true;
	}
	
	while (!freq_good) {       //loop com a finalidade de obrigar o utilizador a inserir um valor valido
		cout << "\nQual a frequencia: " << endl;
		if (!(cin >> freq)) {
			cout << "A frequencia nao e valida. Por favor, insira outra." << endl;
			cin.clear();
		}
		else freq_good = true;
		cin.ignore(1000, '\n');
	}

	while (!paragens_good) {         //loop com a finalidade de obrigar o utilizador a inserir um valor valido
		cout << "\nQuantas paragens tera a linha? " << endl;
		if (!(cin >> numero_de_paragens) || numero_de_paragens < 2) {
			cout << "Numero invalido de paragens. Por favor, insira novamente." << endl;
			cin.clear();
		}
		else paragens_good = true;
		cin.ignore(100,'\n');
	}
	//cin.ignore(); 
	cout << endl;
	for (int i = 0; i < numero_de_paragens; i++) //ciclo para adicionar as novas paragens ao vetor. requer que o utilizador diga quantas parafens querera antes de ser inicializado.
	{
		int j = i;
		cout << "Paragem numero " << ++j << ": ";
		getline(cin, paragem);
		novas_paragens.push_back(paragem);
	}
	cout << endl;
	while (!intervalos_good) {
		for (int i = 0; i < numero_de_paragens - 1; i++)
		{
			int j = i;
			++j;
			int k = j;
			++k;
			cout << "Intervalo entre as paragens " << novas_paragens.at(j-1) << " e " << novas_paragens.at(j) << ": ";
			if (!(cin >> intervalo))
			{
				cout << "Intervalo invalido. Por favor insira todos novamente." << endl;
				cin.clear();
				intervalos_novos.erase(intervalos_novos.begin(), intervalos_novos.end());
				intervalos_good = false;
				break;
			}
			else {
				intervalos_novos.push_back(intervalo);
				intervalos_good = true;
			}
		}
		cin.ignore(1000, '\n');
	}
	cout << endl;

	Empresa.newLine(id, freq, novas_paragens, intervalos_novos);

	Empresa.getLinhaById(id).showInfo();
}

//funcao sem parametros que tem como finalidade remover uma linha ja existente
void removerLinhaDoVetor() {
	cout << "\n===================================" << endl;
	cout << "Qual o identificador da linha a ser removido?" << endl;
	int id;
	bool id_good = false;
	vector<int> lines_used_ids = Empresa.lines_used_ids();
	while (!id_good) {
		if (!(cin >> id) || find(lines_used_ids.begin(), lines_used_ids.end(), id) == lines_used_ids.end()) {
			cout << "ID nao e valido ou nao existe. Por favor introduza outro" << endl;
			cin.clear();
		}
		else id_good = true;
		cin.ignore(100, '\n');
	}
	ptrdiff_t  j = find(lines_used_ids.begin(), lines_used_ids.end(), id) - lines_used_ids.begin();
	Empresa.removeLines(id, j);

	cout << "Linha Removida!" << endl;
}

//funcao semelhante a anterior (adicionarLinha()) que da a possibilidade ao utilizador de guardar a nova linha criada ao documento original, util para, em caso de engano, nao se adicionar ao ficheiro
void alterar_ficheiro_linhas() {
	Empresa.rewriteFileLines(Empresa.getLinesFile());
}

//funcao sem parametros que tem como finalidade alterar uma linha ja existente.
void alterarLinha() {
	cout << "\n===================================" << endl;
	cout << "Qual o identificador da linha a ser alterada?" << endl;
	int id;
	bool id_good = false;
	vector<int> lines_used_ids = Empresa.lines_used_ids();
	
	while (!id_good) {
		if (!(cin >> id) || find(lines_used_ids.begin(), lines_used_ids.end(), id) == lines_used_ids.end()) {   //verificar se o id introduzido esta ou nao presente nas Lines ja existentes
			cout << "ID nao e valido ou nao existe. Por favor introduza outro" << endl;
			cin.clear();
		}
		else id_good = true;
		cin.ignore(100, '\n');
	}
	cout << "\nQual a caracteristica que pretende mudar?\n 1 - Frequencia\n 2 - Lista de paragens e respetivos intervalos" << endl;
	cout << "\nInsira uma opcao: ";
	int escolha;
	bool escolha_good = false;
	while (!escolha_good) {
		if (!(cin >> escolha)) {
			cout << "Por favor, insira uma opcao valida" << endl;
			cin.clear();
		}
		else escolha_good = true;
		cin.ignore(100, '\n');
	}
	bool paragens_good = false;
	bool intervalos_good = false;
	int numero_de_paragens, intervalo;
	string paragem;
	vector<string> novas_paragens;
	vector <int> novos_intervalos;
	switch (escolha) {
	case 1:
		cout << "\nQual a nova frequencia?" << endl;
		int freq_nova;
		cin >> freq_nova;
		Empresa.getLinhaById(id).setFreq(freq_nova);
		break;
	case 2:
		cout << "\nA lista de paragens original: ";
		for (size_t posp = 0; posp < Empresa.getLinhaById(id).getBusStops().size(); posp++) //posp percorre todas as paragens
		{
			if (posp == Empresa.getLinhaById(id).getBusStops().size() - 1)
				cout << Empresa.getLinhaById(id).getBusStops().at(posp) << '.';
			else cout << Empresa.getLinhaById(id).getBusStops().at(posp) << ", ";
		}
		cout << endl << "Com os seguintes intervalos entre as paragens: ";
		for (size_t posh = 0; posh < Empresa.getLinhaById(id).getTimings().size(); posh++) //posh percorre os intervalos de tempo entre paragens
		{
			if (posh == Empresa.getLinhaById(id).getTimings().size() - 1)
				cout << Empresa.getLinhaById(id).getTimings().at(posh) << '.';
			else cout << Empresa.getLinhaById(id).getTimings().at(posh) << ", ";
		}


		while (!paragens_good) {
			cout << endl << "\nQuantas paragens tera a linha modificada? " << endl;
			if (!(cin >> numero_de_paragens)) {
				cout << "Numero invalido de paragens. Por favor, insira novamente." << endl;
				cin.clear();
			}
			else paragens_good = true;
			cin.ignore();
		}
		cout << endl;
		for (int i = 0; i < numero_de_paragens; i++)          //criar um novo vetor que contera as paragens que o utilizador modificou 
		{
			int j = i;
			cout << "Paragem numero " << ++j << ": ";
			getline(cin, paragem);
			novas_paragens.push_back(paragem);
		}
		Empresa.getLinhaById(id).setBusStops(novas_paragens);
		cout << endl;
		while (!intervalos_good) {
			for (int i = 0; i < numero_de_paragens - 1; i++)       //ciclo para introduzir os intervalos entre cada par de paragens
			{
				int j = i;
				++j;
				int k = j;
				++k;
				cout << "Intervalo entre as paragens " << j << " e " << k << ": ";
				if (!(cin >> intervalo))
				{
					cout << "Intervalo invalido. Por favor insira todos novamente." << endl;
					cin.clear();
					novos_intervalos.erase(novos_intervalos.begin(), novos_intervalos.end());
					intervalos_good = false;
					break;
				}
				else {
					novos_intervalos.push_back(intervalo);
					intervalos_good = true;
				}
			}
			cin.ignore(1000, '\n');
		}
		Empresa.getLinhaById(id).setTimings(novos_intervalos);
		break;
	default:
		break;
	}
}

//funcao com uma parametro, tipo string - nome da paragem, que devolve um vetor de inteiros contendo os ids de todas as linhas que contem essa mesma paragem
vector <int> linhas_com_paragem_id(string paragem) {
	vector <int> id_das_linhas = Empresa.getLinhaWithStop(paragem);
	return id_das_linhas;
}

//funcao sem parametros que tem como funcionalidade dar display do horario de uma linha
void horario_de_uma_linha() {
	cout << "\n===================================" << endl;
	cout << "Qual o identificador da linha?" << endl;
	int id;
	bool id_good = false;
	vector<int> lines_used_ids = Empresa.lines_used_ids();

	while (!id_good) {
		if (!(cin >> id) || find(lines_used_ids.begin(), lines_used_ids.end(), id) == lines_used_ids.end()) {   //verificar se o id introduzido esta ou nao presente nas Lines ja existentes
			cout << "ID nao e valido ou nao existe. Por favor introduza outro" << endl;
			cin.clear();
		}
		else id_good = true;
		cin.ignore(100, '\n');
	}
	cout << endl;

	vector <pair<string, vector<int>>> test = Empresa.getTimesLineForward(id, MINUTO_INICIAL, MINUTO_FINAL);
	cout << "Sentido " << test.at(0).first << " -> " << test.at(test.size() - 1).first << endl;
	for (size_t t = 0; t < test.size(); t++) {
		cout << setw(test.at(t).first.size() + 4) << test.at(t).first;
	}
	cout << endl;
	size_t nr_paragens = test.at(0).second.size();
	for (size_t k = 0; k < nr_paragens; k++) {
		for (size_t t = 0; t < test.size(); t++) {
			string tempostring;
			if (test.at(t).second.at(k) % 60 == 0 && (test.at(t).second.at(k) / 60) >= 24)
				tempostring = "0" + to_string(test.at(t).second.at(k) / 60 - 24) + ":00";
			else if (test.at(t).second.at(k) % 60 == 0 && (test.at(t).second.at(k) / 60) < 24)
				tempostring = to_string(test.at(t).second.at(k) / 60) + ":00";
			else if (test.at(t).second.at(k) % 60 < 10 && (test.at(t).second.at(k) / 60) >= 24)
				tempostring = "0" + to_string(test.at(t).second.at(k) / 60 - 24) + ":0" + to_string(test.at(t).second.at(k) % 60);
			else if (test.at(t).second.at(k) % 60 < 10 && (test.at(t).second.at(k) / 60) < 24)
				tempostring = to_string(test.at(t).second.at(k) / 60) + ":0" + to_string(test.at(t).second.at(k) % 60);
			else if ((test.at(t).second.at(k) / 60) >= 24)
				tempostring = "0" + to_string(test.at(t).second.at(k) / 60 - 24) + ":" + to_string(test.at(t).second.at(k) % 60);
			else
				tempostring = to_string(test.at(t).second.at(k) / 60) + ":" + to_string(test.at(t).second.at(k) % 60);
			cout << setw(test.at(t).first.size() + 4) << tempostring;
		}
		cout << endl;
	}
	cout << endl;
	
	//================================ HORARIO NO SENTIDO CONTRARIO ======================================
	vector <pair<string, vector<int>>> test_contrario = Empresa.getTimesLineBackward(id, MINUTO_INICIAL, MINUTO_FINAL);
	cout << "Sentido " << test_contrario.at(0).first << " -> " << test_contrario.at(test_contrario.size() - 1).first << endl;
	for (size_t t = 0; t < test_contrario.size(); t++) {
		cout << setw(test_contrario.at(t).first.size() + 4) << test_contrario.at(t).first;
	}
	cout << endl;
	for (size_t k = 0; k < nr_paragens; k++) {
		for (size_t t = 0; t < test_contrario.size(); t++) {
			string tempostring;
			if (test_contrario.at(t).second.at(k) % 60 == 0 && (test_contrario.at(t).second.at(k) / 60) >= 24)
				tempostring = "0" + to_string(test_contrario.at(t).second.at(k) / 60 - 24) + ":00";
			else if (test_contrario.at(t).second.at(k) % 60 == 0 && (test_contrario.at(t).second.at(k) / 60) < 24)
				tempostring = to_string(test_contrario.at(t).second.at(k) / 60) + ":00";
			else if (test_contrario.at(t).second.at(k) % 60 < 10 && (test_contrario.at(t).second.at(k) / 60) >= 24)
				tempostring = "0" + to_string(test_contrario.at(t).second.at(k) / 60 - 24) + ":0" + to_string(test_contrario.at(t).second.at(k) % 60);
			else if (test_contrario.at(t).second.at(k) % 60 < 10 && (test_contrario.at(t).second.at(k) / 60) < 24)
				tempostring = to_string(test_contrario.at(t).second.at(k) / 60) + ":0" + to_string(test_contrario.at(t).second.at(k) % 60);
			else if ((test_contrario.at(t).second.at(k) / 60) >= 24)
				tempostring = "0" + to_string(test_contrario.at(t).second.at(k) / 60 - 24) + ":" + to_string(test_contrario.at(t).second.at(k) % 60);
			else
				tempostring = to_string(test_contrario.at(t).second.at(k) / 60) + ":" + to_string(test_contrario.at(t).second.at(k) % 60);
			cout << setw(test_contrario.at(t).first.size() + 4) << tempostring;
		}
		cout << endl;
	}
}

//funcao sem parametros que tem como funcionalidade dar display do horario de uma paragem
void horario_de_uma_paragem() {
	cout << "\n===================================" << endl;
	cout << "Qual o nome da paragem?" << endl;
	string nome;
	getline(cin, nome);
	bool id_good = false;
	vector<int> linhas_com_paragem = Empresa.getLinhaWithStop(nome);

	while (!id_good) {
		if (linhas_com_paragem.empty()) {
			cout << "A Paragem nao e valida ou nao existe. Por favor introduza outra" << endl;
		}
		else id_good = true;

	}
	cout << endl;

	vector<pair<int, vector<int>>> test = Empresa.getTimesStopForward(nome, MINUTO_INICIAL, MINUTO_FINAL);

	for (size_t t = 0; t < test.size(); t++) {

		cout << "Horario da paragem " << nome << " na linha " << test.at(t).first << " no sentido " << Empresa.getLinhaById(test.at(t).first).getBusStops().at(0) << " -> " << Empresa.getLinhaById(test.at(t).first).getBusStops().at(Empresa.getLinhaById(test.at(t).first).getBusStops().size() - 1) << ": ";
		cout << endl;
		for (size_t k = 0; k < test.at(t).second.size(); k++) {
			string tempostring;
			if (test.at(t).second.at(k) % 60 == 0 && (test.at(t).second.at(k) / 60) >= 24)
				tempostring = "0" + to_string(test.at(t).second.at(k) / 60 - 24) + ":00";
			else if (test.at(t).second.at(k) % 60 == 0 && (test.at(t).second.at(k) / 60) < 24)
				tempostring = to_string(test.at(t).second.at(k) / 60) + ":00";
			else if (test.at(t).second.at(k) % 60 < 10 && (test.at(t).second.at(k) / 60) >= 24)
				tempostring = "0" + to_string(test.at(t).second.at(k) / 60 - 24) + ":0" + to_string(test.at(t).second.at(k) % 60);
			else if (test.at(t).second.at(k) % 60 < 10 && (test.at(t).second.at(k) / 60) < 24)
				tempostring = to_string(test.at(t).second.at(k) / 60) + ":0" + to_string(test.at(t).second.at(k) % 60);
			else if ((test.at(t).second.at(k) / 60) >= 24)
				tempostring = "0" + to_string(test.at(t).second.at(k) / 60 - 24) + ":" + to_string(test.at(t).second.at(k) % 60);
			else
				tempostring = to_string(test.at(t).second.at(k) / 60) + ":" + to_string(test.at(t).second.at(k) % 60);
			
			if ((k + 1) % 8 == 0)
				cout << setw(4) << tempostring << endl;
			else
				cout << setw(4) << tempostring << "\t";
			

		}
		cout << endl << endl;
	}

	//================================ HORARIO NO SENTIDO CONTRARIO ======================================

	vector<pair<int, vector<int>>> test2 = Empresa.getTimesStopBackward(nome, MINUTO_INICIAL, MINUTO_FINAL);

	for (size_t t = 0; t < test2.size(); t++) {

		cout << "Horario da paragem " << nome << " na linha " << test2.at(t).first << " no sentido " << Empresa.getLinhaById(test2.at(t).first).getBusStops().at(Empresa.getLinhaById(test2.at(t).first).getBusStops().size() - 1) << " -> " << Empresa.getLinhaById(test2.at(t).first).getBusStops().at(0) << ": ";
		cout << endl;
		for (size_t k = 0; k < test2.at(t).second.size(); k++) {
			string tempostring;
			if (test2.at(t).second.at(k) % 60 == 0 && (test2.at(t).second.at(k) / 60) >= 24)
				tempostring = "0" + to_string(test2.at(t).second.at(k) / 60 - 24) + ":00";
			else if (test2.at(t).second.at(k) % 60 == 0 && (test2.at(t).second.at(k) / 60) < 24)
				tempostring = to_string(test2.at(t).second.at(k) / 60) + ":00";
			else if (test2.at(t).second.at(k) % 60 < 10 && (test2.at(t).second.at(k) / 60) >= 24)
				tempostring = "0" + to_string(test2.at(t).second.at(k) / 60 - 24) + ":0" + to_string(test2.at(t).second.at(k) % 60);
			else if (test2.at(t).second.at(k) % 60 < 10 && (test2.at(t).second.at(k) / 60) < 24)
				tempostring = to_string(test2.at(t).second.at(k) / 60) + ":0" + to_string(test2.at(t).second.at(k) % 60);
			else if ((test2.at(t).second.at(k) / 60) >= 24)
				tempostring = "0" + to_string(test2.at(t).second.at(k) / 60 - 24) + ":" + to_string(test2.at(t).second.at(k) % 60);
			else
				tempostring = to_string(test2.at(t).second.at(k) / 60) + ":" + to_string(test2.at(t).second.at(k) % 60);
			
			if ((k+1) % 8 == 0)
				cout << setw(4) << tempostring << endl;
			else
				cout << setw(4) << tempostring << "\t";
		}
		cout << endl << endl;
	}
}

//funcao sem parametros que tem como funcionalidade dar o display do tempo entre duas paragens na mesma linha
bool sortTempo(pair<int, int> par1, pair <int, int> par2) {
	return (par1.second < par2.second);
}

void tempo_entre_paragens() {
	cout << "\n===================================" << endl;
	cout << "Insira duas paragens:\n - Primeira Paragem: ";
	string paragem1;
	getline(cin, paragem1);
	cout << " - Segunda Paragem: ";
	string paragem2;
	getline(cin, paragem2);
	vector <pair <int, int>> tempos = Empresa.getTimeBetweenStops(paragem1, paragem2);
	sort(tempos.begin(), tempos.end(), sortTempo);  //organizar o vetor, ordem crescente de acordo com o tempo gasto
	cout << endl;

	vector<pair<int, vector<string>>> Paragens = Empresa.getPathBetweenStops(paragem1, paragem2);

	// Para paragens que estão em linhas diferentes
	if (tempos.empty())
	{
		vector <int> linhas1 = Empresa.getLinhaWithStop(paragem1);
		vector <int> linhas2 = Empresa.getLinhaWithStop(paragem2);
		vector <string> paragenscomuns;

		//paragem em comum entre as linhas diferentes
		for (size_t i = 0; i < linhas1.size(); i++) {
			vector <string> paragens1 = Empresa.getLinhaById(linhas1.at(i)).getBusStops();
			for (size_t t = 0; t < linhas2.size(); t++) {
				vector <string> paragens2 = Empresa.getLinhaById(linhas2.at(t)).getBusStops();
				for (size_t n = 0; n < paragens1.size(); n++) {
					for (size_t m = 0; m < paragens2.size(); m++) {
						if (paragens1.at(n) == paragens2.at(m))
							paragenscomuns.push_back(paragens1.at(n));
					}
				}
			}
		}
		if (paragenscomuns.empty())
			cout << "Nao e possivel efetuar uma ligacao entre ambas as paragens\n";

		else {
			{
				vector <int> linhas1 = Empresa.getLinhaWithStop(paragem1);
				vector <int> linhas2 = Empresa.getLinhaWithStop(paragem2);
				vector <string> paragenscomuns;

				//paragem em comum entre as linhas diferentes
				for (size_t i = 0; i < linhas1.size(); i++) {
					vector <string> paragens1 = Empresa.getLinhaById(linhas1.at(i)).getBusStops();
					for (size_t t = 0; t < linhas2.size(); t++) {
						vector <string> paragens2 = Empresa.getLinhaById(linhas2.at(t)).getBusStops();
						for (size_t n = 0; n < paragens1.size(); n++) {
							for (size_t m = 0; m < paragens2.size(); m++) {
								if (paragens1.at(n) == paragens2.at(m)) {
									bool igual = false;
									for (size_t q = 0; q < paragenscomuns.size(); q++) {
										if (paragens1.at(n) == paragenscomuns.at(q))
											igual = true;
									}
									if (!igual)
										paragenscomuns.push_back(paragens1.at(n));
								}
							}
						}
					}
				}

				if (paragenscomuns.empty())
					cout << "Nao e possivel efetuar uma ligacao entre ambas as paragens\n";
				else {
					cout << "Percurso e Tempo entre as paragens " << paragem1 << " e " << paragem2 << ": " << endl;
					for (size_t q = 0; q < paragenscomuns.size(); q++) {
						vector <pair <int, int>> tempos1 = Empresa.getTimeBetweenStops(paragem1, paragenscomuns.at(q));
						
						sort(tempos1.begin(), tempos1.end(), sortTempo);

						vector <pair <int, vector <string>>> Paragens11 = Empresa.getPathBetweenStops(paragem1, paragenscomuns.at(q));

						vector <pair <int, int>> tempos2 = Empresa.getTimeBetweenStops(paragenscomuns.at(q), paragem2);
						sort(tempos2.begin(), tempos2.end(), sortTempo);

						vector <pair <int, vector <string>>> Paragens22 = Empresa.getPathBetweenStops(paragenscomuns.at(q), paragem2);

						for (size_t t = 0; t < tempos1.size(); t++) {
							for (size_t n = 0; n < tempos2.size(); n++) {
								cout << endl;
								int tempototal = tempos1.at(t).second + tempos2.at(n).second;
								cout << "Tempo: ";
								if (tempototal >= 60)
									cout << tempototal / 60 << "h e " << tempototal % 60 << " min.";
								else
									cout << tempototal << " min.";
								cout << endl;

								cout << " - Linha " << tempos1.at(t).first << ": ";

								for (size_t posp = 0; posp < Paragens11.size(); posp++) //posp percorre o vetor de busStop em cada linha
								{
									if (Paragens11.at(posp).first == tempos1.at(t).first) {
										for (size_t k = 0; k < Paragens11.at(posp).second.size(); k++)
											cout << Paragens11.at(posp).second.at(k) << ", ";
									}
								}
								cout << paragenscomuns.at(q) << ".";

								cout << endl;

								cout << " - Linha " << tempos2.at(n).first << ": ";

								for (size_t posp = 0; posp < Paragens22.size(); posp++) //posp percorre o vetor de busStop em cada linha
								{
									if (Paragens22.at(posp).first == tempos2.at(n).first) {
										for (size_t k = 0; k < Paragens22.at(posp).second.size(); k++)
											cout << Paragens22.at(posp).second.at(k) << ", ";
									}
								}
								cout << paragem2 << ".";
								cout << endl;
							}
						}
					}
				}
			}
		}
	}

	//Para paragens que estão na mesma linha
	else
	{
		cout << "Percurso e Tempo entre as paragens " << paragem1 << " e " << paragem2 << ": " << endl;
		for (size_t t = 0; t < tempos.size(); t++) {
			cout << endl;
			cout << "Tempo: ";
			if (tempos.at(t).second >= 60)
				cout << tempos.at(t).second / 60 << "h e " << tempos.at(t).second % 60 << " min.";
			else
				cout << tempos.at(t).second << " min.";
			cout << endl;
			cout << " - Linha " << tempos.at(t).first << ": ";
			for (size_t posp = 0; posp < Paragens.size(); posp++) //posp percorre o vetor de busStop em cada linha
			{
				if (Paragens.at(posp).first == tempos.at(t).first) {
					for (size_t k = 0; k < Paragens.at(posp).second.size(); k++)
						cout << Paragens.at(posp).second.at(k) << ", ";
				}
			}
			cout << paragem2 << "." << endl;
		}
	}
}

//=========================================================================







//===================FUNCOES REFERENTES A CONDUTORES====================


//funcao sem parametros que da display de todos os Drivers presentes no vetor
void displayCondutores() {
	Empresa.showAllDrivers();
}

//funcao sem parametros que tem como finalidade adicionar um novo condutor ao vetor
void adicionarCondutor() {
	string name;
	
	cout << "\n===================================" << endl;
	cout << "Qual o nome do novo condutor? " << endl;
	getline(cin, name);
	bool id_good = false;
	bool max_dia_good = false;
	bool max_sem_good = false;
	bool des_good = false;
	cout << "\nQual o identificador unico? ";
	int id, maxDayWorkingTime, maxWeekWorkingTime, minRestTime;
	while (!id_good) {
		if (!(cin >> id) || Empresa.existsDrivers(id)) { //verifica se o ID escolhido para o novo utilizador ja esta em uso ou nao
			cout << "O identificador nao e valido. Por favor, insira outro." << endl;
			cin.clear();
		}
		else id_good = true;
		cin.ignore(100, '\n');
	}

	cout << "\nQual a duracao do seu turno? (max 10 horas)  ";
	while (!max_dia_good) {
		if (!(cin >> maxDayWorkingTime) || maxDayWorkingTime > 10) {
			cout << "Valor nao valido. Por favor, insira outro valor" << endl;
			cin.clear();
		}
		else max_dia_good = true;
		cin.ignore(100, '\n');
	}


	cout << "\nQuantas horas pode conduzir semanalmente? (max 60)  ";
	while (!max_sem_good) {
		if (!(cin >> maxWeekWorkingTime) || maxWeekWorkingTime > 60) {
			cout << "Valor nao valido. Por favor, insira outro valor" << endl;
			cin.clear();
		}
		else max_sem_good = true;
		cin.ignore(100, '\n');
	}

	cout << "\nHoras de descanso obrigatorio entre turnos? (min 2 e max 4)  ";
	while (!des_good) {
		if (!(cin >> minRestTime) || minRestTime > 4 || minRestTime < 2) {
			cout << "Valor nao valido. Por favor, insira outro valor" << endl;
			cin.clear();
		}
		else des_good = true;
		cin.ignore(100, '\n');
	}
	Empresa.newCondutor(id, name, maxDayWorkingTime, maxWeekWorkingTime, minRestTime);

	Empresa.getDriverById(id).showInfo();
}

//funcao sem parametros que tem como finalidade escrever no ficheiro o novo condutor adicionado
void alterar_ficheiro_condutores() {
	Empresa.rewriteFileDrivers(Empresa.getDriversFile());
}


//funcao sem parametros que tem como finalidade remover um condutor do vetor dos Drivers
void removerCondutordoVetor() {
	
	cout << "\n===================================" << endl;
	cout << "ID do condutor a ser removido: " << endl;
	int id;
	bool id_good = false;
	while (!id_good) {
		if (!(cin >> id) || !Empresa.existsDrivers(id)) {
			cout << "ID nao e valido ou nao existe." << endl << "Por favor introduza outro" << endl;
			cin.clear();
		}
		else id_good = true;
		cin.ignore(100, '\n');
	}
	vector<int> drivers_used_ids = Empresa.drivers_used_ids();
	Driver condutor_a_ser_removido = Empresa.getDriverById(id);
	cout << "Tem a certeza que pretende remover o seguinte condutor: (S/N)\n";
	condutor_a_ser_removido.showInfo();
	bool good = false;
	char opcao;
	while (!good)
	{
		cin >> opcao;
		if (opcao == 's' || opcao == 'S') {
			ptrdiff_t  j = find(drivers_used_ids.begin(), drivers_used_ids.end(), id) - drivers_used_ids.begin();    //j contem o apontador para o condutor em questao no vetor
			Empresa.removeDrivers(id, j);
			cout << "\nCondutor Removido!" << endl;
			good = true;
		}
		else if (opcao == 'n' || opcao == 'N')
			good = true;
		else
			cout << "Por favor, insira uma opcao valida." << endl;
	}
	
}

//funcao sem parametros que tem como finalidade alterar um condutor 
void alterarCondutor() {
	cout << "\nQual o ID do condutor a alterar? " << endl;
	int id;
	bool id_good = false;
	vector<int> drivers_used_ids = Empresa.drivers_used_ids();
	
	while (!id_good) {
		cin >> id;
		if (!Empresa.existsDrivers(id)) {
			cout << "\nO identificador nao e valido. Por favor, insira outro.";
			cin.clear();
		}
		else id_good = true;
		cin.ignore(100, '\n');
	}
	
	cout << "\nQual a caracteristica que pretende mudar?\n 1 - Nome\n 2 - Numero de Horas consecutivas por dia\n 3 - Numero de Horas Semanais\n 4 - Horas de Descanso" << endl << "\nInsira uma opcao: " ;
	int escolha;
	bool escolha_good = false;
	while (!escolha_good) {
		if (!(cin >> escolha)) {
			cout << "\nPor favor, insira uma opcao valida" << endl;
			cin.clear();
		}
		else escolha_good = true;
		cin.ignore(100, '\n');
	}
	int h_max_dia, h_max_sem, h_des;
	string name;
	bool max_dia_good = false;
	bool max_sem_good = false;
	bool des_good = false;
	switch (escolha) {
	case 1:
		cout << "\nQual o novo Nome do condutor? " << endl;
		getline(cin, name);
		Empresa.getDriverById(id).setName(name);
		break;
	case 2:
		cout << "\nQual a duracao do seu novo turno? (max 10 horas)  ";
		while (!max_dia_good) {
			if (!(cin >> h_max_dia) || h_max_dia > 10) {
				cout << "Valor nao valido. Por favor, insira outro valor" << endl;
				cin.clear();
			}
			else max_dia_good = true;
			cin.ignore(100, '\n');
		}
		Empresa.getDriverById(id).setMaxHours(h_max_dia);
		break;
	case 3:
		cout << "\nQuantas horas pode conduzir semanalmente? (max 60)  ";
		while (!max_sem_good) {
			if (!(cin >> h_max_sem) || h_max_sem > 60) {
				cout << "Valor nao valido. Por favor, insira outro valor" << endl;
				cin.clear();
			}
			else max_sem_good = true;
			cin.ignore(100, '\n');
		}
		Empresa.getDriverById(id).setMaxWeekWorkingTime(h_max_sem);
		break;
	case 4:
		cout << "\nNovas horas de descanso obrigatorio entre turnos? (min 2 e max 4)  ";
		while (!des_good) {
			if (!(cin >> h_des) || h_des > 4 || h_des < 2) {
				cout << "Valor nao valido. Por favor, insira outro valor" << endl;
				cin.clear();
			}
			else des_good = true;
			cin.ignore(100, '\n');
		}
		Empresa.getDriverById(id).setMinRestTime(h_des);
		break;
	}
}


void displayCondutoresComTempoSemanal() {
	vector <Driver *> CondutoresLivres = Empresa.getDriversWithSpareTime();

	cout << "\n===================================================" << endl;
	if (CondutoresLivres.empty())
		cout << "Nenhum condutor tem tempo livre semanal." << endl;
	else
	{
		cout << "Condutores com tempo livre: " << endl << endl;
		for (size_t t = 0; t < CondutoresLivres.size(); t++) {
			cout << "  - " << (*CondutoresLivres.at(t)).getName() << ", ID = " << (*CondutoresLivres.at(t)).getID() << ", com ";
			if ((*CondutoresLivres.at(t)).getMaxWeekWorkingTime() >= 60)
				cout << (*CondutoresLivres.at(t)).getMaxWeekWorkingTime() / 60 << "h e " << (*CondutoresLivres.at(t)).getMaxWeekWorkingTime() % 60 << " min livres.";
			else
				cout << (*CondutoresLivres.at(t)).getMaxWeekWorkingTime() << " min livres.";
			cout << endl;
		}


	}
}

//=========================================================================





//=============================FUNCOES SHIFT===============================


void adicionarTurno() {
	cout << "\n===================================" << endl;
	cout << "Qual o dia da Semana? " << endl;
	cout << "\n0 - Segunda-Feira" << endl;
	cout << "1 - Terca-Feira" << endl;
	cout << "2 - Quarta-Feira" << endl;
	cout << "3 - Quinta-Feira" << endl;
	cout << "4 - Sexta-Feira" << endl;
	cout << "5 - Sabado" << endl;
	cout << "6 - Domingo" << endl;
	cout << "\nInsira uma opcao: ";
	int dia;
	bool dia_good = false;

	while (!dia_good)
	{
		string temp;
		getline(cin, temp);
		if (!is_number(temp)) {
			cout << "Por favor, insira um dia valido." << endl;
		}

		else if (convert(temp) > 6) {
			cout << "Por favor, insira um dia valido." << endl;
		}
		else {
			dia = convert(temp);
			dia_good = true;
		}
	}
	cout << "\nQual o ID do condutor? " << endl;
	int id;
	bool id_good = false;
	while (!id_good)
	{
		string temp;
		getline(cin, temp);
		if (!is_number(temp)) {
			cout << "Por favor, insira um ID valido. " << endl;
		}
		else if (!Empresa.existsDrivers(convert(temp))) {
			cout << "O ID " << convert(temp) << " nao esta atribuido a nenhum condutor. Por favor, insira outro." << endl;

		}
		else {
			id = convert(temp);
			id_good = true;
		}
	}
	cout << "\nQual a linha? " << endl;
	int line;
	bool line_good = false;
	while (!line_good)
	{
		string temp;
		getline(cin, temp);
		if (!is_number(temp)) {
			cout << "Por favor, insira uma Linha valida. " << endl;
		}
		else if (!Empresa.existsLines(convert(temp))) {
			cout << "Por favor, insira uma Linha valida." << endl;
		}
		else {
			line = convert(temp);
			line_good = true;
		}
	}
	cout << "\nQual a o horario inicial do turno (hh:mm)? " << endl;
	int hora, min;
	int hora_good = false;
	while (!hora_good) {
		char lixo;
		string hora_a_tratar;
		getline(cin, hora_a_tratar);
		istringstream tratar(hora_a_tratar);
		if (!(tratar >> hora >> lixo >> min)) {
			cout << "Por favor, insira a hora no formato valido.";
			cin.clear();
		}
		else
			hora_good = true;
	}

	int tempoInicial = hora * 60 + min;

	if (Empresa.addNewShiftToDriver(dia, id, line, tempoInicial)) {
		cout << "\nTurno Adicionado!" << endl;
	}
	else
		cout << "\nNao foi possivel adicionar o Turno." << endl;
}

void removerTurno() {
	cout << "\n============================================" << endl;
	cout << "Qual o ID do condutor? " << endl;
	int id;
	bool id_good = false;
	while (!id_good)
	{
		string temp;
		getline(cin, temp);
		if (!is_number(temp)) {
			cout << "Por favor, insira um ID valido. " << endl;
		}
		else if (!Empresa.existsDrivers(convert(temp))) {
			cout << "Por favor, insira um ID valido. " << endl;

		}

		else if (Empresa.getDriverById(convert(temp)).getAllDriverShifts().empty())
			cout << "\nO condutor nao tem nenhum Turno atribuido. Por favor, insira outro." << endl;

		else {
			id = convert(temp);
			id_good = true;
		}
	}

	cout << "\nQual o dia da Semana? " << endl;
	cout << "\n0 - Segunda-Feira" << endl;
	cout << "1 - Terca-Feira" << endl;
	cout << "2 - Quarta-Feira" << endl;
	cout << "3 - Quinta-Feira" << endl;
	cout << "4 - Sexta-Feira" << endl;
	cout << "5 - Sabado" << endl;
	cout << "6 - Domingo" << endl;
	cout << "\nInsira uma opcao: ";
	int dia;
	bool dia_good = false;

	while (!dia_good)
	{
		string temp;
		getline(cin, temp);
		if (!is_number(temp)) {
			cout << "Por favor, insira um dia valido. " << endl;
		}

		else if (convert(temp) > 6) {
			cout << "Por favor, insira um dia valido. " << endl;
		}
		else {
			dia = convert(temp);
			dia_good = true;
		}
	}
	cout << "\nQual a linha? " << endl;
	int line;
	bool line_good = false;
	while (!line_good)
	{
		string temp;
		getline(cin, temp);
		if (!is_number(temp)) {
			cout << "Por favor, insira uma Linha valida. " << endl;
		}
		else if (!Empresa.existsLines(convert(temp))) {
			cout << "Por favor, insira uma Linha valida. " << endl;
		}
		else {
			line = convert(temp);
			line_good = true;
		}
	}
	cout << "\nQual a o horario incial do turno (hh:mm)? " << endl;
	int hora, min;
	int hora_good = false;
	while (!hora_good) {
		char lixo;
		string hora_a_tratar;
		getline(cin, hora_a_tratar);
		istringstream tratar(hora_a_tratar);
		if (!(tratar >> hora >> lixo >> min)) {
			cout << "Por favor, insira a hora no formato valido. ";
			cin.clear();
		}
		else
			hora_good = true;
	}

	int tempoInicial = hora * 60 + min;
	if (Empresa.removeWorkFromDriver(dia, id, line, tempoInicial)) {
		cout << "\nTurno removido!" << endl;
	}
	else
		cout << "\nNao foi possivel remover o Turno." << endl;
}

void displayTurnosOcupados2() {
	vector <int> ids = Empresa.drivers_used_ids();
	cout << "\n===================================" << endl;
	for (size_t t = 0; t < ids.size(); t++) {
		vector <pair <int, vector < DriverWork>>> Turnos = Empresa.getDriverById(ids.at(t)).getAllDriverShifts();


		if (Turnos.empty())
			cout << "\nO Condutor " << Empresa.getDriverById(ids.at(t)).getName() << " nao tem turnos atribuidos" << endl;
		else {

			cout << "\nTurnos atribuidos ao condutor " << Empresa.getDriverById(ids.at(t)).getName() << ":";
			for (size_t t = 0; t < Turnos.size(); t++) {
				cout << "\n   Turnos de " << NumberToDay(Turnos.at(t).first) << ":\n";
				for (size_t k = 0; k < Turnos.at(t).second.size(); k++) {
					cout << "    - Das " << formatingCout(Turnos.at(t).second.at(k).getStartTime()) << " as " << formatingCout(Turnos.at(t).second.at(k).getEndTime()) << ", no autocarro " << Turnos.at(t).second.at(k).getBusOrderNumber() << " na linha " << Turnos.at(t).second.at(k).getLine() << ". \n";
				}
			}
			cout << endl;
		}

	}
}

void displayTurnosdoCondutor() {
	cout << "\n===================================" << endl;
	cout << "Qual o ID do condutor? " << endl;
	int id;
	bool id_good = false;
	while (!id_good)
	{
		string temp;
		getline(cin, temp);
		if (!is_number(temp)) {
			cout << "Por favor, insira um ID valido. " << endl;
		}
		else if (!Empresa.existsDrivers(convert(temp))) {
			cout << "O ID " << convert(temp) << " nao esta atribuido a nenhum condutor. Por favor, insira outro." << endl;

		}
		else {
			id = convert(temp);
			id_good = true;
		}
	}

	vector <pair <int, vector < DriverWork>>> Turnos = Empresa.getDriverById(id).getAllDriverShifts();


	if (Turnos.empty())
		cout << "\nO Condutor " << id << " nao tem turnos atribuidos." << endl; 
	else {

		cout << "\nTurnos atribuidos ao condutor " << Empresa.getDriverById(id).getName() << ": ";
		for (size_t t = 0; t < Turnos.size(); t++) {
			cout << "\n  Turnos de " << NumberToDay(Turnos.at(t).first) << ":\n";
			for (size_t k = 0; k < Turnos.at(t).second.size(); k++) {
				cout << "   - Das " << formatingCout(Turnos.at(t).second.at(k).getStartTime()) << " as " << formatingCout(Turnos.at(t).second.at(k).getEndTime()) << ", no autocarro " << Turnos.at(t).second.at(k).getBusOrderNumber() << " na linha " << Turnos.at(t).second.at(k).getLine() << ". \n";
			}
		}
	}

}

void displayAutocarrosSemCondutor() {
	cout << "\n=================================================" << endl;
	cout << "Autocarros sem condutor: " << endl << endl;
	for (size_t t = 0; t < 7; t++) {
		vector < pair < int, vector < int > > > AutocarrosSemCondutor = Empresa.BusWithoutDriver(t);
		cout << " - " << NumberToDay(t) << ": " << endl;
		for (size_t k = 0; k < AutocarrosSemCondutor.size(); k++) {
			cout << "   - Linha " << AutocarrosSemCondutor.at(k).first << ": ";
			for (size_t m = 0; m < AutocarrosSemCondutor.at(k).second.size(); m++)
				cout << AutocarrosSemCondutor.at(k).second.at(m) << "  ";
			cout << endl;
		}
		cout << "\n";
	}

}