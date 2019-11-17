 #include "servicos.h"

using namespace std;


//------------------------------SERVICO------------------------------


servico::servico()
{}


servico::servico(string nome, GPS gps) : nome(nome), gps(gps)
{}


servico::~servico()
{}


GPS servico::getGPS() const {
	return gps;
}


string servico::getNome() const {
	return nome;
}
string servico::getTipo() const {
	return tipo;
}

bool servico::getAberto() const
{
	return aberto;
}

data servico::getData() const
{
	return dt;
}

string servico::getInfo() const
{
	string info;

	info += "Tipo do servico: " + tipo + ", ";
	info += "nome do servico: " + nome + ", ";
	info += "data da ultima inspecao: " + dt.getInfo();

	return info;
}

void servico::setTipo(string tipo)
{
	this->tipo = tipo;
}

void servico::setAberto(bool aberto)
{
	this->aberto = aberto;
}

void servico::setData(data dt)
{
	this->dt = dt;
}

void servico::makeInspection(data dt)
{
	this->dt = dt;
}


bool operator<(const servico& srvc1, const servico& srvc2) {
	return (srvc2.getData() < srvc2.getData());
}

std::ostream& operator<<(std::ostream& os, const servico& srvc){
	return (os << srvc.getInfo());
}


//------------------------------NADADOR------------------------------


nadadorSalvador::nadadorSalvador()
{}


nadadorSalvador::nadadorSalvador(string nome): servico(nome,GPS(0,0))
{
	setTipo("nadadorSalvador");
}


nadadorSalvador::~nadadorSalvador()
{}

//------------------------------CAFE------------------------------


cafe::cafe()
{}


cafe::cafe(string nome, GPS gps) : servico(nome, gps)
{
	setTipo("cafe");
}

cafe::~cafe()
{}

//------------------------------RESTAURANTE------------------------------

restaurante::restaurante()
{}

restaurante::restaurante(string nome, GPS gps) : servico(nome, gps)
{
   setTipo("restaurante");
}

restaurante::~restaurante()
{}

//------------------------------CAMPO------------------------------

campoDesportivo::campoDesportivo()
{}

campoDesportivo::campoDesportivo(string nome, GPS gps) : servico(nome, gps)
{
	setTipo("campoDesportivo");
}

campoDesportivo::~campoDesportivo()
{}


//------------------------------SERVICOFORADAPRAIA------------------------------


servicoForaDaPraia::servicoForaDaPraia()
{}

servicoForaDaPraia::servicoForaDaPraia(string nome, GPS gps) : servico(nome, gps)
{}

servicoForaDaPraia::~servicoForaDaPraia()
{}

void servicoForaDaPraia::close(bool permanente, data dt)
{
	setAberto(false);
	this->permanente = permanente;
	setData(dt);
}

void servicoForaDaPraia::open(data dt)
{
	setAberto(true);
	setData(dt);
}

//------------------------------PONTOTURISTICO------------------------------



pontoTuristico::pontoTuristico()
{}

pontoTuristico::pontoTuristico(string nome, GPS gps) : servicoForaDaPraia(nome, gps)
{
	setTipo("pontoTuristico");
}

pontoTuristico::~pontoTuristico()
{}

//------------------------------ALOJAMENTO------------------------------


alojamento::alojamento()
{}

alojamento::alojamento(string nome, GPS gps) : servicoForaDaPraia(nome, gps)
{
	setTipo("alojamento");
}

alojamento::~alojamento()
{}

