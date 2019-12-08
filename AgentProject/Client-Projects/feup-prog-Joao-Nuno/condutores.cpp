#include "Header.h"

string organizarString(string s);
string maiusculas(string s);
int procurarLinha(int id);
int tempoIdaVolta(int id);
void end(Company &c);


/*
void visualizarTrabalho() {

	clearScreen();

	int id;

	cout << "+-------------------------------+\n";
	cout << "| Visualizar Trabalho           |\n";
	cout << "+-------------------------------+\n";

	cout << "Condutor ? "; cin >> id;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}

	//verifica se o condutor esta escolhido esta guardado no vetor de condutores
	int indice = procurarCondutor(id);

	if (indice == -1) {
		cout << "\nCondutor nao encontrado!...\n";
		system("pause");
		return;
	}

	//visualizar trabalho
	while (true) {
		clearScreen();
		cout << "+-------------------------------+\n";
		cout << "| Visualizar Trabalho           |\n";
		cout << "+-------------------------------+\n";

		//verifica se o condutor escolhido tem algum trabalho atribuido no vetor de trabalhos
		bool trabalha = false;

		size_t i;
		for (i = 0; i < trabalhos.size(); i++) {
			if (id == trabalhos[i].id) {
				trabalha = true;
				break;
			}
		}

		if (!trabalha)
			cout << "O condutor " << id << " nao tem nenhum trabalho atribuido!";
		else
			cout << trabalhos[i].trabalho;

		//fim
		int opcao = 0;

		cout << "\n\n8 - Voltar\n";
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

void condutoresDisponiveis() {

	vector<int> condutoresDisponiveis;	//vetor com os condutores disponiveis

	//verifica se cada condutor do vetor global esta, ou nao, no vetor dos trabalho
	//metendo-o no vetor de condutores livre se nao estiver
	for (size_t i = 0; i < condutores.size(); i++) {	//ciclo para cada condutor
		bool trabalha = false;
		for (size_t j = 0; j < trabalhos.size(); j++) {	//ciclo para cada elemento do vetor dos trabalhos
			if (condutores[i].id == trabalhos[j].id) {
				trabalha = true;
				break;
			}
		}
		if (!trabalha) {
			condutoresDisponiveis.push_back(condutores[i].id);
		}
	}

	while (true) {
	//display dos condutores
		clearScreen();

		cout << "+-------------------------------+\n";
		cout << "| Condutores Disponiveis        |\n";
		cout << "+-------------------------------+\n";
		cout << "Condutores Disponiveis:";

		//ciclo para cada elemento do vetor de condutores disponiveis
		for (size_t i = 0; i < condutoresDisponiveis.size(); i++) {
			cout << endl << condutoresDisponiveis[i];
		}

		//fim
		int opcao = 0;

		cout << "\n\n8 - Voltar\n";
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


void condutoresLinha() {

	clearScreen();

	cout << "+-------------------------------+\n";
	cout << "| Condutores por Linha          |\n";
	cout << "+-------------------------------+\n";

	int id;

	cout << "Linha ? "; cin >> id;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}

	//verifica se a linha escolhida esta guardada no vetor de linhas
	int indice = procurarLinha(id);

	if (indice == -1) {
		cout << "\nLinha nao encontrada!...\n";
		system("pause");
		return;
	}

	int nCondutores = (HORAFINAL + (tempoIdaVolta(id) / 60) - HORAINICIAL) / HORATURNO;
	if ((HORAFINAL + (tempoIdaVolta(id) / 60) - HORAINICIAL) % HORATURNO != 0) {
		nCondutores++;
	}

	while (true) {
		clearScreen();

		cout << "+-------------------------------+\n";
		cout << "| Condutores por Linha          |\n";
		cout << "+-------------------------------+\n";
		cout << "\nPara a linha " << id << " sao necessarios " << nCondutores << " condutores.";

		int opcao = 0;

		//fim
		cout << "\n\n8 - Voltar\n";
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
}*/