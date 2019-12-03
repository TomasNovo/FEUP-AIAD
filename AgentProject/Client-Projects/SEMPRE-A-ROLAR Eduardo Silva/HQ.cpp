#include "HQ.h"

using namespace std;

HQ::HQ(vector<Line> v_l, vector<Driver> v_d, vector<Bus> v_b): vl(v_l), vd(v_d), vb(v_b) {};

void HQ::Save_Info(string lines_file, string drivers_file) const
{
	ofstream write_new;
	string driver_s, line_s;
	unsigned int i = 0, i2, i3;

	Backup_Info(lines_file, drivers_file);
	write_new.open(lines_file.c_str());

	while (i < vl.size())
	{
		i2 = 0;
		i3 = 0;
		write_new << vl[i].getId() << " ; " << vl[i].getFreq() << " ; ";

		while (i2 < vl[i].getBusStops().size() - 1)
		{
			write_new << vl[i].getBusStops()[i2] << ", ";
			i2++;
		}

		write_new << vl[i].getBusStops()[i2] << "; ";

		while (i3 < vl[i].getTimings().size() - 1)
		{
			write_new << vl[i].getTimings()[i3] << ", ";
			i3++;
		}

		write_new << vl[i].getTimings()[i3] << endl;
		i++;
	}

	i = 0;
	i2 = 0;
	i3 = 0;
	write_new.close();
	write_new.open(drivers_file.c_str());

	while (i < vd.size())
	{
		write_new
			<< vd[i].getId()
			<< " ; "
			<< vd[i].getName()
			<< " ; "
			<< vd[i].getShiftMaxDuration()
			<< " ; "
			<< vd[i].getMaxWeekWorkingTime()
			<< " ; "
			<< vd[i].getMinRestTime() << endl;
		i++;
	}

}

void HQ::Reverse_Lines(vector<Line> &rvl) const
{
	vector<string> new_stops;
	vector<int> new_schedule;
	unsigned int i2 = 0;
	int i;

	while (i2 < vl.size())
	{
		i = vl.at(i2).getBusStops().size() - 1;
		new_stops.clear();
		new_schedule.clear();

		while (i >= 0)
		{
			new_stops.push_back(vl.at(i2).getBusStops().at(i));
			i--;
		}

		i = vl.at(i2).getTimings().size() - 1;

		while (i >= 0)
		{
			new_schedule.push_back(vl[i2].getTimings()[i]);
			i--;
		}


		Line new_line(vl.at(i2).getId(), vl.at(i2).getFreq(), new_stops, new_schedule);
		rvl.push_back(new_line);
		i2++;
	}
}

bool HQ::Check_Driver_ID(int id_check, unsigned int &i) const 
{
	while (i < vd.size())
	{
		if (vd[i].getId() == id_check)
		{
			return true;
			break;
		}
		else i++;
	}

	return false;
}

bool HQ::Check_Route_ID(int id_check, unsigned int &i) const 
{
	while (i < vl.size())
	{
		if (vl.at(i).getId() == id_check)
		{
			return true;
			break;
		}
		else i++;
	}

	return false;
}

void HQ::See_Available_Drivers(unsigned int day_start, unsigned int day_end) const
{
	unsigned int driver_int, shift_int, day_it, time_it = 0, time_comp, total_shift_time, free_time_start, free_time_end;
	vector<Shift> Active_Shifts;
	bool error = false;

	cout << "Available drivers:\n" << endl;

	for (driver_int = 0; driver_int < vd.size(); driver_int++)
	{

		total_shift_time = 0;

		for (shift_int = 0; shift_int < vd[driver_int].getShifts().size(); shift_int++) /* Calculates the total number of
																						working hours in a week */
		{
			total_shift_time += (vd[driver_int].getShifts()[shift_int].getEndTime() -
				vd[driver_int].getShifts()[shift_int].getStartTime());
		}

		if (total_shift_time < vd[driver_int].getMaxWeekWorkingTime() * 60) //If the driver is available
		{
			cout << "-------------------------\n" << vd[driver_int].getName() << ", ID: " << vd[driver_int].getId() << endl
				<< "-------------------------\n" << endl;

			for (day_it = 1; day_it <= 5; day_it++)
			{

				for (shift_int = 0; shift_int < vd[driver_int].getShifts().size(); shift_int++)
				{
					if (vd[driver_int].getShifts()[shift_int].getWeekDay() == day_it)
						Active_Shifts.push_back(vd[driver_int].getShifts()[shift_int]);
				}

				switch (day_it)
				{
				case 1:
					cout << "Monday:" << endl << endl;
					break;

				case 2:
					cout << "Tuesday:" << endl << endl;
					break;

				case 3:
					cout << "Wednesday:" << endl << endl;
					break;

				case 4:
					cout << "Thursday:" << endl << endl;
					break;

				case 5:
					cout << "Friday:" << endl << endl;
					break;
				}

				if (Active_Shifts.empty()) // If the driver has no shifts that day, he's free in that particular day
					cout << setfill('0') << setw(2) << day_start / 60
					<< ":"
					<< setfill('0') << setw(2) << day_start % 60
					<< "------"
					<< setfill('0') << setw(2) << day_end / 60
					<< ":"
					<< setfill('0') << setw(2) << day_end % 60 << endl << endl;
				else
				{
					Order_Shifts(Active_Shifts);

					if (Active_Shifts[0].getStartTime() == day_start)
					{
						free_time_start = Active_Shifts[0].getEndTime() + vd[driver_int].getMinRestTime() * 60; /* Accounting for
																												rest time between
																												shifts */
						time_it = 1;
					}
					else
					{
						free_time_start = day_start;
						time_it = 0;
					}
				}

				for (time_it; time_it < Active_Shifts.size(); time_it++)
				{
					free_time_end = Active_Shifts[time_it].getStartTime() - vd[driver_int].getMinRestTime() * 60;

					if (free_time_end < day_start || free_time_end < free_time_start)
						continue;

					if (free_time_start == free_time_end)
					{
						free_time_start = Active_Shifts[time_it].getEndTime() + vd[driver_int].getMinRestTime() * 60;
						continue;
					}

					for (time_comp = 0; time_comp < Active_Shifts.size(); time_comp++)
					{
						if (free_time_end >= Active_Shifts[time_comp].getEndTime()
							&& free_time_start <= Active_Shifts[time_comp].getStartTime())
						{
							error = true;
							break;
						}
					}

					if (error)
					{
						error = false;
						continue;
					}

					cout << setfill('0') << setw(2) << free_time_start / 60
						<< ":"
						<< setfill('0') << setw(2) << free_time_start % 60;
					cout << "------"
						<< setfill('0') << setw(2) << free_time_end / 60
						<< ":"
						<< setfill('0') << setw(2) << free_time_end % 60 << endl << endl;
					free_time_start = Active_Shifts[time_it].getEndTime() + vd[driver_int].getMinRestTime() * 60;
				}

				if (!Active_Shifts.empty())
					if (Active_Shifts[Active_Shifts.size() - 1].getEndTime() != day_end
						&&
						Active_Shifts[Active_Shifts.size() - 1].getEndTime() + vd[driver_int].getMinRestTime() * 60
						< day_end)
					{
						cout << setfill('0') << setw(2) << (Active_Shifts[Active_Shifts.size() - 1].getEndTime() +
							vd[driver_int].getMinRestTime() * 60) / 60
							<< ":"
							<< setfill('0') << setw(2) << (Active_Shifts[Active_Shifts.size() - 1].getEndTime()
								+ vd[driver_int].getMinRestTime() * 60) % 60
							<< "-----"
							<< setfill('0') << setw(2) << day_end / 60
							<< ":"
							<< setfill('0') << setw(2) << day_end % 60 << endl << endl;
					}

				Active_Shifts.clear();
			}
		}
	}
}

void HQ::See_Unattended_Shifts(unsigned int day_start, unsigned int day_end) const 
{
	unsigned int line_it, day_it, driver_it, shift_it, time_it = 0, free_time_start = day_start, free_time_end;
	vector<Shift> Active_Shifts;

	cout << "Unassigned Shifts:\n" << endl;

	for (line_it = 0; line_it < vl.size(); line_it++)
	{
		cout << "----------\n" << "Line " << vl[line_it].getId() << endl << "----------\n" << endl;

		for (day_it = 1; day_it <= 5; day_it++)
		{
			for (driver_it = 0; driver_it < vd.size(); driver_it++)
			{
				for (shift_it = 0; shift_it < vd[driver_it].getShifts().size(); shift_it++)
				{
					if ((vd[driver_it].getShifts()[shift_it].getBusLineId() == vl[line_it].getId())
						&&
						(vd[driver_it].getShifts()[shift_it].getWeekDay() == day_it))
						Active_Shifts.push_back(vd[driver_it].getShifts()[shift_it]);
				}
			}

			switch (day_it)
			{
			case 1:
				cout << "Monday:" << endl << endl;
				break;

			case 2:
				cout << "Tuesday:" << endl << endl;
				break;

			case 3:
				cout << "Wednesday:" << endl << endl;
				break;

			case 4:
				cout << "Thursday:" << endl << endl;
				break;

			case 5:
				cout << "Friday:" << endl << endl;
				break;
			}

			if (Active_Shifts.empty())
				cout << setfill('0') << setw(2) << day_start / 60
				<< ":"
				<< setfill('0') << setw(2) << day_start % 60
				<< "------"
				<< setfill('0') << setw(2) << day_end / 60
				<< ":"
				<< setfill('0') << setw(2) << day_end % 60 << endl << endl;
			else
			{
				Order_Shifts(Active_Shifts);

				if (Active_Shifts[0].getStartTime() == day_start)
				{
					free_time_start = Active_Shifts[0].getEndTime();

					time_it = 1;
				}
				else
				{
					free_time_start = day_start;
					time_it = 0;
				}
			}


			for (time_it; time_it < Active_Shifts.size(); time_it++)
			{
				cout << setfill('0') << setw(2) << free_time_start / 60
					<< ":"
					<< setfill('0') << setw(2) << free_time_start % 60;
				free_time_end = Active_Shifts[time_it].getStartTime();
				cout << "------"
					<< setfill('0') << setw(2) << free_time_end / 60
					<< ":"
					<< setfill('0') << setw(2) << free_time_end % 60 << endl << endl;
				free_time_start = Active_Shifts[time_it].getEndTime();
			}

			if (!Active_Shifts.empty())
				if (Active_Shifts[Active_Shifts.size() - 1].getEndTime() != day_end)
				{
					cout << setfill('0') << setw(2) << Active_Shifts[Active_Shifts.size() - 1].getEndTime() / 60
						<< ":"
						<< setfill('0') << setw(2) << Active_Shifts[Active_Shifts.size() - 1].getEndTime() % 60
						<< "-----"
						<< setfill('0') << setw(2) << day_end / 60
						<< ":"
						<< setfill('0') << setw(2) << day_end % 60 << endl << endl;
				}

			Active_Shifts.clear();
		}
	}
}

void HQ::Add_Route()
{
	int id, freq, time, add_stop_opt, n_stops = 0;
	unsigned int i = 0;
	string stop, backup_line;
	vector<string> stops;
	vector<int> schedule;
	ofstream write;
	ifstream back;

	cout << endl << "Indicate the id number of the route: ";
	cin >> id;

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid input. Please try again\n";
		cin >> id;
	}

	while (true)
	{
		if (Check_Route_ID(id, i)) //Checks if there isn't already one route with the same ID
		{
			cout << "There is already one line with the same id number. Please choose another one.\n" << endl;
			cin >> id;

			while (cin.fail())
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid input. Please try again\n";
				cin >> id;
			}
		}
		else break;
	}

	cout << endl << "Indicate the frequecy of circulation in the route (minutes) :";
	cin >> freq;
	cout << endl;

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid input. Please try again\n";
		cin >> freq;
	}

	cin.ignore(1000, '\n');

	do //The reason why it's a do_while loop is because the route needs to have at least two stops
	{
		cout << "Indicate the name of the stop: ";
		getline(cin, stop);
		cout << endl;
		n_stops++;
		stops.push_back(stop);

		if (n_stops == 1) //Must have at least two stops
		{
			cout << "Indicate the name of the next stop: ";
			getline(cin, stop);
			cout << endl;
			n_stops++;
			stops.push_back(stop);
		}

		cout << "Indicate the time it takes to travel between this stop and the previous one: ";
		cin >> time;
		cout << endl;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input. Please try again\n";
			cin >> time;
		}

		schedule.push_back(time);
		cout << endl << "Write the number of the option you want to choose: \n";
		cout << "1 - Add a stop (must have at least 2): \n" << "2 - End\n" << endl;
		cin >> add_stop_opt;

		while (cin.fail() || (add_stop_opt != 1 && add_stop_opt != 2))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input. Please try again\n";
			cin >> add_stop_opt;
		}

		cin.ignore(1000, '\n');
	} while (add_stop_opt == 1);

	cout << endl;
	Line line(id, freq, stops, schedule);
	vl.push_back(line);
}

void HQ::Remove_Rout()
{
	unsigned int i = 0;
	int id_search;

	cout << "Write the id number of the line you wish to remove: ";
	cin >> id_search;

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid input. Please try again\n";
		cin >> id_search;
	}

	if (Check_Route_ID(id_search, i))
		vl.erase(vl.begin() + i);
	else
		cout << endl << "Line not found\n" << endl;
}

void HQ::Add_Stop(vector<string> &vs, vector<int> &vt, int c1_3_3_1_opt, unsigned int ind) 
{
	unsigned int i = 0, i2 = 0, i3 = 0;
	bool found = false;
	vector<string> new_vs;
	vector<int> new_schedule;
	string new_stop, last_stop;
	int new_travel_time, new_travel_time_2;

	switch (c1_3_3_1_opt)
	{
	case 1: //The new stop is located at the beggining of the route
		cout << "What's the name of the new stop? ";
		cin.ignore(1000, '\n');
		getline(cin, new_stop);
		new_vs.push_back(new_stop);

		while (i < vs.size())
		{
			new_vs.push_back(vs[i]);
			i++;
		}

		cout << "What's the travel time between this stop and " << new_vs[1] << "? ";
		cin >> new_travel_time;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid Input. Please try again.\n";
			cin >> new_travel_time;
		}

		new_schedule.push_back(new_travel_time);

		while (i3 < vt.size())
		{
			new_schedule.push_back(vt[i3]);
			i3++;
		}

		vl[ind].SetStops(new_vs);
		vl[ind].SetSchedule(new_schedule);
		break;

	case 2: // The new stop is located in between two other stops
		cout << "What's the name of the stop before the new one? ";
		cin.ignore(1000, '\n');
		getline(cin, last_stop);

		while (i < vl[ind].getBusStops().size()) //Searches for the last stop before the new one
		{
			if (vl[ind].getBusStops()[i] == last_stop)
			{
				found = true;
				break;
			}
			else
				i++;
		}

		if (found) //If this stop exists, copies all previous stops and itself to a new vector
		{
			while (i2 <= i)
			{
				new_vs.push_back(vl[ind].getBusStops()[i2]);
				i2++;
			}

			cout << "Write the name of the new stop: ";
			getline(cin, new_stop);
			new_vs.push_back(new_stop); //Adds the new stop to the new vector

			while (i2 < vl[ind].getBusStops().size()) //Copies all the remaining stops to the new vector
			{
				new_vs.push_back(vs[i2]);
				i2++;
			}

			vs = new_vs;
			vl[ind].SetStops(new_vs);
			cout << "Please indicate the travel time between this new stop and " << vl[ind].getBusStops()[i] << ": ";
			/*Must know the travel time
			between the new stop and the
			last one*/
			cin >> new_travel_time;

			while (cin.fail())
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid Input. Please try again.\n";
				cin >> new_travel_time;
			}

			cout << "Please indicate the travel time between this stop and " << vl[ind].getBusStops()[i + 2] << ": ";
			/*Must know the travel time
			between the new stop and
			the next one*/
			cin >> new_travel_time_2;

			while (cin.fail())
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid Input. Please try again.\n";
				cin >> new_travel_time_2;
			}

			if (i != 0)
			{
				while (i3 <= (i - 1)) //Copies all the time values before the first change to a new schedules vector
				{
					new_schedule.push_back(vt[i3]);
					i3++;
				}
			}
			else i3 = 0;

			new_schedule.push_back(new_travel_time); //Copies the first new value to the new schedules vector
			new_schedule.push_back(new_travel_time_2);
			i3++;

			while (i3 < vt.size()) //Copies the remaining values to the new schedules vector
			{
				new_schedule.push_back(vt[i3]);
				i3++;
			}

			vl[ind].SetSchedule(new_schedule);
		}
		else cout << "Stop not found.\n";

		break;

	case 3: //The new stop is at the end of the route
		cout << "What's the name of the new stop? ";
		cin.ignore(1000, '\n');
		getline(cin, new_stop);
		vs.push_back(new_stop);
		cout << "What's the travel time between this stop and " << vs[vs.size() - 2] << "? ";
		cin >> new_travel_time;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid Input. Please try again.\n";
			cin >> new_travel_time;
		}

		vt.push_back(new_travel_time);
		vl[ind].SetStops(vs);
		vl[ind].SetSchedule(vt);
		break;
	}

}

void HQ::Remove_Stop(vector<string> vs, vector<int> vt, string rem_stop, unsigned int ind) 
{
	unsigned int i = 0;
	int inter_time;
	bool found = false;

	while (i < vs.size())
	{
		if (vs[i] == rem_stop)
		{
			found = true;
			break;
		}
		else i++;
	}

	if (found)
	{
		if (i != 0 && i != vs.size() - 1) //If the stop is neither at the beggining nor at the end of the route
		{
			cout << "Indicate the traveling time between " << vs[i - 1] << " and " << vs[i + 1] << endl;
			cin >> inter_time;

			while (cin.fail())
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid Input. Please try again.\n";
				cin >> inter_time;
			}

			vs.erase(vs.begin() + i);
			vt[i] = inter_time;
			vt.erase(vt.begin() + i - 1);
			vl[ind].SetStops(vs);
			vl[ind].SetSchedule(vt);
		}
		else
			if (i == 0) //If the stop is the first one
			{
				vs.erase(vs.begin() + i);
				vt.erase(vt.begin() + i);
				vl[ind].SetStops(vs);
				vl[ind].SetSchedule(vt);
			}
			else //If the stop is the last one
			{
				vs.erase(vs.begin() + i);
				vt.erase(vt.begin() + i - 1);
				vl[ind].SetStops(vs);
				vl[ind].SetSchedule(vt);
			}
	}
	else cout << "Stop not found.\n";
}

void HQ::Change_Stop(vector<string> vs, string ch_stop, unsigned int ind) 
{
	unsigned int i = 0;
	bool found = false;
	string new_stop_name;

	while (i < vs.size())
	{
		if (vs[i] == ch_stop)
		{
			found = true;
			break;
		}
		i++;
	}

	if (found)
	{
		cout << "Write the stop's new name: ";
		getline(cin, new_stop_name);
		vs[i] = new_stop_name;
		vl[ind].SetStops(vs);
	}
	else cout << "Stop not found.\n";
}

void HQ::Change_Schedule(vector<string> vs, vector<int> &vt, string stop_1, unsigned int ind) 
{
	unsigned int i = 0;
	bool found = false;
	int new_time;

	while (i < vs.size() - 1)
	{
		if (vs[i] == stop_1)
		{
			found = true;
			break;
		}
		else i++;
	}

	if (found)
	{
		cout << "Write the new value of the time interval: ";
		cin >> new_time;
		vt[i] = new_time;
		vl[ind].SetSchedule(vt);
	}
	else cout << "Stop not found!\n";
}

void HQ::Add_Driver()
{
	int id, d_lim, w_lim, r_min;
	unsigned int i = 0;
	string name;

	cout << "Write the driver's id number (0 isn't accepted): ";
	cin >> id;

	while (cin.fail() || id == 0)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid input. Please try again.\n";
		cin >> id;
	}

	while (true)
	{
		if (Check_Driver_ID(id, i)) //Checks if there isn't already one driver with the same ID
		{
			cout << "There is already one driver with the same id number. Please choose another one.\n" << endl;
			cin >> id;

			while (cin.fail())
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid input. Please try again\n";
				cin >> id;
			}
		}
		else break;
	}

	cin.ignore(1000, '\n');
	cout << "Write the name of the driver: ";
	getline(cin, name);
	cout << "Write the maximum number of consecutive hours the driver can work in a day/shift: ";
	cin >> d_lim;

	while (cin.fail() || d_lim > 24) //The daily limit must't be greater than 24 hours
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid input. Please try again.\n";
		cin >> d_lim;
	}

	cout << "Write the maximum number of hours the driver can work in a week: ";
	cin >> w_lim;

	while (cin.fail() || w_lim > 120 || w_lim > d_lim * 5) /*The weekly limit must't be greater than 120 hours (24 * 5)
														   nor greater than the daily limit times five (it wouldn't make
														   sense */
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid input. Please try again.\n";
		cin >> w_lim;
	}

	cout << "Write the minimum number of hours the driver has to rest between shifts: ";
	cin >> r_min;

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid input. Please try again.\n";
		cin >> r_min;
	}

	Driver new_driver(id, name, d_lim, w_lim, r_min);
	vd.push_back(new_driver);
}

void HQ::Remove_Driver()
{
	unsigned int i = 0;
	int id_search;
	bool found = false;

	cout << "Write the id number of the driver you want to remove: ";
	cin >> id_search;

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid input. Please try again.\n";
		cin >> id_search;
	}

	if (Check_Driver_ID(id_search, i))
		vd.erase(vd.begin() + i);
	else
		cout << endl << "Driver not found.\n";
}

void HQ::Change_Driver() 
{
	int id_driver, opt_1_3, new_id, new_day_lim, new_rest;
	unsigned int i = 0, i2 = 0, new_week_lim;
	string new_name;
	bool exit = false;

	cout << "Write the id number of the driver you want to change: ";
	cin >> id_driver;

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid Input. Please try again.\n";
		cin >> id_driver;
	}

	if (Check_Driver_ID(id_driver, i))
	{
		while (!exit)
		{
			cout
				<< "Please indicate the parameter you want to change: \n" << endl
				<< "+-----------------------+\n"
				<< "| 1 - ID                |\n"
				<< "+-----------------------+\n"
				<< "| 2 - Name              |\n"
				<< "+-----------------------+\n"
				<< "| 3 - Shift Length      |\n"
				<< "+-----------------------+\n"
				<< "| 4 - Weekly Hour Limit |\n"
				<< "+-----------------------+\n"
				<< "| 5 - Minimum rest time |\n"
				<< "+-----------------------+\n"
				<< "| 6 - Go Back           |\n"
				<< "+-----------------------+\n" << endl;
			cin >> opt_1_3;

			while (cin.fail() || (opt_1_3 != 1 && opt_1_3 != 2 && opt_1_3 != 3 && opt_1_3 != 4 && opt_1_3 != 5
				&& opt_1_3 != 6))
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid Input. Please try again.\n";
				cin >> opt_1_3;
			}

			switch (opt_1_3)
			{
			case 1:
				cout << "Write the driver's new id (0 isn't accepted): ";
				cin >> new_id;

				while (cin.fail() || new_id == 0)
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Invalid Input. Please try again.\n";
					cin >> new_id;
				}

				if (!Check_Driver_ID(new_id, i2))
					vd.at(i).setID(new_id);
				else cout << "There is already one driver with this id!\n";

				break;

			case 2:
				cout << "Writhe the driver's new name: ";
				cin.ignore(1000, '\n');
				getline(cin, new_name);
				vd[i].setName(new_name);
				break;

			case 3:
				cout << "Write the new shift length: ";
				cin >> new_day_lim;

				while (cin.fail() || new_day_lim > 24)
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Invalid Input. Please try again.\n";
					cin >> new_day_lim;
				}

				vd[i].setMaxHours(new_day_lim);
				break;

			case 4:
				cout << "Write the new weekly limit: ";
				cin >> new_week_lim;

				while (cin.fail() || new_week_lim > 120 || new_week_lim > vd[i].getShiftMaxDuration() * 5)
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Invalid Input. Please try again.\n";
					cin >> new_week_lim;
				}

				vd[i].setMaxWeekHours(new_week_lim);
				break;

			case 5:
				cout << "Indicate the new minimum rest time between shifts: ";
				cin >> new_rest;

				while (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Invalid Input. Please try again.\n";
					cin >> new_rest;
				}

				vd[i].setMinRestHours(new_rest);
				break;

			case 6:
				exit = true;
				break;
			}
		}
	}
	else cout << "Driver not found.\n";
}

void HQ::Add_Shift(unsigned int day_start, unsigned int day_end)
{
	unsigned int d_id, i = 0, i2 = 0, i3 = 0, i4 = 0, l_id, s_start, s_end, d_week, new_shift_length, total_shifts_length = 0,
		bus_order_no = 0, new_start, daily_shift_length = 0, full_loop_length = 0;
	bool full_loop = false;
	vector<Shift> New_Shifts;

	See_Available_Drivers(day_start, day_end); //Begins by showing which drivers are available and at which times

	cout << "Write the id of the driver who you want to add this shift: ";
	cin >> d_id;

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid Input. Please try again.\n" << endl;
		cin >> d_id;
	}

	if (Check_Driver_ID(d_id, i)) // If the driver exists
	{
		See_Unattended_Shifts(day_start, day_end); /* Shows when it is possible to add a shift independently of the
														   driver */

		cout << "Write the id of the line of this shift: ";
		cin >> l_id;

		if (!Check_Route_ID(l_id, i2))
		{
			cout << "Line not found.\n" << endl;
			return;
		}

		cout << "Write the number of the day of the week this shift takes place (1 - Monday, 2 - Tuesday, etc)" << endl;
		cin >> d_week;

		while (cin.fail() || (d_week != 1 && d_week != 2 && d_week != 3 && d_week != 4 && d_week != 5))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid Input. Please try again.\n";
			cin >> d_week;
		}

		cout << "Pay attention that, despite the available time-frames, a shift can only start when there's a bus\n"
			<< "at the beggining of the line.\n" << endl
			<< "Shift starting times: \n";
		vl[i2].Show_Available_Start_Time(day_start, day_end); // Shows at which points is possible to begin a new shift
		cout << endl << "Shift starting time (HHMM, no dots in between): \n";
		cin >> s_start;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid Inut. Please try again.\n";
			cin >> s_start;
		}

		s_start = (s_start / 100) * 60 + s_start % 100;

		while (s_start < day_start || s_start > day_end) /* Checks if the beggining of the shif is located in between the
														 pre-defined working hours */
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid Input. Shifts can only start between "
				<< setfill('0') << setw(2) << day_start / 60
				<< ":"
				<< setfill('0') << setw(2) << day_start % 60
				<< " and "
				<< setfill('0') << setw(2) << day_end / 60
				<< ":"
				<< setfill('0') << setw(2) << day_end % 60
				<< "." << endl
				<< "Please try again.\n" << endl;
			cin >> s_start;
			s_start = (s_start / 100) * 60 + s_start % 100;
		}

		cout << "Shift ending time (HHMM, no dots in between): \n";
		cin >> s_end;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid Inut. Please try again.\n";
			cin >> s_start;
		}

		s_end = (s_end / 100) * 60 + s_end % 100;

		while (s_end > day_end || s_end < s_start) /* Checks if the end of the shif is located in between the
												   pre-defined working hours */
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid Input. Shifts are only available from "
				<< setfill('0') << setw(2) << day_start / 60
				<< ":"
				<< setfill('0') << setw(2) << day_start % 60
				<< " to "
				<< setfill('0') << setw(2) << day_end / 60
				<< ":"
				<< setfill('0') << setw(2) << day_end % 60
				<< "." << endl
				<< "Please try again.\n" << endl;
			cin >> s_end;
			s_end = (s_end / 100) * 60 + s_end % 100;
		}

		if (s_end <= s_start) // Checks if shift time-frame makes sense
		{
			cout << "Time frame is invalid (starting time is greater than ending time).\n" << endl;
			return;
		}

		new_shift_length = s_end - s_start;

		//Testing if valid

		// Test 1 - Makes sure the shift starts at a correct time period (i.e, one that matches the frequency of the line)

		if (s_start == day_start || (s_start % vl[i2].getFreq() == 0 && s_start >= day_start))
			full_loop = true;


		if (!full_loop)
		{
			cout << "The shift starting time is invalid (a shift can only start when there's a bus leaving the first stop)\n"
				<< endl;
			return;
		}


		// Test 2 - Makes sure the shift limit is respected

		if (vd[i].getShiftMaxDuration() * 60 < new_shift_length)
		{
			cout << "The shift coudln't be added as the maximum number of hours per shift has been reached.\n" << endl;
			return;
		}

		// Test 3 - Makes sure weekly limit is respected

		i3 = 0;

		while (i3 < vd[i].getShifts().size())
		{
			total_shifts_length = total_shifts_length +
				(vd[i].getShifts()[i3].getEndTime() - vd[i].getShifts()[i3].getStartTime());

			i3++;
		}

		total_shifts_length = total_shifts_length + new_shift_length;

		if (vd[i].getMaxWeekWorkingTime() * 60 < total_shifts_length)
		{
			cout << "The maximum number of weekly working hours has been reached.\n";
			return;
		}

		// Test 4 - Makes sure the driver doesn't have any other shifts on the same day that conflict with the new one

		i3 = 0;

		while (i3 < vd[i].getShifts().size())
		{
			if (vd[i].getShifts()[i3].getWeekDay() == d_week)
			{
				if (((s_start >= vd[i].getShifts()[i3].getStartTime()) && (s_start <= vd[i].getShifts()[i3].getEndTime()))
					||
					((s_end >= vd[i].getShifts()[i3].getStartTime()) && (s_end <= vd[i].getShifts()[i3].getEndTime())))
				{
					cout << "This driver already has a shift that conflicts with the new one on the same day.\n" << endl;
					return;
				}
				else i3++;
			}
			else i3++;
		}

		// Test 5 - Makes sure the rest time between shifts is respected

		i3 = 0;

		while (i3 < vd[i].getShifts().size())
		{
			if (vd[i].getShifts()[i3].getWeekDay() == d_week)
			{
				if (((s_end + vd[i].getMinRestTime() * 60 >= vd[i].getShifts()[i3].getStartTime())
					&& (vd[i].getShifts()[i3].getStartTime() >= s_end))
					||
					((vd[i].getShifts()[i3].getEndTime() + vd[i].getMinRestTime() * 60 >= s_start)
						&&
						(s_start >= vd[i].getShifts()[i3].getEndTime())))
				{
					cout << "This shift cannot be assigned to this driver as it doesn't respect its minimum rest time.\n"
						<< endl;
					return;
				}
				else i3++;
			}
			else i3++;
		}

		// Test 6 - Makes sure the new shift doesn't conflict with other drivers shifts on the same day and line

		for (i3 = 0; i3 < vd.size(); i3++)
		{
			for (i4 = 0; i4 < vd[i3].getShifts().size(); i4++)
			{
				if ((vd[i3].getShifts()[i4].getBusLineId() == l_id)
					&&
					(vd[i3].getShifts()[i4].getWeekDay() == d_week))
				{
					if (((s_start >= vd[i3].getShifts()[i4].getStartTime())
						&& (s_start <= vd[i3].getShifts()[i4].getEndTime()))
						||
						((s_end >= vd[i3].getShifts()[i4].getStartTime())
							&& (s_end <= vd[i3].getShifts()[i4].getEndTime())))
					{
						cout << "This shift conflicts with another driver's shift in this line.\n";
						return;
					}
				}
			}
		}

		// Shift is aproved; Adding shift to driver and connecting  bus to it

		for (new_start = day_start; new_start <= s_start; new_start = new_start + vl[i2].getFreq())
		{
			bus_order_no++;

			if (bus_order_no > vl[i2].Calc_No_Busses())
				bus_order_no = 1;
		}

		Shift New_Shift(vl[i2].getId(), vd[i].getId(), bus_order_no, d_week, s_start, s_end);
		vd[i].AddShift(New_Shift);

		for (i3 = 0; i3 < vb.size(); i3++)
		{
			if ((vb[i3].getLineId() == l_id) && (vb[i3].getBusOrderInLine() == bus_order_no))
			{
				vb[i3].setDriverId(vd[i].getId());
				vb[i3].AddShift(New_Shift);
				break;
			}
		}
		cout << "Shift added succesfully.\n" << endl;
		return;
	}
	else cout << "Driver not found.\n" << endl;
}

void HQ::Remove_a_Shift()
{
	unsigned int driver_id, line_id, day_of_the_week, shift_starting_time, driver_it = 0, bus_it;
	bool found_shift = false, found_bus_shift = false;

	cout << "Driver's ID: ";
	cin >> driver_id;

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid Input. Please try again.\n";
		cin >> driver_id;
	}

	cout << "Line ID: ";
	cin >> line_id;

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid Input. Please try again.\n";
		cin >> line_id;
	}

	if (Check_Driver_ID(driver_id, driver_it))
	{
		cout << "Day of the week (1 - Monday, 2 - Tuesday, ...): ";
		cin >> day_of_the_week;

		while (cin.fail() || (day_of_the_week != 1 && day_of_the_week != 2 && day_of_the_week != 3 && day_of_the_week != 4
			&& day_of_the_week != 5))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid Input. Please try again.\n";
			cin >> day_of_the_week;
		}

		cout << "Starting time (in the format HHMM, no dots in between): ";
		cin >> shift_starting_time;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid Input. Please try again.\n";
			cin >> shift_starting_time;
		}

		shift_starting_time = (shift_starting_time / 100) * 60 + shift_starting_time % 100;

		if (!vd[driver_it].RemoveShift(day_of_the_week, shift_starting_time))
		{
			cout << "Shift not found.\n" << endl;
			return;
		}

		for (bus_it = 0; bus_it < vb.size(); bus_it++)
		{
			if (vb[bus_it].getLineId() == line_id)
			{
				if (vb[bus_it].RemoveShift(day_of_the_week, shift_starting_time))
				{
					found_bus_shift = true;
					break;
				}
			}

			if (found_bus_shift)
				break;
		}
	}
	else cout << "Driver not found.\n" << endl;
}

void HQ::See_Driver_Job() const
{
	unsigned int i = 0, shift_it;
	int id;

	cout << "Please write the driver's id: ";
	cin >> id;

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid Input. Please try again\n";
		cin >> id;
	}

	if (Check_Driver_ID(id, i))
	{
		cout << endl << vd[i].getName() << "        " << "ID: " << vd[i].getId() << endl << endl
			<< "Maximum number of working hours/day: " << vd[i].getShiftMaxDuration() << endl
			<< "Maximum number of working hours/week: " << vd[i].getMaxWeekWorkingTime() << endl
			<< "Minimum number of resting hours between shifts: " << vd[i].getMinRestTime() << endl << endl
			<< "Shifts: \n" << endl;

		if (vd[i].getShifts().empty())
			cout << "Currently, this drive doesn't have any shifts assigned.\n" << endl;
		else
			for (shift_it = 0; shift_it < vd[i].getShifts().size(); shift_it++)
			{
				cout << "----------\n" << "Line " << vd[i].getShifts()[shift_it].getBusLineId() << endl
					<< "Bus No " << vd[i].getShifts()[shift_it].getBusOrderNumber() << endl;

				switch (vd[i].getShifts()[shift_it].getWeekDay())
				{
				case 1:
					cout << "Monday:" << endl;
					break;

				case 2:
					cout << "Tuesday:" << endl;
					break;

				case 3:
					cout << "Wednesday:" << endl;
					break;

				case 4:
					cout << "Thursday:" << endl;
					break;

				case 5:
					cout << "Friday:" << endl;
					break;
				}

				cout << "Start: " << setfill('0') << setw(2) << vd[i].getShifts()[shift_it].getStartTime() / 60
					<< ":"
					<< setfill('0') << setw(2) << vd[i].getShifts()[shift_it].getStartTime() % 60 << endl
					<< "End: " << setfill('0') << setw(2) << vd[i].getShifts()[shift_it].getEndTime() / 60
					<< ":"
					<< setfill('0') << setw(2) << vd[i].getShifts()[shift_it].getEndTime() % 60 << endl
					<< "----------\n";
			}
	}
	else cout << "Driver not found!\n";
}

void HQ::See_Bus_Info() const
{
	unsigned int l_id, shift_starting_time, bus_it, shift_it, driver_it = 0, week_day, i = 0;
	string time_s, hours_s, minutes_s;
	bool found = false;

	cout << "Line ID: ";
	cin >> l_id;

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid Input. Please try again.\n";
		cin >> l_id;
	}

	if (Check_Route_ID(l_id, i))
	{
		cout << "Shift starting time (in the format HH:MM): ";
		cin >> time_s;

		while (time_s[2] != ':')
		{
			cout << "Invalid Input. Please try again.\n";
			cin >> time_s;
		}

		hours_s = time_s.substr(0, 2);
		minutes_s = time_s.substr(3, 2);
		shift_starting_time = stoi(hours_s, nullptr) * 60 + stoi(minutes_s, nullptr);

		cout << "Day of the week (1 - Monday, 2 - Tuesday,...): ";
		cin >> week_day;

		while (cin.fail() || (week_day != 1 && week_day != 2 && week_day != 3 && week_day != 4 && week_day != 5))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid Input. Please try again.\n";
			cin >> week_day;
		}

		cout << endl;

		for (bus_it = 0; bus_it < vb.size(); bus_it++)
		{
			if (vb[bus_it].getLineId() == l_id)
			{
				for (shift_it = 0; shift_it < vb[bus_it].getSchedule().size(); shift_it++)
				{
					if ((vb[bus_it].getSchedule()[shift_it].getStartTime() == shift_starting_time)
						&&
						(vb[bus_it].getSchedule()[shift_it].getWeekDay() == week_day))
					{
						found = true;
						break;
					}
				}

				if (found)
					break;
			}
		}

		if (found)
		{
			cout << "Bus No " << vb[bus_it].getBusOrderInLine() << ", Line " << vb[bus_it].getLineId() << endl;

			if (vb[bus_it].getDriverId() == 0)
				cout << "This bus doesn't have a driver assigned to it yet.";
			else
			{
				Check_Driver_ID(vb[bus_it].getSchedule()[shift_it].getDriverId(), driver_it);
				cout << "Driver: " << vd[driver_it].getName() << ", ID: "
					<< vb[bus_it].getSchedule()[shift_it].getDriverId() << endl << endl
					<< "Shifts: \n";

				for (shift_it = 0; shift_it < vb[bus_it].getSchedule().size(); shift_it++)
				{
					cout << setfill('0') << setw(2) << vb[bus_it].getSchedule()[shift_it].getStartTime() / 60
						<< ":"
						<< setfill('0') << setw(2) << vb[bus_it].getSchedule()[shift_it].getStartTime() % 60
						<< "-----"
						<< setfill('0') << setw(2) << vb[bus_it].getSchedule()[shift_it].getEndTime() / 60
						<< ":"
						<< setfill('0') << setw(2) << vb[bus_it].getSchedule()[shift_it].getEndTime() % 60 << endl;
				}
			}
		}
		else cout << "Bus not found.\n" << endl;
	}
	else cout << "Line not found.\n" << endl;
}

void HQ::See_Line_Schedule(vector<Line> v_l, int day_start, int day_end, unsigned int i) const
{
	unsigned int i2 = 0, i4 = 0;
	int new_out_start = day_start, new_in_start, no_spaces, i3 = 1, xtra_spaces = 0;


	cout << "Direction: " << vl[i].getBusStops()[0] << " -----> " << vl[i].getBusStops()[vl[i].getBusStops().size() - 1]
		<< endl << endl;

	while (i2 < vl[i].getBusStops().size()) /* Displays the name of the stops with  |  in between
											(notice the number of spaces on each side of the | (2) */
	{
		cout << vl[i].getBusStops()[i2] << "  |  ";
		i2++;
	}

	i2 = 0;
	cout << endl;

	while (new_out_start <= day_end) //Outer loop, keeps adding the frequency of the route until it reaches the end of the day
	{
		new_in_start = new_out_start;
		cout << setfill('0') << setw(2) << new_out_start / 60 << ":" << setfill('0') << setw(2)
			<< new_out_start % 60;

		if (vl[i].getBusStops()[i4].length() > 5) //Calculates the number of spaces to write after the first time value
			no_spaces = vl[i].getBusStops()[i4].length();
		else
		{
			no_spaces = 0;
			xtra_spaces = vl[i].getBusStops()[i4].length();
		}

		while (i3 <= no_spaces)
		{
			cout << " ";
			i3++;
		}

		while (xtra_spaces > 0)
		{
			cout << " ";
			xtra_spaces--;
		}

		i3 = 1;
		i4++;

		while (i2 < vl[i].getTimings().size()) //Inner loop, adds the travelling times until it reaches the last stop
		{
			new_in_start = new_in_start + vl[i].getTimings()[i2];
			cout << setfill('0') << setw(2) << new_in_start / 60 << ":" << setfill('0') << setw(2) << new_in_start % 60;

			if (vl[i].getBusStops()[i4].length() > 5) //Calculates the number of spaces it takes between each time value
				no_spaces = vl[i].getBusStops()[i4].length();
			else
			{
				no_spaces = 0;
				xtra_spaces = vl[i].getBusStops()[i4].length();
			}

			while (i3 <= no_spaces)
			{
				cout << " ";
				i3++;
			}

			while (xtra_spaces > 0)
			{
				cout << " ";
				xtra_spaces--;
			}

			i3 = 1;
			i2++;
			i4++;
		}

		i4 = 0;
		i3 = 1;
		i2 = 0;
		cout << endl;
		new_out_start = new_out_start + vl[i].getFreq();
	}
}

void HQ::See_Stop_Schedule(vector<Line> rvl, int day_start, int day_end, string stop_search) const
{
	unsigned int i = 0, i2 = 0, i3 = 0, i4 = 0, i5 = 0;
	int new_day_start = day_start, no_spaces = 0, new_day_r_start = day_start;

	cout << endl << stop_search << endl << endl;

	while (i < vl.size()) //Outter loop, goes trohough each route and checks for the particular stop
	{
		while (i2 < vl[i].getBusStops().size()) //1st Inner loop, finds the stop in question
		{
			if (vl[i].getBusStops()[i2] == stop_search)
			{

				cout << endl << "----------" << endl << "Route " << vl[i].getId() << ": \n" << "----------" << endl
					<< "Direction: " << vl[i].getBusStops()[vl[i].getBusStops().size() - 1] << endl << endl;

				while (new_day_start <= day_end)
				{
					cout << setfill('0') << setw(2) << new_day_start / 60 << ":"
						<< setfill('0') << setw(2) << new_day_start % 60;
					no_spaces++;

					if (no_spaces >= 10) /*Calculates how many values has shown in the same line; If greater than 10,
										 jumps to the next line */
					{
						cout << endl << endl;
						no_spaces = 0;
					}
					else cout << "|";
					new_day_start = new_day_start + vl[i].getFreq();
				}

				no_spaces = 0;
				cout << endl << endl << "Direction: " << vl[i].getBusStops()[0] << endl << endl;
				i5 = 0;

				while (i5 < vl[i].getTimings().size())
				{
					new_day_r_start = new_day_r_start + vl[i].getTimings()[i5];
					i5++;
				}

				i5 = 0;

				while (rvl[i].getBusStops()[i4] != stop_search)
				{
					new_day_r_start = new_day_r_start + rvl[i].getTimings()[i5];

					if (i5 == rvl[i].getTimings().size() - 1) //Correction of the last iteration of the schedule
						i5 = i5;
					else i5++;

					i4++;
				}

				while (new_day_r_start <= day_end)
				{
					cout << setfill('0') << setw(2) << new_day_r_start / 60 << ":"
						<< setfill('0') << setw(2) << new_day_r_start % 60;
					no_spaces++;

					if (no_spaces >= 10)
					{
						cout << endl << endl;
						no_spaces = 0;
					}
					else cout << "|";
					new_day_r_start = new_day_r_start + rvl[i].getFreq();
				}

				cout << endl;
				break;
			}
			else
			{
				new_day_start = new_day_start + vl[i].getTimings()[i3]; /* Adds the time between stops until it finds the
																		right one */

				if (i3 == vl[i].getTimings().size() - 1) //Correction of the last iteration of the schedule
					i3 = i3;
				else i3++;

				i2++;
			}
		}
		i2 = 0;
		i3 = 0;
		i4 = 0;
		new_day_start = day_start;
		new_day_r_start = day_start;
		i++;
	}
}

void HQ::Route_Planner(vector<Line> rvl) const
{
	string stop_1, stop_2;
	bool found_s1 = false, found_s2 = false;
	unsigned int i = 0, i2 = 0, i3 = 0, i4;
	int total_time = 0, no_founds = 0;

	cout << "Write the name of the first stop: ";
	cin.ignore(1000, '\n');
	getline(cin, stop_1);
	cout << "Write the name of the second stop: ";
	getline(cin, stop_2);
	cout << endl;

	while (i < vl.size()) //Outter loop: Searches for routes that contain both stops
	{
		while (i2 < vl[i].getBusStops().size()) //1st Inner Loop: Searches for the first stop in a route
		{
			if (vl[i].getBusStops()[i2] == stop_1)
			{
				found_s1 = true;
				break;
			}
			else i2++;
		}

		if (found_s1)
		{
			while (i3 < vl[i].getBusStops().size()) //If the first search is succesfull, it searches for the 2nd stop
			{
				if (vl[i].getBusStops()[i3] == stop_2)
				{
					found_s2 = true;
					break;
				}
				else i3++;
			}

			if (found_s2 && i2 < i3) /* If the 2nd search is succesfull, it shows the path between both stops and the
									 respective travel time */
			{
				i4 = i2;
				cout << "Route: " << vl[i].getId() << endl << endl;

				while (i4 < i3)
				{
					cout << vl[i].getBusStops()[i4] << " -----> ";
					i4++;
				}

				cout << vl[i].getBusStops()[i4] << endl << endl;
				i4 = i2;

				while (i4 <= i3 - 1)
				{
					total_time = total_time + vl[i].getTimings()[i4];
					i4++;
				}

				cout << "Total travelling time: " << total_time << " minutes" << endl << endl;
				no_founds++;
				found_s1 = false;
				found_s2 = false;
				i2 = 0;
				i3 = 0;
				total_time = 0;
				i++;
			}
			else
				if (found_s2 && i3 < i2) //Same as before, but the other way around (if that's the case)
				{
					i4 = rvl[i].getBusStops().size() - 1 - i2;
					i3 = rvl[i].getBusStops().size() - 1 - i3;
					cout << "Route: " << vl[i].getId() << endl << endl;

					while (i4 < i3)
					{
						cout << rvl[i].getBusStops()[i4] << " -----> ";
						i4++;
					}

					cout << rvl[i].getBusStops()[i4] << endl << endl;
					i4 = rvl[i].getBusStops().size() - 1 - i2;

					while (i4 <= i3 - 1)
					{
						total_time = total_time + rvl[i].getTimings()[i4];
						i4++;
					}

					cout << "Total travelling time: " << total_time << " minutes" << endl << endl;
					no_founds++;
					found_s1 = false;
					found_s2 = false;
					i2 = 0;
					i3 = 0;
					i++;
				}
				else
				{
					found_s1 = false;
					i2 = 0;
					i3 = 0;
					total_time = 0;
					i++;
				}
		}
		else
		{
			i2 = 0;
			i++;
		}
	}

	if (!found_s1 && !found_s2 && no_founds == 0)
		cout << "There isn't any line with both stops.\n";
}

void HQ::Search_Stop_By_Line() const
{
	unsigned int i = 0, i2 = 0;
	int n_stops = 0;
	string stop;

	cout << "Write the name of the stop: ";
	cin.ignore(1000, '\n');
	getline(cin, stop);
	cout << endl << "Lines that include the " << stop << " stop:\n" << endl;

	while (i < vl.size()) //Outter loop: Goes through all the routes
	{
		while (i2 < vl[i].getBusStops().size()) //Inner loop: Searches for the stop in a route
		{
			if (stop == vl[i].getBusStops()[i2])
			{
				cout << "Line " << vl[i].getId() << endl;
				n_stops++;
				break;
			}
			else i2++;
		}

		i2 = 0;
		i++;
	}

	if (n_stops == 0)
		cout << "There aren't any lines that include that stop.\n" << endl;
}

void HQ::C3_3_Menu(const unsigned int day_start, const unsigned int day_end) const
{
	int c3_3_opt;
	bool c3_3_end = false;

	while (!c3_3_end)
	{
		cout
			<< "+-------------------------------------+\n"
			<< "| 1 - Display information about a bus |\n"
			<< "+-------------------------------------+\n"
			<< "| 2 - Display unattended shifts       |\n"
			<< "+-------------------------------------+\n"
			<< "| 3 - Go back                         |\n"
			<< "+-------------------------------------+\n" << endl;
		cin >> c3_3_opt;

		while (cin.fail() || (c3_3_opt != 1 && c3_3_opt != 2 && c3_3_opt != 3))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid Input. Please try again\n" << endl;
			cin >> c3_3_opt;
		}

		switch (c3_3_opt)
		{
		case 1:
			See_Bus_Info();
			break;

		case 2:
			See_Unattended_Shifts(day_start, day_end);
			break;

		case 3:
			c3_3_end = true;
			break;
		}
	}
}

void HQ::C3_2_Menu(unsigned int day_start, unsigned int day_end) const
{
	int c3_2_opt;
	bool go_back = false;

	while (!go_back)
	{
		cout
			<< "+---------------------------------+\n"
			<< "| 1 - Display a driver's shift(s) |\n"
			<< "+---------------------------------+\n"
			<< "| 2 - Display available drivers   |\n"
			<< "+---------------------------------+\n"
			<< "| 3 - Go back                     |\n"
			<< "+---------------------------------+\n" << endl;
		cin >> c3_2_opt;

		while (cin.fail() || (c3_2_opt != 1 && c3_2_opt != 2 && c3_2_opt != 3))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid Input. Please try again.\n";
			cin >> c3_2_opt;
		}

		switch (c3_2_opt)
		{
		case 1:
			See_Driver_Job();
			break;

		case 2:
			See_Available_Drivers(day_start, day_end);
			break;

		case 3:
			go_back = true;
			break;
		}
	}
}

void HQ::C3_1_Menu(vector<Line> rvl, int day_start, int day_end) const
{
	int c3_1_opt, id_search, day_start_2 = day_start;
	unsigned int i = 0, i2 = 0;
	bool go_back = false;
	string stop_search;

	while (!go_back)
	{
		cout
			<< "+---------------------------+---------------------------+\n"
			<< "| 1 - See a stop's schedule | 2 - See a line's schedule |\n"
			<< "+---------------------------+---------------------------+\n"
			<< "|  3 - Search lines by stop | 4 - Route Planner         |\n"
			<< "+---------------------------+---------------------------+\n"
			<< "|                      5 - Go Back                      |\n"
			<< "+---------------------------+---------------------------+\n" << endl;
		cin >> c3_1_opt;

		while (cin.fail() || c3_1_opt < 1 || c3_1_opt > 5)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input. Please try again.\n";
			cin >> c3_1_opt;
		}

		switch (c3_1_opt)
		{
		case 1:
			cin.ignore(1000, '\n');
			cout << "Write the name of the stop: ";
			getline(cin, stop_search);
			See_Stop_Schedule(rvl, day_start, day_end, stop_search);
			break;

		case 2:
			cout << "Write the id number of the route: ";
			cin >> id_search;

			while (cin.fail())
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid Input. Please try again.\n";
				cin >> id_search;
			}

			i = 0;

			if (Check_Route_ID(id_search, i))
			{
				cout << endl << "Line " << vl[i].getId() << endl << "Frequency: " << vl[i].getFreq() << " minutes"
					<< endl << endl;
				See_Line_Schedule(vl, day_start, day_end, i);
				cout << endl << endl;

				while (i2 < vl[i].getTimings().size())
				{
					day_start_2 = day_start_2 + vl[i].getTimings()[i2];
					i2++;
				}

				See_Line_Schedule(rvl, day_start_2, day_end, i); //Shows the schedule the other way
			}
			else cout << "Line not found!\n";
			break;

		case 3:
			Search_Stop_By_Line();
			break;

		case 4:
			Route_Planner(rvl);
			break;

		default:
			go_back = true;
			break;
		}
	}
}

void HQ::C2_3_3_Menu(unsigned int i)
{
	int c2_3_3_opt, c2_3_3_1opt;
	string last_stop, rem_stop, ch_stop;
	vector<string> stops;
	vector<int> timings;
	bool go_back = false;

	while (!go_back)
	{
		cout
			<< "+-------------------+-------------------+\n"
			<< "| 1 - Add a stop    | 2 - Remove a stop |\n"
			<< "+-------------------+-------------------+\n"
			<< "| 3 - Change a stop | 4 - Go back       |\n"
			<< "+-------------------+-------------------+\n"
			<< endl;

		cin >> c2_3_3_opt;

		while (cin.fail() || (c2_3_3_opt != 1 && c2_3_3_opt != 2 && c2_3_3_opt != 3 && c2_3_3_opt != 4))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid Input. Please try again.\n";
			cin >> c2_3_3_opt;
		}

		switch (c2_3_3_opt)
		{
		case 1:
			cout
				<< "+--------------------------------------------+\n"
				<< "| 1 - Add stop at the beginning of the route |\n"
				<< "+--------------------------------------------+\n"
				<< "| 2 - Add stop in between two other stops    |\n"
				<< "+--------------------------------------------+\n"
				<< "| 3 - Add stop  at the end of the route      |\n"
				<< "+--------------------------------------------+\n" << endl;

			cin >> c2_3_3_1opt;

			while (cin.fail() || (c2_3_3_1opt != 1 && c2_3_3_1opt != 2 && c2_3_3_1opt != 3))
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid Input. Please try again.\n";
				cin >> c2_3_3_1opt;
			}
			
			Add_Stop(stops, timings, c2_3_3_1opt, i);

			stops = vl[i].getBusStops();
			timings = vl[i].getTimings();
			vl[i].SetStops(stops);
			vl[i].SetSchedule(timings);
			break;

		case 2:
			cout << "Write the name of the stop you wish to remove: ";
			cin.ignore(1000, '\n');
			getline(cin, rem_stop);
			Remove_Stop(vl[i].getBusStops(), vl[i].getTimings(), rem_stop, i);
			break;

		case 3:
			cout << "Write the name of the stop you wish to change: ";
			cin.ignore(1000, '\n');
			getline(cin, ch_stop);
			Change_Stop(vl[i].getBusStops(), ch_stop, i);
			break;

		case 4:
			go_back = true;
			break;
		}
	}
}

void HQ::Change_Route()
{
	int id_reg, c2_3_opt, new_id, new_freq;
	unsigned int i = 0, i2 = 0;
	string stop_1;
	bool c2_3_end = false;
	vector<int> timings;

	cout << endl << "Write the id number of the route you want to change: ";
	cin >> id_reg;

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid Input. Please try again\n";
		cin >> id_reg;
	}

	if (Check_Route_ID(id_reg, i))
	{
		while (!c2_3_end)
		{
			cout
				<< endl << "Please indicate the parameter you want to change:\n"
				<< "+---------------+\n"
				<< "| 1 - ID        |\n"
				<< "+---------------+\n"
				<< "| 2 - Frequency |\n"
				<< "+---------------+\n"
				<< "| 3 - Stops     |\n"
				<< "+---------------+\n"
				<< "| 4 - Schedule  |\n"
				<< "+---------------+\n"
				<< "| 5 - Go back   |\n"
				<< "+---------------+\n" << endl;
			cin >> c2_3_opt;

			while (cin.fail() || (c2_3_opt != 1 && c2_3_opt != 2 && c2_3_opt != 3 && c2_3_opt != 4 && c2_3_opt != 5))
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid Input. Please try again\n";
				cin >> c2_3_opt;
			}

			switch (c2_3_opt)
			{
			case 1:
				cout << "Write the new ID number of the route: ";
				cin >> new_id;

				while (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Invalid Input. Please try again\n";
					cin >> new_id;
				}

				if (!Check_Route_ID(new_id, i2))
					vl[i].SetID(new_id);
				else cout << "There is already one route with this id!\n";

				break;

			case 2:
				cout << "Write the new frequency of the route: ";
				cin >> new_freq;

				while (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Invalid Input. Please try again\n";
					cin >> new_freq;
				}

				vl[i].SetFrequency(new_freq);
				break;

			case 3:
				C2_3_3_Menu(i);
				break;

			case 4:
				cout
					<< "Follow the instructions below: \n" << endl
					<< "Example: <It takes x minutes to get from stop_1 to stop_2> "
					<< "(Note: stop_1 and stop_2 must be consecutive stops!).\n" << endl
					<< "You want to change the value of x. Please write the name of stop_1: ";
				cin.ignore(1000, '\n');
				getline(cin, stop_1);

				timings = vl[i].getTimings();

				Change_Schedule(vl[i].getBusStops(), timings, stop_1, i);
				vl.at(i).SetSchedule(timings);
				break;

			case 5:
				c2_3_end = true;
				break;
			}
		}
	}
	else cout << "Line not found.\n" << endl;
}

void HQ::Main_Menu(string lines_file, string drivers_file)
{
	vector<Line> reverse_lines_vector;
	int main_opt, c3_opt, c1_opt, c2_opt;
	bool end = false, c2_end = false;
	const int day_start = 480, day_end = 1200;

	while (!end)
	{
		system("cls");
		Reverse_Lines(reverse_lines_vector); // Creates another Line vector but with the stops and times reversed
		cout
			<< "+--------------------------------------------------------------------+\n"
			<< "|                            SEMPREARROLAR                           |\n"
			<< "+--------------------------------------------------------------------+\n"
			<< "| 1 - Driver Management            | 2 - Line Management             |\n"
			<< "+--------------------------------------------------------------------+\n"
			<< "| 3 - Information                  | 4 - Save and Backup Information |\n"
			<< "+--------------------------------------------------------------------+\n"
			<< "| 5 - Restore Previous Information | 6 - Terminate                   |\n"
			<< "+--------------------------------------------------------------------+\n" << endl;
		cin >> main_opt;
		cout << endl;

		bool c1_end = false, c2_end = false;

		while (cin.fail() || (main_opt != 1 && main_opt != 2 && main_opt != 3 && main_opt != 4 && main_opt != 5
			&& main_opt != 6 && main_opt != 7))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << endl << "Invalid option! Please try again\n" << endl;
			cin >> main_opt;
		}

		switch (main_opt)
		{
		case 1:
			while (!c1_end)
			{
				cout
					<< "+----------------------+---------------------+\n"
					<< "| 1 - Add a new driver | 2 - Remove a driver |\n"
					<< "+----------------------+---------------------+\n"
					<< "| 3 - Change a driver  | 4 - Assign shifts   |\n"
					<< "+----------------------+---------------------+\n"
					<< "| 5 - Remove a shift   | 6 - Go back         |\n"
					<< "+----------------------+---------------------+\n" << endl;
				cin >> c1_opt;

				while (cin.fail() || (c1_opt != 1 && c1_opt != 2 && c1_opt != 3 && c1_opt != 4 && c1_opt != 5 && c1_opt != 6))
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Invalid option. Please try again\n";
					cin >> c1_opt;
				}

				switch (c1_opt)
				{
				case 1:
					Add_Driver();
					break;

				case 2:
					Remove_Driver();
					break;

				case 3:
					Change_Driver();
					break;

				case 4:
					Add_Shift(day_start, day_end);
					break;

				case 5:
					Remove_a_Shift();
					break;

				case 6:
					c1_end = true;
					break;
				}
			}
			break;

		case 2:
			while (!c2_end)
			{
				cout
					<< "+-------------------------------+\n"
					<< "| 1 - Add a new route           |\n"
					<< "+-------------------------------+\n"
					<< "| 2 - Remove a route            |\n"
					<< "+-------------------------------+\n"
					<< "| 3 - Change a route            |\n"
					<< "+-------------------------------+\n"
					<< "| 4 - Go back                   |\n"
					<< "+-------------------------------+\n" << endl;


				cin >> c2_opt;

				while (cin.fail() || (c2_opt != 1 && c2_opt != 2 && c2_opt != 3 && c2_opt != 4))
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Invalid option. Please try again\n";
					cin >> c2_opt;
				}

				switch (c2_opt)
				{
				case 1:
					Add_Route();
					break;

				case 2:
					Remove_Rout();
					break;

				case 3:
					Change_Route();
					break;

				case 4:
					c2_end = true;
					break;
				}

			}
			break;

		case 3:
			cout
				<< "+--------------------------+-------------+\n"
				<< "| 1 - Schedules and routes | 2 - Drivers |\n"
				<< "+--------------------------+-------------+\n"
				<< "| 3 - Bus                  | 4 - Go back |\n"
				<< "+--------------------------+-------------+\n" << endl;
			cin >> c3_opt;

			while (cin.fail() || (c3_opt != 1 && c3_opt != 2 && c3_opt != 3 && c3_opt != 4))
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid option! Please try again\n";
				cin >> c3_opt;
			}

			switch (c3_opt)
			{
			case 1:
				C3_1_Menu(reverse_lines_vector, day_start, day_end);
				break;

			case 2:
				C3_2_Menu(day_start, day_end);
				break;

			case 3:
				C3_3_Menu(day_start, day_end);
				break;

			case 4:
				break;
			}

		case 4:
			Save_Info(lines_file, drivers_file);
			break;

		case 5:
			Restore_Info(lines_file, drivers_file);
			break;

		case 6:
			end = true;
		}
	}
}