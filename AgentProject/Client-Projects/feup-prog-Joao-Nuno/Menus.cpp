#include "Header.h"

void menuCondutores(Company &c);
void menuLinhas(Company &c);
void menuInfo(Company &c);

void menuHorarios();
//void horariosLinha();
//void horariosParagem();
//void percurso();
//void paragens();
//void menuTrabalhos();
void end(Company &c);


void menu(Company &c) {

	while (true) {
		int opcao = 0;

		clearScreen();
		cout << "+-------------------------------+\n";
		cout << "| Menu Principal                |\n";
		cout << "+-------------------------------+\n";
		cout << "| Selecione uma opcao :         |\n";
		cout << "+-------------------------------+\n";
		cout << "| 1. Gestao de Linhas           |\n";
		cout << "| 2. Gestao de Condutores       |\n";
		cout << "| 3. Visualizacao de Informacao |\n";
		cout << "|                               |\n";
		cout << "| 9. Sair                       |\n";
		cout << "+-------------------------------+\n";
		cout << "\nOpcao: "; cin >> opcao;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}

		switch (opcao) {
		case 1:
			menuLinhas(c);
			break;
		case 2:
			menuCondutores(c);
			break;
		case 3:
			menuInfo(c);
			break;
		case 9:
			end(c);
			exit(1);
			break;
		}
	}
}

void menuCondutores(Company &c) {

	while (true) {
		int opcao = 0;

		clearScreen();
		cout << "+-------------------------------+\n";
		cout << "| Gestao de Condutores          |\n";
		cout << "+-------------------------------+\n";
		cout << "| Selecione uma opcao :         |\n";
		cout << "+-------------------------------+\n";
		cout << "| 1. Adicionar Condutor         |\n";
		cout << "| 2. Remover Condutor           |\n";
		cout << "| 3. Alterar Condutor           |\n";
		cout << "| 4. Trabalhos                  |\n";
		cout << "|                               |\n";
		cout << "| 8. Voltar                     |\n";
		cout << "| 9. Sair                       |\n";
		cout << "+-------------------------------+\n";
		cout << "\nOpcao: "; cin >> opcao;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}

		switch (opcao) {
		case 1:
			c.addDriver(c);
			break;
		case 2:
			c.removeDriver(c);
			break;
		case 3:
			c.changeDriver(c);
			break;
		case 4:
			//menuTrabalhos();
			break;
		case 8:
			return;
		case 9:
			end(c);
			exit(1);
			break;
		}
	}
}

void menuLinhas(Company &c) {

	while (true) {
		int opcao = 0;

		clearScreen();
		cout << "+-------------------------------+\n";
		cout << "| Gestao de Linhas              |\n";
		cout << "+-------------------------------+\n";
		cout << "| Selecione uma opcao :         |\n";
		cout << "+-------------------------------+\n";
		cout << "| 1. Adicionar Linha            |\n";
		cout << "| 2. Remover Linha              |\n";
		cout << "| 3. Alterar Linha              |\n";
		cout << "|                               |\n";
		cout << "| 8. Voltar                     |\n";
		cout << "| 9. Sair                       |\n";
		cout << "+-------------------------------+\n";
		cout << "\nOpcao: "; cin >> opcao;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}

		switch (opcao) {
		case 1:
			c.addLine(c);
			break;
		case 2:
			c.removeLine(c);
			break;
		case 3:
			c.changeLine(c);
			break;
		case 8:
			return;
		case 9:
			end(c);
			exit(1);
			break;
		}
	}
}

void menuInfo(Company &c) {

	while (true) {
		int opcao = 0;

		clearScreen();
		cout << "+-------------------------------+\n";
		cout << "| Visualizacao de Informacao    |\n";
		cout << "+-------------------------------+\n";
		cout << "| Selecione uma opcao :         |\n";
		cout << "+-------------------------------+\n";
		cout << "| 1. Linhas                     |\n";
		cout << "| 2. Condutores                 |\n";
		cout << "| 3. Horarios                   |\n";
		cout << "| 4. Percursos                  |\n";
		cout << "| 5. Linhas por Paragem         |\n";
		cout << "|                               |\n";
		cout << "| 8. Voltar                     |\n";
		cout << "| 9. Sair                       |\n";
		cout << "+-------------------------------+\n";
		cout << "\nOpcao: "; cin >> opcao;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}

		switch (opcao) {
		case 1:
			c.showLines(c);
			break;
		case 2:
			c.showDrivers(c);
			break;
		case 3:
			//menuHorarios();
			break;
		case 4:
			//percurso();
			break;
		case 5:
			//paragens();
			break;
		case 8:
			return;
		case 9:
			end(c);
			exit(1);
			break;
		}
	}
}

void menuHorarios() {

	while (true) {
		int opcao = 0;

		clearScreen();
		cout << "+-------------------------------+\n";
		cout << "| Horarios                      |\n";
		cout << "+-------------------------------+\n";
		cout << "| Selecione uma opcao :         |\n";
		cout << "+-------------------------------+\n";
		cout << "| 1. Horario de uma Paragem     |\n";
		cout << "| 2. Horario de uma Linha       |\n";
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
			//horariosParagem();
			break;
		case 2:
			//horariosLinha();
			break;
		case 8:
			return;
		}
	}
}

/*
void menuTrabalhos() {
	while (true) {
		int opcao = 0;

		clearScreen();
		cout << "+-------------------------------+\n";
		cout << "| Trabalhos                     |\n";
		cout << "+-------------------------------+\n";
		cout << "| Selecione uma opcao :         |\n";
		cout << "+-------------------------------+\n";
		cout << "| 1. Trabalho Atribuido         |\n";
		cout << "| 2. Condutores Disponiveis     |\n";
		cout << "| 3. Condutores por Linha       |\n";
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
			visualizarTrabalho();
			break;
		case 2:
			condutoresDisponiveis();
			break;
		case 3:
			condutoresLinha();
		case 8:
			return;
		}
	}
}
*/