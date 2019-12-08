/*
 * Menu.cpp
 */

#include "menu.h"

using namespace std;

void menu() {
	cout << "--------------------------------------------- " << endl;
	cout << "ASSOCIACAO PORTUGUESA INVESTIGACAO CIENTIFICA" << endl;
	cout << "--------------------------------------------- " << endl;
	cout << endl << endl;
	cout << " 1 - Carregar ficheiros com informacoes guardadas" << endl;
	cout << " 2 - Criar novos ficheiros" << endl;
	cout << " 3 - Sair" << endl;
	int opcao = 0;
	cout << endl;
	cout << "Introduza uma opcao: ";
	while (opcao < 1 || opcao > 3) {
		if (cin >> opcao) {

			switch (opcao) {
			case 1:
				initialize();
				menu2();
				break;
			case 2:
				initialize2();
				menu2();
				break;
			case 3:
				sair();
				break;
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

void menu2() {
	cout << endl << endl;
	cout << "--------------------------------------------- " << endl;
	cout << "ASSOCIACAO PORTUGUESA INVESTIGACAO CIENTIFICA" << endl;
	cout << "--------------------------------------------- " << endl;
	cout << endl << endl;
	cout << " 1 - Gestao de Associados" << endl;
	cout << " 2 - Gestao de Eventos" << endl;
	cout << " 3 - Gestao de Cotas" << endl;
	cout << " 4 - Gestao da Rede de Distribuicao" << endl;
	cout << " 5 - Ver ano atual" << endl;
	cout << " 6 - Anterior" << endl;
	cout << " 7 - Sair" << endl;

	int opcao = 0;
	cout << endl;
	cout << "Introduza uma opcao: ";
	while (opcao < 1 || opcao > 6) {
		if (cin >> opcao) {

			switch (opcao) {
			case 1:
				submenu1();
				break;
			case 2:
				submenu2();
				break;
			case 3:
				submenu3();
				break;
			case 4:
				submenu4();
				break;
			case 5:
				ano();
				regressar();
				break;
			case 6:
				menu();
				break;
			case 7:
				sair();
				break;
			default:
				cout << "Opcao invalida. Introduza uma nova opcao: ";
			}
		} else {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Opcao invalida. Introduza uma nova opcao: ";
		}
	}
}

void submenu1() {
	cout << endl << endl;
	cout << "--------------------------------------------- " << endl;
	cout << "ASSOCIACAO PORTUGUESA INVESTIGACAO CIENTIFICA" << endl;
	cout << "--------------------------------------------- " << endl;
	cout << endl << endl;
	cout << " 1 - Adicionar Associado" << endl;
	cout << " 2 - Remover Associado" << endl;
	cout << " 3 - Alterar informacoes de um Associado" << endl;
	cout << " 4 - Ver informacoes sobre os Associado" << endl;
	cout << " 5 - Anterior" << endl;
	cout << " 6 - Sair" << endl;

	int opcao = 0;
	cout << endl;
	cout << "Introduza uma opcao: ";
	while (opcao < 1 || opcao > 6) {
		if (cin >> opcao) {

			switch (opcao) {
			case 1:
				adicionarAssociado();
				regressar();
				break;
			case 2:
				removerAssociado();
				regressar();
				break;
			case 3:
				alterarAssociado();
				regressar();
				break;
			case 4:
				verInfoAssociado();
				regressar();
				break;
			case 5:
				menu2();
				break;
			case 6:
				sair();
				break;
			default:
				cout << "Opcao invalida. Introduza uma nova opcao: ";
			}
		} else {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Opcao invalida. Introduza uma nova opcao: ";
		}
	}
}

void submenu2() {
	cout << endl << endl;
	cout << "--------------------------------------------- " << endl;
	cout << "ASSOCIACAO PORTUGUESA INVESTIGACAO CIENTIFICA" << endl;
	cout << "--------------------------------------------- " << endl;
	cout << endl << endl;
	cout << " 1 - Criar Evento" << endl;
	cout << " 2 - Remover Evento" << endl;
	cout << " 3 - Alterar informacoes de um Evento" << endl;
	cout << " 4 - Ver informacoes sobre os Eventos" << endl;
	cout << " 5 - Ordenar Eventos" << endl;
	cout << " 6 - Anterior" << endl;
	cout << " 7 - Sair" << endl;

	int opcao = 0;
	cout << endl;
	cout << "Introduza uma opcao: ";
	while (opcao < 1 || opcao > 7) {
		if (cin >> opcao) {

			switch (opcao) {
			case 1:
				criarEvento();
				regressar();
				break;
			case 2:
				removerEvento();
				regressar();
				break;
			case 3:
				alterarEvento();
				regressar();
				break;
			case 4:
				verInfoEvento();
				regressar();
				break;
			case 5:
				organizarEventos();
				regressar();
				break;
			case 6:
				menu2();
				break;
			case 7:
				sair();
				break;
			default:
				cout << "Opcao invalida. Introduza uma nova opcao: ";
			}
		} else {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Opcao invalida. Introduza uma nova opcao: ";
		}
	}
}

void submenu3() {
	cout << endl << endl;
	cout << "--------------------------------------------- " << endl;
	cout << "ASSOCIACAO PORTUGUESA INVESTIGACAO CIENTIFICA" << endl;
	cout << "--------------------------------------------- " << endl;
	cout << endl << endl;
	cout << " 1 - Pagar cota anual individualmente" << endl;
	cout << " 2 - Pagar cotas automaticamente" << endl;
	cout << " 3 - Ver Associados com cotas em atraso" << endl;
	cout << " 4 - Anterior" << endl;
	cout << " 5 - Sair" << endl;

	int opcao = 0;
	cout << endl;
	cout << "Introduza uma opcao: ";
	while (opcao < 1 || opcao > 5) {
		if (cin >> opcao) {

			switch (opcao) {
			case 1:
				pagarCotas();
				regressar();
				break;
			case 2:
				pagarTodasCotas();
				regressar();
				break;
			case 3:
				verAssociadosCotas();
				regressar();
				break;
			case 4:
				menu2();
				break;
			case 5:
				sair();
				break;
			default:
				cout << "Opcao invalida. Introduza uma nova opcao: ";
			}
		} else {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Opcao invalida. Introduza uma nova opcao: ";
		}
	}
}

void submenu4() {
	cout << endl << endl;
	cout << "--------------------------------------------- " << endl;
	cout << "ASSOCIACAO PORTUGUESA INVESTIGACAO CIENTIFICA" << endl;
	cout << "--------------------------------------------- " << endl;
	cout << endl << endl;
	cout << " 1 - Divulgar Email para a Rede" << endl;
	cout << " 2 - Ver Emails da Rede" << endl;
	cout << " 3 - Organizar Emails" << endl;
	cout << " 4 - Anterior" << endl;
	cout << " 5 - Sair" << endl;

	int opcao = 0;
	cout << endl;
	cout << "Introduza uma opcao: ";
	while (opcao < 1 || opcao > 5) {
		if (cin >> opcao) {

			switch (opcao) {
			case 1:
				divulgarEmail();
				regressar();
				break;
			case 2:
				verEmails();
				regressar();
				break;
			case 3:
				organizarMails();
				regressar();
				break;
			case 4:
				menu2();
				break;
			case 5:
				sair();
				break;
			default:
				cout << "Opcao invalida. Introduza uma nova opcao: ";
			}
		} else {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Opcao invalida. Introduza uma nova opcao: ";
		}
	}

}

void regressar() {
	cout << endl << endl;
	cout << " 1 - Regressar ao Menu principal" << endl;
	cout << " 2 - Sair" << endl;

	int opcao = 0;
	cout << endl;
	cout << "Introduza uma opcao: ";
	while (opcao < 1 || opcao > 2) {
		if (cin >> opcao) {
			switch (opcao) {
			case 1:
				menu2();
				break;
			case 2:
				sair();
				break;
			default:
				cout << "Opcao invalida. Introduza uma nova opcao: ";
			}
		} else {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Opcao invalida. Introduza uma nova opcao: ";
		}
	}
}

void sair() {
	string opcao;
	cout << endl;
	cout << "Deseja guardar as alteracoes feitas? (S/N): ";
	cin.clear();
	cin.ignore(10000, '\n');
	while (opcao != "s" && opcao != "S" && opcao != "n" && opcao != "N") {
		getline(cin,opcao);
		if(opcao == "s" || opcao == "S"){
			guardarficheiroAssociacao();
			guardarficheiroAreas();
			guardarficheiroAssociados();
			guardarficheiroEventos();
			cout << "\nAlteracoes guardadas! A sair... \n";
			sleep(1);
			break;
		}
		if(opcao == "n" || opcao == "N"){
			cout << "\nA sair...\n";
			sleep(1);
			break;
		}
		else{
			cout << "Opcao invalida. Introduza uma nova opcao: ";
		}
	}
	exit(0);
}
