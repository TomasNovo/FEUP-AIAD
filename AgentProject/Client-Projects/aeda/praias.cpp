#include "praias.h"
#include "algoritmos.cpp"
#include "utilities.h"
#include <sstream>
#include <fstream>

using namespace std;

//------------------------------PRAIAFLUVIAL------------------------------


praiaFluvial::praiaFluvial()
{}


praiaFluvial::praiaFluvial(string nome, string concelho, GPS gps, bool bandeiraazul, unsigned int capacidade, vector<servico*> servicosdapraia) : nome(nome), concelho(concelho), gps(gps), bandeiraazul(bandeiraazul), capacidade(capacidade), servicosdapraia(servicosdapraia)
{}

praiaFluvial::praiaFluvial(const praiaFluvial& praia)
{
	(*this) = praia;
}

praiaFluvial::~praiaFluvial()
{}

/**
 * @brief      Gets the praia's name.
 *
 * @return     The praia's name.
 */
string praiaFluvial::getNome() const {
	return this->nome;
}

/**
 * @brief      Gets the gps.
 *
 * @return     The gps.
 */
GPS praiaFluvial::getGPS() const {
	return this->gps;
}
/**
 * @brief      Gets the praia's concelho.
 *
 * @return     The praia's concelho.
 */
string praiaFluvial::getConcelho() const {
	return this->concelho;
}
/**
 * @brief      Gets the praia's bandeira azul.
 *
 * @return     The praia's bandeira azul.
 */
bool praiaFluvial::getBandeiraAzul() const {
	return bandeiraazul;
}

/**
 * @brief      Gets the praia's capacidade.
 *
 * @return     The praia's capacidade.
 */
unsigned int praiaFluvial::getCapacidade() const {
	return capacidade;
}

vector<servico*> praiaFluvial::getServicos() const {
	return servicosdapraia;
}


string praiaFluvial::getTipo() const {
	return tipo;
}
/**
 * @brief      Gets the information from a praiaFluvial.
 *
 * @return     The information.
 */
string praiaFluvial::getInfo() const
{
	string info;

	info += "Tipo da praia: " + tipo + ", ";
	info += "Nome da praia: " + nome + ", ";
	info += "Concelho onde a praia se situa: " + concelho + ", ";
	info += "Capacidade da praia: " + to_string(capacidade) + ", ";
	if (bandeiraazul == true)
	{
		info += "A praia possui bandeira azul, ";
	}
	else
	{
		info += "A praia nao possui bandeira azul, ";
	}

	return info;
}


void praiaFluvial::setNome(string nome) {
	this->nome = nome;
}

void praiaFluvial::setGPS(GPS gps) {
	this->gps = gps;
}

void praiaFluvial::setBandeira(bool bandeiraazul) {
	this->bandeiraazul = bandeiraazul;
}

void praiaFluvial::setTipo(string tipo) {
	this->tipo = tipo;
}


void praiaFluvial::listServicos() const
{
	for (int i = 0; i < servicosdapraia.size(); ++i)
	{
		cout << (*servicosdapraia[i]) << '\n';
	}
}



bool praiaFluvial::operator<(const praiaFluvial& praia1) const {
	if (this->concelho != praia1.getConcelho())
		return (this->concelho < praia1.getConcelho());

	else
		return (this->bandeiraazul < praia1.getBandeiraAzul());
}

bool praiaFluvial::operator==(const praiaFluvial& praia1) const {
	return (this->nome == praia1.getNome());
}

unsigned int praiaFluvial::getLargura() const {
	return 0;
}

unsigned int praiaFluvial::getCaudal() const {
	return 0;
}

unsigned int praiaFluvial::getProfundidade() const {
	return 0;
}

unsigned int praiaFluvial::getArea() const {
	return 0;
}

void praiaFluvial::print(ostream& os) const {
	os << this->getInfo();
}

ostream& operator<<(ostream & os, const praiaFluvial& praia) {
	praia.print(os);
	return (os);
}

//------------------------------RIO------------------------------

rio::rio()
{
	setTipo("rio");
}

rio::rio(string nome, string concelho, GPS gps, bool bandeiraazul, unsigned int capacidade, vector<servico*> servicosdapraia, unsigned int larguraMax, unsigned int caudalMax, unsigned int profundidadeMax): praiaFluvial(nome,concelho,gps,bandeiraazul,capacidade, servicosdapraia), larguraMax(larguraMax), caudalMax(caudalMax), profundidadeMax(profundidadeMax)
{
	setTipo("rio");
}

rio::~rio()
{}


unsigned int rio::getLargura() const {
	return larguraMax; 
}

unsigned int rio::getCaudal() const { 
	return caudalMax;
}

unsigned int rio::getProfundidade() const {
	return profundidadeMax;
}

string rio::getInfo() const
{
	string info_rio = praiaFluvial::getInfo();

	info_rio += "A praia trata-se de uma praia fluvial de rio, ";
	info_rio += "Largura Minima da praia: " + to_string(larguraMax) + ", ";
	info_rio += "Caudal Maximo da praia: " + to_string(caudalMax) + ", ";
    info_rio += "Profundidade Maximo da praia: " + to_string(profundidadeMax);

	return info_rio;
}

//------------------------------ALBUFEIRA------------------------------

albufeira::albufeira()
{
	setTipo("albufeira");
}

albufeira::albufeira(string nome, string concelho, GPS gps, bool bandeiraazul, unsigned int capacidade, vector<servico*> servicosdapraia, unsigned int area) : praiaFluvial(nome, concelho, gps, bandeiraazul, capacidade, servicosdapraia), area(area)
{
	setTipo("albufeira");
}

albufeira::~albufeira()
{}


unsigned int albufeira::getArea() const {
	return area;
}

string albufeira::getInfo() const
{
	string info_albufeira = praiaFluvial::getInfo();

	info_albufeira += "A praia trata-se de uma praia fluvial de albufeira, ";
	info_albufeira += "Area da albufeira: " + to_string(area);
	
	return info_albufeira;
}


//------------------------------GESTORPRAIAS------------------------------


GestorPraias::GestorPraias()
{
	inspecoes.resize(4);
}

GestorPraias::GestorPraias(set<praiaFluvial*, comparePraia> praias, vector<servicoForaDaPraia*> servicosdefora) : praias(praias), servicosdefora(servicosdefora)
{
	inspecoes.resize(4);
}

GestorPraias::~GestorPraias()
{}


void GestorPraias::addPraia(praiaFluvial praia) {
	praias.insert(new praiaFluvial(praia));
}

void GestorPraias::removePraia(set<praiaFluvial*, comparePraia>::iterator it) {
	delete (*it);
	praias.erase(it);
}


/**
 * @brief      Gets the closest praia.
 *
 * @param[in]  gps   The GPS coordinates
 *
 * @return     The closest praia to gps.
 */

void GestorPraias::setPraias(set<praiaFluvial*, comparePraia> input) {
	praias = input;
}


set<praiaFluvial*, comparePraia> GestorPraias::getPraias() {
	return praias;
}

vector<servicoForaDaPraia*> GestorPraias::getServicos() {
	return servicosdefora;
}

praiaFluvial GestorPraias::getPraia(set<praiaFluvial*, comparePraia>::iterator it) {

	return (**it);
}

set<praiaFluvial*, comparePraia>::iterator GestorPraias::getClosestPraia(GPS gps) {

	if (praias.size() == 0)
		return praias.end();

	set<praiaFluvial*, comparePraia>::iterator it;

	set<praiaFluvial*, comparePraia>::iterator min = praias.begin();

	for (it = praias.begin(); it != praias.end(); ++it)
	{
		if ((*it)->getGPS().distance(gps) < (*min)->getGPS().distance(gps))
			min = it;
	}

	return min;
}


set<praiaFluvial*, comparePraia>::iterator GestorPraias::findPraia(string nome) {

	set<praiaFluvial*, comparePraia>::iterator it = praias.begin();

	for (it = praias.begin(); it != praias.end(); it++)
	{
		if ((*it)->getNome() == nome)
			return it;
	}

	return praias.end();
}

set<praiaFluvial*, comparePraia>::iterator GestorPraias::findPraia(GPS gps) {

	set<praiaFluvial*, comparePraia>::iterator it = praias.begin();

	for (it = praias.begin(); it != praias.end(); it++)
	{
		if ((*it)->getGPS() == gps)
			return it;
	}

	return praias.end();
}

bool GestorPraias::isEnd(set<praiaFluvial*, comparePraia>::iterator &it) {
	return (it == praias.end());
}


bool lesserConcelho(praiaFluvial praia1, praiaFluvial praia2) {
	return (praia1.getConcelho() < praia2.getConcelho());
}


/*void GestorPraias::servicosInfo(praiaFluvial praia)
{
	string nome;
	GPS gps;
	string cafes, restaurantes, nadador, campos;
	int c = 0, r = 0, ns = 0, cd = 0;

	for (unsigned int i = 0; i < praias.size(); i++)
	{
		if (praia.getNome() == praias[i]->getNome() )
		{
			for (unsigned int u = 0; u < praias[i]->getServicos().size(); u++)
			{
				gps = praias[i]->getServicos().at(u).getGPS();

				if (praias[i]->getServicos().at(u).getTipo() == "restaurante")
				{
					r++;
				}
				else if (praias[i]->getServicos().at(u).getTipo() == "cafe")
				{
					c++;
				}
				else if (praias[i]->getServicos().at(u).getTipo() == "campoDesportivo")
				{
					cd++;
				}
				else if (praias[i]->getServicos().at(u).getTipo() == "nadador")
				{
					ns++;
				}
			}
		}
	}
	
	cout << "A praia possui " << c << " cafes, " << r << "restaurantes, " << cd << " campos desportivos e " << ns << " nadadores salvadores\n" ;

}*/


void GestorPraias::makePraiaInspection(string srvcname, string tipo, data dt)
{
	vector<servico*> temp;
	int index = -1;
	
	if (tipo == "nadadorSalvador")
		index = 0;
	else if (tipo == "cafe")
		index = 1;
	else if (tipo == "restaurante")
		index = 2;
	else if (tipo == "campoDesportivo")
		index = 3;

	while (inspecoes[index].size() != 0)
	{
		temp.push_back(inspecoes[index].top());

		if (inspecoes[index].top()->getNome() == srvcname)
		{
			temp.back()->makeInspection(dt);
			break;
		}

		inspecoes[index].pop();
	}

	for (int i = 0; i < temp.size(); ++i)
	{
		inspecoes[index].push(temp[i]);
	}

}

bool GestorPraias::closeService(string srvcname, bool permanente, data dt)
{
	for (int i = 0; i < servicosdefora.size(); ++i)
	{
		if (servicosdefora[i]->getNome() == srvcname)
		{
			servicosdefora[i]->close(permanente, dt);
			servicosnaoativos.insert(servicosdefora[i]);
			servicosdefora.erase(servicosdefora.begin() + i);
			return true;
		}
	}
	return false;
}

bool GestorPraias::openService(string srvcname, data dt)
{
	for (tabHS::iterator it = servicosnaoativos.begin(); it != servicosnaoativos.end(); it++)
	{
		if ((*it)->getNome() == srvcname)
		{
			(*it)->open(dt);
			servicosdefora.push_back(*it);
			servicosnaoativos.erase(it);
			return true;
		}
	}
	return false;
}

void GestorPraias::listPraias() const
{
	for (set<praiaFluvial*, comparePraia>::iterator it = praias.begin(); it != praias.end(); it++)
	{
		cout << (**it) << '\n';
	}
}

void GestorPraias::listServicosDeFora() const
{
	for (int i = 0; i < servicosdefora.size(); ++i)
	{
		cout << *servicosdefora[i] << "\n";
	}
}

void GestorPraias::listServicosNaoAtivos() const
{
	for (auto it = servicosnaoativos.begin(); it != servicosnaoativos.end(); it++)
	{
		cout << (**it) << "\n";
	}
}

bool GestorPraias::LoadPraias(string filename) 
{
	ifstream file(filename);

	if (!file.is_open())
		return false;

	string tempPraia;

	vector<string> parser(14,"");

	vector<servico*> tempServicos;

	while (getline(file, tempPraia, '\n'))
	{
		stringstream ss(tempPraia);

		getline(ss, parser[0], ',');
		utilities::trimString(parser[0]);

		if (parser[0] == "rio") //"rio",nome,concelho,latitude,longitude,bandeiraazul,capacidade,largura,caudal,profundidade,tipo1,nome1,latitude1,longitude1,...
		{
			getline(ss, parser[1], ',');
			getline(ss, parser[2], ',');
			getline(ss, parser[3], ',');
			getline(ss, parser[4], ',');
			getline(ss, parser[5], ',');
			getline(ss, parser[6], ',');
			getline(ss, parser[7], ',');
			getline(ss, parser[8], ',');
			getline(ss, parser[9], ',');

			for(int i = 1; i <= 9; i++)
				utilities::trimString(parser[i]);

			tempServicos.resize(0);
			while (getline(ss, parser[10], ',') && getline(ss, parser[11], ',') && getline(ss, parser[12], ',') && getline(ss, parser[13], ',')) //tipo1,nome1,latitude1,longitude1,tipo2,nome2,latitude2,longitude2,...
			{
				for(int i = 10; i <= 13; i++)
					utilities::trimString(parser[i]);

				if (parser[10] == "nadadorSalvador")
				{
					tempServicos.push_back(new nadadorSalvador(parser[11]));
					inspecoes[0].push(tempServicos.back());
				}

				else if (parser[10] == "cafe")
				{
					tempServicos.push_back(new cafe(parser[11], GPS(stod(parser[12]), stod(parser[13]))));
					inspecoes[1].push(tempServicos.back());
				}

				else if (parser[10] == "restaurante")
				{
					tempServicos.push_back(new restaurante(parser[11], GPS(stod(parser[12]), stod(parser[13]))));
					inspecoes[2].push(tempServicos.back());
				}

				else if (parser[10] == "campoDesportivo")
				{
					tempServicos.push_back(new campoDesportivo(parser[11], GPS(stod(parser[12]), stod(parser[13]))));
					inspecoes[3].push(tempServicos.back());
				}

				else
					throw BadFileInput(filename);
			}

			try
			{
				praias.insert(new rio(parser[1], parser[2], GPS(stod(parser[3]), stod(parser[4])), (bool)stoi(parser[5]), stoi(parser[6]),  tempServicos, stoi(parser[7]), stoi(parser[8]), stoi(parser[9])));
			}
			catch (exception& e)
			{
				throw BadFileInput(filename);
			}


		}

		else if (parser[0] == "albufeira") //"albufeira",nome,concelho,latitude,longitude,bandeiraazul,capacidade,area
		{
			getline(ss, parser[1], ',');
			getline(ss, parser[2], ',');
			getline(ss, parser[3], ',');
			getline(ss, parser[4], ',');
			getline(ss, parser[5], ',');
			getline(ss, parser[6], ',');
			getline(ss, parser[7], ',');

			for(int i = 1; i <= 7; i++)
				utilities::trimString(parser[i]);

			tempServicos.resize(0);
			while (getline(ss, parser[10], ',') && getline(ss, parser[11], ',') && getline(ss, parser[12], ',') && getline(ss, parser[13], ',')) //tipo1,nome1,latitude1,longitude1,tipo2,nome2,latitude2,longitude2,...
			{
				for(int i = 10; i <= 13; i++)
					utilities::trimString(parser[i]);

				if (parser[10] == "nadadorSalvador")
				{
					tempServicos.push_back(new nadadorSalvador(parser[11]));
					inspecoes[0].push(tempServicos.back());
				}

				else if (parser[10] == "cafe")
				{
					tempServicos.push_back(new cafe(parser[11], GPS(stod(parser[12]), stod(parser[13]))));
					inspecoes[1].push(tempServicos.back());
				}

				else if (parser[10] == "restaurante")
				{
					tempServicos.push_back(new restaurante(parser[11], GPS(stod(parser[12]), stod(parser[13]))));
					inspecoes[2].push(tempServicos.back());
				}

				else if (parser[10] == "campoDesportivo")
				{
					tempServicos.push_back(new campoDesportivo(parser[11], GPS(stod(parser[12]), stod(parser[13]))));
					inspecoes[3].push(tempServicos.back());
				}

				else
					throw BadFileInput(filename);
			}

			try
			{
				praias.insert(new albufeira(parser[1], parser[2], GPS(stod(parser[3]), stod(parser[4])), (bool)stoi(parser[5]), stoi(parser[6]),  tempServicos, stoi(parser[7])));
			}
			catch (exception& e)
			{
				throw BadFileInput(filename);
			}
		}

		else if (parser[0] == "servicosdefora") //"servicosdefora",tipo1,nome1,latitude1,longitude1,tipo2,nome2,latitude2,longitude2,...
		{
			while(getline(ss, parser[1], ',') && getline(ss, parser[2], ',') && getline(ss, parser[3], ',') && getline(ss, parser[4], ','))
			{
				for(int i = 1; i <= 4; i++)
					utilities::trimString(parser[i]);

				if (parser[1] == "pontoTuristico")
				{
					try
					{
						servicosdefora.push_back(new pontoTuristico(parser[2], GPS(stod(parser[3]),stod(parser[4]))));
					}
					catch (exception& e)
					{
						throw BadFileInput(filename);
					}
				}

				else if (parser[1] == "alojamento")
				{
					try
					{
						servicosdefora.push_back(new alojamento(parser[2], GPS(stod(parser[3]),stod(parser[4]))));
					}
					catch (exception& e)
					{
						throw BadFileInput(filename);
					}
				}

				else
					throw BadFileInput(filename);
			}
		}
		else
			throw BadFileInput(filename);

	}

	file.close();

	return true;
}


bool GestorPraias::SavePraias(string filename) {

	ofstream file(filename);

	if (!file.is_open())
		return false;

	for (set<praiaFluvial*, comparePraia>::iterator it = praias.begin(); it != praias.end(); it++)
	{
		if (it != praias.begin())
			file << '\n';

		if ((*it)->getTipo() == "rio")
			file << (*it)->getTipo() << ',' << (*it)->getNome() << ',' << (*it)->getConcelho() << ',' << (*it)->getGPS().getLatitude() << ',' << (*it)->getGPS().getLongitude() << ',' << (*it)->getBandeiraAzul() << ',' << (*it)->getCapacidade() << ',' << (*it)->getLargura() << ',' << (*it)->getCaudal() << ',' << (*it)->getProfundidade();
		else
			file << (*it)->getTipo() << ',' << (*it)->getNome() << ',' << (*it)->getConcelho() << ',' << (*it)->getGPS().getLatitude() << ',' << (*it)->getGPS().getLongitude() << ',' << (*it)->getBandeiraAzul() << ',' << (*it)->getCapacidade() << ',' << (*it)->getArea();

		for (int j = 0; j < (*it)->getServicos().size(); ++j)
		{
			file << ',' << (*it)->getServicos()[j]->getTipo() << ',' << (*it)->getServicos()[j]->getNome() << ',' << (*it)->getServicos()[j]->getGPS().getLatitude() << ',' << (*it)->getServicos()[j]->getGPS().getLongitude();
		}
	}

	for (int i = 0; i < servicosdefora.size(); ++i)
	{
		if (i == 0)
			file << '\n' << "servicosdefora";

		file << ',' << servicosdefora[i]->getTipo() << ',' << servicosdefora[i]->getNome() << ',' << servicosdefora[i]->getGPS().getLatitude() << ',' << servicosdefora[i]->getGPS().getLongitude();
	}

	file.close();

	return true;
}


//2
tabHS GestorPraias::getServicosNaoAtivos() const
{
	return servicosnaoativos;
}
