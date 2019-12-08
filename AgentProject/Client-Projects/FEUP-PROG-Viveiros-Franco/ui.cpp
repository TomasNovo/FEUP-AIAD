#include "ui.h"

void ui::PreMenu()
{
	ui_utilities::SetWindow(ConsoleWidth,ConsoleHeight);
	ui_utilities::ClearScreen();
	string tempstr;

	PrintBanner();

	while(1)
	{
		cout <<"\n Insert lines filename (leave empty for default: linhas.txt): ";

		getline(cin, tempstr);
		if (tempstr == "")	tempstr = "linhas.txt";

		if (!Lines.LoadFromFile(tempstr)) {
			cout << "File doesn't exist!";
			continue;
		}
		Bus_Stops.RebuildBus_Stops(Lines.GetLines()); // build bus stops cache
		break;
	}
	cout << "\n";

	while (1)
	{
		cout << "\n Insert drivers filename (leave empty for default: condutores.txt): ";

		getline(cin, tempstr);
		if (tempstr == "")	tempstr = "condutores.txt";

		if (!Drivers.LoadFromFile(tempstr)) {
			cout << "File doesn't exist!";
			continue;
		}
		break;
	}

	cout << '\n';

	while (1)
	{
		cout << "\n Insert buses filename (leave empty for default: autocarros.txt): ";

		getline(cin, tempstr);
		if (tempstr == "")	tempstr = "autocarros.txt";

		if (!Buses.LoadFromFile(tempstr)) {
			cout << "File doesn't exist!";
			continue;
		}
		break;
	}

	cout << '\n';

	while (1)
	{
		cout << "\n Insert shifts filename (leave empty for default: turnos.txt): ";

		getline(cin, tempstr);
		if (tempstr == "")	tempstr = "turnos.txt";

		if (!Shifts_Interface.LoadFromFile(tempstr)) {
			cout << "File doesn't exist!";
			continue;
		}
		break;
	}

	cout << "\n\n   All files have been loaded with success. Press enter to continue...";
	getchar();

	MainMenu();
}

void ui::MainMenu()
{
	while (true) {

		ui_utilities::SetWindow(ConsoleWidth, ConsoleHeight);
		ui_utilities::ClearScreen();
		PrintBanner();

		//   FUNCIONALIDADES QUE O PROJETO DEVE TER, RETIRADO DO PDF
		//1. Ler e guardar a informa?o de linhas e condutores armazenada em ficheiros;
		//2. Gerir os condutores : criar, alterar e remover um condutor;
		//3. Gerar e visualizar de modo formatado tabelas com hor?ios de uma paragem;
		//4. Visualizar o trabalho atribu?o a um condutor;
		//5. Visualizar a informa?o de um autocarro;
		//6. Visualizar a informa?o de uma linha, visualizando de modo formatado a tabela com o seu hor?io;
		//7. Inquirir sobre quais as linhas que incluem determinada paragem;
		//8. Calcular e visualizar um percurso e tempo de viagem entre duas quaisquer paragens indicadas pelo
		//	utilizador.Deve procurar a solu?o : na linha que cont? a paragem inicial ou; na linha que cont? a
		//	paragem inicial e numa das linhas que tenha paragens comuns com a ?linha inicial?.Havendo mais
		//	do que uma solu?o o programa deve apresentar todas as solu?es encontradas mas por ordem
		//		crescente de dist?cia.Se n? encontrar uma solu?o dentro das restri?es indicadas, o programa
		//		deve indicar que n? encontrou uma liga?o entre as duas paragens.
		//		9. Listar todos os per?dos de autocarros sem condutor atribu?o.
		//		10. Listar todos os per?dos de condutores sem o servi? completo atribu?o(que n? tenham atingido o
		//			limite m?imo semanal).
		//		11. Efetuar interactivamente a atribui?o de servi? a um condutor, permitindo ao utilizador ver as
		//		disponibilidades de servi? dos autocarros, pedindo ao utilizador informa?o sobre um novo turno e
		//		verificando a consist?cia dessa informa?o com as restri?es de hor?io do condutor e restantes
		//		dados existentes.

		// OK! PARECE QUE ESTAO TODAS IMPLEMENTADAS! HURRAY!!

		cout << "  - MAIN MENU -\n";
		cout << " 1- Line management\n";
		cout << " 2- Driver management\n";
		cout << " 3- Bus management\n";
		cout << " 4- Shift management\n";
		cout << " 5- Calculate shortest trip\n";
		cout << " 6- Visualize Schedules\n";
		cout << " 7- Search Bus Lines by Bus Stop\n";
		cout << " 0- Quit\n";
		cout << "\n";

		string input;

		while (true)
		{
			cout << "Select an option: ";

			getline(cin, input);
			utilities::trimString(input);
			cout << "\n";

			if (input == "1")
			{
				LineManagementMenu();
				break;
			}

			else if (input == "2")
			{
				DriverManagementMenu();
				break;
			}

			else if (input == "3")
			{
				BusManagementMenu();
				break;
			}

			else if (input == "4")
			{
				ShiftManagementMenu();
				break;
			}

			else if (input == "5")
			{
				FindShortestTrip();
				break;
			}
			else if (input == "6")
			{
				SchedulesMenu();
				break;
			}
			else if (input == "7")
			{
				FindBusLineByBusStop();
				break;
			}

			else if (input == "0")
				return;

			else
				cout << "Invalid input\n";

		}

	}
}

void ui::LineManagementMenu()
{
	while (true) {
		ui_utilities::SetWindow(ConsoleWidth, ConsoleHeight);
		ui_utilities::ClearScreen();
		PrintBanner();

		cout << "  - LINE MANAGEMENT MENU -\n";
		cout << " Active bus lines:";
		Lines.PrintLinesNames();
		cout << endl << endl;
		cout << " 1- Create line\n";
		cout << " 2- Edit line \n";
		cout << " 3- Remove line\n";
		cout << " 9- Return to previous menu\n";
		cout << "\n";

		string input;

		while (true)
		{
			cout << "Select an option: ";

			getline(cin, input);
			utilities::trimString(input);
			cout << "\n";

			if (input == "1")
			{
				CreateLineMenu();
				break;
			}

			else if (input == "2")
			{
				EditLineMenu();
				break;
			}

			else if (input == "3")
			{
				RemoveLineMenu();
				break;
			}

			else if (input == "9")
			{
				return;
			}

			else 
				cout << "Invalid input\n";

		}

	}
}

void ui::CreateLineMenu()
{
	ui_utilities::SetWindow(ConsoleWidth,ConsoleHeight);
	ui_utilities::ClearScreen();
	PrintBanner();

	string tempstr;

	Line templine;

	cout << "\n - CREATE LINE MENU -";
	cout << endl;

	while (1)
	{
		cout << "\n Insert new Line's ID: ";

		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (Lines.LineExists(tempstr)) {
			cout << "\nSorry but that Line ID isn't valid! It seems that line already exists.";
			continue;
		}
		else if (tempstr.length() < 3) {
			cout << "\nSorry but the ID you inserted is too short. Please try again!";
			continue;
		}

		break;
	}
	templine.SetID(tempstr);

	while (1)
	{
		cout << "\n Insert new Line's frequency of service (minutes): ";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (!utilities::isNumeric(tempstr)) {
			cout << "\nSorry but it seems you didn't insert a number! Try again.";
			continue;
		}
		if (stoi(tempstr) > 300 || stoi(tempstr) <= 2) {
			cout << "\nYeah... That doesn't seem about right. Try again";
			continue;
		}
		break;
	}

	templine.SetFreq(stoi(tempstr));

	vector<string> tempstops;

	cout << "\n Insert new Line's bus stops (press enter after you type each one and to stop insert 0):";
	cout << endl;


	while (getline(cin, tempstr)) {
		utilities::trimString(tempstr);
		if (tempstr == "0")
		{
			if (tempstops.size() < 2)
			{
				cout << "\nSorry but you need to insert at least 2 stops";
				continue;
			}
			else
				break;

		}
		if (tempstr.length() < 3)
		{
			cout << "\nOops! That is too short... Try again!" << endl;
			continue;
		}
		else
			tempstops.push_back(tempstr);
	}


	vector<unsigned int> temptimebetweenstops;

	cout << "\n Perfect! Now please insert the time it takes to travel between the following stops (minutes): ";
	cout << endl;

	for (size_t i = 0; i < tempstops.size() - 1; i++) {
		cout << "-Travel time beetween " << tempstops[i] << " and " << tempstops[i + 1] << "? ";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (!utilities::isNumeric(tempstr)) {
			cout << "Sorry but it seems you didn't insert a number! Try again.";
			i--;
			continue;
		}
		if (stoi(tempstr) > 300 || stoi(tempstr) <= 2) {
			cout << "Yeah... That doesn't seem about right. Try again";
			i--;
			continue;
		}

		temptimebetweenstops.push_back( stoi(tempstr) );
	}

	templine.SetBus_Stops(tempstops);
	templine.SetTimeBetweenStops(temptimebetweenstops);

	cout << "\n\n Line created, Press any key to continue...";
	cin.get();

	Lines.AddBusLine(templine);
	Lines.SaveToFile();
	Bus_Stops.RebuildBus_Stops(Lines.GetLines()); // rebuild bus stops cache

	return;
}

void ui::EditLineMenu() 
{
	ui_utilities::SetWindow(ConsoleWidth, ConsoleHeight);
	ui_utilities::ClearScreen();
	PrintBanner();

	string tempstr;
	int lineindex;

	cout << "\n - EDIT LINE MENU -"
	<< "\n\n Please select one of the following bus lines:";

	Lines.PrintLinesNames();
	cout << endl << endl;

	while (1)
	{
		cout << " Line: ";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (tempstr == "0") return;

		if (Lines.LineExists(tempstr))
			break;

		cout << "\nLine not found!";
		cout << "\nEnter 0 if you wish to go back to the previous menu.\n";
	}
	lineindex = Lines.SearchLine(tempstr);

	while(1)
	{
		cout << "\n Insert line's new ID (leave blank to not edit): ";
		getline(cin,tempstr);
		utilities::trimString(tempstr);

		if (tempstr == "")
			break;

		if (Lines.LineExists(tempstr)) {
			cout << "\nSorry but that Line ID isn't valid! It seems that line already exists.";
			continue;
		}
		else if (tempstr.length() < 3) {
			cout << "\nSorry but the ID you inserted is too short. Please try again!";
			continue;
		}

		Lines.GetLines()[lineindex].SetID(tempstr);
		break;
	}

	while(1)
	{
		cout << "\n Insert line's new frequency of service (leave blank to not edit): ";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (tempstr == "")
			break;

		if (!utilities::isNumeric(tempstr)) {
			cout << "\nSorry but it seems you didn't insert a number! Try again.";
			continue;
		}
		if (stoi(tempstr) > 300 || stoi(tempstr) <= 2) {
			cout << "\nYeah... That doesn't seem about right. Try again";
			continue;
		}

		Lines.GetLines()[lineindex].SetFreq(stoi(tempstr));
		break;
	}

	vector<string> tempstops;

	cout << "\n Insert line's new bus stops (press enter after you type each one and to stop insert 0) \n(leave blank if you don't wish to make changes):";
	cout << endl;

	bool altered = 1;

	while (getline(cin, tempstr)) {
		utilities::trimString(tempstr);

		if (tempstr == "")
		{
			altered = 0;
			break;
		}

		if (tempstr == "0")
		{
			if (tempstops.size() < 2)
			{
				cout << "\nSorry but you need to insert at least 2 stops";
				continue;
			}
			else
			{
				Lines.GetLines()[lineindex].SetBus_Stops(tempstops);
				break;
			}

		}
		if (tempstr.length() < 3)
		{
			cout << "\nOops! That is too short... Try again!" << endl;
			continue;
		}
		else
			tempstops.push_back(tempstr);
	}

	vector<unsigned int> temptimebetweenstops;

	if(altered) cout << "\n Now please insert the time it takes to travel between the following stops (minutes): ";
	else cout << "\n Now please insert the time it takes to travel between the following stops (minutes)\n (leave blank if you don't wish to make changes): ";
	cout << endl;

	bool test = 1;

	for (size_t i = 0; i < Lines.GetLines()[lineindex].GetBus_Stops().size() - 1; i++) {
		cout << "-Travel time beetween " << Lines.GetLines()[lineindex].GetBus_Stops()[i] << " and " << Lines.GetLines()[lineindex].GetBus_Stops()[i + 1] << "? ";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (tempstr == "" && !altered)
		{
			test = 0;
			break;
		}

		if (!utilities::isNumeric(tempstr)) {
			cout << "Sorry but it seems you didn't insert a number! Try again.";
			i--;
			continue;
		}
		if (stoi(tempstr) > 300 || stoi(tempstr) <= 2) {
			cout << "Yeah... That doesn't seem about right. Try again";
			i--;
			continue;
		}

		temptimebetweenstops.push_back( stoi(tempstr) );
	}

	if (test)
		Lines.GetLines()[lineindex].SetTimeBetweenStops(temptimebetweenstops);

	Lines.SaveToFile();
	cout << "\n\n Line edited, Press any key to continue...";
	cin.get();

	Bus_Stops.RebuildBus_Stops(Lines.GetLines()); // rebuild bus stops cache

	return;
}

void ui::RemoveLineMenu()
{
	ui_utilities::SetWindow(ConsoleWidth,ConsoleHeight);
	ui_utilities::ClearScreen();
	PrintBanner();

	string tempstr;

	cout << "\n - REMOVE LINE MENU -"
	<< "\n Please select one of the following bus lines:";

	Lines.PrintLinesNames();

	cout << "\n Keep in mind all the shifts associated with that line will be also deleted!";

	cout << endl << endl;

	while (1)
	{
		cout << " Line: ";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (tempstr == "0") return;

		if (Lines.RemoveBusLineByID(tempstr))
			break;

		cout << "\nLine not found!";
		cout << "\nEnter 0 if you wish to go back to the previous menu.\n";
	}

	Bus_Stops.RebuildBus_Stops(Lines.GetLines()); // rebuild bus stops cache
	Lines.SaveToFile();
	cout << "\n  Line removed, Press any key to continue...";
	cin.get();

	return;
}


void ui::DriverManagementMenu()
{
	while (true) {

		ui_utilities::SetWindow(ConsoleWidth, ConsoleHeight);
		ui_utilities::ClearScreen();
		PrintBanner();

		cout << " - MANAGE DRIVERS MENU -";
		cout << "\n Currently there are " << Drivers.GetDrivers().size() << " drivers employed at SEMPRARROLAR.";
		cout << endl << endl;
		cout << " 1- Create driver\n";
		cout << " 2- Edit driver\n";
		cout << " 3- Remove driver\n";
		cout << " 4- List drivers\n";
		cout << " 5- List driver shifts\n";
		cout << " 9- Return to previous menu\n";
		cout << "\n";

		string input;

		while (1)
		{
			cout << "Select an option: ";

			getline(cin, input);
			cout << "\n";

			if (input == "1")
			{
				CreateDriverMenu();
				break;
			}

			else if (input == "2")
			{
				EditDriverMenu();
				break;
			}

			else if (input == "3")
			{
				RemoveDriverMenu();
				break;
			}

			else if (input == "4")
			{
				ListDriversMenu();
				break;
			}

			else if (input == "5")
			{
				ListDriverShiftsMenu();
				break;
			}

			else if (input == "9")
			{
				return;
			}
			else
				cout << "Invalid input\n";

		}

	}
}

void ui::CreateDriverMenu()
{
	ui_utilities::SetWindow(ConsoleWidth,ConsoleHeight);
	ui_utilities::ClearScreen();
	PrintBanner();

	string tempstr;

	Driver tempdriver;

	cout << " - CREATE DRIVER MENU -";
	cout << endl;

	while (1)
	{
		cout << "\n Insert new driver's ID: ";

		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (Drivers.DriverExists(tempstr)) {
			cout << "\nSorry but it seems there already exists a driver with that ID! Try again.";
			continue;
		}
		else if (tempstr.length() < 2) {
			cout << "\nSorry but the ID you entered is too short! Try again.";
			continue;
		}
		break;
	}
	tempdriver.SetID(tempstr);


	while (1)
	{
		cout << "\n Insert driver's name: ";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (tempstr.length() < 3) {
			cout << "Sorry but the name you entered is too short! Try again.";
			continue;
		}
		break;
	}
	tempdriver.SetName(tempstr);

	while (1)
	{
		cout << "\n Insert driver's maximum hours per shift:";
		getline(cin, tempstr);

		// Condition to continue program
		if (utilities::isNumeric(tempstr) && stoi(tempstr) > 0)
			break;

		cout << "Invalid input!";
	}
	tempdriver.SetMaxHoursShift(stoi(tempstr));


	while (1)
	{
		cout << "\n Insert driver's maximum hours of work per week:";
		getline(cin, tempstr);

		// Condition to continue program
		if (utilities::isNumeric(tempstr) && stoi(tempstr) > 0)
			break;

		cout << "Invalid input!";
	}
	tempdriver.SetMaxHoursWeek(stoi(tempstr));


	while (1)
	{
		cout << "\n Insert driver's minimum rest hours between shifts:";
		getline(cin, tempstr);

		// Condition to continue program
		if (utilities::isNumeric(tempstr) && stoi(tempstr) > 0)
			break;

		cout << "Invalid input!";
	}

	tempdriver.SetMinHoursRest(stoi(tempstr));

	Drivers.AddDriver(tempdriver);
	Drivers.SaveToFile();	
	cout << "\n\n  Driver created, Press any key to continue...";
	cin.get();

	return;
}

void ui::EditDriverMenu()
{
	ui_utilities::SetWindow(ConsoleWidth, ConsoleHeight);
	ui_utilities::ClearScreen();
	PrintBanner();

	string tempstr;
	Driver* driver;

	cout << "\n - EDIT DRIVER MENU -"
	<< "\n\n Please select one of the following drivers:";

	Drivers.PrintLinesNames();
	cout << endl << endl;

	while (1)
	{
		cout << " Driver: ";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (tempstr == "0") return;

		if (Drivers.DriverExists(tempstr))
			break;

		cout << "\nDriver not found!";
		cout << "\nEnter 0 if you wish to go back to the previous menu.\n";
	}

	driver = Drivers.FindDriver(tempstr);

	while(1)
	{
		cout << "\n Insert driver's new ID (leave blank to not edit) :";
		getline(cin,tempstr);
		utilities::trimString(tempstr);

		if (tempstr == "")
			break;

		if (Drivers.DriverExists(tempstr)) {
			cout << "\nSorry but that ID isn't valid! It seems that driver already exists.";
			continue;
		}
		else if (tempstr.length() < 3) {
			cout << "\nSorry but the ID you inserted is too short. Please try again!";
			continue;
		}

		driver->SetID(tempstr);
		break;
	}

	while(1)
	{
		cout << "\n Insert driver's new name (leave blank to not edit): ";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (tempstr == "")
			break;

		bool test = 1;
		for (int i = 0; i < tempstr.size(); ++i)
		{
			if (tempstr[i] >= '0' && tempstr[i]<= '9')
			{
				test = 0;
				break;
			}
		}

		if (test)
		{
			driver->SetName(tempstr);
			break;
		}
		else
		{
			cout << "\nSorry but a name has no numbers!";
			continue;
		}

	}

	while(1)
	{
		cout << "\n Insert driver's new maximum hours per shift (leave blank to not edit): ";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (tempstr == "")
			break;

		if (utilities::isNumeric(tempstr) && stoi(tempstr) > 0)
		{
			driver->SetMaxHoursShift(stoi(tempstr));
			break;
		}

		cout << "\nSorry but you need to insert a number!";
	}

	while(1)
	{
		cout << "\n Insert driver's new maximum hours per week (leave blank to not edit): ";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (tempstr == "")
			break;

		if (utilities::isNumeric(tempstr) && stoi(tempstr) > 0)
		{
			driver->SetMaxHoursWeek(stoi(tempstr));
			break;
		}

		cout << "\nSorry but you need to insert a number!";
	}

	while(1)
	{
		cout << "\n Insert driver's new minimum rest hours (leave blank to not edit): ";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (tempstr == "")
			break;

		if (utilities::isNumeric(tempstr) && stoi(tempstr) > 0)
		{
			driver->SetMinHoursRest(stoi(tempstr));
			break;
		}

		cout << "\nSorry but you need to insert a number!";
	}
	
	Drivers.SaveToFile();	
	cout << "\n\n  Driver Edited, Press any key to continue...";
	cin.get();

	return;
}

void ui::ListDriversMenu() {
	ui_utilities::SetWindow(ConsoleWidth, ConsoleHeight);
	ui_utilities::ClearScreen();
	PrintBanner();
	cout << endl << endl << " Listing Drivers: " << endl << endl;

	Drivers.ListDrivers();
	
	cout << "\n Press any key to continue...";
	cin.get();
}

void ui::ListDriverShiftsMenu() {

	ui_utilities::SetWindow(ConsoleWidth, 500);
	ui_utilities::ClearScreen();
	PrintBanner();

	string tempstr;

	cout << " - LIST DRIVER SHIFTS MENU -";
	cout << endl;

	cout << "\nPlease select one of the following drivers:";

	Drivers.PrintLinesNames();
	cout << endl << endl;

	while (1)
	{
		cout << "\n Driver's ID:";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (Drivers.DriverExists(tempstr))
			break;

		cout << "\nDriver not found!";
	}
	Driver *driver = Drivers.FindDriver(tempstr);

	cout << endl;

	Shifts_InterfaceClass::ListShifts( utilities::GetShiftsFromDriver(Shifts_Interface.GetShifts(), driver->GetID()) , Drivers.GetDrivers());

	cout << endl << endl << "\n       Press any key to continue...";
	cin.get();
}

void ui::RemoveDriverMenu()
{
	ui_utilities::SetWindow(ConsoleWidth,ConsoleHeight);
	ui_utilities::ClearScreen();
	PrintBanner();

	string tempstr;

	cout << " - REMOVE DRIVER MENU -";
	cout << endl;

	while (1)
	{
		cout << "\n Insert driver's ID:";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (Drivers.RemoveDriverByID(tempstr))
			break;

		cout << "\nDriver not found!";
	}

	Drivers.SaveToFile();
	cout << "\n\n  Driver removed, Press any key to continue...";
	cin.get();

	return;
}

void ui::BusManagementMenu() {
	while (true) {

		ui_utilities::SetWindow(ConsoleWidth, ConsoleHeight);
		ui_utilities::ClearScreen();
		PrintBanner();

		cout << " - MANAGE BUSES MENU -";
		cout << "\n Currently there are " << Buses.GetNumberOfBuses() << " buses being used at SEMPRARROLAR.";
		cout << endl << endl;
		cout << " 1- Create bus\n";
		cout << " 2- List buses\n";
		cout << " 3- List bus shifts\n";
		cout << " 4- Remove bus\n";
		cout << " 9- Return to previous menu\n";
		cout << "\n";

		string input;

		while (1)
		{
			cout << "Select an option: ";

			getline(cin, input);
			cout << "\n";

			if (input == "1")
			{
				CreateBusMenu();
				break;
			}
			else if (input == "2")
			{
				ListBusesMenu();
				break;
			}
			else if (input == "3")
			{
				ListBusShiftsMenu();
				break;
			}
			else if (input == "4")
			{
				RemoveBusMenu();
				break;
			}
			else if (input == "9")
			{
				return;
			}
			else {
				cout << "\nInvalid Input";
			}
		}
	}
}

void ui::CreateBusMenu() {
	ui_utilities::SetWindow(ConsoleWidth, ConsoleHeight);
	ui_utilities::ClearScreen();
	PrintBanner();

	string tempstr;

	Driver tempdriver;

	cout << " - CREATE BUS MENU -";
	cout << endl;

	while (1)
	{
		cout << "\n Insert new Bus ID: ";

		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (Buses.BusExists(tempstr)) {
			cout << "\nSorry but it seems there already exists a bus with that ID! Try again.";
			continue;
		}
		else if (tempstr.length() < 2) {
			cout << "\nSorry but the ID you entered is too short! Try again.";
			continue;
		}
		break;
	}
	Buses.InsertBus(tempstr);
	cout << "\n   Bus created, Press any key to continue...";
	cin.get();
	return;

}

void ui::ListBusesMenu() {
	ui_utilities::SetWindow(ConsoleWidth, ConsoleHeight);
	ui_utilities::ClearScreen();
	PrintBanner();

	string tempstr;

	Driver tempdriver;

	cout << " - LIST BUSES MENU -" << endl << endl;

	Buses.ListBuses();

	cout << "\n Press any key to continue...";
	cin.get();
	return;

}

void ui::ListBusShiftsMenu() {
	ui_utilities::SetWindow(ConsoleWidth, ConsoleHeight);
	ui_utilities::ClearScreen();
	PrintBanner();

	string tempstr;

	cout << " - LIST BUS SHIFTS MENU -";
	cout << endl;

	while (1)
	{
		cout << "\n Insert bus ID :";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (Buses.BusExists(tempstr))
			break;

		cout << "\nBus not found!";
	}

	cout << endl;

	Shifts_InterfaceClass::ListShifts( Buses.GetShifts(tempstr), Drivers.GetDrivers());

	cout << endl << endl << "\n       Press any key to continue...";
	cin.get();
}

void ui::RemoveBusMenu() {
	ui_utilities::SetWindow(ConsoleWidth, ConsoleHeight);
	ui_utilities::ClearScreen();
	PrintBanner();

	string tempstr;

	Driver tempdriver;

	cout << " - REMOVE BUS MENU -"
	<< "\n Please select one of the following buses:";

	Buses.ListBuses();

	cout << "\n Keep in mind all the shifts associated with that bus will be also deleted!";

	cout << endl << endl;

	while (1)
	{
		cout << "\n Insert Bus ID: ";

		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (!Buses.BusExists(tempstr)) {
			cout << "\nSorry but no Bus was found with that ID! Try again.";
			continue;
		}
		break;
	}
	Buses.RemoveBus(tempstr);
	cout << "\n   Bus removed, Press any key to continue...";
	cin.get();
	return;

}

void ui::ShiftManagementMenu() {
	while (true) {

		ui_utilities::SetWindow(ConsoleWidth, ConsoleHeight);
		ui_utilities::ClearScreen();
		PrintBanner();

		cout << " - MANAGE SHIFTS MENU -";
		cout << "\n Currently there are " << Shifts_Interface.GetShifts().size() << " work shifts at SEMPRARROLAR.";
		cout << endl << endl;
		cout << " 1- Create Shift\n";
		cout << " 2- List all shifts\n";
		cout << " 3- Remove Shift\n";
		cout << " 4- Visualize driver work schedule\n";
		cout << " 5- List drivers who haven't reached their weekly work limit\n";
		cout << " 6- Visualize bus service schedule\n";
		cout << " 9- Return to previous menu\n";
		cout << "\n";

		string input;

		while (1)
		{
			cout << "Select an option: ";

			getline(cin, input);
			cout << "\n";

			if (input == "1")
			{
				CreateShiftMenu();
				break;
			}
			else if (input == "2")
			{
				ListAllShiftsMenu();
				break;
			}
			else if (input == "3")
			{
				RemoveShiftMenu();
				break;
			}
			else if (input == "4")
			{
				VisualizeDriverWorkScheduleMenu();
				break;
			}
			else if (input == "5")
			{
				ListAvailableDriversMenu();
				break;
			}
			else if (input == "6")
			{
				VisualizeBusServiceScheduleMenu();
				break;
			}
			else if (input == "9")
			{
				return;
			}
			else {
				cout << "\nInvalid Input\n";
			}
		}
	}
}

void ui::CreateShiftMenu() {
	ui_utilities::SetWindow(ConsoleWidth, 500);
	ui_utilities::ClearScreen();
	PrintBanner();

	string tempstr;

	cout << " - CREATE SHIFT MENU -";
	cout << endl;

	cout << " --> First select one of the following drivers:";
	Drivers.PrintLinesNames();

	cout << endl << endl;

	while (1)
	{
		cout << " Driver: ";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (tempstr == "0") return;

		if (Drivers.DriverExists(tempstr))
			break;

		cout << "\nDriver not found!";
		cout << "\nEnter 0 if you wish to go back to the previous menu.\n";
	}

	Driver* driver = Drivers.FindDriver(tempstr);

	unsigned int workHours = driver->GetNrWorkingHours(utilities::GetShiftsFromDriver(Shifts_Interface.GetShifts(), driver->GetID()));
	if (driver->GetMaxHoursWeek() - workHours == 0) {
		cout << endl << "Oops! It seems that driver has reached his weekly limit of work hours. ";
		cout << endl << endl << "\n     Press any key to continue...";
		cin.get();
		return;
	}
	driver->ShowWorkSchedule(utilities::GetShiftsFromDriver(Shifts_Interface.GetShifts(), driver->GetID()));
	cout << endl;
	cout << "  Number of available hours to work: " << driver->GetMaxHoursWeek() - driver->GetNrWorkingHours(utilities::GetShiftsFromDriver(Shifts_Interface.GetShifts(), driver->GetID()));
	cout << endl;
	cout << endl;

	cout << " --> Now select one of the following buses:";

	Buses.ListBuses();

	cout << endl << endl;

	while (1)
	{
		cout << "\n Insert Bus ID: ";

		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (!Buses.BusExists(tempstr)) {
			cout << "\nSorry but no Bus was found with that ID! Try again.";
			continue;
		}
		break;
	}

	Buses.ShowServiceSchedule(tempstr, utilities::GetShiftsFromBusID(Shifts_Interface.GetShifts(), tempstr));

	string busID = tempstr;

	cout << endl << endl;

	cout << " --> Now enter the day of the shift: ";

	while (1)
	{
		cout << "\n Insert Day: ";

		getline(cin, tempstr);
		utilities::trimString(tempstr);

		for (auto& elem : tempstr) // lower case the string
			elem = tolower(elem);

		if (utilities::DayStringToNumber(tempstr) == -1) {
			cout << "\nSorry but that isn't a valid day. Try again";
			continue;
		}
		break;
	}

	int dayNumber = utilities::DayStringToNumber(tempstr);

	cout << " --> Now please enter the start hour of the shift: ";

	while (1)
	{
		cout << "\n Insert Start Hour: ";

		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (!utilities::isNumeric(tempstr)) {
			cout << "\nSorry but it seems you didn't insert a number! Try again.";
			continue;
		}
		else if (stoi(tempstr) < SCHEDULE_START || stoi(tempstr) >= SCHEDULE_END-1) {
			cout << "\nSorry but it seems you didn't insert a valid number! Let me remind you that the shift start hour must be between " << SCHEDULE_START << " and " << (SCHEDULE_END - 1)
				<< endl << "Try again.";
			continue;
		}
		break;
	}

	unsigned int startHour = stoi(tempstr);

	cout << " --> Now please enter the end hour of the shift: ";

	while (1)
	{
		cout << "\n Insert End Hour: ";

		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (!utilities::isNumeric(tempstr)) {
			cout << "\nSorry but it seems you didn't insert a number! Try again.";
			continue;
		}
		else if (stoi(tempstr) < SCHEDULE_START+1 || stoi(tempstr) >= SCHEDULE_END) {
			cout << "\nSorry but it seems you didn't insert a valid number! Let me remind you that the shift end hour must be between " << (SCHEDULE_START+1) << " and " << SCHEDULE_END
				<< endl << "Try again.";
			continue;
		}
		break;
	}

	unsigned int endHour = stoi(tempstr);

	cout << " --> Now please enter one of the following lines of the shift:";

	Lines.PrintLinesNames();

	cout << endl << endl;

	while (1)
	{
		cout << " Line: ";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (Lines.LineExists(tempstr))
			break;

		cout << "\nLine not found! Try again \n";
	}

	string lineID = tempstr;

	Shift newShift(dayNumber, startHour, endHour, driver->GetID(), busID, lineID);


	int canAddShift = driver->CanAddShift(newShift, utilities::GetShiftsFromDriver(Shifts_Interface.GetShifts(), driver->GetID()));
	switch (canAddShift) {
		case NOT_AVAILABLE:
			cout << "The driver is already working during that time! I'm sorry but you will have to try again." << endl; // try harder this time
			cout << endl << "\n    Press any key to continue...";
			cin.get();
			return;
		case MUST_RESPECT_REST_TIME:
			cout << "The driver cannot work that shift because it includes his mandatory rest hours! I'm sorry but you will have to try again." << endl;
			cout << endl << "\n    Press any key to continue...";
			cin.get();
			return;
		case SHIFT_TOO_LONG:
			cout << "The driver cannot work that shift because it is too long for him! I'm sorry but you will have to try again." << endl;
			cout << endl << "\n    Press any key to continue...";
			cin.get();
			return;
	}

	if (!Buses.CanAddShift(busID, newShift)) {
		cout << "The driver is cannot work that shift because the bus isn't available during that time! I'm sorry but you will have to try again." << endl;
		cout << endl << "\n    Press any key to continue...";
		cin.get();
		return;
	}

	Shifts_Interface.InsertShift(newShift);

	cout << endl << endl << "\n    Shift created, Press any key to continue...";
	cin.get();
}

void ui::RemoveShiftMenu()
{
	ui_utilities::SetWindow(ConsoleWidth, ConsoleHeight);
	ui_utilities::ClearScreen();
	PrintBanner();

	string tempstr;

	cout << " - REMOVE SHIFT MENU -";
	cout << endl;

	cout << endl;

	Shifts_InterfaceClass::ListShifts(Shifts_Interface.GetShifts(), Drivers.GetDrivers(), true);
	cout << endl;

	while (1)
	{
		cout << " Shift #: ";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (tempstr == "0") return;

		if (!utilities::isNumeric(tempstr)) {
			cout << "\nSorry but it seems you didn't insert a number! Try again.";
			continue;
		}
		if (stoi(tempstr) > Shifts_Interface.GetShifts().size() ) {
			cout << "\nSorry but it seems the number you inserted is just too damn high! Try again";
			continue;
		}

		cout << "\nShift not found!";
		cout << "\nEnter 0 if you wish to go back to the previous menu.\n";
	}

	Shifts_Interface.RemoveShiftByIndex(stoi(tempstr));

	cout << endl << endl << "\n     Shift removed,  Press any key to continue...";
	cin.get();
}

void ui::VisualizeDriverWorkScheduleMenu() {
	ui_utilities::SetWindow(ConsoleWidth, ConsoleHeight);
	ui_utilities::ClearScreen();
	PrintBanner();

	string tempstr;
	Driver* driver;

	cout << "\n - VIEW DRIVER SCHEDULE MENU -"
		<< "\n\n Please select one of the following drivers:";

	Drivers.PrintLinesNames();
	cout << endl << endl;

	while (1)
	{
		cout << " Driver: ";
		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (tempstr == "0") return;

		if (Drivers.DriverExists(tempstr))
			break;

		cout << "\nDriver not found!";
		cout << "\nEnter 0 if you wish to go back to the previous menu.\n";
	}
	
	driver = Drivers.FindDriver(tempstr);

	driver->ShowWorkSchedule(utilities::GetShiftsFromDriver(Shifts_Interface.GetShifts(), driver->GetID()));

	cout << endl;

	cout << "\n   Press any key to continue...";
	cin.get();
}

void ui::ListAvailableDriversMenu() {
	ui_utilities::SetWindow(ConsoleWidth, 500);
	ui_utilities::ClearScreen();
	PrintBanner();

	string tempstr;

	cout << "\n - LIST AVAILABLE DRIVERS MENU -" << endl << endl;

	Drivers.ListAvailableDrivers(Shifts_Interface.GetShifts());

	cout << endl;

	cout << endl;

	cout << "\n   Press any key to continue...";
	cin.get();
}

void ui::ListAllShiftsMenu()
{
	ui_utilities::SetWindow(ConsoleWidth, 500);
	ui_utilities::ClearScreen();
	PrintBanner();

	string tempstr;

	cout << " - LIST ALL SHIFTS MENU -";
	cout << endl;

	cout << endl;

	Shifts_InterfaceClass::ListShifts( Shifts_Interface.GetShifts(), Drivers.GetDrivers());

	cout << endl << endl << "\n       Press any key to continue...";
	cin.get();
}

void ui::VisualizeBusServiceScheduleMenu()
{
	ui_utilities::SetWindow(ConsoleWidth, ConsoleHeight);
	ui_utilities::ClearScreen();
	PrintBanner();

	string tempstr;

	Driver tempdriver;

	cout << " - VISUALIZE BUS SERVICE SCHEDULE MENU -"
		<< "\n Please select one of the following buses:";

	Buses.ListBuses();

	cout << endl << endl;

	while (1)
	{
		cout << "\n Insert Bus ID: ";

		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (!Buses.BusExists(tempstr)) {
			cout << "\nSorry but no Bus was found with that ID! Try again.";
			continue;
		}
		break;
	}

	cout << endl;
	
	Buses.ShowServiceSchedule(tempstr, utilities::GetShiftsFromBusID(Shifts_Interface.GetShifts(), tempstr));

	cout << endl;

	cout << "\n   Press any key to continue...";
	cin.get();
	return;
}


void ui::FindShortestTrip() {
	ui_utilities::SetWindow(ConsoleWidth, 500);
	ui_utilities::ClearScreen();
	PrintBanner();

	string tempstr;

	Driver tempdriver;

	cout << " - FIND SHORTEST TRIP MENU -"
	<< "\n Please select two of the following bus stops:";

	Bus_Stops.PrintAllBus_Stops_Names();
	cout << endl;

	while (1)
	{
		cout << "\n Insert Bus Stop 1 Name: ";

		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (!Bus_Stops.FindBus_StopByName(tempstr)) {
			cout << "\nSorry but no Bus Stop was found with that name! Try again.";
			continue;
		}
		break;
	}

	Bus_Stop* bus_stop1 = Bus_Stops.FindBus_StopByName(tempstr);

	while (1)
	{
		cout << "\n Insert Bus Stop 2 Name: ";

		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (!Bus_Stops.FindBus_StopByName(tempstr)) {
			cout << "\nSorry but no Bus Stop was found with that name! Try again.";
			continue;
		}
		break;
	}

	Bus_Stop* bus_stop2 = Bus_Stops.FindBus_StopByName(tempstr);

	cout << endl;


	//// ONLY GO 1 LEVEL DEEP, AS REQUESTED BY THE PROJECT SPECIFICATION
	struct Viagem {
		vector<Line*> lines;
		vector<string> bus_stops;

	};
	multimap<unsigned int, Viagem> mmapTrips; // first element is the duration, the second one is the trip struct
											  // LEVEL 0
	for (Line* line1 : bus_stop1->GetLines())
	{
		for (Line* line2 : bus_stop2->GetLines())
		{ // we can directly compare the pointers for better performance
			if (line1 == line2) {
				unsigned int bus_stop_1_nr = Bus_Stop::GetBus_StopNumber(line1->GetBus_Stops(), bus_stop1->GetName());
				unsigned int bus_stop_2_nr = Bus_Stop::GetBus_StopNumber(line1->GetBus_Stops(), bus_stop2->GetName());
				unsigned int tripTime = abs(Bus_Stop::CalculateOffset(line1->GetTimeBetweenStops(), bus_stop_1_nr) - Bus_Stop::CalculateOffset(line1->GetTimeBetweenStops(), bus_stop_2_nr));

				Viagem trip;
				trip.lines.push_back(line1);

				if (bus_stop_1_nr < bus_stop_2_nr) {
					for (size_t i = bus_stop_1_nr; i <= bus_stop_2_nr; i++) {
						trip.bus_stops.push_back(line1->GetBus_Stops()[i] + "[" + line1->GetID() + "]");
					}
				}
				else {
					for (size_t i = bus_stop_1_nr; i >= bus_stop_2_nr && i <= bus_stop_1_nr; i--) {	// O uso do tipo int nesta linha face ao size_t ?com o intuito de prevenir casos de overflow que surgiram durante o teste do programa
						trip.bus_stops.push_back(line1->GetBus_Stops()[i] + "[" + line1->GetID() + "]");
					}
				}
				mmapTrips.insert(pair<unsigned int, Viagem>(tripTime, trip));
			}
		}
	}
	// LEVEL 1
	for (Line* line1 : bus_stop1->GetLines())
	{
		for (const string& bus_stop_line1_name : line1->GetBus_Stops()) {
			auto bus_stop2_obj = Bus_Stops.FindBus_StopByName(bus_stop_line1_name);
			for (Line* line2 : bus_stop2_obj->GetLines()) {
				if (line1->GetID() == line2->GetID()) continue;
				if (bus_stop1 == bus_stop2_obj) continue;
				bool containsSecondBus_Stop = find(line2->GetBus_Stops().begin(), line2->GetBus_Stops().end(), bus_stop2->GetName()) != line2->GetBus_Stops().end();
				if (!containsSecondBus_Stop) continue;
				for (const string& bus_stop_line2_name : line2->GetBus_Stops()) {
					if (bus_stop_line1_name == bus_stop_line2_name && line1 != line2) { // Got a Match
																						//auto bus_stop3_obj = Bus_Stops.FindBus_StopByName(bus_stop_line2_name);
						unsigned int bus_stop_1_line1_nr = Bus_Stop::GetBus_StopNumber(line1->GetBus_Stops(), bus_stop1->GetName());
						unsigned int bus_stop_2_line1_nr = Bus_Stop::GetBus_StopNumber(line1->GetBus_Stops(), bus_stop2_obj->GetName());
						unsigned int bus_stop_2_line2_nr = Bus_Stop::GetBus_StopNumber(line2->GetBus_Stops(), bus_stop2_obj->GetName());
						unsigned int bus_stop_3_line2_nr = Bus_Stop::GetBus_StopNumber(line2->GetBus_Stops(), bus_stop2->GetName());

						if (bus_stop_1_line1_nr == bus_stop_2_line1_nr || bus_stop_2_line2_nr == bus_stop_3_line2_nr) break;
						// the code that lays ahead may not be pretty, but it gets the job done. no time for refactoring
						unsigned int tripTime = abs(Bus_Stop::CalculateOffset(line1->GetTimeBetweenStops(), bus_stop_1_line1_nr) - Bus_Stop::CalculateOffset(line1->GetTimeBetweenStops(), bus_stop_2_line1_nr))
							+ abs(Bus_Stop::CalculateOffset(line2->GetTimeBetweenStops(), bus_stop_2_line2_nr) - Bus_Stop::CalculateOffset(line2->GetTimeBetweenStops(), bus_stop_3_line2_nr));

						Viagem trip;
						trip.lines.push_back(line1);
						trip.lines.push_back(line2);

						// direct direction
						if (bus_stop_1_line1_nr < bus_stop_2_line1_nr) {
							for (size_t i = bus_stop_1_line1_nr; i <= bus_stop_2_line1_nr; i++) {
								trip.bus_stops.push_back(line1->GetBus_Stops()[i] + "[" + line1->GetID() + "]");
							}
						}
						// reverse direction
						else {
							for (size_t i = bus_stop_1_line1_nr; i >= bus_stop_2_line1_nr && i <= bus_stop_1_line1_nr; i--) {
								trip.bus_stops.push_back(line1->GetBus_Stops()[i] + "[" + line1->GetID() + "]");
							}
						}
						// lets make the intersection of the lines obvious to the user:
						trip.bus_stops[trip.bus_stops.size() - 1].pop_back(); // delete last char
						trip.bus_stops[trip.bus_stops.size() - 1] += "|" + line2->GetID() + "]";

						// build the rest of the trip bus stops after the mutual stop:
						// forward direction
						if (bus_stop_2_line2_nr < bus_stop_3_line2_nr) {
							bus_stop_2_line2_nr++;
							for (size_t i = bus_stop_2_line2_nr; i <= bus_stop_3_line2_nr; i++) {
								trip.bus_stops.push_back(line2->GetBus_Stops()[i] + "[" + line2->GetID() + "]");
							}
						}
						// reverse direction
						else {
							bus_stop_2_line2_nr--;
							for (size_t i = bus_stop_2_line2_nr; i >= bus_stop_3_line2_nr && i <= bus_stop_2_line2_nr; i--) {
								trip.bus_stops.push_back(line2->GetBus_Stops()[i] + "[" + line2->GetID() + "]");
							}
						}
						mmapTrips.insert(pair<unsigned int, Viagem>(tripTime, trip));
					}
				}
			}
		}
	}

	// DISPLAY RESULTS
	int x = 1;
	for (auto iterator = mmapTrips.begin(); iterator != mmapTrips.end(); iterator++) {
		cout << "-----> Trip " << x << endl;;
		cout << "--> Trip Time: " << iterator->first << " minutes" << endl;
		cout << "--> Lines: ";
		bool firstIteration = true;
		for (Line* line : iterator->second.lines) {
			if (firstIteration) {
				cout << line->GetID();
				firstIteration = false;
				continue;
			}
			cout << ", " << line->GetID();
		}
		firstIteration = true;
		cout << endl;
		cout << "--> Bus Stops: ";
		for (const string& bus_stop_name : iterator->second.bus_stops) {
			if (firstIteration) {
				cout << bus_stop_name;
				firstIteration = false;
				continue;
			}
			cout << ", " << bus_stop_name;
		}
		cout << endl << endl;
		x++;

	}

	if (mmapTrips.empty()) {
		cout << " There are no connections between those 2 bus stops";
	}

	cout << endl;

	cout << "   Press any key to continue...";
	cin.get();
}

void ui::SchedulesMenu() {
	while (true) {

		ui_utilities::SetWindow(ConsoleWidth, ConsoleHeight);
		ui_utilities::ClearScreen();
		PrintBanner();

		cout << " - VIEW SCHEDULES MENU -";
		cout << "\n Currently there are " << Bus_Stops.getVecBusStops().size() << " different bus stops.";
		cout << endl << endl;
		cout << " 1- View Line Schedule\n";
		cout << " 2- View Bus Stop Schedule\n";
		cout << " 9- Return to previous menu\n";
		cout << "\n";

		string input;

		while (1)
		{
			cout << "\nSelect an option: ";

			getline(cin, input);
			cout << "\n";

			if (input == "1")
			{
				ViewLineScheduleMenu();
				break;
			}
			else if (input == "2")
			{
				ViewBus_StopScheduleMenu();
				break;
			}
			else if (input == "9")
			{
				return;
			}
			else {
				cout << "\nInvalid Input";
			}
		}
	}
}

void ui::ViewLineScheduleMenu() {
	ui_utilities::SetWindow(ConsoleWidth, 500);
	ui_utilities::ClearScreen();
	PrintBanner();

	string tempstr;

	Driver tempdriver;

	cout << " - VIEW LINE SCHEDULE MENU -"
	<< "\n Please select one of the following bus lines:";

	Lines.PrintLinesNames();
	cout << endl << endl;

	while (1)
	{
		cout << "\n Insert Line: ";

		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (!Lines.LineExists(tempstr)) {
			cout << "\nSorry but no Bus Line was found with that ID! Try again.";
			continue;
		}
		break;
	}

	cout << endl;

	Line* line = Lines.FindLine(tempstr);

	line->ShowSchedule();

	cout << "\n   Press any key to continue...";
	cin.get();
}

void ui::ViewBus_StopScheduleMenu() {
	ui_utilities::SetWindow(ConsoleWidth, 500);
	ui_utilities::ClearScreen();
	PrintBanner();

	string tempstr;

	Driver tempdriver;

	cout << " - VIEW BUS STOP SCHEDULE MENU -"
	<< "\n Please select one of the following bus stops:";

	Bus_Stops.PrintAllBus_Stops_Names();
	cout << endl << endl;

	while (1)
	{
		cout << "\n Insert Bus Stop Name: ";

		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (!Bus_Stops.FindBus_StopByName(tempstr)) {
			cout << "\nSorry but no Bus Stop was found with that name! Try again.";
			continue;
		}
		break;
	}

	Bus_Stop* bus_stop = Bus_Stops.FindBus_StopByName(tempstr);

	bus_stop->ShowSchedule();

	cout << "\n   Press any key to continue...";
	cin.get();
}


void ui::FindBusLineByBusStop() 
{
	ui_utilities::SetWindow(ConsoleWidth, 500);
	ui_utilities::ClearScreen();
	PrintBanner();

	string tempstr;

	Driver tempdriver;

	cout << " - SEARCH BUS LINES BY BUS STOP SCHEDULE MENU -"
	<< "\n Please select one of the following bus stops:";

	Bus_Stops.PrintAllBus_Stops_Names();
	cout << endl << endl;

	while (1)
	{
		cout << "\n Insert Bus Stop Name: ";

		getline(cin, tempstr);
		utilities::trimString(tempstr);

		if (!Bus_Stops.FindBus_StopByName(tempstr)) {
			cout << "\nSorry but no Bus Stop was found with that name! Try again.";
			continue;
		}
		break;
	}

	Bus_Stop* bus_stop = Bus_Stops.FindBus_StopByName(tempstr);

	cout << endl << " The following bus lines include that bus stop in their trip: " << endl;
	for (Line *line : bus_stop->GetLines()) {
		cout << "  -" << line->GetID() << endl;
	}

	cout << endl;
	cout << "\n   Press any key to continue...";
	cin.get();
}

///////////////////////////////////////////////7
///////// FORBIDDEN LAND LAYS AHEAD ///////////7
///////////////////////////////////////////////7

void ui::StartMenu()
{
	PreMenu();
}

bool ui::StartMenu(const string& filename)
{
	if (SetBannerFilename(filename))
	{
		PreMenu();
		return true;
	}
	return false;
}

bool ui::StartMenu(const int& Width, const int& Height, const string& filename)
{
	if (SetConsoleWidth(Width) && SetConsoleHeight(Height) && SetBannerFilename(filename))
	{
		PreMenu();
		return true;
	}
	return false;
}


bool ui::SetConsoleWidth(const unsigned int& Width)
{
	//if (Width > 119 && Width < 241)
	//{
	ConsoleWidth = Width;
	return true;
	//}
	return false;
}

bool ui::SetConsoleHeight(const unsigned int& Height)
{
	// if (Height > 29 && Height < 64)
	// {
	ConsoleHeight = Height;
	return true;
	// }
	return false;
}

bool ui::SetBannerFilename(const string& filename)
{
	ifstream bannerfile(filename);

	if (bannerfile.fail())
	{
		bannerfile.close();
		return false;
	}
	else
	{
		bannerfilename = filename;
		return true;
	}
}



unsigned int ui::GetConsoleWidth()
{
	return ConsoleWidth;
}

unsigned int ui::GetConsoleHeight()
{
	return ConsoleHeight;
}

string ui::GetBannerFilename()
{
	return bannerfilename;
}


void ui::PrintBanner()
{

	static string Banner = "";
	if (Banner == "") {
		ifstream hBanner(bannerfilename);
		if (hBanner.fail()) {
			cout << "Error openning banner file." << endl;
			hBanner.close();
			return;
		}
		string asciiTemp;
		while (getline(hBanner, asciiTemp))
			Banner += string(((ConsoleWidth - asciiTemp.size()) / 2), ' ') + asciiTemp + "\n";
	}

	cout << endl << Banner << endl << endl;

	//ifstream banner(bannerfilename);

	//cout << "\n";
	//string asciiTemp;

	//while (getline(banner, asciiTemp))
	//	cout << string(((ConsoleWidth - asciiTemp.size()) / 2),' ') << asciiTemp << "\n";

	//cout << "\n\n\n";

	//cout << string(3,'\n');

}