#ifndef GAME_H_
#define GAME_H_

#include "Player.h"
#include "AI.h"
#include "Human.h"
#include "Map.h"
#include "macros.h"

class Game
{
  private:
    u_int level;
    Player *player;
    Map *map;
    int levelChoose();

    bool is_number(const std::string &s)
    {
        return !s.empty() && std::find_if(s.begin(),
                                          s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
    }

  public:
    Game(std::string file);
    void menu();
    void loop();
};
#endif