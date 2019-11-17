#include "menu.h"
#include "ui_utilities.h"
#include "utilities.h"
#include <fstream>
#include "GPS.h"
#include <sstream>

using namespace std;

menu::menu()
{}

menu::menu(unsigned int width, unsigned int height) : width(width), height(height)
{}

void menu::Begin()
{
	PreMenu();
}

void menu::PreMenu()
{
	ui_utilities::SetWindow(width, height);
	ui_utilities::ClearScreen();
	string tempstr;

	while(1)
	{
		cout <<"\n Insert input filename (leave empty for default: \"inputfile\"): ";

		getline(cin, tempstr);
		utilities::trimString(tempstr);
		if (tempstr == "")
			tempstr = "inputfile";

		if (gestor.LoadPraias(tempstr))
		{
			inputfilename = tempstr;
			break;
		}
		else
			cout << "File doesn't exist!";

	}
	cout << "\n";

	while (1)
	{
		cout <<"\n Insert banner filename (leave empty for default: \"bannerfile\"): ";

		getline(cin, tempstr);
		utilities::trimString(tempstr);
		if (tempstr == "")
			tempstr = "bannerfile";

		if (LoadBanner(tempstr))
			break;
		else
			cout << "File doesn't exist!";
	}

	cout << "\n\n   All files have been loaded with success. Press enter to continue...";
	getline(cin, tempstr);

	MainMenu();
}


void menu::MainMenu()
{
	while(true)
	{
		ui_utilities::SetWindow(width, height);
		ui_utilities::ClearScreen();
		PrintBanner();

		cout << "Enter a number to choose the sub-menu that you want to go !\n\n";
		cout << "1- Add a river beach \n";
		cout << "2- Remove a river beach \n";
		cout << "3- Edit a river beach's flag \n";
		cout << "4- Register an inspection of a river beach \n";
		cout << "5- Close a service \n";
		cout << "6- Open a service \n";
		cout << "7- List all river beaches \n";
		cout << "8- List river beaches of specific county\n";
		cout << "9- Search river beach \n";
		cout << "10- Search nearest river beach \n";
		cout << "11- Search services near river beach \n";
		cout << "0- Quit \n\n";


		string input;

		while (true)
		{
			cout << "Select an option: ";

			getline(cin, input);
			utilities::trimString(input);
			cout << "\n";

			if (input == "1")
			{
				AddPraia();
				break;
			}

			else if (input == "2")
			{
				RemovePraia();
				break;
			}

			else if (input == "3")
			{
				EditBandeira();
				break;
			}

			else if (input == "4")
			{
				MakeInspectionPraia();
				break;
			}

			else if (input == "5")
			{
				CloseService();
				break;
			}

			else if (input == "6")
			{
				OpenService();
				break;
			}

			else if (input == "7")
			{
				ListPraias();
				break;
			}

			else if (input == "8")
			{
				ListByConcelho();
				break;
			}

			else if (input == "9")
			{
				SearchPraia();
				break;
			}

			else if (input == "10")
			{
				SearchNearestPraia();
				break;
			}

			else if (input == "11")
			{
				SearchServices();
				break;
			}

			else if (input == "0")
			{
				gestor.SavePraias(inputfilename);
				ui_utilities::ClearScreen();
				return;
			}

			else
				cout << "Invalid input!\n";

		}
	}
}

void menu::AddPraia()
{
	ui_utilities::SetWindow(width, height);
	ui_utilities::ClearScreen();
	PrintBanner();

	string tempstr, tipo, nome, concelho;
	GPS gps;
	bool bandeiraazul;
	int capacidade, larguraMax, caudalMax, profundidadeMax, area;
	vector<servico*> tempServicos;

	cout << "\n\nEnter the information of the river beach that you want to add! (write \".\" at any time to go back)\n";

	while(1)
	{
		cout << "Please enter the type of the beach (\"rio\" or \"albufeira\")\n";

		getline(cin, tipo);
		utilities::trimString(tipo);

		if (tipo == ".")
			return;

		if (tipo == "rio" || tipo == "albufeira")
			break;

		cout << "Wrong type! Must be either \"rio\" or \"albufeira\"\n\n";
	}

	while(1)
	{
		cout << "Please enter the name of the beach\n";

		getline(cin, nome);
		utilities::trimString(nome);

		if (nome == ".")
			return;

		if (nome != "")
			break;

		cout << "You need to write something!\n\n";
	}

	while(1)
	{
		cout << "Please enter the county of the beach\n";

		getline(cin, concelho);
		utilities::trimString(concelho);

		if (concelho == ".")
			return;

		if (concelho != "")
			break;

		cout << "You need to write something!\n\n";
	}

	while(1)
	{
		cout << "Please enter the latitude coordinate of the beach\n";

		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (tempstr == ".")
			return;

		string tempstr2;

		cout << "Please enter the longitude coordinate of the beach\n";

		getline(cin, tempstr2);
		utilities::trimString(tempstr2);

		if (tempstr2 == ".")
			return;

		try
		{
			gps = GPS(stod(tempstr), stod(tempstr2));
		}
		catch (exception &e)
		{
			cout << "Wrong Coordinates!\n";
			continue;
		}
		break;
	}

	while(1)
	{
		cout << "Does the beach have blue flag? (Y/N)\n";

		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (tempstr == ".")
			return;

		if (tempstr == "Y" || tempstr == "y")
			bandeiraazul = true;
		else
			bandeiraazul = false;

		break;
	}

	while(1)
	{
		cout << "Please enter the capacity of the beach\n";

		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (tempstr == ".")
			return;

		try
		{
			capacidade = stoi(tempstr);

			if (capacidade < 0)
			{
				cout << "Capacity must be an unsigned integer!\n";
				continue;
			}

			break;
		}
		catch (exception &e)
		{
			cout << "Capacity must be an unsigned integer!\n";
		}

	}

	if (tipo == "rio")
	{

		while(1)
		{
			cout << "Please enter the maximum width of the beach\n";

			getline(cin, tempstr);
			utilities::trimString(tempstr);

			if (tempstr == ".")
				return;

			try
			{
				larguraMax = stoi(tempstr);

				if (larguraMax < 0)
				{
					cout << "The maximum width must be an unsigned integer!\n";
					continue;
				}

				break;
			}
			catch (exception &e)
			{
				cout << "The maximum width must be an unsigned integer!\n";
			}

		}

		while(1)
		{
			cout << "Please enter the maximum volume of water of the beach\n";

			getline(cin, tempstr);
			utilities::trimString(tempstr);

			if (tempstr == ".")
				return;

			try
			{
				caudalMax = stoi(tempstr);

				if (caudalMax < 0)
				{
					cout << "The maximum volume must be an unsigned integer!\n";
					continue;
				}

				break;
			}
			catch (exception &e)
			{
				cout << "The maximum volume must be an unsigned integer!\n";
			}

		}

		while(1)
		{
			cout << "Please enter the maximum depth of the beach\n";

			getline(cin, tempstr);
			utilities::trimString(tempstr);

			if (tempstr == ".")
				return;

			try
			{
				profundidadeMax = stoi(tempstr);

				if (profundidadeMax < 0)
				{
					cout << "The maximum depth must be an unsigned integer!\n";
					continue;
				}

				break;
			}
			catch (exception &e)
			{
				cout << "The maximum depth must be an unsigned integer!\n";
			}

		}

	}
	else
	{
		while(1)
		{
			cout << "Please enter the area of the beach\n";

			getline(cin, tempstr);
			utilities::trimString(tempstr);

			if (tempstr == ".")
				return;

			try
			{
				area = stoi(tempstr);

				if (area < 0)
				{
					cout << "The area must be an unsigned integer!\n";
					continue;
				}

				break;
			}
			catch (exception &e)
			{
				cout << "The area must be an unsigned integer!\n";
			}

		}

	}

	while(1)
	{
		cout << "Enter a service of the beach (write \"..\" to end input of services)";
		string tempstr2, tipo2, nome2;
		GPS gps2;

		while(1)
		{
			cout << "Please enter the type of the service\n";

			getline(cin, tipo2);
			utilities::trimString(tipo2);

			if (tipo2 == ".")
				goto endinput;

			if (tipo2 == "nadadorSalvador" || tipo2 == "cafe" || tipo2 == "restaurante" || tipo2 == "campoDesportivo")
				break;

			cout << "Wrong type\n";
		}

		while(1)
		{
			cout << "Please enter the name of the service\n";

			getline(cin, nome2);
			utilities::trimString(nome2);

			if (nome2 == ".")
				goto endinput;

			if (nome2 == "")
			{
				cout << "You need to enter something\n";
				continue;
			}

			break;
		}

		while(1)
		{
			cout << "Please enter the latitude coordinate of the beach\n";

			getline(cin, tempstr2);
			utilities::trimString(tempstr2);

			if (tempstr2 == ".")
				goto endinput;

			string tempstr3;

			cout << "Please enter the longitude coordinate of the beach\n";

			getline(cin, tempstr3);
			utilities::trimString(tempstr3);

			if (tempstr3 == ".")
				goto endinput;

			try
			{
				gps2 = GPS(stod(tempstr2), stod(tempstr3));
			}
			catch (exception &e)
			{
				cout << "Wrong Coordinates!\n";
				continue;
			}
			break;
		}

		if (tipo == "nadadorSalvador")
			tempServicos.push_back(new nadadorSalvador(nome2));
		else if (tipo == "cafe")
			tempServicos.push_back(new cafe(nome2, gps2));
		else if (tipo == "restaurante")
			tempServicos.push_back(new restaurante(nome2, gps2));
		else if (tipo == "campoDesportivo")
			tempServicos.push_back(new campoDesportivo(nome2, gps2));
	}

endinput: 
	if (tipo == "rio")
		gestor.addPraia(rio(nome, concelho, gps, bandeiraazul, capacidade, tempServicos, larguraMax, caudalMax, profundidadeMax));
	else
		gestor.addPraia(albufeira(nome, concelho, gps, bandeiraazul, capacidade, tempServicos, area));

	gestor.SavePraias(inputfilename);

	cout << "River beach added!\n";
}


void menu::RemovePraia()
{
	ui_utilities::SetWindow(width, height);
	ui_utilities::ClearScreen();
	PrintBanner();

	cout << "Enter the praia's name (write \".\" to enter the GPS coordinates instead)\n";

	string tempstr;
	GPS gps;
	set<praiaFluvial*, comparePraia>::iterator it;

	getline(cin, tempstr);
	utilities::trimString(tempstr);

	if (tempstr == ".")
	{
		while(1)
		{
			string tempstr2, tempstr3;

			cout << "Please enter the latitude coordinate of the beach\n";

			getline(cin, tempstr2);
			utilities::trimString(tempstr2);

			if (tempstr2 == ".")
				return;

			cout << "Please enter the longitude coordinate of the beach\n";

			getline(cin, tempstr3);
			utilities::trimString(tempstr3);

			if (tempstr3 == ".")
				return;

			try
			{
				gps = GPS(stod(tempstr2), stod(tempstr3));
			}
			catch (exception &e)
			{
				cout << "Wrong Coordinates!\n";
				continue;
			}
			break;
		}
		it = gestor.findPraia(gps);
	}
	else
	{
		it = gestor.findPraia(tempstr);
	}

	if (gestor.isEnd(it))
	{
		cout << "Beach not found!\n";
		cout << "Would you like to try again ? (Y/N) \n";
		getline(cin, tempstr);

		if (tempstr == "Y" || tempstr == "y")
			RemovePraia();
		else
			return;
	}
	else
	{
		gestor.removePraia(it);
		gestor.SavePraias(inputfilename);
		cout << "Beach removed!\n";
		getline(cin, tempstr);
	}
}

void menu::EditBandeira()
{
	ui_utilities::SetWindow(width, height);
	ui_utilities::ClearScreen();
	PrintBanner();

	cout << "Enter the praia's name (write \".\" to enter the GPS coordinates instead):\n";

	string tempstr;
	GPS gps;
	set<praiaFluvial*, comparePraia>::iterator it;

	getline(cin, tempstr);
	utilities::trimString(tempstr);

	if (tempstr == ".")
	{
		while(1)
		{
			string tempstr2, tempstr3;

			cout << "Please enter the latitude coordinate of the beach\n";

			getline(cin, tempstr2);
			utilities::trimString(tempstr2);

			if (tempstr2 == ".")
				return;

			cout << "Please enter the longitude coordinate of the beach\n";

			getline(cin, tempstr3);
			utilities::trimString(tempstr3);

			if (tempstr3 == ".")
				return;

			try
			{
				gps = GPS(stod(tempstr2), stod(tempstr3));
			}
			catch (exception &e)
			{
				cout << "Wrong Coordinates!\n";
				continue;
			}
			break;
		}
		it = gestor.findPraia(gps);
	}
	else
	{
		it = gestor.findPraia(tempstr);
	}


	if (gestor.isEnd(it))
	{
		cout << "Beach not found!\n";
		cout << "Would you like to try again ? (Y/N)\n";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (tempstr == "Y" || tempstr == "y")
			SearchPraia();
		else
			return;
	}
	else
	{
		while(true)
		{
			cout << "Set flag to true or false ? (T/F)\n";
			getline(cin, tempstr);
			utilities::trimString(tempstr);

			if (tempstr == "T" || tempstr == "t")
			{
				praiaFluvial* foo = *it;
				foo->setBandeira(true);
				gestor.SavePraias(inputfilename);
				break;
			}

			else if (tempstr == "F" || tempstr == "f")
			{
				praiaFluvial* foo = *it;
				foo->setBandeira(false);
				gestor.SavePraias(inputfilename);
				break;
			}

			else
			{
				cout << "Invalid input!\n";
				cout << "Would you like to try again ? (Y/N)\n";
				getline(cin, tempstr);
				utilities::trimString(tempstr);

				if (tempstr == "Y" || tempstr == "y")
					EditBandeira();
				else
					return;
			}

		}

		cout << "Beach edited!\n";
		getline(cin, tempstr);

	}

}

void menu::MakeInspectionPraia()
{
	ui_utilities::SetWindow(width, height);
	ui_utilities::ClearScreen();
	PrintBanner();

	cout << "Enter the praia's name (write \".\" to enter the GPS coordinates instead):\n";

	string tempstr;
	GPS gps;
	set<praiaFluvial*, comparePraia>::iterator it;

	getline(cin, tempstr);
	utilities::trimString(tempstr);

	if (tempstr == ".")
	{
		while(1)
		{
			string tempstr2, tempstr3;

			cout << "Please enter the latitude coordinate of the beach\n";

			getline(cin, tempstr2);
			utilities::trimString(tempstr2);

			if (tempstr2 == ".")
				return;

			cout << "Please enter the longitude coordinate of the beach\n";

			getline(cin, tempstr3);
			utilities::trimString(tempstr3);

			if (tempstr3 == ".")
				return;

			try
			{
				gps = GPS(stod(tempstr2), stod(tempstr3));
			}
			catch (exception &e)
			{
				cout << "Wrong Coordinates!\n";
				continue;
			}
			break;
		}
		it = gestor.findPraia(gps);
	}
	else
	{
		it = gestor.findPraia(tempstr);
	}


	if (gestor.isEnd(it))
	{
		cout << "Beach not found!\n";
		cout << "Would you like to try again ? (Y/N)\n";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (tempstr == "Y" || tempstr == "y")
			SearchPraia();
		else
			return;
	}
	else
	{
		while(true)
		{
			cout << "\n\n";

			vector<servico*> foo = (*it)->getServicos();

			for (int i = 0; i < foo.size(); ++i)
			{
				cout << "\n" << (*foo[i]);
			}

			cout << "\n\nEnter the service's name:\n";

			getline(cin, tempstr);
			utilities::trimString(tempstr);

			string nome = "", tipo;

			for (int i = 0; i < foo.size(); ++i)
			{
				if (foo[i]->getNome() == tempstr)
				{
					nome = foo[i]->getNome();
					tipo = foo[i]->getTipo();
					break;
				}
			}

			if (nome == "") //fail
			{
				cout << "Service not found!!\n";
				cout << "Would you like to try again ? (Y/N)\n";
				getline(cin, tempstr);
				utilities::trimString(tempstr);

				if (tempstr == "Y" || tempstr == "y")
					continue;
				else
					return;
			}
			else //sucess
			{
				cout << "\nEnter the date of the inspection: (dd/mm/yyyy)\n";
				getline(cin, tempstr);
				utilities::trimString(tempstr);

				unsigned int dia,mes,ano;

				while (true)
				{
					try
					{
						tempstr += '/';
						stringstream ss(tempstr);

						getline(ss, tempstr, '/');
						dia = stoi(tempstr);
						getline(ss, tempstr, '/');
						mes = stoi(tempstr);
						getline(ss, tempstr, '/');
						ano = stoi(tempstr);

					}
					catch (exception &e)
					{
						cout << "Invalid input!!\n";
						cout << "Would you like to try again ? (Y/N)\n";
						getline(cin, tempstr);
						utilities::trimString(tempstr);

						if (tempstr == "Y" || tempstr == "y")
							continue;
						else
							return;
					}

					gestor.makePraiaInspection(nome, tipo, data(dia,mes,ano));

					break;
				}

			}

			break;
		}

	}

	cout << "\nInspection registered!\n";
	getline(cin, tempstr);
}

void menu::CloseService()
{
	ui_utilities::SetWindow(width, height);
	ui_utilities::ClearScreen();
	PrintBanner();
	
	gestor.listServicosDeFora();
	
	bool found;
	string tempstr;
	
	try
	{
		string srvcname;
		cout << "\n\nEnter the service's name:\n";

		getline(cin, srvcname);
		utilities::trimString(srvcname);

		cout << "\nEnter the date: (dd/mm/yyyy)\n";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		unsigned int dia,mes,ano;

		tempstr += '/';
		stringstream ss(tempstr);

		getline(ss, tempstr, '/');
		dia = stoi(tempstr);
		getline(ss, tempstr, '/');
		mes = stoi(tempstr);
		getline(ss, tempstr, '/');
		ano = stoi(tempstr);

		cout << "\nIs the closure of the service permanent ? (Y/N)\n";
		getline(cin, tempstr);
		utilities::trimString(tempstr);
		bool permanente;

		if (tempstr == "Y" || tempstr == "y")
			bool permanente = true;

		else if (tempstr == "N" || tempstr == "n")
			bool permanente = false;
		else
			throw;

		found = gestor.closeService(srvcname, permanente, data(dia,mes,ano));

	}
	catch (exception &e)
	{
		cout << "Invalid input!!\n";
		cout << "Would you like to try again ? (Y/N)\n";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (tempstr == "Y" || tempstr == "y")
			CloseService();
		else
			return;
	}

	if (!found)
	{
		cout << "Service not found!!\n";
		cout << "Would you like to try again ? (Y/N)\n";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (tempstr == "Y" || tempstr == "y")
			CloseService();
		else
			return;
	}

	cout << "\nService closed!\n";
	getline(cin, tempstr);
}


void menu::OpenService()
{
	ui_utilities::SetWindow(width, height);
	ui_utilities::ClearScreen();
	PrintBanner();
	
	gestor.listServicosNaoAtivos();
	
	bool found;
	string tempstr;

	try
	{
		string srvcname;
		cout << "\n\nEnter the service's name:\n";

		getline(cin, srvcname);
		utilities::trimString(srvcname);

		cout << "\nEnter the date: (dd/mm/yyyy)\n";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		unsigned int dia,mes,ano;

		tempstr += '/';
		stringstream ss(tempstr);

		getline(ss, tempstr, '/');
		dia = stoi(tempstr);
		getline(ss, tempstr, '/');
		mes = stoi(tempstr);
		getline(ss, tempstr, '/');
		ano = stoi(tempstr);

		found = gestor.openService(srvcname, data(dia,mes,ano));

	}
	catch (exception &e)
	{
		cout << "Invalid input!!\n";
		cout << "Would you like to try again ? (Y/N)\n";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (tempstr == "Y" || tempstr == "y")
			CloseService();
		else
			return;
	}

	if (!found)
	{
		cout << "Service not found!!\n";
		cout << "Would you like to try again ? (Y/N)\n";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (tempstr == "Y" || tempstr == "y")
			OpenService();
		else
			return;
	}

	cout << "\nService open!\n";
	getline(cin, tempstr);
}

void menu::ListPraias()
{
	ui_utilities::SetWindow(160, height);
	ui_utilities::ClearScreen();
	PrintBanner(160);

	string tempstr;

	cout << "As praias sao:\n";

	gestor.listPraias();

	getline(cin, tempstr);

}


void menu::ListByConcelho()
{
	ui_utilities::SetWindow(160, height);
	ui_utilities::ClearScreen();
	PrintBanner(160);

	cout << "Enter the county (write \".\" at any time to leave):\n";

	string tempstr;
	bool found = false;

	getline(cin, tempstr);
	utilities::trimString(tempstr);

	if (tempstr == ".")
	{
		return;
	}

	set<praiaFluvial*, comparePraia> p = gestor.getPraias();
	vector<praiaFluvial*> foo;

	for (set<praiaFluvial*, comparePraia>::iterator it = p.begin(); it != p.end(); it++)
	{
		if ((*it)->getConcelho() == tempstr)
		{
			found = true;
			cout << '\n' << (**it); 
		}
	}

	if (!found)
	{
		cout << "County not found!\n";
		cout << "Would you like to try again ? (Y/N) \n";
		getline(cin, tempstr);

		if (tempstr == "Y" || tempstr == "y")
			ListByConcelho();

		return;
	}

	cout << "\n\n";
	getline(cin, tempstr);
}

void menu::SearchPraia()
{
	ui_utilities::SetWindow(width, height);
	ui_utilities::ClearScreen();
	PrintBanner();

	cout << "Enter the praia's name (write \".\" to enter the GPS coordinates instead):\n";

	string tempstr;
	GPS gps;
	set<praiaFluvial*, comparePraia>::iterator it;

	getline(cin, tempstr);
	utilities::trimString(tempstr);

	if (tempstr == ".")
	{
		while(1)
		{
			string tempstr2, tempstr3;

			cout << "Please enter the latitude coordinate of the beach\n";

			getline(cin, tempstr2);
			utilities::trimString(tempstr2);

			if (tempstr2 == ".")
				return;

			cout << "Please enter the longitude coordinate of the beach\n";

			getline(cin, tempstr3);
			utilities::trimString(tempstr3);

			if (tempstr3 == ".")
				return;

			try
			{
				gps = GPS(stod(tempstr2), stod(tempstr3));
			}
			catch (exception &e)
			{
				cout << "Wrong Coordinates!\n";
				continue;
			}
			break;
		}
		it = gestor.findPraia(gps);
	}
	else
	{
		it = gestor.findPraia(tempstr);
	}



	if (gestor.isEnd(it))
	{
		cout << "Beach not found!\n";
		cout << "Would you like to try again ? (Y/N) \n";
		getline(cin, tempstr);

		if (tempstr == "Y" || tempstr == "y")
			SearchPraia();
		else
			return;
	}
	else
	{
		cout << '\n' << (**it) << '\n';
		getline(cin, tempstr);
	}

}


void menu::SearchNearestPraia()
{
	ui_utilities::SetWindow(width, height);
	ui_utilities::ClearScreen();
	PrintBanner();

	double latitude, longitude;
	GPS gps;
	string tempstr, tempstr2, tempstr3;

	while(1)
	{
		cout << "Enter the praia's GPS coordinates (write \".\" at any time to leave):\n";

		cout << "Please enter the latitude coordinate of the beach\n";

		getline(cin, tempstr2);
		utilities::trimString(tempstr2);

		if (tempstr2 == ".")
			return;

		cout << "Please enter the longitude coordinate of the beach\n";

		getline(cin, tempstr3);
		utilities::trimString(tempstr3);

		if (tempstr3 == ".")
			return;

		try
		{
			gps = GPS(stod(tempstr2), stod(tempstr3));

			if (gestor.findPraia(gps) == gestor.getPraias().end())
			{
				cout << "Beach not found!\n";
				cout << "Would you like to try again ? (Y/N) \n";
				getline(cin, tempstr);

				if (tempstr == "Y" || tempstr == "y")
					SearchNearestPraia();
				else
					return;
			}
		}
		catch (exception &e)
		{
			cout << "Invalid Coordinates!\n";
			continue;
		}
		break;
	}

	set<praiaFluvial*, comparePraia>::iterator it= gestor.getClosestPraia(gps);

	cout << "The nearest beach is " << (*it)->getNome();

	getline(cin, tempstr);
}


void menu::SearchServices()
{
	ui_utilities::SetWindow(width, height);
	ui_utilities::ClearScreen();
	PrintBanner();

	cout << "Enter the praia's name (write \".\" to enter the GPS coordinates instead):\n";

	string tempstr;
	GPS gps;
	set<praiaFluvial*, comparePraia>::iterator it;

	getline(cin, tempstr);
	utilities::trimString(tempstr);

	if (tempstr == ".")
	{
		while(1)
		{
			string tempstr2, tempstr3;

			cout << "Please enter the latitude coordinate of the beach\n";

			getline(cin, tempstr2);
			utilities::trimString(tempstr2);

			if (tempstr2 == ".")
				return;

			cout << "Please enter the longitude coordinate of the beach\n";

			getline(cin, tempstr3);
			utilities::trimString(tempstr3);

			if (tempstr3 == ".")
				return;

			try
			{
				gps = GPS(stod(tempstr2), stod(tempstr3));

				if (gestor.findPraia(gps) == gestor.getPraias().end())
				{
					cout << "Beach not found!\n";
					cout << "Would you like to try again ? (Y/N) \n";
					getline(cin, tempstr);

					if (tempstr == "Y" || tempstr == "y")
						SearchServices();
					else
						return;
				}
			}
			catch (exception &e)
			{
				cout << "Wrong Coordinates!\n";
				continue;
			}
			break;
		}
		it = gestor.findPraia(gps);
	}
	else
	{
		it = gestor.findPraia(tempstr);
	}

	vector<servicoForaDaPraia*> s = gestor.getServicos();

	bool existe = false;
	for (int i = 0; i < s.size(); ++i)
	{
		if ((*it)->getGPS().distance(s[i]->getGPS()) < 5000) //Menor que 5km
		{
			existe = true;
			cout << "Existe um " << s[i]->getTipo() << " com nome " << s[i]->getNome() << " nas coordenadas " << s[i]->getGPS() << "\n"; 
		}
	}

	if (!existe)
		cout << "Nao exite nenhum servico a menos de 5km da praia\n";

	getline(cin,tempstr);
}

unsigned int menu::getWidth()
{
	return width;
}

unsigned int menu::getHeight()
{
	return height;
}


void menu::setWidth(unsigned int width)
{
	this->width = width;
}

void menu::setHeight(unsigned int height)
{
	this->height = height;
}

bool menu::LoadBanner(string filename) {

	ifstream file(filename);

	if (!file.is_open())
		return false;

	string tempstr;

	while(getline(file, tempstr, '\n'))
	{
		banner.push_back(tempstr);
	}

	return true;
}

void menu::PrintBanner() {

	for (int i = 0; i < banner.size(); ++i)
	{
		cout << string((width - banner[i].size())/2, ' ') << banner[i] << '\n';
	}

	cout << '\n';
}

void menu::PrintBanner(unsigned int width) {

	for (int i = 0; i < banner.size(); ++i)
	{
		cout << string((width - banner[i].size())/2, ' ') << banner[i] << '\n';
	}

	cout << '\n';
}
