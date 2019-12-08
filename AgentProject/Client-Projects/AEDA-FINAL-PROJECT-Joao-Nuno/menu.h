/*
 * menu.h
 *
 *  Created on: 02/11/2017
 *      Author: nl
 */

#ifndef MENU_H_
#define MENU_H_

#include "Associate.h"
#include "Area.h"
#include "Association.h"
#include "SubArea.h"
#include "Functions.h"

#include <iostream>
#include <unistd.h> //for usleep(miliseconds) function
#include <fstream>

/**
 * @brief - The first menu to which the user is greeted.
 * Allows him to choose between reading information from files or not.
 */
void menu();

/**
 * @brief - The so called main menu.
 * Allows the user a smooth navigation through all the programs main functionalities.
 * Subdivides itself into the different main aspects of the program
 */
void menu2();

/**
 * @brief - The menu division regarding associate's management.
 * Here the user can see, change and create almost all the information regarding the associates
 */
void submenu1();

/**
 * @brief - The menu division regarding event's management.
 * Here the user can see, change and create almost all the information regarding the events
 */
void submenu2();

/**
 * @brief - The menu division regarding payment's management.
 * Here the user can see, change and create almost all the information regarding the payments
 */
void submenu3();

/**
 * @brief - The menu division regarding network management.
 * Here the user can see, change and create almost all the information regarding the network.
 */
void submenu4();

/**
 * @brief - Used to go back from a certain submenu to the main menu
 */
void regressar();

/**
 * @brief - The last menu the user will see.
 * The exit menu, allows the user to save or not the information made during the runtime
 */
void sair();

#endif /* MENU_H_ */
