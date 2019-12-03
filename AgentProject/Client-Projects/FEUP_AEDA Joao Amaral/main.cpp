//============================================================================
// Name        : main.cpp
// Author      : Francisco Maria / João Gama Amaral
// Version     :
// Copyright   :
// Description : Main file of the first project of AEDA class.
//============================================================================

#include "Libraries.h"
#include "Interface.h"
#include "ImportInfo.h"
#include "ExportInfo.h"


void importInfo(MovingCompany& company){

	importCountries(company);
	importCountriesZones(company);
	importClients(company);
	importVehicles(company);
	importServices(company);

}

void terminateProgram(MovingCompany& company){

	saveClients(company);
	saveServices(company);
	company.freeMemory();

	std::cout << "\n\n\t\tProgram terminated." << std::endl;
}

int main() {

	MovingCompany company("EletroMoving, S.A.", "Great company with moving.", "PT50 1452 0023 14698 7456 9878 3", "14579", 10, 9, 1995);

	importInfo(company);

	run(company);

	terminateProgram(company);

	return 0;
}
