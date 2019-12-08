#include "Game.h"
#include <iostream>

using namespace std;


int main()
{
    
    Game *LabyrinthRobots = new Game("res/maps.txt");
    LabyrinthRobots->menu();
    return 0;
}
