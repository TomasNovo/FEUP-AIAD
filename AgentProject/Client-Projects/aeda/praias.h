#ifndef PRAIAS_H
#define PRAIAS_H

#include <vector>
#include <string>
#include "GPS.h"
#include "servicos.h"
#include <iostream>
#include <set>
#include <unordered_set>
#include <queue>
#include <utility>

/**
 * @brief      Class for praias fluviais.
 */
class praiaFluvial
{
	std::string nome;
	std::string concelho;
	GPS gps;
	bool bandeiraazul;
	unsigned int capacidade;
	std::vector<servico*> servicosdapraia;
	std::string tipo;

public:

	/**
	 * @brief      Constructs the object.
	 */
	praiaFluvial();

	/**
	 * @brief      Constructs the object.
	 *
	 * @param[in]  concelho         The concelho
	 * @param[in]  gps              The gps
	 * @param[in]  bandeirazul      The bandeirazul
	 * @param[in]  capacidade       The capacidade
	 * @param[in]  servicosdapraia  The servicosdapraia
	 */
	praiaFluvial(std::string nome, std::string concelho, GPS gps, bool bandeiraazul, unsigned int capacidade, std::vector<servico*> servicosdapraia);
	
	/**
	 * @brief      Constructs an object equal to praia.
	 *
	 * @param[in]  praia  The praia
	 */
	praiaFluvial(const praiaFluvial& praia);
	
	/**
	 * @brief      Destroys the object of praiaFluvial.
	 */
	~praiaFluvial();

	/**
	*@brief      Gets the praiaFluvial's name.
	*
	* @return     The praiaFluvial's name.
	*/
	std::string getNome() const;
	
	/**
	*@brief      Gets the praiaFluvial's GPS.
	*
	* @return     The praiaFluvial's GPS.
	*/
	GPS getGPS() const;
	
	/**
	*@brief      Gets the praiaFluvial's county.
	*
	* @return     The praiaFluvial's county.
	*/
	std::string getConcelho() const;
	
	/**
	*@brief      Gets the praiaFluvial's bandeiraAzul.
	*
	* @return     true if praiaFluvial has a blue flag.
	*/
	bool getBandeiraAzul() const;
	
	/**
	*@brief      Gets the praiaFluvial's capacity.
	*
	* @return   The praiaFluvial's capacity.
	*/
	unsigned int getCapacidade() const;
	
	/**
	*@brief      Gets the praiaFluvial's servico's vector.
	*
	* @return   A vector with the servico's of the beach.
	*/
	std::vector<servico*> getServicos() const;
	
	/**
	*@brief      Gets the praiaFluvial's type.
	*
	* @return   The praiaFluvial's type.
	*/
	std::string getTipo() const;

	/**
	*@brief      Gets the praiaFluvial's info.
	*
	* @return   The praiaFluvial's info.
	*/
	virtual std::string getInfo() const;


	/**
	* @brief      Sets the name of praiaFluvial.
	*
	*@param[in] nome The name.
	*/
	void setNome(std::string nome);
	
	/**
	* @brief      Sets the GPS of praiaFluvial.
	*
	*@param[in] gps The GPS.
	*/
	void setGPS(GPS gps);

	/**
	* @brief      Sets the bandeiraAzul of praiaFluvial.
	*
	*@param[in] bandeiraazul The flag.
	*/
	void setBandeira(bool bandeiraazul);
	
	/**
	* @brief      Sets the type of praiaFluvial.
	*
	*@param[in] tipo The type.
	*/
	void setTipo(std::string tipo);

	/**
	* @brief      Lists the servico's of praiaFluvial.
	*/
	void listServicos() const;

	
	/**
	* @brief      The less operator for objects of class praiaFluvial
    *
	* @param[in]  praia1  The second beach
	*
	* @return     True if the first county comes alphabetically first than the second or if they are from the same county if the the first has bandeiraAzul. Returns false otherwise.
	*/
	bool operator<(const praiaFluvial& praia1) const;
	
	/**
	* @brief      The equal operator for objects of class praiaFluvial
	*
	* @param[in]  praia1  The second beach
	*
	* @return     True if the first and the second beach are equal. False otherwise.
	*/
	bool operator==(const praiaFluvial& praia1) const;

	
	
	
	/**
	*@brief      Gets the praiaFluvial's width.
	*
	* @return   The praiaFluvial's width.
	*/
	virtual unsigned int getLargura() const;
	
	/**
	*@brief      Gets the praiaFluvial's flow.
	*
	* @return   The praiaFluvial's flow.
	*/
	virtual unsigned int getCaudal() const;

	/**
	*@brief      Gets the praiaFluvial's depth.
	*
	* @return   The praiaFluvial's depth.
	*/
	virtual unsigned int getProfundidade() const;

	/**
	*@brief      Gets the praiaFluvial's area.
	*
	* @return   The praiaFluvial's area.
	*/
	virtual unsigned int getArea() const;

	/**
	*@brief      Prints the info of praiaFluvial in a ostream.
	*
	* @param os The ostream.
	*/
	void print(std::ostream& os) const;

};
std::ostream& operator<<(std::ostream & os, const praiaFluvial& praia); 


/**
 * @brief      Class for rio. Derivates from praiaFluvial.
 */
class rio : public praiaFluvial
{
	unsigned int larguraMax;
	unsigned int caudalMax;
	unsigned int profundidadeMax;
public:
	
	/**
	 * @brief      Contructs the object.
	 */
	rio();

	/**
	 * @brief      Constructs the object with parameters.
	 *
	 * @param[in]  nome             The nome
	 * @param[in]  concelho         The concelho
	 * @param[in]  gps              The gps
	 * @param[in]  bandeiraazul     The bandeiraazul
	 * @param[in]  capacidade       The capacidade
	 * @param[in]  servicosdapraia  The servicosdapraia
	 * @param[in]  larguraMax       The maximum width
	 * @param[in]  caudalMax        The maximum volume
	 * @param[in]  profundidadeMax  The maximum depth
	 */
	rio(std::string nome, std::string concelho, GPS gps, bool bandeiraazul, unsigned int capacidade, std::vector<servico*> servicosdapraia, unsigned int larguraMax, unsigned int caudalMax, unsigned int profundidadeMax);
	
	/**
	 * @brief      Destroys the object.
	 */
	~rio();

	/**
	*@brief      Gets the width.
	*
	* @return   The width.
	*/
	unsigned int getLargura() const;

	/**
	*@brief      Gets the flow.
	*
	* @return   The flow.
	*/
	unsigned int getCaudal() const;

	/**
	*@brief      Gets the depth.
	*
	* @return   The depth.
	*/
	unsigned int getProfundidade() const;

	/**
	*@brief      Gets the info.
	*
	* @return   The info.
	*/
	std::string getInfo() const;
};


/**
* @brief      Class for albufeira. Derivates from praiaFluvial.
*/
class albufeira : public praiaFluvial
{
	unsigned int area;
public:

	/**
	 * @brief      Constructs the object.
	 */
	albufeira();

	/**
	 * @brief      Construct the object with parameters.
	 *
	 * @param[in]  nome             The nome
	 * @param[in]  concelho         The concelho
	 * @param[in]  gps              The gps
	 * @param[in]  bandeiraazul     The bandeiraazul
	 * @param[in]  capacidade       The capacidade
	 * @param[in]  servicosdapraia  The servicosdapraia
	 * @param[in]  area             The area
	 */
	albufeira(std::string nome, std::string concelho, GPS gps, bool bandeiraazul, unsigned int capacidade, std::vector<servico*> servicosdapraia, unsigned int area);
	
	/**
	 * @brief      Destroys the object.
	 */
	~albufeira();

	/**
	*@brief      Gets the area.
	*
	* @return   The area.
	*/
	unsigned int getArea() const;

	/**
	*@brief      Gets the info.
	*
	* @return   The info.
	*/
	std::string getInfo() const;
};


/**
 * @brief      Struct to compare two objects from type praiaFluvial.
 */
struct comparePraia
{
  bool operator() (const praiaFluvial* lhs, const praiaFluvial* rhs) const
  {
  	return *lhs<*rhs;
  }

};


/**
* @brief      Struct to compare two objects from type servico.
*/
struct compareServico
{
	bool operator() (const servico* lhs, const servico* rhs) const
  {
  	return !(*lhs<*rhs);
  }
};

/**
* @brief      Struct of functions to get the hash value of a servicoForaDaPraia and to get an equality check for two hashes.
*/
struct servicoHash
{
	int operator() (const servicoForaDaPraia* srvc) const
	{
		return static_cast<int>(std::hash<std::string>()(srvc->getNome())); //Mudar para GPS
	}

	bool operator() (const servicoForaDaPraia* srvc1, const servicoForaDaPraia* srvc2) const
	{
		return (srvc1->getNome() == srvc2->getNome());
	}
};



typedef std::unordered_set<servicoForaDaPraia*, servicoHash, servicoHash> tabHS;

/**
* @brief      Class for GestorPraias.
*/
class GestorPraias
{
	std::set<praiaFluvial*, comparePraia> praias; // BST
	std::vector<servicoForaDaPraia*> servicosdefora;
	std::vector<std::priority_queue<servico*, std::vector<servico*>, compareServico>> inspecoes; // 0 = nadadorSalvador, 1 = cafe, 2 = restaurante, 3 = campoDesportivo
	tabHS servicosnaoativos;

public:

	/**
	 * @brief      Construct the object.
	 */
	GestorPraias();

	/**
	 * @brief      Construct the object with parameters.
	 *
	 * @param[in]  praias          The praias
	 * @param[in]  servicosdefora  The servicosdefora
	 */
	GestorPraias(std::set<praiaFluvial*, comparePraia> praias, std::vector<servicoForaDaPraia*> servicosdefora);
	
	/**
	 * @brief      Destroys the object.
	 */
	~GestorPraias();

	/**
	* @brief      Adds the praiaFluvial.
	*
	*@param[in] praia The praiaFluvial.
	*/
	void addPraia(praiaFluvial praia);
	
	/**
	* @brief      Removes the praiaFluvial.
	*
	*@param[in] it The iterator
	*/
	void removePraia(std::set<praiaFluvial*, comparePraia>::iterator it);
	
	/**
	* @brief      Sets the set of beaches.
	*
	*@param[in] input The input.
	*/
	void setPraias(std::set<praiaFluvial*, comparePraia> input);

	/**
	* @brief      Gets the set of beaches.
	*/
	std::set<praiaFluvial*, comparePraia> getPraias();
	
	/**
	* @brief      Gets the servico's vector.
	*/
	std::vector<servicoForaDaPraia*> getServicos();

	/**
	* @brief      Gets the praiaFluvial.
	*
	*@param[in] it The iterator
	*/
	praiaFluvial getPraia(std::set<praiaFluvial*, comparePraia>::iterator it);

	/**
	* @brief      Gets the closest praiaFluvial.
	*
	*@param[in] gps The GPS type variable
	*/
	std::set<praiaFluvial*, comparePraia>::iterator getClosestPraia(GPS gps);

	/**
	* @brief      Finds the praiaFluvial with name nome.
	*
	*@param[in] nome The name.
	*/
	std::set<praiaFluvial*, comparePraia>::iterator findPraia(std::string nome);
	
	/**
	* @brief      Finds the praiaFluvial from it gps-.
	*
	*@param[in] gps The GPS coordinates.
	*/
	std::set<praiaFluvial*, comparePraia>::iterator findPraia(GPS gps);
	
	/**
	* @brief      Checks if iterator it is at the end of the BST.
	*
	*@param[in] it The iterator.
	*
	*@return true if iterator it is at the end
	*/
	bool isEnd(std::set<praiaFluvial*, comparePraia>::iterator &it);

	/**
	* @brief      Creates an inspection with data dt in servico srvcname of type tipo.
	*
	* @param[in]  srvcname  The name of the servico.
	* @param[in]  tipo  The type of the servico.
	* @param[in]  dt  The date of the inspection.
	*/
	void makePraiaInspection(std::string srvcname, std::string tipo, data dt);


	/**
	* @brief      Closes the servico with name srvcname permanently or not at date dt.
	*
	* @param[in]  srvcname  The name of the servico.
	* @param[in]  permanente  The bool variable that checks if it's permanent or not.
	* @param[in]  dt  The date when it closes.
	*
	*@return true if closed permanently
	*/
	bool closeService(std::string srvcname, bool permanente, data dt);
	

	/**
	* @brief      Opens the servico with name srvcname at date dt.
	*
	* @param[in]  srvcname  The name of the servico.
	* @param[in]  dt  The date when it closes.
	*
	*@return True if open.
	*/
	bool openService(std::string srvcname, data dt);

	/**
	 * @brief      Lists the contents of the BST of praiaFluvial.
	 */
	void listPraias() const;

	/**
	 * @brief      Lists the contents of the vector of servicoForaDaPraia.
	 */
	void listServicosDeFora() const;

	/**
	 * @brief      Lists the contents of the hash table of servicoForaDaPraia
	 */
	void listServicosNaoAtivos() const;

	/**
	 * @brief      Loads the content from the input file. Throws a BadFileInput exception if corrupted input.
	 *
	 * @param[in]  filename  The name of the file
	 *
	 * @return     True if file exists and False otherwise.
	 */
	bool LoadPraias(std::string filename);

	/**
	 * @brief      Saves the member variables of the object to a file.
	 *
	 * @param[in]  filename  The name of the file
	 *
	 * @return     True if file exists and False otherwise.
	 */
	bool SavePraias(std::string filename);

	//2

	/**
	* @brief      Gets the servico's that aren't available.
	*
	* @return     An hash table with non activated servico.
	*/
	tabHS getServicosNaoAtivos() const;

};


/**
 * @brief      Class for handling badly formatted input files
 */
class BadFileInput {

	std::string filename;
public:

	/**
	 * @brief      Generic constructor.
	 */
	BadFileInput() {}

	/**
	 * @brief      Constructor with parameters.
	 *
	 * @param[in]  filename  The name of the ill-formatted file.
	 */
	BadFileInput(std::string filename) : filename(filename) {}

	/**
	 * @brief      Gets the name of the file.
	 *
	 * @return     The name of the file.
	 */
	std::string getFilename() { return filename; }

};

#endif