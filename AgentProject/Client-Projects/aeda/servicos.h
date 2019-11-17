#ifndef SERVICOS_H
#define SERVICOS_H

#include <string>
#include "GPS.h"
#include "data.h"
#include <iostream>

/**
 * @brief      Class for services inside a river beach area.
 */
class servico
{	
	std::string nome;
	GPS gps;
	std::string tipo;
	bool aberto = true;
	data dt = data(0,0,0);
public:

	/**
	* @brief      Constructs servico.
	 */
	servico();

	/**
	 * @brief      Constructs servico.
	 *
	 * @param[in]  nome  The name
	 * @param[in]  gps   The gps
	 */
	servico(std::string nome, GPS gps);
	
	/**
	 * @brief      Destroys servico.
	 */
	~servico();

	/**
	 * @brief      Gets the gps coordinates of servico.
	 *
	 * @return     The gps.
	 */
	GPS getGPS() const;

	/**
	 * @brief      Gets the name of servico
	 *
	 * @return     The name.
	 */
	std::string getNome() const;

	/**
	 * @brief      Gets the type of the servico
	 *
	 * @return     The name.
	 */
	std::string getTipo() const;
	
	/**
	 * @brief      Gets the bool aberto which tells whether the service is open or closed.
	 *
	 * @return     The aberto.
	 */
	bool getAberto() const;

	/**
	 * @brief      Gets the date of the closure.
	 *
	 * @return     The data.
	 */
	data getData() const;

	/**
	 * @brief      Gets a string containing the information of the servico.
	 *
	 * @return     The information.
	 */
	std::string getInfo() const;
	
	/**
	 * @brief      Sets the type of servico.
	 *
	 * @param[in]  tipo  The type
	 */
	void setTipo(std::string tipo);
	
	/**
	 * @brief      Sets the aberto bool.
	 *
	 * @param[in]  aberto  The value
	 */
	void setAberto(bool aberto);
	
	/**
	 * @brief      Sets the date.
	 *
	 * @param[in]  dt    the date
	 */
	void setData(data dt);

	/**
	 * @brief      Registers an inspection.
	 *
	 * @param[in]  dt    date of the inspection
	 */
	void makeInspection(data dt);

};

/**
 * @brief      The "lesser than" operator for objects of servico.
 *
 * @param[in]  srvc1  The first servico
 * @param[in]  srvc2  The second servico
 *
 * @return     True if less and False otherwise
 */
bool operator<(const servico& srvc1, const servico& srvc2);

/**
 * @brief      Overloads the "<<" operator for servico, making it easier to print to the stardard output.
 *
 * @param      os    The output stream
 * @param[in]  srvc  The servico
 *
 * @return     The output stream after inserting the servico
 */
std::ostream& operator<<(std::ostream& os, const servico& srvc);

/**
 * @brief      Class for lifeguard. Derivates from servico.
 */
class nadadorSalvador : public servico
{
public:

	/**
	 * @brief      Constructs lifeguard.
	 */
	nadadorSalvador();
	
	/**
	 * @brief      Constructs lifeguard with nome as name and gps as its GPS coordinates.
	 *
	 * @param[in]  nome  The name
	 * @param[in]  gps   The GPS coordinates
	 */
	nadadorSalvador(std::string nome);
	
	/**
	 * @brief      Destroys lifeguard.
	 */
	~nadadorSalvador();

};

/**
 * @brief      Class for cafe. Derivates from servico.
 */
class cafe : public servico
{
public:

	/**
	 * @brief      Constructs cafe.
	 */
	cafe();

	/**
	 * @brief      Constructs cafe.
	 *
	 * @param[in]  nome  The name
	 * @param[in]  gps   The GPS coordinates
	 */
	cafe(std::string nome, GPS gps);
	
	/**
	 * @brief      Destroys cafe.
	 */
	~cafe();
	
};

/**
 * @brief      Class for restaurant. Derivates from servico.
 */
class restaurante : public servico
{
public:

	/**
	 * @brief      Constructs restaurant.
	 */
	restaurante();

	/**
	 * @brief      Constructs restaurant.
	 *
	 * @param[in]  nome  The name
	 * @param[in]  gps   The GPS coordinates
	 */
	restaurante(std::string nome, GPS gps);

	/**
	 * @brief      Destroys restaurant.
	 */
	~restaurante();
	
};

/**
 * @brief      Class for sports field. Derivates from servico.
 */
class campoDesportivo : public servico
{
public:

	/**
	 * @brief      Constructs sports field.
	 */
	campoDesportivo();

	/**
	 * @brief      Constructs sports field.
	 *
	 * @param[in]  nome  The name
	 * @param[in]  gps   The GPS coordinates
	 */
	campoDesportivo(std::string nome, GPS gps);

	/**
	 * @brief      Destroys sports field.
	 */
	~campoDesportivo();

};


/**
 * @brief      Class for services out of the river beach area. Derivates from servico.
 */
class servicoForaDaPraia : public servico
{
	bool permanente;
public:

	/**
	 * @brief      Constructs a service out of the beach area.
	 */
	servicoForaDaPraia();

	/**
	 * @brief      Constructs a service out of the beach area.
	 *
	 * @param[in]  nome  The name
	 * @param[in]  gps   The GPS coordinates
	 */
	servicoForaDaPraia(std::string nome, GPS gps);


	/**
	 * @brief      Destroys the service out of the beach area.
	 */
	~servicoForaDaPraia();
	
	/**
	 * @brief      Closes service with inspection
	 *
	 * @param[in]  permanente  Boolean wether the closure of the service was temporary or permanent
	 * @param[in]  dt          The date of the inspection
	 */
	void close(bool permanente, data dt);

	/**
	 * @brief      Opens service
	 */
	void open(data dt);
};

/**
 * @brief      Class for tourism stops. Derivates from servicoForaDaPraia.
 */
class pontoTuristico: public servicoForaDaPraia
{
public:

	/**
	 * @brief      Constructs a tourism stop.
	 */
	pontoTuristico();

	/**
	 * @brief      Constructs a tourism stop.
	 *
	 * @param[in]  nome  The name
	 * @param[in]  gps   The GPS coordinates
	 */
	pontoTuristico(std::string nome, GPS gps);

	/**
	 * @brief      Destroys the tourism stop.
	 */
	~pontoTuristico();
};

/**
 * @brief      Class for hotels. Derivates from servicoForaDaPraia.
 */
class alojamento : public servicoForaDaPraia
{
public:

	/**
	 * @brief      Constructs a hotel.
	 */
	alojamento();

	/**
	 * @brief      Constructs a hotel.
	 *
	 * @param[in]  nome  The name
	 * @param[in]  gps   The GPS coordinates
	 */
	alojamento(std::string nome, GPS gps);

	/**
	 * @brief      Destroys the hotel.
	 */
	~alojamento();
};




#endif