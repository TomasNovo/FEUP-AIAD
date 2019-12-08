 #include <iostream>
#include "menu.h"
#include "extras.h"
#include "cruise.h"
#include <climits>
#include "BST.h"

using namespace std;

/**
 * @brief      Displays the company title
 */
void Empresa::titulo() {


	clearScreen();

	cout << "__________              __           __________.__                               \n";
	cout << "\\______   \\____________/  |_  ____   \\______   \\__|__  __ ___________  ______      \n";
	cout << " |     ___/  _ \\_  __ \\   __\\/  _ \\   |       _/  \\  \\/ // __ \\_  __ \\/  ___/    \n";
	cout << " |    |  (  <_> )  | \\/|  | (  <_> )  |    |   \\  |\\   /\\  ___/|  | \\/\\___ \\   \n";
	cout << " |____|   \\____/|__|   |__|  \\____/   |____|_  /__| \\_/  \\_____>__|  /_____ >\n";
	cout << "                                             \\/                            \\/       \n";
	cout << "\n";
	cout << "\n";

}


/**
 * @brief      displays the client menu
 */
void Empresa::menuCliente() {


	int opcaocliente;
	while (true) {
		titulo();
		cout << "+----------------------------------------------------------+\n";
		cout << "| Escolha o que pretende fazer com os clientes             |\n";
		cout << "+----------------------------------------------------------+\n";
		cout << "| Selecione a sua opcao (insira apenas o numero):          |\n";
		cout << "+----------------------------------------------------------+ \n";
		cout << "| 1 - Adicionar Cliente                                    |\n";
		cout << "| 2 - Modificar Cliente                                    |\n";
		cout << "| 3 - Apagar Cliente                                       |\n";
		cout << "| 4 - Ver Todos os Clientes                                |\n";
		cout << "| 5 - Ver Todos os Clientes Inativos                       |\n";
		cout << "| 6 - Ver Faturas                                          |\n";
		cout << "| 7 - Ver Todas as Reservas de um Cliente                  |\n";
		cout << "| 0 - Sair                                                 |\n";
		cout << "+----------------------------------------------------------+\n";

		cin >> opcaocliente;

		if (cin.fail()){
			cin.clear();
			cin.ignore(INT_MAX,'\n');
			clearScreen();
			cout << "Erro: Introduziu um input invalido. So pode usar numeros inteiros." << endl;
			cout << "Pressione Enter para voltar ao menu" << endl;
			cin.get();
		}
		switch (opcaocliente) {

		case 0:
			return;
			break;

		case 1:
			try{
			adicionaCliente();
			}
			catch(ObjetoRepetido<Cliente> & ex){
				clearScreen();
				cout << "O cliente " << ex << " ja existe " << endl;
				cout << "Pressione enter para regressar ao menu" << endl;
				cin.get();
			}
			break;
		case 2:
			try{
			modificaCliente();
			}
			catch(ObjetoInexistente<Cliente> & ex){
				clearScreen();
				cout << "O cliente " << ex << " nao existe. " << endl;
				cout << "Pressione enter para regressar ao menu" << endl;
				cin.get();
			}
			break;
		case 3:
			try{
			removeCliente();
			}
			catch (ObjetoInexistente<Cliente> & ex) {
				clearScreen();
				cout << "O cliente " << ex << " nao existe. " << endl;
				cout << "Pressione Enter para voltar ao menu";
				cin.get();
			}
			break;
		
		case 4:
			displayClientes();
			cin.get();
			cin.get();
			break;
		case 5:
			displayClientesInativos();
			cin.get();
			cin.get();
			break;

		case 6:
			listaFaturas();
			cin.get();
			cin.get();
			break;
		
		case 7:
			try {
				displayTodasAsReservasdeUmCliente();
			}
			catch (ObjetoInexistente<Cliente> & ex) {
				clearScreen();
				cout << "O cliente " << ex << " nao existe. " << endl;
				cout << "Pressione enter para regressar ao menu" << endl;
				cin.get();
			}

			break;
			
		default:
			cout << "Lamento, mas a opcao que inseriu nao e valida. Sera redirecionado/a para o inicio do menu. \n";


		}
		
	}
}

void Empresa::adicionaCliente() {


	titulo();

	int opcaoRegisto;
	bool clientechoice = true;
	while (clientechoice) {

		cout << "+----------------------------------------------------------+\n";
		cout << "| Pretende tornar-se um cliente registado?                 |\n";
		cout << "+----------------------------------------------------------+\n";
		cout << "| Selecione a sua opcao (insira apenas o numero):          |\n";
		cout << "+----------------------------------------------------------+\n";
		cout << "| 1 - Sim (tera conta registada e acumulara pontos)        |\n";
		cout << "| 2 - Nao (continuara como cliente normal)                 |\n";
		cout << "| 0 - Sair                                                 |\n";
		cout << "+----------------------------------------------------------+\n";
		cin >> opcaoRegisto;
		if (cin.fail()){
			cin.clear();
			cin.ignore(INT_MAX,'\n');
			clearScreen();
			cout << "Erro: Introduziu um input invalido. So pode usar numeros inteiros." << endl;
			cout << "Pressione Enter para voltar ao menu" << endl;
			cin.get();
		}
		switch (opcaoRegisto) {
		case 0:
			return;
			break;
		case 1:
			adicionaClienteRegistado();
			clientechoice = false;
			break;
		case 2:
			adicionaClienteNormal();
			clientechoice = false;
			break;
		default:
			cout << "Lamento, mas a opcao que inseriu nao e valida. Sera redirecionado/a para o inicio do menu. \n";
		}

	}


}

void Empresa::adicionaClienteNormal() {

	titulo();
	string nomeCliente;
	string morada;

	cout << "+----------------------------------------------------------+\n";
	cout << "| Qual e o seu nome?                                       |\n";
	cout << "+----------------------------------------------------------+\n";

	cin.ignore (INT_MAX,'\n');
	getline(cin,nomeCliente);

	if(BinarySearch(this->_clientes,nomeCliente) != -1){
		throw ObjetoRepetido<Cliente>(nomeCliente);
	}

	cout << "+----------------------------------------------------------+\n";
	cout << "| Qual a sua morada?                                       |\n";
	cout << "+----------------------------------------------------------+\n";

	getline(cin,morada);

	Cliente * novocliente = new Cliente(nomeCliente, morada);
	addClientes(*novocliente);
	this->sort();
	return;

}

void Empresa::adicionaClienteRegistado() {

	titulo();
	string nomeClienteRegistado;
	string morada;

	cout << "+----------------------------------------------------------+\n";
	cout << "| Com que nome pretende ficar registado?                   |\n";
	cout << "+----------------------------------------------------------+\n";

	cin.ignore(INT_MAX, '\n');
	getline(cin,nomeClienteRegistado);
	if(BinarySearch(this->_clientes,nomeClienteRegistado) != -1){
		throw ObjetoRepetido<Cliente>(nomeClienteRegistado);
	}

	cout << "+----------------------------------------------------------+\n";
	cout << "| Qual a sua morada?                                       |\n";
	cout << "+----------------------------------------------------------+\n";

	getline(cin,morada);

	Cliente * novoClienteRegistado = new ClienteRegistado(nomeClienteRegistado,morada, 0);
	addClientes(*novoClienteRegistado);
	this->sort();
	cout << "Pressione Enter para regressar\n";
	cin.get();
	return;

}

void Empresa::modificaCliente() {

	titulo();
	string nome_cliente, novonome,novaMorada;
	int modifica, pontos;

	displayClientes();

	cout << "+----------------------------------------------------------+\n";
	cout << "| Qual e o nome do cliente?                                |\n";
	cout << "+----------------------------------------------------------+\n";

	cin.ignore(INT_MAX, '\n');
	getline(cin, nome_cliente);


	int index = BinarySearch(_clientes, nome_cliente);
	if (index == -1) { throw ObjetoInexistente<Cliente>(nome_cliente); }

	cout << "+----------------------------------------------------------+\n";
	cout << "| Que propriedade do cliente pretende modificar?           |\n";
	cout << "+----------------------------------------------------------+\n";
	cout << "| 1 - Nome                                                 |\n";
	cout << "| 2 - Pontos                                               |\n";
	cout << "| 3 - Estatuto de Registado                                |\n";
	cout << "| 4 - Morada                                               |\n";
	cout << "| 0 - Sair                                                 |\n";
	cout << "+----------------------------------------------------------+\n";

	cin >> modifica;

	switch (modifica) {
	case 0:
		return;
		break;
	case 1:
		cout << "+----------------------------------------------------------+\n";
		cout << "| Indique o novo nome:                                     |\n";
		cout << "+----------------------------------------------------------+\n";

		cin.ignore(INT_MAX, '\n');
		getline(cin, novonome);
		_clientes.at(index)->setNome(novonome);
		break;

	case 2:

		if (_clientes.at(index)->isRegistado()) {
			cout << "+----------------------------------------------------------+\n";
			cout << "| Indique os pontos:                                       |\n";
			cout << "+----------------------------------------------------------+\n";

			cin >> pontos;
			_clientes.at(index)->setPontos(pontos);
		}
		else cout << "Esse cliente nao esta registado, logo nao tem pontos. Registe-o antes de utilizar os pontos. \n";

		break;

	case 3:
		if(this->_clientes.at(index)->isRegistado()){
			cout << "O cliente ja se encontra registado" << endl;
			cout << "Pressione Enter para regressar ao menu" << endl;
			cin.get();
		}
		else{
		novonome = _clientes.at(index)->getNome();
		novaMorada = _clientes.at(index)->getMorada();
		delete _clientes.at(index);
		_clientes.at(index) = new ClienteRegistado(novonome, novaMorada,0);
		}
		break;

	case 4:
		cout << "+----------------------------------------------------------+\n";
		cout << "| Indique a nova morada:                                   |\n";
		cout << "+----------------------------------------------------------+\n";
		cin.ignore(INT_MAX, '\n');
		getline(cin, novaMorada);
		_clientes.at(index)->setMorada(novaMorada);
	
	default:
		cout << "Essa opcao nao e viavel. Pressione Enter para voltar ao menu anterior.";

	}
	cin.get();
	return;

}

void Empresa::removeCliente() {
	titulo();

	displayClientes();
	string clienteremover;
	cout << "+----------------------------------------------------------+\n";
	cout << "| Qual e o cliente a remover?	                            |\n";
	cout << "+----------------------------------------------------------+\n";

	cin.ignore(INT_MAX, '\n');
	getline(cin, clienteremover);
	

		int index = BinarySearch(_clientes, clienteremover);
		if (index == -1) { throw ObjetoInexistente<Cliente>(clienteremover); }


	deleteClientes(clienteremover);
	cout << endl << "O cliente foi removido com sucesso" << endl;
	cout << "Pressione Enter para regressar" << endl;
	cin.get();
	return;
	

}
void Empresa::displayTodasAsReservasdeUmCliente() {

	titulo();
	string nome_cliente;

	displayClientes();

	cout << "+----------------------------------------------------------+\n";
	cout << "| Qual e o nome do cliente?                                |\n";
	cout << "+----------------------------------------------------------+\n";

	cin.ignore(INT_MAX, '\n');
	getline(cin, nome_cliente);


	int index = BinarySearch(_clientes, nome_cliente);
	if (index == -1) { throw ObjetoInexistente<Cliente>(nome_cliente); }
	cout << "+----------------------------------------------------------+\n";
	cout << "| Estas sao todas as reservas efetuadas pelo cliente:      |\n";
	cout << "+----------------------------------------------------------+\n";

	for (unsigned int i = 0; i < _reservas.size(); i++)
	{
		if (_reservas[i]->getNomeCliente() == nome_cliente)
		{
			cout << "Fornecedor: " << _reservas.at(i)->getNomeFornecedor() << endl
				<< "Oferta: ";  _reservas.at(i)->getOferta()->printOferta();
			cout << "Cliente: " << _reservas.at(i)->getCliente()->getNome() << endl
				<< "Pontos do Cliente: " << _reservas.at(i)->getCliente()->getPontos() << endl
				<< "Preco (a pagar): " << _reservas.at(i)->getPreco() << endl
				<< "Cancelada: " << (_reservas.at(i)->isCancelada() ? "sim" : "nao") << endl << endl;
		}
	}
	cin.get();
	cin.get();
	return;


}


void Empresa::menuFornecedor() {

	int opcaofornecedor;

	while(true){
	titulo();
	cout << "+----------------------------------------------------------+\n";
	cout << "| Escolha o que pretende fazer com os fornecedores         |\n";
	cout << "+----------------------------------------------------------+\n";
	cout << "| Selecione a sua opcao (insira apenas o numero):          |\n";
	cout << "+----------------------------------------------------------+\n";
	cout << "| 1 - Adicionar Fornecedor                                 |\n";
	cout << "| 2 - Modificar Fornecedor                                 |\n";
	cout << "| 3 - Apagar Fornecedor                                    |\n";
	cout << "| 4 - Ver Fornecedores (sem ofertas)                       |\n";
	cout << "| 5 - Ver Fornecedores (com ofertas)                       |\n";
	cout << "| 6 - Ver todas as ofertas de um fornecedor                |\n";
	cout << "| 7 - Ver todas as reservas feitas para um fornecedor      |\n";
	cout << "| 0 - Sair                                                 |\n";
	cout << "+----------------------------------------------------------+\n";

	cin >> opcaofornecedor;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		clearScreen();
		cout << "Erro: Introduziu um input invalido. So pode usar numeros inteiros." << endl;
		cout << "Pressione Enter para voltar ao menu" << endl;
		cin.get();
	}
	switch (opcaofornecedor) {

	case 0:
		return;
		break;

	case 1:
		try{
		adicionaFornecedor();
		}
		catch(ObjetoRepetido<Fornecedor> & ex){
			clearScreen();
			cout << "O cliente " << ex << " ja existe " << endl;
			cout << "Pressione enter para regressar ao menu" << endl;
			cin.get();
		}
		break;
	case 2:
		try{
		modificaFornecedor();
		}
		catch(ObjetoInexistente<Fornecedor> & ex){
			clearScreen();
			cout << "O fornecedor " << ex << " nao existe. " << endl;
			cout << "Pressione enter para regressar ao menu" << endl;
			cin.get();
		}
		break;
	case 3:
		try{
		removeFornecedor();
		}
		catch(ObjetoInexistente<Fornecedor> & ex){
			clearScreen();
			cout << "O fornecedor " << ex << " nao existe. " << endl;
			cout << "Pressione enter para regressar ao menu" << endl;
			cin.get();
		}
		break;
	case 4:
		displayFornecedores();
		cin.get();
		cin.get();
		break;
	case 5:
		displayFornecedorescomOfertas();
		cin.get();
		cin.get();
		break;

	case 6:
		try {
			displayTodasAsOfertasdeUmFornecedor();
		}
		catch (ObjetoInexistente<Fornecedor> & ex) {
			clearScreen();
			cout << "O fornecedor " << ex << " nao existe. " << endl;
			cout << "Pressione enter para regressar ao menu" << endl;
			cin.get();
		}
		break;

	case 7:
		try {
			displayTodasAsReservasdeUmFornecedor();
	}
		catch (ObjetoInexistente<Fornecedor> & ex) {
			clearScreen();
			cout << "O fornecedor " << ex << " nao existe. " << endl;
			cout << "Pressione enter para regressar ao menu" << endl;
			cin.get();
		}
		break;
	
		
	default:
		cout << "Lamento, mas a opcao que inseriu nao e valida \n";


	}

}
}

void Empresa::adicionaFornecedor() {

	titulo();
	string nome_fornecedor, morada;
	long unsigned int NIF;

	cout << "+----------------------------------------------------------+\n";
	cout << "| Qual e o nome do fornecedor?                             |\n";
	cout << "+----------------------------------------------------------+\n";

	cin.ignore(INT_MAX,'\n');
	getline(cin,nome_fornecedor);
	if(BinarySearch(this->_fornecedores,nome_fornecedor) != -1){
		throw ObjetoRepetido<Fornecedor>(nome_fornecedor);
	}

	cout << "+----------------------------------------------------------+\n";
	cout << "| Indique o NIF:                                           |\n";
	cout << "+----------------------------------------------------------+\n";

	cin >> NIF;

	cout << "+----------------------------------------------------------+\n";
	cout << "| Indique a morada:                                        |\n";
	cout << "+----------------------------------------------------------+\n";

	cin.ignore(INT_MAX, '\n');
	getline(cin,morada);
	Fornecedor * novoFornecedor = new Fornecedor(nome_fornecedor, NIF, morada);
	novoFornecedor->setDefinicoesFornecedor();
	addFornecedores(*novoFornecedor);
	this->sort();
}


void Empresa::modificaFornecedor() {

	titulo();
	string nome_fornecedor, novonome,novamorada;
	int modifica;
	long unsigned int novoNIF;


	cout << "+----------------------------------------------------------+\n";
	cout << "| Estes sao os fornecedores:                               |\n";
	cout << "+----------------------------------------------------------+\n";

	displayFornecedores();


	cout << "+----------------------------------------------------------+\n";
	cout << "| Qual e o nome do fornecedor?                             |\n";
	cout << "+----------------------------------------------------------+\n";

	cin.ignore(INT_MAX, '\n');
	getline(cin, nome_fornecedor);
	

	int index = BinarySearch(_fornecedores, nome_fornecedor);
	if (index == -1) { throw ObjetoInexistente<Fornecedor>(nome_fornecedor); }


	cout << "+----------------------------------------------------------+\n";
	cout << "| Que propriedade do fornecedor pretende modificar?        |\n";
	cout << "+----------------------------------------------------------+\n";
	cout << "| 1 - Nome                                                 |\n";
	cout << "| 2 - NIF                                                  |\n";
	cout << "| 3 - Morada                                               |\n";
	cout << "| 4 - Definicoes de Fornecedor                             |\n";
	cout << "| 0 - Sair                                                 |\n";
	cout << "+----------------------------------------------------------+\n";

	cin >> modifica;
	
	switch (modifica) {
	case 0:
		return;
		break;
	case 1:
		cout << "+----------------------------------------------------------+\n";
		cout << "| Indique o novo nome:                                     |\n";
		cout << "+----------------------------------------------------------+\n";

		cin.ignore(INT_MAX, '\n');
		getline(cin, novonome);
		_fornecedores.at(index)->setNome(novonome);
		break;

	case 2:
		cout << "+----------------------------------------------------------+\n";
		cout << "| Indique o novo NIF:                                      |\n";
		cout << "+----------------------------------------------------------+\n";

		cin >> novoNIF;
		_fornecedores.at(index)->setNIF(novoNIF);
		break;

	case 3:
		cout << "+----------------------------------------------------------+\n";
		cout << "| Indique a nova morada:                                   |\n";
		cout << "+----------------------------------------------------------+\n";

		cin.ignore(INT_MAX, '\n');
		getline(cin, novamorada);
		_fornecedores.at(index)->setMorada(novamorada);
		break;
	
	case 4:
		_fornecedores.at(index)->setDefinicoesFornecedor();
		break;

	default:
		cout << "Essa opcao nao e viavel. Pressione Enter para voltar ao menu anterior.";

	}
	cin.get();
	return;

}
void Empresa::removeFornecedor() {
	titulo();

	string fornecedorremover;

	cout << "+----------------------------------------------------------+\n";
	cout << "| Estes sao os fornecedores:                               |\n";
	cout << "+----------------------------------------------------------+\n";

	displayFornecedores();
	
	
	cout << "+----------------------------------------------------------+\n";
	cout << "| Qual e o fornecedor a remover?                           |\n";
	cout << "+----------------------------------------------------------+\n";

	cin.ignore(INT_MAX, '\n');
	getline(cin, fornecedorremover);
	for (unsigned int i = 0; i < _fornecedores.size(); i++)
	{
		if (_fornecedores.at(i)->getNome() == fornecedorremover)
		{
			deleteFornecedores(fornecedorremover);
			cout << endl << "O fornecedor foi removido com sucesso" << endl;
			cout << "Pressione Enter para regressar" << endl;
			cin.get();
			return;
		}
	}

	cout << endl << "O fornecedor com esse nome nao foi encontrado" << endl;
	cout << "Pressione Enter para regressar" << endl;

	cin.get();
	return;
}

void Fornecedor::setDefinicoesFornecedor() {


	int porpessoa, iate, barco_rabelo, veleiro;

	definicoesfornecedor.erase(definicoesfornecedor.begin(), definicoesfornecedor.end()); //limpa_o_vetor, caso tivesse definicoes prévias


	cout << "+----------------------------------------------------------+\n";
	cout << "| Quanto pretende que custe, por pessoa, a reserva?        |\n";
	cout << "+----------------------------------------------------------+\n";

	cin >> porpessoa;


	cout << "+----------------------------------------------------------+\n";
	cout << "| Indique o preco base para a reserva de um iate:          |\n";
	cout << "+----------------------------------------------------------+\n";

	cin >> iate;

	cout << "+----------------------------------------------------------+\n";
	cout << "| Indique o preco base para a reserva de um barco rabelo:  |\n";
	cout << "+----------------------------------------------------------+\n";

	cin >> barco_rabelo;

	cout << "+----------------------------------------------------------+\n";
	cout << "| Indique o preco base para a reserva de um veleiro:       |\n";
	cout << "+----------------------------------------------------------+\n";

	cin >> veleiro;
	
	definicoesfornecedor.push_back(porpessoa);
	definicoesfornecedor.push_back(iate);
	definicoesfornecedor.push_back(barco_rabelo);
	definicoesfornecedor.push_back(veleiro);

	cout << "+----------------------------------------------------------+\n";
	cout << "| As definicoes de fornecedor foram registadas com sucesso.|\n";
	cout << "| Pressione a tecla Enter para sair                        |\n";
	cout << "+----------------------------------------------------------+\n";


	return;
}

void Empresa::displayTodasAsReservasdeUmFornecedor() {

	titulo();
	string nome_fornecedor;
	bool existe = false;

	displayFornecedores();

	cout << "+----------------------------------------------------------+\n";
	cout << "| Qual e o nome do fornecedor?                                |\n";
	cout << "+----------------------------------------------------------+\n";

	cin.ignore(INT_MAX, '\n');
	getline(cin, nome_fornecedor);


	int index = BinarySearch(_fornecedores, nome_fornecedor);
	if (index == -1) { throw ObjetoInexistente<Fornecedor>(nome_fornecedor); }
	cout << "+----------------------------------------------------------+\n";
	cout << "| Estas sao as reservas efetuadas para este fornecedor:    |\n";
	cout << "+----------------------------------------------------------+\n";

	for (unsigned int i = 0; i < _reservas.size(); i++)
	{
		if (_reservas[i]->getNomeFornecedor() == nome_fornecedor)
		{
			existe = true;

			cout << "Fornecedor: " << _reservas.at(i)->getNomeFornecedor() << endl
				<< "Oferta: ";  _reservas.at(i)->getOferta()->printOferta();
			cout << "Cliente: " << _reservas.at(i)->getCliente()->getNome() << endl
				<< "Pontos do Cliente: " << _reservas.at(i)->getCliente()->getPontos() << endl
				<< "Preco (a pagar): " << _reservas.at(i)->getPreco() << endl
				<< "Cancelada: " << (_reservas.at(i)->isCancelada() ? "sim" : "nao") << endl << endl;
		}
		
	}
	if (!existe)
	{
		cout << "+----------------------------------------------------------+\n";
		cout << "| Ninguem reservou uma oferta deste fornecedor!            |\n";
		cout << "+----------------------------------------------------------+\n";
	}


	cin.get();
	cin.get();
	return;


}


void Empresa::displayTodasAsOfertasdeUmFornecedor() {

	titulo();
	string nome_fornecedor;

	displayFornecedores();

	cout << "+----------------------------------------------------------+\n";
	cout << "| Qual e o nome do fornecedor?                                |\n";
	cout << "+----------------------------------------------------------+\n";

	cin.ignore(INT_MAX, '\n');
	getline(cin, nome_fornecedor);


	int index = BinarySearch(_fornecedores, nome_fornecedor);
	if (index == -1) { throw ObjetoInexistente<Fornecedor>(nome_fornecedor); }
	cout << "+----------------------------------------------------------+\n";
	cout << "| Estas sao todas as reservas efetuadas pelo fornecedor:      |\n";
	cout << "+----------------------------------------------------------+\n";

	_fornecedores[index]->displayOfertas();
	
	cin.get();
	cin.get();
	return;


}

void Empresa::menuReservas() {


	int opcaoreservas;
	while (true) {
		titulo();
		cout << "+----------------------------------------------------------+\n";
		cout << "| Escolha o que pretende fazer com as reservas             |\n";
		cout << "+----------------------------------------------------------+\n";
		cout << "| Selecione a sua opcao (insira apenas o numero):          |\n";
		cout << "+----------------------------------------------------------+\n";
		cout << "| 1 - Adicionar Reserva                                    |\n";
		cout << "| 2 - Modificar Reserva                                    |\n";
		cout << "| 3 - Cancelar Reserva                                     |\n";
		cout << "| 4 - Apagar Reserva                                       |\n";
		cout << "| 5 - Ver Reservas                                         |\n";
		cout << "| 0 - Sair                                                 |\n";
		cout << "+----------------------------------------------------------+\n";

		cin >> opcaoreservas;

		if (cin.fail()){

			cin.clear();
			cin.ignore(INT_MAX,'\n');
			clearScreen();
			cout << "Erro: Introduziu um input invalido. So pode usar numeros inteiros." << endl;
			cout << "Pressione Enter para voltar ao menu" << endl;
			cin.get();
			return;



				}
		switch (opcaoreservas) {

		

		case 1:
			try{
			adicionaReserva();
			}
			catch(ObjetoInexistente<Cliente> & ex){
				cout << "O cliente " << ex << " nao existe" << endl;
				cout << "Pressione Enter para regressar ao menu anterior" << endl;
				cin.get();
				return;
			}
			catch(ObjetoInexistente<Fornecedor> & ex){
				cout << "O fornecedor " << ex << " nao existe" << endl;
				cout << "Pressione Enter para regressar ao menu anterior" << endl;
				cin.get();
				return;
			}
			catch(ObjetoInexistente<Oferta> & ex){
				cout << "A oferta " << ex << " nao existe" << endl;
				cout << "Pressione Enter para regressar ao menu anterior" << endl;
				cin.get();
				return;
			}
			break;
		case 2:
			try{
			modificaReserva();
			}
			catch(ObjetoInexistente<Cliente> & ex){
				clearScreen();
				cout << "O cliente " << ex << " nao existe. " << endl;
				cout << "Pressione enter para regressar ao menu" << endl;
				cin.get();
			}
			catch (ObjetoInexistente<Reserva> & ex) {
				clearScreen();
				cout << "A reserva indicada nao existe. " << endl;
				cout << "Pressione enter para regressar ao menu" << endl;
				cin.get();
			}
			break;
		case 3:
			try{
			cancelaReservas();
			}
			catch(ObjetoInexistente<Reserva> & ex){
				clearScreen();
				cout << "A reserva indicada nao existe. " << endl;
				cout << "Pressione enter para regressar ao menu" << endl;
				cin.get();
			}
			catch (ObjetoInexistente<Oferta> & ex) {
				cout << "A oferta " << ex << " nao existe" << endl;
				cout << "Pressione Enter para regressar ao menu anterior" << endl;
				cin.get();
				return;
			}
			break;
		case 4:
			try{
			removeReservas();
			}
			catch(ObjetoInexistente<Reserva> & ex){
				clearScreen();
				cout << "A reserva indicada nao existe. " << endl;
				cout << "Pressione enter para regressar ao menu" << endl;
				cin.get();
			}
			break;
		case 5:
			displayReservas();
			cin.get();
			cin.get();
			break;
		

		case 0:
			return;

		default:
			cout << "Lamento, mas a opcao que inseriu nao e valida. \n";
			

	}
}
	return;
}
	

void Empresa::adicionaReserva() {

	titulo();
	string nome_fornecedor, nomeCliente, nomeOferta;
	unsigned int  preco,lotacao;
	unsigned int pontos;
	bool cancelada = false;
	bool erroNome = true;
	vector<Oferta*> ofertas;

	
	cout << "+----------------------------------------------------------+\n";
	cout << "| Estes sao os clientes:                                   |\n";
	cout << "+----------------------------------------------------------+\n";

	displayClientes();

	cout << "+----------------------------------------------------------+\n";
	cout << "| Indique o nome do cliente:                               |\n";
	cout << "+----------------------------------------------------------+\n";
	cin.ignore(INT_MAX,'\n');
	getline(cin, nomeCliente);

	int indexCliente = BinarySearch(_clientes, nomeCliente);

	if (indexCliente == -1) { throw ObjetoInexistente<Cliente>(nomeCliente); }

	
	cout << "+----------------------------------------------------------+\n";
	cout << "| Estes sao todos os fornecedores e respetivas ofertas     |\n";
	cout << "+----------------------------------------------------------+\n";
	
	displayFornecedorescomOfertas();

	cout << "+----------------------------------------------------------+\n";
	cout << "| Indique o nome do fornecedor:                            |\n";
	cout << "+----------------------------------------------------------+\n";


	getline(cin, nome_fornecedor);
	int index = BinarySearch(_fornecedores, nome_fornecedor);

	if (index == -1) { throw ObjetoInexistente<Fornecedor>(nome_fornecedor); }


	cout << "+----------------------------------------------------------+\n";
	cout << "| Estas sao as suas ofertas:                               |\n";
	cout << "+----------------------------------------------------------+\n";

	_fornecedores.at(index)->displayOfertas();

	cout << "+----------------------------------------------------------+\n";
	cout << "| Indique o nome da oferta que pretende reservar:          |\n";
	cout << "+----------------------------------------------------------+\n";
	
	getline(cin, nomeOferta);

	for (unsigned int k = 0; k < _fornecedores.at(index)->getOfertas().size(); k++)
	{
		if (_fornecedores.at(index)->getOfertas().at(k).getNome() == nomeOferta)
		{
			ofertas.push_back(&_fornecedores.at(index)->getOfertas()[k]);
			erroNome = false;

		}

	}

	if (erroNome)
	{
		throw ObjetoInexistente<Oferta>(nomeOferta);
	}

	cout << "+----------------------------------------------------------+\n";
	cout << "| Indique para quantas pessoas quer efetuar a reserva:     |\n";
	cout << "+----------------------------------------------------------+\n";

	cin >> lotacao;

	if (lotacao <= ofertas[0]->getLotacao())
		ofertas[0]->diminuiLotacao(lotacao);
	else {
		cout << "Esse numero de pessoas excede o limite na oferta. Pressione Enter regressar.";
		cin.get();
		return;
	}

	cin.get();

	preco = _fornecedores.at(index)->calculaPreco(ofertas[0]->getBarcoNumber(), lotacao, ofertas[0]->getDistancia());

	//se os clientes tiverem 0 pontos, acumulam 1/5 do preço da viagem em pontos
	//se eles tiverem pontos inferiores à viagem, gastam todos e ficam set a 0, mas o custo é reduzido em numero igual aos pontos
	//se tiverem superior, gastam até cobrir o custo da viagem, e têm a viagem de graça

	if (_clientes.at(indexCliente)->isRegistado()) {
		pontos = _clientes.at(indexCliente)->getPontos();
		if (_clientes.at(indexCliente)->getPontos() == 0)
		{
			pontos = preco / 5;

		}
		else if (_clientes.at(indexCliente)->getPontos() <= preco)
		{
			preco = preco - _clientes.at(indexCliente)->getPontos();
			pontos = 0;

		}
		else { // (_clientes.at(indexCliente)->getPontos() > preco)

			pontos = pontos - preco;
			preco = 0;


		}
		_clientes.at(indexCliente)->setPontos(pontos);
	}
		
	
	
	

	Reserva * novaReserva = new Reserva(nome_fornecedor, ofertas[0], nomeCliente, _clientes.at(indexCliente), preco, cancelada);
	addReservas(*novaReserva);  
	Fatura novaFatura(novaReserva);
	this->_faturas.insert(novaFatura);
	RealTime tempoReserva;
	for (unsigned int l = 0; l < _fornecedores.at(index)->getOfertas().size(); l++)
	{
		if (_fornecedores.at(index)->getOfertas().at(l).getBarcoNumber() == ofertas[0]->getBarcoNumber())
		{
			_fornecedores.at(index)->getOfertas().at(l).setTimeUltimaReserva(tempoReserva);

		}
	}
	ClienteInativo * ci = new ClienteInativo(this->_clientes[indexCliente]);
		this->_clientesInativos.erase(*ci);
	cout << "+----------------------------------------------------------+\n";
	cout << "| A oferta foi reservada com sucesso.                      |\n";
	cout << "+----------------------------------------------------------+\n";
	this->sort();


	addOfertasQueue();
	aplicaDesconto();

	cin.get();
	cin.get();


}

void Empresa::modificaReserva()
{
	titulo();
	bool nfound = true;
	int reserva, novopreco;
	

	cout << "+----------------------------------------------------------+\n";
	cout << "| Estas sao as reservas disponiveis para modificar:        |\n";
	cout << "+----------------------------------------------------------+\n";

	displayReservas();

	string reservaremoveOferta, reservaremoveCliente;
	cout << "+----------------------------------------------------------+\n";
	cout << "| Indique o nome do cliente cuja oferta quer modificar:    |\n";
	cout << "+----------------------------------------------------------+\n";

	cin.ignore(INT_MAX, '\n');
	getline(cin, reservaremoveCliente);


	int index = BinarySearch(_clientes, reservaremoveCliente);
	if (index == -1) { throw ObjetoInexistente<Cliente>(reservaremoveCliente); }


	cout << "+----------------------------------------------------------+\n";
	cout << "| Estas sao todas as reservas efetuadas pelo cliente:      |\n";
	cout << "+----------------------------------------------------------+\n";

	for (unsigned int i = 0; i < _reservas.size(); i++)
	{
		if (_reservas[i]->getNomeCliente() == reservaremoveCliente)
		{
			cout << "Fornecedor: " << _reservas.at(i)->getNomeFornecedor() << endl
				<< "Oferta: ";  _reservas.at(i)->getOferta()->printOferta();
			cout << "Cliente: " << _reservas.at(i)->getCliente()->getNome() << endl
				<< "Pontos do Cliente: " << _reservas.at(i)->getCliente()->getPontos() << endl
				<< "Preco (a pagar): " << _reservas.at(i)->getPreco() << endl
				<< "Cancelada: " << (_reservas.at(i)->isCancelada() ? "sim" : "nao") << endl << endl;
		}
	}
	

	cout << "+----------------------------------------------------------+\n";
	cout << "| Indique o nome da reserva que pretende modificar:        |\n";
	cout << "+----------------------------------------------------------+\n";

	

	getline(cin, reservaremoveOferta);

	for (unsigned int j = 0; j < _reservas.size(); j++)
	{
		if (_reservas.at(j)->getOferta()->getNome() == reservaremoveOferta && _reservas.at(j)->getCliente()->getNome() == reservaremoveCliente)
		{
			nfound = false;
			reserva = j;
		}
	}
	if (nfound) {
		throw ObjetoInexistente<Reserva>("");
	}
	cout << "+----------------------------------------------------------+\n";
	cout << "| Escolha o que pretende fazer com a reserva               |\n";
	cout << "+----------------------------------------------------------+\n";
	cout << "| 1 - Alterar Preco                                        |\n";
	cout << "| 2 - Alterar Estado de Cancelada                          |\n";
	cout << "+----------------------------------------------------------+\n";

	int alteracao;
	

	cin >> alteracao;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		clearScreen();
		cout << "Erro: Introduziu um input invalido. So pode usar numeros inteiros." << endl;
		cout << "Pressione Enter para voltar ao menu" << endl;
		cin.get();
	}

	switch (alteracao) {
	
	case 1:
		cout << "Indique o novo preco da reserva:";
		cin >> novopreco; 
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			clearScreen();
			cout << "Erro: Introduziu um input invalido. So pode usar numeros inteiros." << endl;
			cout << "Pressione Enter para voltar ao menu" << endl;
			cin.get();
		}
		_reservas.at(reserva)->setPreco(novopreco);
		break;
	case 2:
		if (!(_reservas.at(reserva)->isCancelada()))
			_reservas.at(reserva)->cancelamento();
		else cout << "Lamento, mas devido a ja terem sido efetuadas as transicoes monetarias no que toca ao cancelamento, nao e possivel reverter este processo. Pedimos que remova esta reserva e crie uma nova.";
		break;
	default:
		return;
		
	}

	return;
}

void Empresa::removeReservas() {
	titulo();
	bool nfound = true;

	cout << "+----------------------------------------------------------+\n";
	cout << "| Estas sao as reservas disponiveis para remover:          |\n";
	cout << "+----------------------------------------------------------+\n";

	displayReservas();

	string reservaremoveOferta, reservaremoveCliente;
	cout << "+----------------------------------------------------------+\n";
	cout << "| Indique o nome do cliente cuja oferta quer remover:      |\n";
	cout << "+----------------------------------------------------------+\n";

	cin.ignore(INT_MAX, '\n');
	getline(cin, reservaremoveCliente);


	cout << "+----------------------------------------------------------+\n";
	cout << "| Indique o nome da oferta reservada pelo cliente:         |\n";
	cout << "+----------------------------------------------------------+\n";


	getline(cin, reservaremoveOferta);

	for (unsigned int i = 0; i < _reservas.size(); i++)
	{
		if (_reservas.at(i)->getOferta()->getNome() == reservaremoveOferta && _reservas.at(i)->getCliente()->getNome() == reservaremoveCliente)
		{
			deleteReservas(reservaremoveOferta);
			nfound = false;
		}
	}
	if(nfound){
		throw ObjetoInexistente<Reserva>("");
	}

	cout << "+----------------------------------------------------------+\n";
	cout << "| Reserva apagada com sucesso!                             |\n";
	cout << "| Pressione a tecla Enter para sair                        |\n";
	cout << "+----------------------------------------------------------+\n";

	cin.get();
	return;
}
                         


void Empresa::cancelaReservas() {
	titulo();
	int novoPreco, diferencadias;
	bool nfound = true;

	cout << "+----------------------------------------------------------+\n";
	cout << "| Estas sao as reservas disponiveis:                       |\n";
	cout << "+----------------------------------------------------------+\n";

	displayReservas();

	string reservaremoveOferta,reservaremoveCliente;
	cout << "+----------------------------------------------------------+\n";
	cout << "| Indique o nome do cliente cuja oferta quer cancelar      |\n";
	cout << "+----------------------------------------------------------+\n";

    cin.ignore(INT_MAX,'\n');
	getline(cin,reservaremoveCliente);
	
	cout << "+----------------------------------------------------------+\n";
	cout << "| Indique o nome da oferta reservada pelo cliente:         |\n";
	cout << "+----------------------------------------------------------+\n";

	
	getline(cin, reservaremoveOferta);

	for (unsigned int i = 0; i < _reservas.size(); i++)
	{
		if (_reservas.at(i)->getOferta()->getNome() == reservaremoveOferta && _reservas.at(i)->getCliente()->getNome() == reservaremoveCliente)
		{
			diferencadias = _reservas.at(i)->getOferta()->getDataMesmo().diferencaDias();
			nfound = false;
			if (diferencadias >= 7)
			{
				_reservas.at(i)->cancelamento();
				_reservas.at(i)->setPreco(0);
				break;
			}
			else if (diferencadias >= 2)
			{
				_reservas.at(i)->cancelamento();
				novoPreco = _reservas.at(i)->getPreco() / 2;
				_reservas.at(i)->setPreco(novoPreco);
				break;
			}
			else
				_reservas.at(i)->cancelamento();

		}
	}
	if(nfound){
		throw ObjetoInexistente<Reserva>("");
	}

	cout << "+----------------------------------------------------------+\n";
	cout << "| Reserva cancelada com sucesso!                           |\n";
	cout << "| Pressione a tecla Enter para sair                        |\n";
	cout << "+----------------------------------------------------------+\n";

	cin.get();
	return;


}
void Empresa::menuOfertas() {



	int opcaoOfertas;
	while (true) {
		titulo();
		cout << "+----------------------------------------------------------+\n";
		cout << "| Escolha o que pretende fazer com as Ofertas              |\n";
		cout << "+----------------------------------------------------------+\n";
		cout << "| Selecione a sua opcao (insira apenas o numero):          |\n";
		cout << "+----------------------------------------------------------+\n";
		cout << "| 1 - Adicionar Oferta                                     |\n";
		cout << "| 2 - Modificar Oferta                                     |\n";
		cout << "| 3 - Apagar Oferta                                        |\n";
		cout << "| 4 - Ver Ofertas                                          |\n";
		cout << "| 5 - Ver Ofertas (Ordenadas por Prioridade)               |\n";
		cout << "| 6 - Ver os clientes que reservaram uma oferta especifica |\n";
		cout << "| 0 - Sair                                                 |\n";
		cout << "+----------------------------------------------------------+\n";
		cin >> opcaoOfertas;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			clearScreen();
			cout << "Erro: Introduziu um input invalido. So pode usar numeros inteiros." << endl;
			cout << "Pressione Enter para voltar ao menu" << endl;
			cin.get();
		}
		switch (opcaoOfertas) {

		case 1:
			try {
				adicionaOferta();
			}
			catch (ObjetoRepetido<Oferta> & ex) {
				clearScreen();
				cout << "A oferta " << ex << " ja existe " << endl;
				cout << "Pressione enter para regressar ao menu" << endl;
				cin.get();
			}
			catch (ObjetoInexistente<Fornecedor> & ex) {
				clearScreen();
				cout << "O fornecedor " << ex << " nao existe. " << endl;
				cout << "Pressione enter para regressar ao menu" << endl;
				cin.get();
			}
			break;
		case 2:
			try {
				modificaOferta();
			}
			catch (ObjetoInexistente<Cliente> & ex) {
				clearScreen();
				cout << "O cliente " << ex << " nao existe. " << endl;
				cout << "Pressione enter para regressar ao menu" << endl;
				cin.get();
			}
			catch (ObjetoInexistente<Oferta> & ex) {
				clearScreen();
				cout << "A oferta " << ex << " nao existe. " << endl;
				cout << "Pressione enter para regressar ao menu" << endl;
				cin.get();

			}
			break;
		case 3:
			try {
				removeOferta();
			}
			catch (ObjetoInexistente<Fornecedor> & ex) {
				clearScreen();
				cout << "O fornecedor " << ex << " nao existe. " << endl;
				cout << "Pressione enter para regressar ao menu" << endl;
				cin.get();
			}
			catch (ObjetoInexistente<Oferta> & ex) {
				clearScreen();
				cout << "A oferta " << ex << " nao existe. " << endl;
				cout << "Pressione enter para regressar ao menu" << endl;
				cin.get();
			}
			break;
		case 4:
			displayFornecedorescomOfertas();
			cin.get();
			cin.get();
			break;

		case 5:
			displayOfertasemOrdem();
			cin.get();
			cin.get();
			break;

		case 6:
			try {
				displayTodosOsClientesdeumaOferta();
			}
			catch (ObjetoInexistente<Fornecedor> & ex) {
				clearScreen();
				cout << "O fornecedor " << ex << " nao existe. " << endl;
				cout << "Pressione enter para regressar ao menu" << endl;
				cin.get();
			}
			catch (ObjetoInexistente<Oferta> & ex) {
				clearScreen();
				cout << "A oferta " << ex << " nao existe. " << endl;
				cout << "Pressione enter para regressar ao menu" << endl;
				cin.get();
			}
			catch (ObjetoInexistente<Reserva> & ex) {
				clearScreen();
				cout << "Parece que nao foi efetuada nenhuma reserva para dessa oferta." << endl;
				cout << "Pressione enter para regressar ao menu" << endl;
				cin.get();
			}
				break;
			
		case 0:
			return;
			break;

		default:
			cout << "Lamento, mas a opcao que inseriu nao e valida. Tente outra vez" << endl;
			cout << "Pressione Enter para repetir" << endl;
			cin.get();
			clearScreen();

			}

		
	}
}



void Empresa::displayTodosOsClientesdeumaOferta() {
	
	displayFornecedorescomOfertas();
	string nomeOferta,nomefornecedor;
	int index, indexOferta;
	bool nfound = true;

	cout << "+----------------------------------------------------------+\n";
	cout << "| Indique o fornecedor em questao:                         |\n";
	cout << "+----------------------------------------------------------+\n";


	cin.ignore(INT_MAX, '\n');
	getline(cin, nomefornecedor);
	index = BinarySearch(this->_fornecedores, nomefornecedor);
	if (index == -1) {
		throw ObjetoInexistente<Fornecedor>(nomefornecedor);
	}


	_fornecedores[index]->displayOfertas();

	cout << "+----------------------------------------------------------+\n";
	cout << "| Indique o nome da oferta em questao:					    |\n";
	cout << "+----------------------------------------------------------+\n";

	getline(cin, nomeOferta);

	indexOferta = -1;
	for (unsigned int i = 0; i <_fornecedores.at(index)->getOfertas().size(); i++)
	{

		if (_fornecedores.at(index)->getOfertas().at(i).getNome() == nomeOferta)
		{
			indexOferta = i;
		}
	}
	if (indexOferta == -1) { throw ObjetoInexistente<Oferta>(nomeOferta); }

	for (unsigned int j = 0; j < _reservas.size(); j++)
	{
		if (_reservas.at(j)->getOferta()->getNome() == nomeOferta)
		{

			nfound = false;

			for (unsigned int i = 0; i < _clientes.size(); i++)
			{
				if (_reservas.at(j)->getNomeCliente() == _clientes.at(i)->getNome())
				{
					cout << "Cliente: " << _clientes.at(i)->getNome() << endl << "Morada: " << _clientes.at(i)->getMorada() << endl << "Pontos: " << _clientes.at(i)->getPontos() << endl;
					if (_clientes.at(i)->isRegistado()) {
						cout << "Registado: Sim" << endl << endl;
					}
					else cout << "Registado: Nao" << endl << endl;
				}
			}
		}
	}
	if (nfound) {
		throw ObjetoInexistente<Reserva>("");
	}
	cin.get();
	cin.get();


}

void Empresa::adicionaOferta() {

	titulo();
	std::string nome;
	std::string barco;
	int numeroBarco;
	std::string temp;
	std::vector<std::string> destinos;
	Oferta * novaOferta;
	unsigned int distancia;
	unsigned int preco;
	int lotacao;
	std::string data;
	Time * tempo;
	int index;

	displayFornecedores();

	cout << "+----------------------------------------------------------+\n";
	cout << "| Qual e o nome do fornecedor?                             |\n";
	cout << "+----------------------------------------------------------+\n";

	cin.ignore(INT_MAX,'\n');
	getline(cin,nome);
	index = BinarySearch(this->_fornecedores,nome);
	if(index == -1){
		throw ObjetoInexistente<Fornecedor>(nome);
	}
	

	cout << "+----------------------------------------------------------+\n";
	cout << "| Qual e o nome da oferta?                                 |\n";
	cout << "+----------------------------------------------------------+\n";

	getline(cin,nome);

	cout << "+----------------------------------------------------------+\n";
	cout << "| Escolha o tipo de barco:                                 |\n";
	cout << "+----------------------------------------------------------+\n";
	cout << "| 1 - Iate                                                 |\n";
	cout << "| 2 - Barco rabelo                                         |\n";
	cout << "| 3 - Veleiro                                              |\n";
	cout << "+----------------------------------------------------------+\n";

	cin >> numeroBarco;
	switch (numeroBarco) {
	case 1: 
		barco = "iate";
		break;
	case 2:
		barco = "barco rabelo";
		break;
	case 3:
		barco = "veleiro";
		break;
	default:
		cout << "Esse número nao e reconhecido como barco.";
		

	}



	cout << "+----------------------------------------------------------+\n";
	cout << "| Indique os destinos (escreva FIM quando terminar):       |\n";
	cout << "+----------------------------------------------------------+\n";
	cin.ignore(INT_MAX,'\n');
	while (temp != "FIM")
	{
		getline(cin,temp);
		if(temp != "FIM"){
		 destinos.push_back(temp);
		}
		cout << "\n";
	}

	cout << "+----------------------------------------------------------+\n";
	cout << "| Indique a distancia total percorrida:                    |\n";
	cout << "+----------------------------------------------------------+\n";

	cin >> distancia;

	cout << "+----------------------------------------------------------+\n";
	cout << "| Indique a lotacao total do barco:                        |\n";
	cout << "+----------------------------------------------------------+\n";

	cin >> lotacao;

	cout << "+----------------------------------------------------------+\n";
	cout << "| Indique a data da viagem (YY/MM/DD H:M):                 |\n";
	cout << "+----------------------------------------------------------+\n";

	cin.ignore(INT_MAX,'\n');
	getline(cin,data);
	tempo = new Time(data);

	preco = _fornecedores.at(index)->calculaPreco(numeroBarco, lotacao, distancia);
	
	
	novaOferta = new Oferta(nome, barco, destinos, distancia, lotacao, *tempo, preco);

	for (unsigned int i = 0; i < _fornecedores.size(); i++)
	{
		for (unsigned int j = 0; j < _fornecedores[i]->getOfertas().size(); j++)
		{
			if (_fornecedores[i]->getOfertas().at(j).getBarcoNumber() == novaOferta->getBarcoNumber()){
				_fornecedores[i]->getOfertas().at(j).setTimeUltimaReserva(novaOferta->getUltimaReserva());
		}
		}
	}
	this->_fornecedores[index]->addOferta(*novaOferta);

	addOfertasQueue();
	aplicaDesconto();

}

void Empresa::modificaOferta()
{

	titulo();
	int modifica, indexOferta = -1;
	string nomeCliente, nomeOferta, novonome, novobarco, novahora, novodestino, temp;
	unsigned int novopreco, novalotacao, novadistancia;
	std::vector<std::string> novosdestinos;
	Time *tempo;

	displayFornecedorescomOfertas();
	
	cout << "+----------------------------------------------------------+\n";
	cout << "| Indique o nome do fornecedor cuja oferta quer alterar:   |\n";
	cout << "+----------------------------------------------------------+\n";

	cin.ignore(INT_MAX, '\n');
	getline(cin, nomeCliente);

	int index = BinarySearch(_fornecedores, nomeCliente);
	if (index == -1) { throw ObjetoInexistente<Fornecedor>(nomeCliente); }
	

	cout << "+----------------------------------------------------------+\n";
	cout << "| Indique o nome da oferta em questao:					    |\n";
	cout << "+----------------------------------------------------------+\n";

	getline(cin, nomeOferta);

	indexOferta = -1;
	for (unsigned int i = 0; i <_fornecedores.at(index)->getOfertas().size(); i++)
	{
		
		if (_fornecedores.at(index)->getOfertas().at(i).getNome() == nomeOferta)
		{
			indexOferta = i;
		}
	}
	if(indexOferta == -1){ throw ObjetoInexistente<Oferta>(nomeOferta); }

	cout << "+----------------------------------------------------------+\n";
	cout << "| Que propriedade da oferta retende modificar?             |\n";
	cout << "+----------------------------------------------------------+\n";
	cout << "| 1 - Nome                                                 |\n";
	cout << "| 2 - Tipo de Barco                                        |\n";
	cout << "| 3 - Destinos                                             |\n";
	cout << "| 4 - Distancia                                            |\n";
	cout << "| 5 - Lotacao                                              |\n";
	cout << "| 6 - Data e Hora                                          |\n";
	cout << "| 7 - Preco                                                |\n";
	cout << "| 0 - Sair                                                 |\n";
	cout << "+----------------------------------------------------------+\n";

	cin >> modifica;

	switch (modifica) {
	case 0:
		return;
		break;
	case 1:
		cout << "+----------------------------------------------------------+\n";
		cout << "| Indique o novo nome:                                     |\n";
		cout << "+----------------------------------------------------------+\n";

		cin.ignore(INT_MAX, '\n');
		getline(cin, novonome);
		_fornecedores.at(index)->getOfertas().at(indexOferta).setNome(novonome);
		break;

	case 2:

		cout << "+----------------------------------------------------------+\n";
		cout << "| Escolha o tipo de barco:                                 |\n";
		cout << "+----------------------------------------------------------+\n";
		cout << "| 1 - Iate                                                 |\n";
		cout << "| 2 - Barco Rabelo                                         |\n";
		cout << "| 3 - Veleiro                                              |\n";
		cout << "+----------------------------------------------------------+\n";

		int numeroBarco;
		cin >> numeroBarco;
		if (numeroBarco == 1) {
			novobarco = "iate";
			_fornecedores.at(index)->getOfertas().at(indexOferta).setBarco(novobarco);
		}
		else if (numeroBarco == 2) {
			novobarco = "barco rabelo";
			_fornecedores.at(index)->getOfertas().at(indexOferta).setBarco(novobarco);
		}
		else if (numeroBarco == 3) {
			novobarco = "veleiro";
			_fornecedores.at(index)->getOfertas().at(indexOferta).setBarco(novobarco);
		}
		else
			cout << "Esse número nao e reconhecido como barco.";
		break;
		return;



	case 3:
		cout << "+----------------------------------------------------------+\n";
		cout << "| Indique os novos destinos (os anteriores serao apagados):|\n";
		cout << "| Para terminar, escreva FIM                               |\n";
		cout << "+----------------------------------------------------------+\n";
		_fornecedores.at(index)->getOfertas().at(indexOferta).apagaDestinos();
		cin.ignore(INT_MAX, '\n');

		while (temp != "FIM")
		{
			getline(cin, temp);
			if (temp != "FIM") {
				novosdestinos.push_back(temp);
			}
			cout << "\n";
		}
		_fornecedores.at(index)->getOfertas().at(indexOferta).setDestinos(novosdestinos);
		break;

	case 4:
		cout << "+----------------------------------------------------------+\n";
		cout << "| Indique a nova distancia:                                |\n";
		cout << "+----------------------------------------------------------+\n";
		cin >> novadistancia;
		_fornecedores.at(index)->getOfertas().at(indexOferta).setDistancia(novadistancia);
		break;

	case 5:
		cout << "+----------------------------------------------------------+\n";
		cout << "| Indique a nova lotacao total:                            |\n";
		cout << "+----------------------------------------------------------+\n";
		cin >> novalotacao;
		_fornecedores.at(index)->getOfertas().at(indexOferta).setLotacao(novalotacao);
		break;

	case 6:

		cout << "+----------------------------------------------------------+\n";
		cout << "| Indique a data da viagem (YY/MM/DD H:M):                 |\n";
		cout << "+----------------------------------------------------------+\n";

		cin.ignore(INT_MAX, '\n');
		getline(cin, novahora);
		tempo = new Time(novahora);
		_fornecedores.at(index)->getOfertas().at(indexOferta).setTime(*tempo);
		break;



	case 7:
		cout << "+----------------------------------------------------------+\n";
		cout << "| Indique o novo preco total:                              |\n";
		cout << "+----------------------------------------------------------+\n";
		cin >> novopreco;
		_fornecedores.at(index)->getOfertas().at(indexOferta).setPreco(novopreco);
		break;


	default:
		cout << "Essa opcao nao e viável. Pressione Enter para voltar ao menu anterior.";

	}
	cin.get();
	return;

	addOfertasQueue();
	aplicaDesconto();
}

void Empresa::removeOferta() {


	titulo();

	string ofertaremover, nomeFornecedor;
	bool nfound = true;


	cout << "+----------------------------------------------------------+\n";
	cout << "| Qual e o fornecedor com a oferta a remover?	            |\n";
	cout << "+----------------------------------------------------------+\n";

	displayFornecedorescomOfertas();

	cin.ignore(INT_MAX, '\n');
	getline(cin, nomeFornecedor);


	int index = BinarySearch(_fornecedores, nomeFornecedor);
	if (index == -1) { throw ObjetoInexistente<Fornecedor>(nomeFornecedor); }


	cout << "+----------------------------------------------------------+\n";
	cout << "| Estas sao as ofertas desse fornecedor:                   |\n";
	cout << "+----------------------------------------------------------+\n";
	_fornecedores.at(index)->displayOfertas();

	cout << "+----------------------------------------------------------+\n";
	cout << "| Qual e a oferta a remover?	                            |\n";
	cout << "+----------------------------------------------------------+\n";


	

	getline(cin,ofertaremover);
	for (unsigned int i = 0; i < _fornecedores.at(index)->getOfertas().size(); i++)
	{
		if (ofertaremover == _fornecedores.at(index)->getOfertas().at(i).getNome()){
			_fornecedores.at(index)->getOfertas().erase(_fornecedores.at(index)->getOfertas().begin() + i);
			nfound = false;	
		}
	}
	if(nfound){
		throw ObjetoInexistente<Oferta>(ofertaremover);
	}
	cout << "Oferta removida com sucesso" << endl;
	cout << "Pressione Enter para regressar" << endl;

}

void Empresa::menuTipodeUtilizador()
{
	
	
	int tipodeutilizador;
	while (true){
		titulo();
		
		cout << "+----------------------------------------------------------+\n";
		cout << "| Escolha o tipo de opcao sobre o qual quer trabalhar      |\n";
		cout << "+----------------------------------------------------------+\n";
		cout << "| Selecione a sua opcao (insira apenas o numero):          |\n";
		cout << "+----------------------------------------------------------+\n";
		cout << "| 1 - Gestao de Clientes                                   |\n";
		cout << "| 2 - Gestao de Fornecedores                               |\n";
		cout << "| 3 - Gestao de Reservas                                   |\n";
		cout << "| 4 - Gestao de Ofertas                                    |\n";
		cout << "| 0 - Sair                                                 |\n";
		cout << "+----------------------------------------------------------+\n";

		cin >> tipodeutilizador;

		if (cin.fail()){
			cin.clear();
			cin.ignore(INT_MAX,'\n');
			clearScreen();
			cout << "Erro: Introduziu um input invalido. So pode usar numeros inteiros." << endl;
			cout << "Pressione Enter para voltar ao menu" << endl;
			cin.get();
		}

		switch (tipodeutilizador) {

		case 0:
			cout << "\n" << "Agradecemos a utilizacao do nosso servico, a aplicacao ira agora fechar.\n";
			return;
			break;
		case 1:
			menuCliente();
			break;
		case 2:
			menuFornecedor();
			break;

		case 3:
			menuReservas();
			break;

		case 4:
			menuOfertas();
			break;
		default:
			clearScreen();
			cout << "Lamento, mas a opcao que inseriu nao e valida. Tente outra vez. \n";
			cin.get();
			clearScreen();
		}
	}
	addOfertasQueue();
	aplicaDesconto();
}

void Empresa::menuInicial()
{
	cout << "\n" << endl;
	titulo();
	cout << "\n";
	cout << "\n";
	cout << "Seja bem vindo ao gestor da Porto Rivers, aqui podera controlar todas as vertentes da sua empresa e visualizar toda a informacao de que necessita. \n";
	cout <<  "Pressione qualquer tecla para continuar" << endl;
	cin.get();
	menuTipodeUtilizador();
	clearScreen();

}
