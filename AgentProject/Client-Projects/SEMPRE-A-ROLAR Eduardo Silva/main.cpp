#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "HQ.h"

using namespace std;


int main()
{
	string drivers_file, lines_file, line_string, driver_string; 
	ifstream read_drivers, read_lines;
	vector<Line> lines_vector;
	vector<Driver> drivers_vector;
	vector<Bus> bus_vector;
	int no_busses, bus_order_number;
	unsigned int line_it;
	ofstream write_line, write_driver;

    cout << "Please indicate the name of the lines file: ";
	getline(cin, lines_file);
	cout << endl << endl;
	read_lines.open(lines_file.c_str());

	while (!read_lines.is_open())
	{
		cout << "There isn't any file with that name. Try again.\n";
		read_lines.clear();
		getline(cin, lines_file);
		cout << endl << endl;
		read_lines.open(lines_file.c_str());
	}
	
	while (getline(read_lines, line_string))
	{
		Line line_ready(line_string);
		lines_vector.push_back(line_ready);
	}

	read_lines.close();

	cout << "Please indicate the name of the drivers file: ";
	getline(cin, drivers_file);
	cout << endl << endl;
	read_drivers.open(drivers_file.c_str());

	while (!read_drivers.is_open())
	{
		cout << "There isn't any file with that name. Try again.\n";
		read_drivers.clear();
		getline(cin, drivers_file);
		cout << endl << endl;
		read_drivers.open(drivers_file.c_str());
	} 

	while (getline(read_drivers, driver_string))
	{
		Driver driver_ready(driver_string);
		drivers_vector.push_back(driver_ready);
	}

	read_drivers.close();

	for (line_it = 0; line_it < lines_vector.size(); line_it++) /*  Creates a vector with all the busses needed for all the
																lines */
	{
		no_busses = lines_vector[line_it].Calc_No_Busses();

		for (bus_order_number = 1; bus_order_number <= no_busses; bus_order_number++)
		{
			Bus bus(bus_order_number, 00, lines_vector[line_it].getId());
			bus_vector.push_back(bus);
		}
 
	}
	
	HQ hq(lines_vector, drivers_vector, bus_vector);

	hq.Main_Menu(lines_file, drivers_file);

  return 0;
}
