#ifndef MENU_H_
#define MENU_H_





#ifdef _WIN32         // Depending on the User OS, the program can recognize the portuguese chars
#include <windows.h>
#define SetPTchar() SetConsoleCP(1252); SetConsoleOutputCP(1252);
#else
#define SetPTchar() NULL
#endif

#ifdef _WIN32 // To clear the screen depending in the User OS
#define clearScreen() system("cls");
#else
#define clearScreen() system("clear");
#endif



#endif /* SRC_MENU_H_ */
