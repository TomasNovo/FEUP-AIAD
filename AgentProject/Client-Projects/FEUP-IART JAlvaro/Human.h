#ifndef HUMAN_H_
#define HUMAN_H_

#include "macros.h"
#include "Player.h"
#include "Map.h"
#include <iostream>
#include <vector>
#include <utility>
#include <climits>


class Human:public Player{
private: 

public:
    Human(){}
    Human(int level,Map *map);

    bool makeMove();

    bool getHint();

};

#endif