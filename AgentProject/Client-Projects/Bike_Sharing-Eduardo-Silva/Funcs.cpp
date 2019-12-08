#include "Funcs.h"

using namespace std;

void InvalidInput(int n_op, int &op)
{
    while(cin.fail() || (op < 1 || op > n_op))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << endl << "Invalid option! Please try again\n" << endl;
        cin >> op;
    }
}

double calc_distance(int x1, int y1, int x2, int y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

Date read_date()
{
	ifstream read;
	istringstream sstr;
	string date, interval;
	int min, hr, d, mt;

	read.open("Date.txt");
	getline(read, date);
	read.close();

	sstr.str(date);
	sstr >> d >> interval >> mt >> interval >> hr >> interval >> min;

	Date global_date(mt, d, hr, min);

	return global_date;
}

void write_date(Date global_date)
{
	ofstream write;

	write.open("Date.txt");

	write << global_date.getDay() << " / " << global_date.getMonth() << " ; "
		<< global_date.getHour() << " : " << global_date.getMinutes();

	write.close();
}










