#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <Windows.h>

#include "Bus.h"
#include "Company.h"
#include "Driver.h"
#include "Line.h"
#include "Shift.h"

using namespace std;

#ifdef _WINDOWS_
#define clearScreen() system("cls")
#else
#define clearScreen() system("clear")
#endif

#define HORAINICIAL 8
#define HORAFINAL 11
#define HORATURNO 6
