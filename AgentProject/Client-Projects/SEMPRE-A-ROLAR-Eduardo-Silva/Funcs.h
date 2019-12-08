#ifndef FUNCS_H
#define FUNCS_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include "Driver.h"
#include "Line.h"
#include "Bus.h"

void Backup_Info(string lines_file, string drivers_file); /*  Saves information contained in the lines/drivers files into
														 Backup_Lines.txt and Backp_Drivers.txt */

void Restore_Info(string lines_file, string drivers_file); /*Copies the information in Backup_Drivers.txt and
															Backup_Lines.txt to the lines/drivers file */

void Order_Shifts(vector<Shift> &Line_Shifts); // Orders the shifts in the vector by their starting time
	
#endif