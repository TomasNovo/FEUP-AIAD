#ifndef __UI_UTILITIES_INCLUDED__
#define __UI_UTILITIES_INCLUDED__

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class ui_utilities{

public:
	
	static void ClearScreen();
	static bool SetWindow(const int&, const int&);

};


#endif