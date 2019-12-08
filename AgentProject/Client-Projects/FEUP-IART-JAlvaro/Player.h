#ifndef PLAYER_H_
#define PLAYER_H_

#include "macros.h"
#include "Map.h"

class Player {

protected:

    int level;
    u_int number_robots;
    std::vector<std::pair<u_int,u_int>> robot_positions;
    std::vector<std::vector<char>> map_char;

    Map * map;

    void printMap();

    int transformCharToNumber(char ch);
    char transformNumberToChar(int number);


public:
    //Constructor
    Player(){}
    Player(int level,Map * map);
    Player(int level,Map * map,std::vector<std::pair<u_int,u_int>> robotCoords);

    //Diz qual a posição que vai ter mas não move
    std::pair<u_int,u_int> MoveTop(int robot_number);
    std::pair<u_int,u_int> MoveBottom(int robot_number);
    std::pair<u_int,u_int> MoveRight(int robot_number);
    std::pair<u_int,u_int> MoveLeft(int robot_number);
    std::pair<u_int,u_int> MoveTop(std::vector<std::vector<char>> map_char,int robot_number,std::vector<std::pair<u_int,u_int>> robot_positions);
    std::pair<u_int,u_int> MoveBottom(std::vector<std::vector<char>> map_char,int robot_number,std::vector<std::pair<u_int,u_int>> robot_positions);
    std::pair<u_int,u_int> MoveRight(std::vector<std::vector<char>> map_char,int robot_number,std::vector<std::pair<u_int,u_int>> robot_positions);
    std::pair<u_int,u_int> MoveLeft(std::vector<std::vector<char>> map_char,int robot_number,std::vector<std::pair<u_int,u_int>> robot_positions);

    //Faz um movimento
    bool PlayTop(int robot_number);
    bool PlayBottom(int robot_number);
    bool PlayRight(int robot_number);
    bool PlayLeft(int robot_number);

    //Função que é chamada a cada movimento feito. Implementado pela funções abstratas
    virtual bool makeMove() = 0;

    //Substitui a posição no map_char do robot. Substitui a posição no vector de posições do robot
    void replacePosition(int robot_number,std::pair<u_int,u_int> current,std::pair<u_int,u_int> to);
    void replacePosition(int robot_number,std::pair<u_int,u_int> current,std::pair<u_int,u_int> to,std::vector<std::pair<u_int,u_int>> &robot_positions,std::vector<std::vector<char>> &map_char);

    //Verifica se o jogo acabou, true se acabou ou false caso contrario
    bool checkEndGame();
    bool checkEndGame(std::vector<std::pair<u_int,u_int>> robot_positions);

};

#endif