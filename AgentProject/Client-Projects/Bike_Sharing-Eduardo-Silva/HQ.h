#ifndef AEDA_P1_HQ_H
#define AEDA_P1_HQ_H

#include <time.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <unordered_set>
#include "User.h"
#include "Station.h"
#include "Funcs.h"
#include "Destroy.h"
#include "Part.h"
#include "BST.h"
#include "Shop.h"

using namespace std;

struct DestroyBikeHash
{
	int operator() (const Destroy_Form &df) const
	{
		return df.getDate().getDay() + df.getDate().getHour() + df.getDate().getMinutes() + df.getDate().getMonth();
	}

	bool operator() (const Destroy_Form &df1, const Destroy_Form &df2) const
	{
		return df1 == df2;
	}
};

typedef unordered_set<Destroy_Form, DestroyBikeHash, DestroyBikeHash> HashTabDestroyForms;

class HQ
{
    vector<Member *> members;
    vector<User *> active_users;
    vector<Station *> stations;
	HashTabDestroyForms hash_table;
	BST<Part> parts;
	priority_queue<Shop> shops;

public:
    HQ(); //Constructor

	// Read/Write Operations

	void read_info(Date global_date); //Reads from file and fills the vectors
	void write_info() const; //Writes the data from the vectors to the text files

	// Get Methods

	vector<User *> getActiveUsers() const; //Returns the active users vector
	vector<Member *> getMembers() const; //Returns the members vector
	vector<Station *> getStations() const; //Returns the stations vector
	priority_queue<Shop> getShops() const; //Returns the shops priority queue

    //SHOP Methods
    void BikeShop_Menu();
    void setShops(priority_queue<Shop> new_shops);
    vector<bike_stock> createPurchase();
    int HandlePurchase();
    void printTopFive();
    void searchShop();
    string askShopName();


	// Menus

	void Main_Menu(Date &global_date); //Main user interface
	void Bikes_Menu(); //Interface related to the Bikes
	void Station_Menu(); //Interface related to the Stations
	void Payment_Menu(Date global_date); //Interface related to the payment options
	void Options_Menu(Date &global_date); //Interface with several options for testing purposes
	void Add_remove_member_menu(); //Interface regarding the addition or removal of members
	void Add_remove_station_menu(Date global_date); //Interface regarding the addition or removal of stations
	void Destruction_Menu(const Date &global_date);
	void fast_forward_menu(Date &global_date);

	//Bikes Menu

	void RentBike(); //Initiates the renting process of a bike
	void addActiveUser(User *user); //Adds an active user

	//Stations Menu

	void Search_Station() const; //Searches for a particular station and, if found, returns information about it
	void Nearest_Station(); //Returns information about the closest station to the user
	int find_Station(string name); //Returns the index of the station in the HQ vector, else returns -1
	vector<Station *> find_bike_type(string type) const;
	void search_station(string name) const;
	void show_stations() const;

	//Payment Menu

	void Check_Balance(Date global_date); //Shows how much a regular active user has to pay so far or how much a member has to pay at the end of the month
	void Check_out(Date global_date); //Initiates the process of returning a bike and payment(if necessary)
  
	 //Options Menu

	void addStation(Date global_date); //Adds a new station
	void removeStation(); //Removes an existing station
	void addMember(); //Adds a new member
	void removeMember(); //Removes an existing member
	void Reset_Members_MonthlyTime();
	void Rand_Localization();
	void FastForward_Time(int month, int day, int hour, int minute, Date &global_date);
	void addHoursActiveMembers(Date &global_date);
	
	//Destruction Menu

	void destroy_bike(Date g_date);
	void show_bikes_to_destroy() const;
	void remove_from_table(Date g_date);

	//Other

    int find_Member(string name); //Returns the index of the member in the HQ vector, else returns -1
    int find_ActiveUser(string name);  //Returns the index of the active user in the HQ vector, else returns -1
	
	//Binary tree
	void cheapest_supplier();
	void Add_remove_part_menu();
	void part_menu();
	void addPart();
	void removePart();
	void show_suppliers();
	void buy_part_func();
	
	
	
};

#endif
