#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "HQ.h"

using namespace std;

int main()
{
	HQ hq;
	Date g_date = read_date();

	hq.read_info(g_date);
	hq.Main_Menu(g_date);
	write_date(g_date);

    return 0;
}