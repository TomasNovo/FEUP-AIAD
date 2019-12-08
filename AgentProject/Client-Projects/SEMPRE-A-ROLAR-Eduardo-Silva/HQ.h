#ifndef HQ_h
#define HQ_H

#include <fstream>
#include "Driver.h"
#include "Line.h"
#include "Funcs.h"

class HQ
{
private:

	vector<Driver> vd;
	vector<Line> vl;
	vector<Bus> vb;

public:
	
	HQ(vector<Line> v_l, vector<Driver> v_d, vector<Bus> v_b);

	void Save_Info(string lines_file, string drivers_file) const; /*Saves the information contained in the 2 main vectors 
															(Drivers and Lines) in the lines/drivers files */

	void Reverse_Lines(vector<Line> &rvl) const;//Reverses the order of the Stops and Schedule vectors in each line

	bool Check_Driver_ID(int id_check, unsigned int &i) const; /* Returns true if there's a driver with that id or false 
															   otherwise. If theres is, the vairable i is updated with its 
															   position in the vector */

	bool Check_Route_ID(int id_check, unsigned int &i) const; /* Returns true if there is a route with that id or
																 false if otherwise. If there is, the value of i is
																 updated with the index of the line in the vector */

	void See_Available_Drivers(unsigned int day_start, unsigned int day_end) const; //Shows available drivers

	void See_Unattended_Shifts(unsigned int day_start, unsigned int day_end) const; /* Display available time frames between
																					   all the drivers shifts*/

	void Add_Route(); //Adds an element, created by the user, of type Line to the vector of the same category
	void Remove_Rout(); //Removes a rout from the respective vector based on its id

	void Add_Stop(vector<string> &vs, vector<int> &vt, int c1_3_3_1_opt, unsigned int ind); /*Adds a stop to a certain route, 
																							as well as the respective time,
																							based on a previous choice*/

	void Remove_Stop(vector<string> vs, vector<int> vt, string rem_stop, unsigned int ind); // Removes a stop from a route 
	void Change_Stop(vector<string> vs, string ch_stop, unsigned int ind); // Changes the name of a particular stop in a route

	void Change_Schedule(vector<string> vs, vector<int> &vt, string stop_1, unsigned int ind); /* Changes a particular time
																								  value in a route */

	void Add_Driver(); // Adds an element, created by the user, of the type Driver to the vector of the same category 
	void Remove_Driver(); //Removes a driver from the respective vector based on its id

	void Change_Driver(); /* Interface that shows up when the user follows the path: Main Menu -> Driver Management 
						  -> Change a driver; Used to change the parameters of a driver */

	void Add_Shift(unsigned int day_start, unsigned int day_end); /* Allows the user to assign a shift created by him to a 
																  particular driver */

	void Remove_a_Shift(); // Removes a shift from a driver as weel as from the respective bus
	void See_Driver_Job() const; //Shows the data about a driver, as well as it's current shifts
	void See_Bus_Info() const; // Shows a bus's information, as well as its shifts
	void See_Line_Schedule(vector<Line> v_l, int day_start, int day_end, unsigned int i) const; // Displays tbe schedule of a line

	void See_Stop_Schedule(vector<Line> rvl, int day_start, int day_end, string stop_search) const; /*Displays the schedule of a 
																									stop, both ways */

	void Route_Planner(vector<Line> rvl) const; /*Shows the stops in-between two other stops indicated by the user as well as the
												travel time between them. If there is more than one route with the same stops in 
												the same order, it also shows them.*/

	void Search_Stop_By_Line() const; //Shows the routes that include a certain stop

	void C3_3_Menu(const unsigned int day_start, const unsigned int day_end) const; /* Path to this menu: Main Menu 
																					-> Information -> Bus */

	void C3_2_Menu (unsigned int day_start, unsigned int day_end) const; /* Path to this menu: Main Menu -> Information 
																		 -> Drivers */

	void C3_1_Menu(vector<Line> rvl, int day_start, int day_end) const; /* Path to this menu: Main Menu -> Information 
																		-> Schedules and Routes */

	void C2_3_3_Menu(unsigned int i); // Path to this Menu: Main Menu -> Route Management -> Change a route -> Stops 

	void Change_Route(); /* Interface that shows up when the user followed the path: Main Menu -> Line Management 
						 -> Change a Route; Used to change the parameters of a route */

	void Main_Menu(string lines_file, string drivers_file); /* Main Menu of the application. Serves an interface with a variaty 
															of options. */
};

#endif
