/*
 * ExportInfo.h
 *
 *  Created on: 16/11/2017
 *      Author: Francisco Maria / João Gama Amaral
 */

#ifndef EXPORTINFO_H_
#define EXPORTINFO_H_

#include "Libraries.h"
#include "MovingCompany.h"
#include <fstream>

/**
 * @brief parses information of a particular client
 * @return line to be written to the .txt file
 */
std::string saveParticularClient(Client* c);

/**
 * @brief parses information of a company client
 * @return line to be written to the .txt file
 */
std::string saveCompanyClient(Client* c);

/**
 * @brief saves information to the .txt file
 * @param company company itself
 */
void saveClients(MovingCompany& company);

/**
 * @brief parses transport service information
 * @param tService service to be parsed
 * @param idC client ID
 */
std::string saveTransportService(Transport* tService, int idC);

/**
 * @brief parses warehousing service information
 * @param wService service to be parsed
 * @param idClient client ID
 */
std::string saveWarehousingService(Warehousing* wService, int idClient);

/**
 * @brief saves services to .txt file
 * @param company company itself
 */
void saveServices(MovingCompany& company);


#endif /* EXPORTINFO_H_ */
