#include "Funcs.h"

using namespace std;

void Backup_Info(string lines_file, string drivers_file) /*  Saves information contained in the lines/drivers files into
														 Backup_Lines.txt and Backp_Drivers.txt */
{
	ifstream lines_in, drivers_in;
	ofstream lines_out, drivers_out;
	string lines, drivers;

	lines_in.open(lines_file.c_str());
	lines_out.open("Backup_Lines.txt", ofstream::out | ofstream::trunc);

	while (getline(lines_in, lines))
	{
		lines_out << lines << endl;
	}

	lines_in.close();
	lines_out.close();
	drivers_in.open(drivers_file.c_str());
	drivers_out.open("Backup_Drivers.txt", ofstream::out | ofstream::trunc);

	while (getline(drivers_in, drivers))
	{
		drivers_out << drivers << endl;
	}

	drivers_in.close();
	drivers_out.close();
}

void Restore_Info(string lines_file, string drivers_file) /*Copies the information in Backup_Drivers.txt and
														  Backup_Lines.txt to the lines/drivers file */
{
	ifstream read_backup;
	ofstream restore;
	string backup_s;

	read_backup.open("Backup_Lines.txt");
	restore.open(lines_file.c_str());

	while (true)
	{
		getline(read_backup, backup_s);

		if (read_backup.eof())
			break;
		else
			restore << backup_s << endl;
	}

	read_backup.close();
	restore.close();
	read_backup.open("Backup_Drivers.txt");
	restore.open(drivers_file.c_str());

	while (true)
	{
		getline(read_backup, backup_s);

		if (read_backup.eof())
			break;
		else
			restore << backup_s << endl;
	}

	read_backup.close();
	restore.close();
}

void Order_Shifts(vector<Shift> &Line_Shifts) // Orders the shifts in the vector by their starting time
{
	unsigned int i3, i4;

	Shift temp(Line_Shifts[0].getBusLineId(), Line_Shifts[0].getDriverId(),
		Line_Shifts[0].getBusOrderNumber(), Line_Shifts[0].getWeekDay(),
		Line_Shifts[0].getStartTime(), Line_Shifts[0].getEndTime());

	for (i3 = 1; i3 < Line_Shifts.size(); i3++)
	{
		for (i4 = 0; i4 < Line_Shifts.size() - i3; i4++)
		{
			if (Line_Shifts[i4].getStartTime() > Line_Shifts[i4 + 1].getStartTime())
			{
				temp.setBusLineId(Line_Shifts[i4].getBusLineId());
				temp.setBusOrderNumber(Line_Shifts[i4].getBusOrderNumber());
				temp.setDriverId(Line_Shifts[i4].getDriverId());
				temp.setEndTime(Line_Shifts[i4].getEndTime());
				temp.setStartTime(Line_Shifts[i4].getStartTime());
				temp.setWeekDay(Line_Shifts[i4].getWeekDay());
				Line_Shifts[i4].setBusLineId(Line_Shifts[i4 + 1].getBusLineId());
				Line_Shifts[i4].setBusOrderNumber(Line_Shifts[i4 + 1].getBusOrderNumber());
				Line_Shifts[i4].setDriverId(Line_Shifts[i4 + 1].getDriverId());
				Line_Shifts[i4].setEndTime(Line_Shifts[i4 + 1].getEndTime());
				Line_Shifts[i4].setStartTime(Line_Shifts[i4 + 1].getStartTime());
				Line_Shifts[i4].setWeekDay(Line_Shifts[i4 + 1].getWeekDay());
				Line_Shifts[i4 + 1].setBusLineId(temp.getBusLineId());
				Line_Shifts[i4 + 1].setBusOrderNumber(temp.getBusOrderNumber());
				Line_Shifts[i4 + 1].setDriverId(temp.getDriverId());
				Line_Shifts[i4 + 1].setEndTime(temp.getEndTime());
				Line_Shifts[i4 + 1].setStartTime(temp.getStartTime());
				Line_Shifts[i4 + 1].setWeekDay(temp.getWeekDay());
			}
		}
	}
}