#include "Human.h"
#include "AI.h"

using namespace std;

Human::Human(int level, Map *map) : Player(level, map) {}

bool Human::makeMove()
{
    bool hint;

    this->map->printMap(this->level, this->robot_positions);
    char robot, direction;
    do {
    hint = false;
    cout << "Play: ";
    cin >> robot;
    if (robot == '0' || robot == 'q')
        return false;

    if(robot == 'h' || robot == 'H'){
        hint = this->getHint();
    }
    } while(hint);
    cin >> direction;

    int robot_number = this->transformCharToNumber(robot);
    switch (direction)
    {
    case 't':
    case 'T':
    case 'u':
    case 'U':
        return this->PlayTop(robot_number);
        break;
    case 'b':
    case 'B':
    case 'd':
    case 'D':
        return this->PlayBottom(robot_number);
        break;
    case 'r':
    case 'R':
        return this->PlayRight(robot_number);
        break;
    case 'l':
    case 'L':
        return this->PlayLeft(robot_number);
        break;
    }
    return false;
}

bool Human::getHint()
{
    AI solver(this->level, this->robot_positions, this->map);
    return solver.get_best_move();
}