#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

void menuSec();
void displayLinhas();
void displayCondutores();
void adicionarLinha();
bool is_number(const string& s);
int convert(const string& s);
void alterar_ficheiro_linhas();
void alterar_ficheiro_condutores();
void guardar_ficheiro_linhas();
void guardar_ficheiro_condutores();
void removerLinhaDoVetor();
void removerCondutordoVetor();
void alterarLinha();
void alterarCondutor();
void adicionarCondutor();
vector<int> linhas_com_paragem_id(string paragem);
void horario_de_uma_linha();
void horario_de_uma_paragem();
void tempo_entre_paragens();
void adicionarTurno();
void displayTurnosOcupados2();
void removerTurno();
void displayTurnosdoCondutor();
void displayCondutoresComTempoSemanal();
void displayAutocarrosSemCondutor();
string company_name_capitalized();

//Todo este ficheiro lida com a parte da interface, recorrendo as funcoes no tratamento_de_dados.cpp para processar a informacao
string ficheiro_turnos();

vector<string> Iniciar() {
	string name_Company, LinesFile, DriversFile, ShiftsFile;
	cout << "============================================\n";
	cout << "Qual o nome da Empresa? ";
	getline(cin, name_Company);
	cout << "Qual o Ficheiro das Linhas? ";
	getline(cin, LinesFile);
	cout << "Qual o Ficheiro dos Condutores? ";
	getline(cin, DriversFile);
	ShiftsFile = ficheiro_turnos();
	vector<string> info;
	info.push_back(name_Company);
	info.push_back(LinesFile);
	info.push_back(DriversFile);
	info.push_back(ShiftsFile);
	return info;
}


void menuSec() {
	int opcao = 0, escolha1 = 0, escolha2 = 0, escolha3 = 0, escolha4 = 0, retornar = 0;
	string opcaostr;
	
	do {
		escolha1 = 0, escolha2 = 0, escolha3 = 0, escolha4 = 0; //para inicializar as variáveis cada vez que se regressa ao menu

		cout << "\n\n============= " << company_name_capitalized() << " =============\n";
		cout <<
			"+---+--------------------------- +\n" <<
			"| 1 |    Gestao de Linhas        |\n" <<
			"+-- - +------------------------- +\n" <<
			"| 2 |   Gestao de Condutores     |\n" <<
			"+-- - +------------------------- +\n" <<
			"| 3 | Visualizacao de Informacao |\n" <<
			"+-- - +------------------------- +\n" <<
			"| 4 | Escalonamento de Condutores|\n" <<
			"+-- - +------------------------- +\n" <<
			"| 0 |           Sair             |\n" <<
			"+-- - +------------------------- +\n";

		bool good = false;
		while (!good)
		{
			cout << "\nInsira uma opcao: ";
			getline(cin, opcaostr);
			if (!is_number(opcaostr)) {
				cout << "Por favor, insira uma opcao valida. " << endl;
			}
			else if (convert(opcaostr) < 0 || convert(opcaostr) > 4)
				cout << "Por favor, insira uma opcao valida. " << endl;
			else {
				opcao = convert(opcaostr);
				good = true;
			}
		}

		bool good1 = false;
		bool good2 = false;
		bool good3 = false;
		bool good4 = false;

		switch (opcao)
		{
		case 1:
			//MENU DE GESTAO DE LINHAS
			cout << "\n===================================" << endl;
			cout << "1 - Adicionar Linha" << endl;
			cout << "2 - Remover Linha" << endl;
			cout << "3 - Alterar Linha" << endl;
			cout << "0 - Voltar ao Menu" << endl;
			while (!good1)
			{
				cout << "\nInsira uma opcao: ";
				getline(cin, opcaostr);
				if (!is_number(opcaostr)) {
					cout << "Por favor, insira uma opcao valida. " << endl;
				}
				else if (convert(opcaostr) < 0 || convert(opcaostr) > 3)
					cout << "Por favor, insira uma opcao valida. " << endl;
				else {
					escolha1 = convert(opcaostr);
					good1 = true;
				}
			}
		break;

		case 2:
			//MENU DE GESTAO DE CONDUTORES
			cout << "\n===================================" << endl;
			cout << "1 - Adicionar Condutor" << endl;
			cout << "2 - Remover Condutor" << endl;
			cout << "3 - Alterar Condutor" << endl;
			cout << "0 - Voltar ao Menu" << endl;
			while (!good2)
			{
				cout << "\nInsira uma opcao: ";
				getline(cin, opcaostr);
				if (!is_number(opcaostr)) {
					cout << "Por favor, insira uma opcao valida. " << endl;
				}
				else if (convert(opcaostr) < 0 || convert(opcaostr) > 3)
					cout << "Por favor, insira uma opcao valida. " << endl;
				else {
					escolha2 = convert(opcaostr);
					good2 = true;
				}
			}
		break;

		case 3:
			//MENU DE INFORMACAO
			cout << "\n\n===================================" << endl;
			cout << "1 - Todas as Linhas" << endl;
			cout << "2 - Todos os Condutores" << endl;
			cout << "3 - Procurar Linhas com a Paragem" << endl;
			cout << "4 - Horario de uma Linha" << endl;
			cout << "5 - Horario de uma Paragem" << endl;
			cout << "6 - Percurso e Tempo entre duas paragens" << endl;
			cout << "7 - Turnos atribuidos" << endl;
			cout << "8 - Turnos de um Condutor" << endl;
			cout << "9 - Condutores com tempo livre semanal" << endl;
			cout << "10 - Autocarros sem Condutores" << endl;
			cout << "0 - Voltar ao Menu Principal" << endl;
			while (!good3)
			{
				cout << "\nInsira uma opcao: ";
				getline(cin, opcaostr);
				if (!is_number(opcaostr)) {
					cout << "Por favor, insira uma opcao valida. " << endl;
				}
				else if (convert(opcaostr) < 0 || convert(opcaostr) > 10)
					cout << "Por favor, insira uma opcao valida. " << endl;
				else {
					escolha3 = convert(opcaostr);
					good3 = true;
				}
			}
		break;

		case 4:
			//MENU DO ESCALONAMENTO DE CONDUTORES
			cout << "\n===================================" << endl;
			cout << "1 - Adicionar Turno a um Condutor" << endl;
			cout << "2 - Remover Turno a um Condutor" << endl;
			cout << "0 - Voltar ao Menu" << endl;
			while (!good4)
			{
				cout << "\nInsira uma opcao: ";
				getline(cin, opcaostr);
				if (!is_number(opcaostr)) {
					cout << "Por favor, insira uma opcao valida. " << endl;
				}
				else if (convert(opcaostr) < 0 || convert(opcaostr) > 2)
					cout << "Por favor, insira uma opcao valida. " << endl;
				else {
					escolha4 = convert(opcaostr);
					good4 = true;
				}
			}
		break;

		case 0:
			exit(1);
			break;
		}


		// FUNÇÕES PARA CADA SUBMENU

		switch (escolha1) {
		case 1:
			//SUB-MENU PARA ADICIONAR LINHA
			adicionarLinha();
			guardar_ficheiro_linhas();
			cout << endl;
			system("pause");
			break;
		case 2:
			//SUB-MENU PARA REMOVER LINHA
			removerLinhaDoVetor();
			guardar_ficheiro_linhas();
			cout << endl;
			system("pause");
			break;
		case 3:
			//SUB-MENU PARA ALTERAR LINHA
			alterarLinha();
			guardar_ficheiro_linhas();
			cout << endl;
			system("pause");
			break;
		}

		switch (escolha2) {
		case 1:
			//SUB-MENU PARA ADICIONAR CONDUTOR
			adicionarCondutor();
			cout << endl;
			guardar_ficheiro_condutores();
			cout << endl;
			system("pause");
			break;
		case 2:
			//SUB-MENU PARA REMOVER CONDUTOR
			removerCondutordoVetor();
			guardar_ficheiro_condutores();
			cout << endl;
			system("pause");
			break;
		case 3:
			//SUB-MENU PARA ALTERAR CONDUTOR
			alterarCondutor();
			guardar_ficheiro_condutores();
			cout << endl;
			system("pause");
			break;
		}

		switch (escolha3) {
		case 1:
			//SUB-MENU PARA DISPLAY DAS LINHAS
			cout << endl;
			displayLinhas();
			system("pause");
			break;
		case 2:
			//SUB-MENU PARA DISPLAY DOS CONDUTORES
			cout << endl;
			displayCondutores();
			cout << endl;
			system("pause");
			break;
		case 3: {
			//SUB-MENU PARA PROCURAR LINHAS
			cout << "\n===================================" << endl;
			cout << "Qual a paragem a procurar? ";
			string paragem;
			getline(cin, paragem);
			vector<int> linhas_boas = linhas_com_paragem_id(paragem);
			if (linhas_boas.empty())
				cout << "\nA paragem nao esta presente em nenhuma das linhas.\n";
			else if (linhas_boas.size() == 1)
				cout << "\nA unica linha quem contem a paragem " << paragem << " e " << linhas_boas.at(0) << ".";
			else {
				cout << "\nAs linhas que contem a paragem " << paragem << " sao: ";

				for (size_t t = 0; t < linhas_boas.size(); t++) {
					if (t == linhas_boas.size() - 1)
						cout << linhas_boas.at(t) << ".";
					else cout << linhas_boas.at(t) << ", ";
				}
			}
			cout << endl;
			cout << endl;
			system("pause");
			break;
		}
		case 4:
			//SUB-MENU DO HORARIO DE UMA LINHA
			horario_de_uma_linha();
			cout << endl;
			system("pause");
			break;
		case 5:
			//SUB-MENU DO HORARIO DE UMA PARAGEM
			horario_de_uma_paragem();
			cout << endl;
			system("pause");
			break;
		case 6: {
			//SUB-MENU DO TEMPO ENTRE DUAS PARAGENS
			tempo_entre_paragens();
			cout << endl;
			system("pause");
			break;
		}
		case 7:
			//SUB-MENU DISPLAY DE TODOS OS TURNOS
			displayTurnosOcupados2();
			cout << endl;
			system("pause");
			break;
		case 8: 
			//SUB-MENU DISPLAY DOS TURNOS DE UM CONDUTOR
			displayTurnosdoCondutor();
			cout << endl;
			system("pause");
			break;
		case 9:
			//SUB-MENU DISPLAY DOS CONDUTORES COM TEMPO LIVRE SEMANAL
			displayCondutoresComTempoSemanal();
			cout << endl;
			system("pause");
			break;
		case 10:
			//SUB-MENU DISPLAY DOS AUTOCARROS SEM CONDUTORES
			displayAutocarrosSemCondutor();
			cout << endl;
			system("pause");
			break;
		}

		switch (escolha4)
		{
		case 1:
			//SUB-MENU DE ADICIONAR TURNO
			adicionarTurno();
			cout << endl;
			system("pause");
			break;
		case 2:
			//SUB-MENU DE REMOVER TURNO
			removerTurno();
			cout << endl;
			system("pause");
			break;
				
		}

	} while (escolha1 == 0 || escolha2 == 0 || escolha3 == 0 || escolha4 == 0 || retornar == 0);
}


void guardar_ficheiro_linhas() {
	char opcao;
	bool good = false;
	cout << endl;
	while (!good)
	{
		cout << "Deseja guardar a nova informacao no ficheiro? (S/N): ";
		cin >> opcao;
		if (opcao == 's' || opcao == 'S') {
			alterar_ficheiro_linhas();
			cout << "\nFicheiro alterado!" << endl;
			good = true;
		}
		else if (opcao == 'n' || opcao == 'N')
			good = true;
		else
			cout << "Por favor, insira uma opcao valida." << endl;
	}
	cin.clear();
	cin.ignore(100, '\n');
}

void guardar_ficheiro_condutores() {
	char opcao;
	bool good = false;
	cout << endl;
	while (!good)
	{
		cout << "Deseja guardar a nova informacao no ficheiro? (S/N): ";
		cin >> opcao;
		if (opcao == 's' || opcao == 'S') {
			alterar_ficheiro_condutores();
			cout << "\nFicheiro alterado!" << endl;
			good = true;
		}
		else if (opcao == 'n' || opcao == 'N')
			good = true;
		else
			cout << "Por favor, insira uma opcao valida." << endl;
	}
	cin.clear();
	cin.ignore(100, '\n');
}

string ficheiro_turnos() {
	cout << "\n=======================================================" << endl;
	cout << "1 - Criar um novo ficheiro para guardar os turnos." << endl;
	cout << "2 - Abrir um ficheiro com turnos previamente definidos." << endl;
	string opcaostr;
	int opcao;
	bool good = false;
	while (!good)
	{
		cout << "\nInsira uma opcao: ";
		getline(cin, opcaostr);
		if (!is_number(opcaostr)) {
			cout << "Por favor, insira uma opcao valida. " << endl;
		}
		else if (convert(opcaostr) < 1 || convert(opcaostr) > 2)
			cout << "Por favor, insira uma opcao valida. " << endl;
		else {
			opcao = convert(opcaostr);
			good = true;
		}
	}
	
	string nomeficheiro;

	if (opcao == 1)
	{
		cout << "\nIntroduza o nome do ficheiro a criar: ";
		getline(cin, nomeficheiro);
		ofstream outfile;
		outfile.open(nomeficheiro);
		outfile << "Empty";
		outfile.close();
	}

	else if (opcao == 2) 
	{
		cout << "\nIntroduza o nome do ficheiro: ";
		getline(cin, nomeficheiro);
	}

	return nomeficheiro;
}