#include "User.h"
#include "HQ.h"

using namespace std;

//User

double User::price_hour = 5;
double Member::price_month = 30;

User::User(string username)
{
	srand(static_cast<int> (time(NULL)));
	Date null_date(1,1,0,0);
    Urban_simple_b *null_bike = new Urban_simple_b(null_date);
    bike = null_bike;
    name = username;
    active = false;
	Localization.first = rand() % 15 + 1;
	Localization.second = rand() % 15 + 1;
}

string User::getName() const
{
    return name;
}

pair<int, int> User::getLocalization() const
{
	return Localization;
}

Bike* User::getBike() const
{
	return bike;
}

void User::setName(string new_name)
{
	name = new_name;
}

void User::setLocalization(int x, int y)
{
	Localization.first = x;
	Localization.second = y;
}

void User::setBike(Bike *bk)
{
	bike = bk;
}

void User::set_active(bool cond)
{
	active = cond;
}

void User::addBike(Bike *bk, HQ *hq)
{
    bike = bk;
    active = true;
	hq->addActiveUser(this);
}

void User::removeBike()
{
    active = false;
}

Station* User::getClosestStation(vector<Station *> vs) const
{
	unsigned int i = 0, i_min = 0;
	pair< int, int> stat_loc = vs[i]->getLocalization();
	double min = sqrt(pow(stat_loc.first - Localization.first, 2) + pow(stat_loc.second - Localization.second, 2));

	for (i; i < vs.size(); i++)
	{
		stat_loc = vs[i]->getLocalization();

		if (sqrt(pow(stat_loc.first - Localization.first, 2) + pow(stat_loc.second - Localization.second, 2)) < min)
		{
			min = sqrt(pow(stat_loc.first - Localization.first, 2) + pow(stat_loc.second - Localization.second, 2));
			i_min = i;
		}
	}

	return vs[i_min];
}

double User::getPrice() const
{
	return price_hour;
}

void User::Checkout(Date global_date)
{
	double price = getBike()->getPrice(global_date);

	cout << endl << "Total cost: " << setprecision(2) << price << " euros\n";

	set_active(false);
}

//Member

Member::Member(string username) : User(username)
{
    total_monthly_time = 0;
}

void Member::setHours(int hours)
{
	total_monthly_time = hours;
}

void Member::addHours(int hours)
{
	total_monthly_time += hours;
}

int Member::getHours() const
{
	return total_monthly_time;
}

double Member::getPrice() const
{
	if (total_monthly_time >= 20)
		return price_month * 0.90;
	else return price_month * 0.95;
}

void Member::Checkout(Date global_date)
{
	int n_hours = global_date - getBike()->getDate();
	total_monthly_time += n_hours;
	cout << "This month's bill: " << fixed << setprecision(2) << getPrice() << " euros" << endl;
	set_active(false);
}

//Regular

Regular::Regular(string username) : User(username) {}

void Regular::Checkout(Date global_date){}

//Already Active User

Already_Active_User::Already_Active_User(string name)
{
	this->name = name;
}

string Already_Active_User::getName() const
{
	return name;
}

//Not Active User

Not_Active_User::Not_Active_User(string nm)
{
	name = nm;
}

string Not_Active_User::getName() const
{
	return name;
}

//Another member

Another_member::Another_member(string am_name)
{
	name = am_name;
}

string Another_member::getName() const
{
	return name;
}






