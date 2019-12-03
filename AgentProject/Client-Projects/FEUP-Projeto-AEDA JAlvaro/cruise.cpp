
#include <fstream>
#include "cruise.h"
#include "extras.h"
#include <iostream>
#include <ostream>


using namespace std;


                      /////                                            /////
                     /////               CRUISE . CPP                 /////
                    /////                                            /////

/// Metodos da classe Empresa ////


/**
 * @brief      Constructs object of type Empresa
 */
Empresa::Empresa(): _faturas(Fatura(NULL)){
	this->load();
	atualizaInatividade();
	addOfertasQueue();
	sort();
	this->menuInicial();
	this->save();
}

const std::vector<Fornecedor*> & Empresa::getFornecedores(){
	return this->_fornecedores;
}

const std::vector<Cliente*> & Empresa::getClientes(){
	return this->_clientes;
}

Empresa & Empresa::addFornecedores(Fornecedor& f){
	this->_fornecedores.push_back(&f);
	return *this;
}

Empresa & Empresa::addClientes(Cliente &c){
	this->_clientes.push_back(&c);
	return *this;
}


Empresa & Empresa::addReservas(Reserva& r){
	this->_reservas.push_back(&r);
	return *this;
}


Empresa & Empresa::deleteClientes(string name){
	int index = BinarySearch(this->_clientes,name);
	if(index != -1){
		_clientes.erase(_clientes.begin() + index);
	}
	else{
		throw ObjetoInexistente<string>(name);
	}
	return *this;
}


Empresa & Empresa::deleteFornecedores(string name) {

	for (unsigned int i = 0; i < _fornecedores.size(); i++)
	{
		if (name == _fornecedores.at(i)->getNome())
			_fornecedores.erase(_fornecedores.begin() + i);
	}
	return *this;
}


Empresa & Empresa::deleteReservas(string name) {

	for (unsigned int i = 0; i < _reservas.size(); i++)
	{
		if (name == _reservas.at(i)->getNomeCliente())
			_reservas.erase(_reservas.begin() + i);
	}
	return *this;
}

Fornecedor & Fornecedor::deleteOfertas(string name) {
	for (unsigned int i = 0; i < ofertas.size(); i++)
	{
		if (name == this->ofertas.at(i).getNome())
			ofertas.erase(ofertas.begin() + i);
	}
	return *this;

}


void Empresa::displayClientes()
{
	cout << endl;
	for (unsigned int i = 0; i < _clientes.size(); i++) {
		cout << "Cliente: " << _clientes.at(i)->getNome() << endl << "Morada: " << _clientes.at(i)->getMorada() << endl << "Pontos: " << _clientes.at(i)->getPontos() << endl;
		if (_clientes.at(i)->isRegistado()) {
			cout << "Registado: Sim" << endl << endl;
		}
		else cout << "Registado: Nao" << endl << endl;
	}
}


void Empresa::displayFornecedores()
{
	cout << endl;
	for (unsigned int i = 0; i < _fornecedores.size(); i++)
	{
		cout << "Fornecedor: " << _fornecedores.at(i)->getNome() << endl
			<< "NIF: " << _fornecedores.at(i)->getNif() << endl
			<< "Morada: " << _fornecedores.at(i)->getMorada() << endl
			<< "Definicoes de Fornecedor: " << endl
			<< "Preco Base Iate:" << _fornecedores.at(i)->getDefinicoesFornecedor().at(1) << endl
			<< "Preco Base Barco Rebelo:" << _fornecedores.at(i)->getDefinicoesFornecedor().at(2) << endl
			<< "Preco Base Veleiro:" << _fornecedores.at(i)->getDefinicoesFornecedor().at(3) << endl
			<< "Preco por pessoa global:" << _fornecedores.at(i)->getDefinicoesFornecedor().at(0) << endl << endl;

	}
}

void Empresa::displayFornecedorescomOfertas()
{
	cout << endl;
	for (unsigned int i = 0; i < _fornecedores.size(); i++)
	{
		cout << "Fornecedor: " << _fornecedores.at(i)->getNome() << endl
			<< "NIF: " << _fornecedores.at(i)->getNif() << endl
			<< "Morada: " << _fornecedores.at(i)->getMorada() << endl
			<< "Definicoes de Fornecedor: " << endl
			<< "Preco Base Iate:" << _fornecedores.at(i)->getDefinicoesFornecedor().at(1) << endl
			<< "Preco Base Barco Rebelo:" << _fornecedores.at(i)->getDefinicoesFornecedor().at(2) << endl
			<< "Preco Base Veleiro:" << _fornecedores.at(i)->getDefinicoesFornecedor().at(3) << endl
			<< "Preco por pessoa global:" << _fornecedores.at(i)->getDefinicoesFornecedor().at(0) << endl << endl;
		_fornecedores.at(i)->displayOfertas();
		cout << endl;


	}
}

void Empresa::displayReservas()
{
	cout << endl;
	for (unsigned int i = 0; i < _reservas.size(); i++)
	{
		cout << "Fornecedor: " << _reservas.at(i)->getNomeFornecedor() << endl
			<< "Oferta: ";  _reservas.at(i)->getOferta()->printOferta();
		cout << "Cliente: " << _reservas.at(i)->getCliente()->getNome() << endl
			<< "Pontos do Cliente: " << _reservas.at(i)->getCliente()->getPontos() << endl
			<< "Preco (a pagar): " << _reservas.at(i)->getPreco() << endl
			<< "Cancelada: " << (_reservas.at(i)->isCancelada()? "sim" : "nao") << endl << endl;

	}
}


void Empresa::listaFaturas() {

	BSTItrIn<Fatura> it(_faturas);
	while (!it.isAtEnd()) {


		cout << "----------------------------------------------------\n" << endl;

		cout << "Nome do cliente: " << it.retrieve().getNomeCliente() << endl;
		cout << "Fornecedor: " << it.retrieve().getFornecedor() << endl;
		cout << "Data de faturacao: ";
		it.retrieve().getData().printTime(cout);
		cout << endl;
		it.advance();
	}

	
}

void Empresa::load(){
	ifstream clientes_file("clientes.txt");
	ifstream registados_file("clientes_registados.txt");
	ifstream fornecedores_file("fornecedores.txt");
	ifstream reservas_file("reservas.txt");
	string line;
	string s1;
	string s2;
	string s3;
	string morada;
	unsigned int num1;
	unsigned int num2;
	long unsigned int num3;
	vector<int> v;
	unsigned int p;
	vector<string> destinos;
	Cliente * c = NULL;
	Fornecedor * f;
	Oferta * o = NULL;
	Reserva * r;
	Fatura * l;
	Time * t;
	Time * t2;
	vector<Oferta> ofertas;
	//Stores the clients who aren't registered in the data base
	if(clientes_file.is_open())
		while(getline(clientes_file,line)){
			s1 = line;
			getline(clientes_file,line);
			s2 = line;
			c = new Cliente(s1,s2);
			this->addClientes(*c);
		}
	else {
		cout << "O programa falhou a abrir o ficheiro com a informacao de clientes" << endl;
	}
	clientes_file.close();
	//Stores the clients who are registered in the data base
	s1.clear();
	s2.clear();
	if(registados_file.is_open())
			while(getline(registados_file,line)){
				s1 = line;
				getline(registados_file,line);
				s2 = line;
				getline(registados_file,line,'\n');
				num1 = stoi(line);
				c = new ClienteRegistado(s1,s2,num1);
				this->addClientes(*c);
			}
		else {
			cout << "O programa falhou a abrir o ficheiro com a informacao de clientes registados" << endl;
		}
	registados_file.close();
   //Stores the supplier
	if(fornecedores_file.is_open()){
			while(getline(fornecedores_file,line)){
				s1 = line;
				getline(fornecedores_file,line,'\n');
				num3 = stoi(line);
				getline(fornecedores_file,line);
				s2 = line;
				f = new Fornecedor(s1,num3,s2);
				getline(fornecedores_file,line);
				v.push_back(stoi(line));
				getline(fornecedores_file,line);
				v.push_back(stoi(line));
				getline(fornecedores_file,line);
				v.push_back(stoi(line));
				getline(fornecedores_file,line);
				v.push_back(stoi(line));
				f->setDefenicoes(v);
				v.clear();
				while(true){
					getline(fornecedores_file,line);
					if(line == "fend")
						break;
					else{
						s1 = line;
						getline(fornecedores_file,line);
						s2 = line;
						getline(fornecedores_file,line,'\n');
						num1 = stoi(line);
						getline(fornecedores_file,line,'\n');
						num2 = stoi(line);
						getline(fornecedores_file,line);
						t = new Time(line);
						getline(fornecedores_file,line);
						t2 = new Time(line);
						getline(fornecedores_file,line,'\n');

						p = stoi(line);
						getline(fornecedores_file,line);
						if(line == "oend"){
							break;
						}
						else{
							do{
								destinos.push_back(line);
								getline(fornecedores_file,line);
							} while(line != "oend");
						}
						o = new Oferta(s1,s2,destinos,num1,num2,*t,p);
						o->setTimeUltimaReserva(*t2);
						f->addOferta(*o);
						destinos.clear();


					}
				}

				this->addFornecedores(*f);
			}
	}
		else {
			cout << "O programa falhou a abrir o ficheiro com a informacao de fornecedores" << endl;
		}
	fornecedores_file.close();

	bool cancelada;
	if(reservas_file.is_open()){
		while (getline(reservas_file, line)) {
			s1 = line;
			getline(reservas_file, line);
			s2 = line;
			getline(reservas_file, line);
			if (line == "true") {
				cancelada = true;
			}
			else cancelada = false;
			getline(reservas_file, line, '\n');

			num1 = stoi(line);
			for (unsigned int i = 0; i < this->_clientes.size(); i++) {
				if (this->_clientes[i]->getNome() == s2) {
				c = this->_clientes[i];
				}
			}
			for (unsigned int i = 0; i < this->_fornecedores.size(); i++) {
				for (unsigned int j = 0; j < this->_fornecedores[i]->getOfertas().size(); j++) {
					if (this->_fornecedores[i]->getOfertas().at(j).getNome() == s1) {
						*o = this->_fornecedores[i]->getOfertas()[j];
					}
				}
			}
			r = new Reserva(s1, o, s2, c, num1, cancelada);
			this->addReservas(*r);
			l = new Fatura(r);
			this->addFaturas(*l);
			
		}
	}
	else{
		cout << "Erro: O programa nao conseguiu abrir o ficheiro das reservas" << endl;
	}
	this->sort();


	reservas_file.close();
}
void Empresa::save(){
	ofstream clientes_file("clientes.txt");
	ofstream registados_file("clientes_registados.txt");
	ofstream fornecedores_file("fornecedores.txt");
	ofstream reservas_file("reservas.txt");
	if(!clientes_file.is_open()){
		cout << "O programa nao consegue abrir o ficheiro de clientes" << endl;
		return;
	}
	if(!registados_file.is_open()){
		cout << "O programa nao consegue abrir o ficheiro de clientes registados" << endl;
		return;
	}
	if(!fornecedores_file.is_open()){
		cout << "O programa nao consegue abrir o ficheiro de fornecedores" << endl;
		return;
	}
	if(!reservas_file.is_open()){
		cout << "O programa nao consegue abrir o ficheiro de reservas" << endl;
		return;
	}
	for(unsigned int i = 0; i < this->_clientes.size(); i++){
		if(this->_clientes[i]->isRegistado())
			registados_file << this->_clientes[i]->getNome() << endl << this->_clientes[i]->getMorada() << endl << this->_clientes[i]->getPontos();
		else
			clientes_file << this->_clientes[i]->getNome() << endl << this->_clientes[i]->getMorada();
		if(i < this->_clientes.size() -1){
			if(this->_clientes[i]->isRegistado())
						registados_file << endl;
			else
						clientes_file << endl;
		}
	}
	for(unsigned int i = 0; i < this->_fornecedores.size(); i++){
		fornecedores_file << this->_fornecedores[i]->getNome() << endl;
		fornecedores_file << this->_fornecedores[i]->getNif() << endl;
		fornecedores_file << this->_fornecedores[i]->getMorada() << endl;
		fornecedores_file << this->_fornecedores[i]->getDefinicoesFornecedor().at(0) << endl;
		fornecedores_file << this->_fornecedores[i]->getDefinicoesFornecedor().at(1) << endl;
		fornecedores_file << this->_fornecedores[i]->getDefinicoesFornecedor().at(2) << endl;
		fornecedores_file << this->_fornecedores[i]->getDefinicoesFornecedor().at(3) << endl;
		for(unsigned int j = 0; j < this->_fornecedores[i]->getOfertas().size(); j++){
			fornecedores_file << this->_fornecedores[i]->getOfertas()[j].getNome() << endl;
			fornecedores_file << this->_fornecedores[i]->getOfertas()[j].getBarco() << endl;
			fornecedores_file << this->_fornecedores[i]->getOfertas()[j].getDistancia() << endl;
			fornecedores_file << this->_fornecedores[i]->getOfertas()[j].getLotacao() << endl;
			fornecedores_file << this->_fornecedores[i]->getOfertas()[j].getData() << endl;
			fornecedores_file << this->_fornecedores[i]->getOfertas()[j].getUltimaReserva() << endl;
			fornecedores_file << this->_fornecedores[i]->getOfertas()[j].getPreco() << endl;
			for(unsigned int k = 0; k < this->_fornecedores[i]->getOfertas()[j].getDestinos().size(); k++){
				fornecedores_file << this->_fornecedores[i]->getOfertas()[j].getDestinos()[k] << endl;
			}
			if(this->_fornecedores[i]->getOfertas().size() != 0){
				fornecedores_file << "oend" << endl;
			}

		}
		fornecedores_file << "fend";
		if(i < this->_fornecedores.size()-1){
			fornecedores_file << endl;
		}
	}
	for(unsigned int i = 0; i < this->_reservas.size(); i++){
		reservas_file << this->_reservas[i]->getNomeFornecedor() << endl;
		reservas_file << this->_reservas[i]->getNomeCliente() << endl;
		if(this->_reservas[i]->isCancelada()){
			reservas_file << "true" << endl;
		}
		else reservas_file << "false" << endl;


		reservas_file << this->_reservas[i]->getPreco() << endl;
	}
}
void Empresa::sort(){
	selectionSort(this->_clientes);
	selectionSort(this->_fornecedores);
}

//// Metodos da classe Fornecedor ////

Fornecedor::Fornecedor(string nome, long unsigned int nif, string morada):nome(nome), nif(nif), morada(morada){}

void Fornecedor::addOferta(Oferta & oferta){
	this->ofertas.push_back(oferta);
}

vector<Oferta> & Fornecedor::getOfertas(){
	return this->ofertas;
}


int Fornecedor::calculaPreco(int tipodebarco, int lotacao, int distancia) {

	return (definicoesfornecedor.at(tipodebarco) + definicoesfornecedor.at(0) * lotacao)*distancia/1000 ; //1 - iate; 2 - barco rabelo; 3 - veleiro;

}



void Fornecedor::displayOfertas() {
	
	cout << endl;

	for (unsigned int i = 0; i < ofertas.size(); i++)
	{
		cout << "Nome: " << ofertas.at(i).getNome() << endl;
		cout << "Barco: " << ofertas.at(i).getBarco() << endl;
		cout << "Destinos:" << endl;
		for (unsigned int j = 0; j < ofertas.at(i).getDestinos().size(); j++) {

			cout << "	Destino numero " << j + 1 << " : " << ofertas.at(i).getDestinos().at(j) << endl;
		}
		cout << "Distancia: " << ofertas.at(i).getDistancia() << endl;
		cout << "Lotacao: " << ofertas.at(i).getLotacao() << endl;
		cout << "Data: " << ofertas.at(i).getData() << endl;
		cout << "Preco (por pessoa): " << calculaPreco(ofertas.at(i).getBarcoNumber(), ofertas.at(i).getLotacao(), ofertas.at(i).getDistancia()) / ofertas.at(i).getLotacao() << endl;
		cout << "Preco (total): " << calculaPreco(ofertas.at(i).getBarcoNumber(), ofertas.at(i).getLotacao(), ofertas.at(i).getDistancia()) << endl << endl;

	}
}



//// Metodos da classe Reserva ////

Reserva::Reserva(string nome_fornecedor, Oferta * oferta, string nome_cliente, Cliente * cliente, unsigned int preco, bool cancelada):
		nome_fornecedor(nome_fornecedor), oferta(oferta), nome_cliente(nome_cliente),cliente(cliente),preco(preco), cancelada(cancelada) {
	this->data = RealTime();
}



//// Metodos da classe Cliente ////

Cliente::Cliente(string nome, string morada): nome(nome), morada(morada){}


//// Metodos da classe ClienteRegistado ////

ClienteRegistado::ClienteRegistado(string nome, string morada,unsigned int pontos): Cliente(nome, morada),pontos(pontos){}

void ClienteRegistado::setPontos(unsigned int pontos){
	this->pontos = pontos;
}

//// Metodos da classe Cliente Inativo ////

ClienteInativo::ClienteInativo(Cliente * ptr): ptr(ptr){}

string ClienteInativo::getNome() const {
	return this->ptr->getNome();
}

string ClienteInativo::getMorada() const{
	return this->ptr->getMorada();
}

void ClienteInativo::setMorada(string novaMorada){
	this->setMorada(novaMorada);
}


//// Metodos da classe Oferta ////
Oferta::Oferta(string name,string boat, vector<string> dest, unsigned int dist, unsigned int lot, Time  date, unsigned int price): nome(name),
barco(boat),
destinos(dest),
distancia(dist),
lotacao(lot),
data(date),
preco(price)
{
	RealTime * rt = new RealTime();
	Time tempooferta(rt->getMinutes(),rt->getHours(),rt->getDay(), rt->getMonth(),rt->getYear() - 1000);
	
	ultimaReserva = tempooferta;
};

const std::vector<std::string> & Oferta::getDestinos(){
	return this->destinos;
}

int Oferta::getBarcoNumber()
{
	if (barco == "iate")
		return 1;
	else if (barco == "barco rabelo" || barco == "barco_rabelo")
		return 2;
	else if (barco == "veleiro")
		return 3;
	else return -1;

}

string Oferta::getData() {

	return to_string(data.getYear()) + "/" + to_string(data.getMonth()) + "/" + to_string(data.getDay()) + " " + to_string(data.getHours()) + ":" + to_string(data.getMinutes());
}

void Oferta::printOferta()
{

	cout << "Nome: " << getNome() << endl;
	cout << "Barco: " <<getBarco() << endl;
	cout << "Destinos:" << endl;

	for (unsigned int j = 0; j < getDestinos().size(); j++) {

		cout << "	Destino numero" << j + 1 << " : " << getDestinos().at(j) << endl;
	}
	cout << "Distancia: " << getDistancia() << "\n";
	cout << "Lotacao: " << getLotacao() << endl;
	cout << "Data: " << getData() << endl;
	cout << "Preco: " << getPreco() << endl;
}

//priority queue stuff

void Empresa::addOfertasQueue()
{
	while (!queueOfertasOrdenadas.empty()) {
		queueOfertasOrdenadas.pop();
	}

	for (unsigned int i = 0; i < _fornecedores.size(); i++)
	{
		for (unsigned int j = 0; j < _fornecedores[i]->getOfertas().size(); j++)
		{
			queueOfertasOrdenadas.push(_fornecedores[i]->getOfertas()[j]);
		}
	}
}


void Empresa::displayOfertasemOrdem() {

	pq_ofertas temp = queueOfertasOrdenadas;


	cout << endl;
	while (!(temp.empty())) {
		Oferta ofertatemp = temp.top();

		cout << "Nome: " << ofertatemp.getNome() << endl;
		cout << "Barco: " << ofertatemp.getBarco() << endl;
		cout << "Destinos:" << endl;
		for (unsigned int j = 0; j < ofertatemp.getDestinos().size(); j++) {

			cout << "Destino numero " << j + 1 << " : " << ofertatemp.getDestinos().at(j) << endl;
		}
		cout << "Distancia: " << ofertatemp.getDistancia() << endl;
		cout << "Lotacao: " << ofertatemp.getLotacao() << endl;
		cout << "Data: " << ofertatemp.getData() << endl;
		cout << "Preco (por pessoa): " << ofertatemp.getPreco() / ofertatemp.getLotacao() << endl;
		cout << "Preco (total): " << ofertatemp.getPreco() << endl << endl;
		temp.pop();

	}
}

void Empresa::aplicaDesconto() {
	int antigopreco;
	
	Oferta ofertatemp = queueOfertasOrdenadas.top();
	antigopreco = ofertatemp.getPreco();
	ofertatemp.setPreco(antigopreco*0.8);
	queueOfertasOrdenadas.pop();
	queueOfertasOrdenadas.push(ofertatemp);
}
//Hash table stuff


Empresa & Empresa::desativaCliente(Cliente * c){
	ClienteInativo ci(c);
	this->_clientesInativos.insert(ci);
	return *this;
}

Empresa & Empresa::atualizaInatividade(){
	Time ultimaReserva;
	RealTime rt;
	ClienteInativo * ci;
	for(unsigned int i = 0; i < this->_reservas.size(); i++){
		ci = new ClienteInativo(this->_reservas[i]->getCliente());
		if(this->_clientesInativos.find(*ci) != this->_clientesInativos.end()){
				continue;
		}
		if(this->_reservas[i]->getData().diferencaDias() > (6*30)){
			this->_clientesInativos.insert(*ci);
		}

	}

	return *this;
}

Empresa & Empresa::reativaCliente(Cliente * c){
	ClienteInativo ci(c);
	this->_clientesInativos.erase(ci);
	return *this;
}


void Empresa::displayClientesInativos(){
	tabHInativos::const_iterator it;
	cout << endl;
	for(it = this->_clientesInativos.begin();it != this->_clientesInativos.end();it++){
		cout << "Nome: " <<  it->getNome() << endl << "Morada: " << it->getMorada() << endl << endl;
	}
}


//BST stuff
Fatura::Fatura(Reserva* r): reserva(r) {}

Empresa& Empresa::addFaturas(Fatura& r) {
	this->_faturas.insert(r);
	return *this;
}

Reserva * Fatura::getReserva() {
	return reserva;
}

string Fatura::getNomeCliente() const{
	return this->reserva->getNomeCliente();
}

Time Fatura::getData() const{
	return this->reserva->getData();
}

Time Fatura::getData() {
	return this->reserva->getData();
}


bool Fatura::operator<(const Fatura& f1) const {
	if (this->getNomeCliente() != f1.getNomeCliente()) {
		return this->getNomeCliente() < f1.getNomeCliente();
	}
	else return this->getData() < f1.getData();
}

string Fatura::getFornecedor() {
	return this->reserva->getNomeFornecedor();
}

bool Fatura::operator==(const Fatura& f1) const {
	return (this->getNomeCliente() == f1.getNomeCliente()) && (this->getData() == f1.getData());
}
