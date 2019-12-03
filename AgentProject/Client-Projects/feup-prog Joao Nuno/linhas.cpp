#include "Header.h"

string organizarString(string s);
string maiusculas(string s);
void end(Company &c);

/*
vector<int> procurarParagem(string paragem) {
	vector<int> v;

	string paragem_maiusculas = maiusculas(paragem);

	//ciclo para pesquisar no vetor de linhas
	for (size_t i = 0; i < linhas.size(); i++) {
		for (size_t j = 0; j < linhas[i].paragens.size(); j++) {
			string a_analisar = maiusculas(linhas[i].paragens[j]);
			if (a_analisar == paragem_maiusculas) {
				v.push_back(linhas[i].id);
			}
		}
	}
	return v;
}

void paragens() {

	clearScreen();
	string paragem;
	cin.ignore(1, '\n');

	cout << "+-------------------------------+\n";
	cout << "| Linhas por Paragem            |\n";
	cout << "+-------------------------------+\n";
	cout << "Paragem ? "; getline(cin, paragem, '\n');
	paragem = organizarString(paragem);
	
	
	vector<int> vLinhas = procurarParagem(paragem);	//vetor com os id's de todas as linhas que passam na paragem

	//verifica se a paragem existe
	if (vLinhas.size() == 0) {
		cout << "Paragem nao encontrada!...\n";
		system("pause");
		return;
	}
	while (true) {
		clearScreen();

		cout << "+-------------------------------+\n";
		cout << "| Linhas por Paragem            |\n";
		cout << "+-------------------------------+\n";
		cout << "Pela paragem " << paragem << " passam as linhas: ";
		//ciclo para dar display de todas as paragens
		for (size_t i = 0; i < vLinhas.size(); i++)
			cout << endl << vLinhas[i];

		//fim
		int opcao = 0;
		cout << "\n\n8 - Voltar\n9 - Sair";
		cout << "\n\nOpcao: "; cin >> opcao;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		switch (opcao) {
		case 8:
			return;
		case 9:
			end();
			break;
		}
	}
}

struct HorarioParagem {
	int linha;
	string sentido;
	int horas;
	int min;
};

vector<int> procurarIndicesLinhas(vector<int> v) {
	vector<int> vI;
	for (size_t j = 0; j < v.size(); j++) {
		for (size_t i = 0; i < linhas.size(); i++) {
			if (linhas[i].id == v[j])
				vI.push_back(i);
		}
	}
	return vI;
}

int procurarIndiceParagem(int i, string paragem) {
	int indice = 0;
	string paragem_maiusculas = maiusculas(paragem);

	//ciclo para correr as paragens todas da linha
	for (size_t j = 0; j < linhas[i].paragens.size(); j++) {
		string a_analisar = maiusculas(linhas[i].paragens[j]);
		if (a_analisar == paragem_maiusculas) {
			indice = j;
			break;
		}
	}
	return indice;
}

vector <HorarioParagem> horarioParagem2Sentidos(vector<int> indiceLinhasParagem, string paragem) {

	vector <HorarioParagem> v;	//vetor para guardar toda a informacao

	//sentido direto
	for (size_t i = 0; i < indiceLinhasParagem.size(); i++) {
		float dif = (HORAFINAL - HORAINICIAL) * 60;	//tempo de funcionamento dos autocarros (em minutos)

		int horas = HORAINICIAL;
		int minutos = 0;
		//ciclo para calcular o tempo que demora desde a primeira paragem ate a pretendida
		for (size_t j = 0; j < procurarIndiceParagem(indiceLinhasParagem[i], paragem); j++) {
			minutos += linhas[indiceLinhasParagem[i]].tempo_viagem[j];
		}

		while (dif >= 0) {
			HorarioParagem horario;
			horario.linha = linhas[indiceLinhasParagem[i]].id;
			horario.sentido = linhas[indiceLinhasParagem[i]].paragens[linhas[indiceLinhasParagem[i]].paragens.size() - 1]; //ultima paragem

			//acerto dos minutos
			while (minutos >= 60) {
				horas++;
				//acerto das horas
				if (horas > 23)
					horas = 0;
				minutos -= 60;
			}
				

			horario.horas = horas;
			horario.min = minutos;

			v.push_back(horario);
			minutos += linhas[indiceLinhasParagem[i]].freq;
			dif -= linhas[indiceLinhasParagem[i]].freq;
		}

	}

	//sentido contrario
	for (size_t i = 0; i < indiceLinhasParagem.size(); i++) {
		float dif = (HORAFINAL - HORAINICIAL) * 60;	//tempo de funcionamento dos autocarros (em minutos)

		int horas = HORAINICIAL;
		int tempo = 0;
		//ciclo para calcular o tempo que demora desde a primeira paragem ate a pretendida
		for (size_t j = 0; j < procurarIndiceParagem(indiceLinhasParagem[i], paragem); j++) {
			tempo += linhas[indiceLinhasParagem[i]].tempo_viagem[j];
		}

		int tempoTotal = 0;
		//ciclo para calcular o tempo que demora do inicio ate ao fim da linha
		for (size_t j = 0; j < linhas[indiceLinhasParagem[i]].tempo_viagem.size(); j++) {
			tempoTotal += linhas[indiceLinhasParagem[i]].tempo_viagem[j];
		}

		int minutos = tempo + (tempoTotal - tempo) * 2;		// tempo que demora desde o inicio ate a ao fim e voltar a paragem

		while (dif >= 0) {
			HorarioParagem horarioOposto;
			horarioOposto.linha = linhas[indiceLinhasParagem[i]].id;
			horarioOposto.sentido = linhas[indiceLinhasParagem[i]].paragens[0]; //primeira paragem

			//acerto dos minutos
			while (minutos >= 60) {
				horas++;
				//acerto das horas
				if (horas > 23)
					horas = 0;
				minutos -= 60;
			}

			horarioOposto.horas = horas;
			horarioOposto.min = minutos;

			v.push_back(horarioOposto);
			minutos += linhas[indiceLinhasParagem[i]].freq;
			dif -= linhas[indiceLinhasParagem[i]].freq;
		}
	}

	return v;
}

int horasParaMinutosParagem(HorarioParagem v) {
	HorarioParagem temp = v;
	int minutos = temp.min;
	while (temp.horas > 0) {
		temp.horas--;
		minutos += 60;
	}
	return minutos;
}

void ordenarHorarioParagem(vector<HorarioParagem> &v, int left, int right) {
	int i = left, j = right;

	HorarioParagem tmp;

	int pivot = horasParaMinutosParagem(v[(left + right) / 2]);

	while (i <= j) {
		while (horasParaMinutosParagem(v[i]) < pivot)
			i++;
		while (horasParaMinutosParagem(v[j]) > pivot)
			j--;
		if (i <= j) {
			tmp = v[i];
			v[i] = v[j];
			v[j] = tmp;
			i++;
			j--;
		}
	};

	if (left < j)
		ordenarHorarioParagem(v, left, j);
	if (i < right)
		ordenarHorarioParagem(v, i, right);
}

void horariosParagem() {

	clearScreen();
	cin.ignore(1, '\n');
	string paragem;
	cout << "+-------------------------------+\n";
	cout << "| Horario de uma Paragem        |\n";
	cout << "+-------------------------------+\n";
	cout << "Paragem ? "; getline(cin, paragem, '\n');
	paragem = organizarString(paragem);

	//verifica se a paragem existe
	vector<int> linhasParagem = procurarParagem(paragem);

	if (linhasParagem.size() == 0) {
		cout << "\nParagem nao encontrada!...\n";
		system("pause");
		return;
	}

	vector<int> indiceLinhasParagem = procurarIndicesLinhas(linhasParagem);

	vector <HorarioParagem> v = horarioParagem2Sentidos(indiceLinhasParagem, paragem);
	ordenarHorarioParagem(v, 0, v.size() - 1);

	//display do horario
	while (true) {
		clearScreen();
		cout << "Horario da paragem: " << paragem << endl;
		cout << "+" << setfill('-') << setw(48) << "+" << setfill(' ') << endl;
		cout << "|" << setw(5) << "Horas" << "|" << setw(4) << "Linha" << "|" << setw(37) << "Sentido|\n";
		cout << "+" << setfill('-') << setw(48) << "+" << setfill(' ') << endl;

		for (size_t i = 0; i < v.size(); i++) {
			if (v[i].horas < 10) {
				if (v[i].min < 10)
					cout << "|" << setw(1) << "0" << v[i].horas << ":0" << v[i].min << "|" << setw(5) << v[i].linha << "|" << setw(35) << v[i].sentido << "|" << endl;
				else
					cout << "|" << setw(1) << "0" << v[i].horas << ":" << v[i].min << "|" << setw(5) << v[i].linha << "|" << setw(35) << v[i].sentido << "|" << endl;
			}
			else {
				if (v[i].min < 10)
					cout << "|" << setw(2) << v[i].horas << ":0" << v[i].min << "|" << setw(5) << v[i].linha << "|" << setw(35) << v[i].sentido << "|" << endl;
				else
					cout << "|" << setw(2) << v[i].horas << ":" << v[i].min << "|" << setw(5) << v[i].linha << "|" << setw(35) << v[i].sentido << "|" << endl;
			}
		}
		cout << "+" << setfill('-') << setw(48) << "+" << setfill(' ') << endl;


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
			end();
			break;
		}
	}

}

struct HorarioLinha {
	string paragem;
	string sentido;
	int horas;
	int min;
};

int horasParaMinutosLinha(HorarioLinha v) {
	HorarioLinha temp = v;
	int minutos = temp.min;
	while (temp.horas > 0) {
		temp.horas--;
		minutos += 60;
	}
	return minutos;
}

void ordenarHorarioLinha(vector<HorarioLinha> &v, int left, int right) {
	int i = left, j = right;

	HorarioLinha tmp;

	int pivot = horasParaMinutosLinha(v[(left + right) / 2]);

	while (i <= j) {
		while (horasParaMinutosLinha(v[i]) < pivot)
			i++;
		while (horasParaMinutosLinha(v[j]) > pivot)
			j--;
		if (i <= j) {
			tmp = v[i];
			v[i] = v[j];
			v[j] = tmp;
			i++;
			j--;
		}
	};

	if (left < j)
		ordenarHorarioLinha(v, left, j);
	if (i < right)
		ordenarHorarioLinha(v, i, right);
}

vector<HorarioLinha> horarioLinha2Sentidos(int indice) {
	vector<HorarioLinha> v;

	int dif = (HORAFINAL - HORAINICIAL) * 60;	//tempo de funcionamento dos autocarros (em min)

	int horas = HORAINICIAL;
	int minutos = 0;

 	while (dif >= 0) {
		//acerto dos min e das horas
		while (minutos >= 60) {
			horas++;
			if (horas > 23)
				horas = 0;
			minutos -= 60;
		}

		int horasTemp = horas;
		int minTemp = minutos;
		//sentido direto
		for (size_t i = 0; i < linhas[indice].paragens.size(); i++) {
			HorarioLinha horario;

			if (i != 0)
				minTemp += linhas[indice].tempo_viagem[i - 1];

			while (minTemp >= 60) {
				horasTemp++;
				if (horasTemp > 23)
					horasTemp = 0;
				minTemp -= 60;
			}

			horario.horas = horasTemp;
			horario.min = minTemp;
			horario.sentido = linhas[indice].paragens[linhas[indice].paragens.size() - 1];
			horario.paragem = linhas[indice].paragens[i];

			v.push_back(horario);
		}
		//sentido inverso
		for (int i = linhas[indice].paragens.size() - 1; i >= 0; i--) {
			HorarioLinha horario;

			if (i != linhas[indice].paragens.size() - 1)
				minTemp += linhas[indice].tempo_viagem[i];

			while (minTemp >= 60) {
				horasTemp++;
				if (horasTemp > 23)
					horasTemp = 0;
				minTemp -= 60;
			}

			horario.horas = horasTemp;
			horario.min = minTemp;
			horario.sentido = linhas[indice].paragens[0];
			horario.paragem = linhas[indice].paragens[i];

			v.push_back(horario);
		}

		dif -= linhas[indice].freq;
		minutos += linhas[indice].freq;
	}
	return v;
}

void horariosLinha() {
	clearScreen();

	int id;

	cout << "+-------------------------------+\n";
	cout << "| Horario de uma Paragem        |\n";
	cout << "+-------------------------------+\n";
	cout << "Linha ? "; cin >> id;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	//verifica se a linha introduzida existe
	int indice = procurarLinha(id);

	if (indice == -1) {
		cout << "\nLinha nao encontrada!...\n";
		system("pause");
		return;
	}

	vector<HorarioLinha> v = horarioLinha2Sentidos(indice);
	ordenarHorarioLinha(v, 0, v.size() - 1);

	//display do horario
	while (true) {

		clearScreen();
		cout << "Horario da linha " << id << endl;
		cout << "+" << setfill('-') << setw(66) << "+" << setfill(' ') << endl;
		cout << "|" << setw(5) << "Horas" << "|" << setw(30) << "Paragem" << "|" << setw(30) << "Sentido|\n";
		cout << "+" << setfill('-') << setw(66) << "+" << setfill(' ') << endl;

		for (size_t i = 0; i < v.size(); i++) {
			if (v[i].horas < 10) {
				if (v[i].min < 10)
					cout << "|" << setw(1) << "0" << v[i].horas << ":0" << v[i].min << "|" << setw(30) << v[i].paragem << "|" << setw(28) << v[i].sentido << "|" << endl;
				else
					cout << "|" << setw(1) << "0" << v[i].horas << ":" << v[i].min << "|" << setw(30) << v[i].paragem << "|" << setw(28) << v[i].sentido << "|" << endl;
			}
			else {
				if (v[i].min < 10)
					cout << "|" << setw(2) << v[i].horas << ":0" << v[i].min << "|" << setw(30) << v[i].paragem << "|" << setw(28) << v[i].sentido << "|" << endl;
				else
					cout << "|" << setw(2) << v[i].horas << ":" << v[i].min << "|" << setw(30) << v[i].paragem << "|" << setw(28) << v[i].sentido << "|" << endl;
			}
		}
		cout << "+" << setfill('-') << setw(66) << "+" << setfill(' ') << endl;

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
			end();
			break;
		}
	}
	
}

int tempoIdaVolta(int id) {

	int indice = procurarLinha(id);
	int tempo = 0;

	for (size_t i = 0; i < linhas[indice].tempo_viagem.size(); i++)
		tempo += linhas[indice].tempo_viagem[i];

	tempo += tempo;
	return tempo;
}

void displayPercursoMesmaLinha(int indice, int p1, int p2) {
	while (true) {
		int total = 0;

		clearScreen();

		cout << linhas[indice].paragens[p1] << " -------> " << linhas[indice].paragens[p2];
		cout << "\nLinha " << linhas[indice].id << endl << endl;

		//se for no sentido direto
		if ((p2 - p1) > 0) {
			for (int i = p1; i <= p2; i++) {
				if (i == p2) {
					cout << linhas[indice].paragens[i];
				}
				else {
					cout << linhas[indice].paragens[i] << "\n  |\n  |\n" << linhas[indice].tempo_viagem[i] << " min\n  |\n  |\n  V\n";
					total += linhas[indice].tempo_viagem[i];
				}
			}
		}
		//se for no sentido inverso
		else {
			for (int i = p1; i >= p2; i--) {
				if (i == p2) {
					cout << linhas[indice].paragens[i];
				}
				else {
					cout << linhas[indice].paragens[i] << "\n  |\n  |\n" << linhas[indice].tempo_viagem[i - 1] << "min\n  |\n  |\n  V\n";
					total += linhas[indice].tempo_viagem[i - 1];
				}
			}
		}
		cout << "\n\nTempo total: " << total << " minutos";

		//fim
		int opcao = 0;
		cout << "\n\n8 - Voltar\n9 - Sair";
		cout << "\n\nOpcao: "; cin >> opcao;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		switch (opcao) {
		case 8:
			return;
		case 9:
			end();
			break;
		}
	}
}

int tempoEntreParagens(int indice, int p1, int p2) {
	int total = 0;
	//se for no sentido direto
	if ((p2 - p1) > 0) {
		for (int i = p1; i < p2; i++) {
			total += linhas[indice].tempo_viagem[i];
		}
	}
	//se for no sentido inverso
	else {
		for (int i = p1; i > p2; i--) {
			total += linhas[indice].tempo_viagem[i - 1];
		}
	}

	return total;
}

vector<int> analisarLinhasParagens(vector<int> linhasParagem1, vector<int> linhasParagem2) {

	vector <int> linhasComum;

	for (size_t i = 0; i < linhasParagem1.size(); i++) {
		bool mesmaLinha = false;
		for (size_t j = 0; j < linhasParagem2.size(); j++) {
			if (linhasParagem1[i] == linhasParagem2[j])
				mesmaLinha = true;
		}
		if (mesmaLinha)
			linhasComum.push_back(linhasParagem1[i]);
	}

	return linhasComum;

}

void percurso() {

	string paragem1;	//primeira paragem
	string paragem2;	//segunda paragem


	clearScreen();
	cout << "+-------------------------------+\n";
	cout << "| Escolha duas Paragens         |\n";
	cout << "+-------------------------------+\n";
	cin.ignore(1, '\n');
	cout << "Paragem 1 ? "; getline(cin, paragem1, '\n');
	paragem1 = organizarString(paragem1);

	//verifica se a paragem 1 existe
	vector<int> linhasParagem1 = procurarParagem(paragem1);

	if (linhasParagem1.size() == 0) {
		cout << "\nParagem nao encontrada!...\n";
		system("pause");
		return;
	}

	cout << "\nParagem 2 ? "; getline(cin, paragem2, '\n');
	paragem2 = organizarString(paragem2);

	//verifica se a paragem 2 existe
	vector<int> linhasParagem2 = procurarParagem(paragem2);

	if (linhasParagem2.size() == 0) {
		cout << "\nParagem nao encontrada!...\n";
		system("pause");
		return;
	}
	
	clearScreen();

	cout << "+-------------------------------+\n";
	cout << "| Percurso                      |\n";
	cout << "+-------------------------------+\n\n";

	vector<int> linhasComum = analisarLinhasParagens(linhasParagem1, linhasParagem2); //vetor com as linhas em comum

	if (linhasComum.size() == 0) {	//nenhuma linha em comum
		cout << "Nao se encontram na mesma linha...\n";
		system("pause");
	}
	else if (linhasComum.size() == 1) {	//apenas uma linha em comum
		displayPercursoMesmaLinha(procurarLinha(linhasComum[0]), procurarIndiceParagem(procurarLinha(linhasComum[0]), paragem1), procurarIndiceParagem(procurarLinha(linhasComum[0]), paragem2));
		return;
	}
	else {	//varias linhas em comum (ver qual e a mais rapida entre as duas paragens)
		int melhorLinha = linhasComum[0];
		int melhorTempo = tempoEntreParagens(procurarLinha(linhas[0].id), procurarIndiceParagem(procurarLinha(linhasComum[0]), paragem1), procurarIndiceParagem(procurarLinha(linhasComum[0]), paragem2));
		for (size_t i = 0; i < linhasComum.size(); i++) {
			if (tempoEntreParagens(procurarLinha(linhas[i].id), procurarIndiceParagem(procurarLinha(linhasComum[i]), paragem1), procurarIndiceParagem(procurarLinha(linhasComum[i]), paragem2)) < melhorTempo) {
				melhorLinha = linhasComum[i];
				melhorTempo = tempoEntreParagens(procurarLinha(linhas[i].id), procurarIndiceParagem(procurarLinha(linhasComum[i]), paragem1), procurarIndiceParagem(procurarLinha(linhasComum[i]), paragem2));
			}
		}
		displayPercursoMesmaLinha(procurarLinha(melhorLinha), procurarIndiceParagem(procurarLinha(melhorLinha), paragem1), procurarIndiceParagem(procurarLinha(melhorLinha), paragem2));
		return;
	}
}*/