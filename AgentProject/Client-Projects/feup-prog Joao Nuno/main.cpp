#include "Header.h"

void menu(Company &c);


/*
organizarString
recebe como parametro um string
retorna essa mesma string na sua forma "organizada", apenas com um espaco entre as palavras
e sem nenhum espaco no inicio ou no fim
*/
string organizarString(string s) {

	int inicio = s.find_first_not_of(' ');
	s = s.substr(inicio);
	int fim = s.find_last_not_of(' ');
	s = s.substr(0, fim + 1);

	for (size_t i = 0; i < s.length(); i++) {
		if (s[i] == ' ' && s[i + 1] == ' ') {
			int primeiraletra = s.substr(i).find_first_not_of(' ');
			s = s.substr(0, i + 1) + s.substr(primeiraletra + i);
		}
	}
	return s;
}

string maiusculas(string s) {
	string s1 = s;
	for (size_t i = 0; i < s1.size(); i++) {
		s1[i] = toupper(s1[i]);
	}
	return s1;
}

/*
end - Fim do programa
pede ao utilizar se quer apenas finalizar ou guardar as alteracoes que ele podera ter efetuado
*/
void end(Company &c) {

	while (true) {
		clearScreen();

		int opcao = 0;
		cout << "+-------------------+\n";
		cout << "| ~ Semprarrolar ~  |\n";
		cout << "+-------------------+\n\n";
		cout << "Guardar alteracoes efetuadas?\n";
		cout << "1. Sim\n" << "2. Nao\n";
		cout << "\nOpcao: "; cin >> opcao;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}

		switch (opcao) {
		case 1:
			c.saveFiles();
			exit(1);
		case 2:
			exit(1);
		}
	}
}

int main() {

	cout << "+-------------------+\n";
	cout << "| ~ Semprarrolar ~  |\n";
	cout << "+-------------------+\n\n";
	
	string lines, drivers;
	ifstream fLines, fDrivers;

	cout << "Ficheiro das Linhas: ";
	getline(cin, lines);
	fLines.open(lines);
	if (fLines.fail()) {
		cerr << "\nFicheiro nao encontrado!...\n";
		system("pause");
		exit(1);
	}
	fLines.close();

	cout << "Ficheiro das Condutores: ";
	getline(cin, drivers);
	fDrivers.open(drivers);
	if (fDrivers.fail()) {
		cerr << "\nFicheiro nao encontrado!...\n";
		system("pause");
		exit(1);
	}
	fDrivers.close();
	
	Company company(drivers, lines);
	menu(company);

} 