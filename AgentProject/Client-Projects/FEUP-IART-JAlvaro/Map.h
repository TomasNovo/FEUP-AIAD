#ifndef MAP_H_
#define MAP_H_

#include "macros.h"


// Class que guarda todos os mapas. Serve para guardar informação apenas ou imprimir mapas
class Map {
private:
    std::vector<std::pair<u_int,u_int>> sizes;
    std::vector<std::vector<std::vector<char>>> map;
    std::vector<u_int> number_of_robots;
    std::vector<std::vector<std::pair<u_int,u_int>>> robot_positions;
    std::vector<std::vector<std::pair<u_int,u_int>>> robot_targets;
public:
    //Load all the map in a given file
    Map(std::string file);

    //Imprime o mapa com as posições dos robots que eu pretendo
    void printMap(int level,std::vector<std::pair<u_int,u_int>> robot_positions);
    //Imprime o mapa com as posições originais
    void printMap(int level);

    std::vector<std::vector<char>> getCharMap(int level, std::vector<std::pair<u_int, u_int>> robot_positions);

    //Devolve os valores originais
    std::vector<std::pair<u_int,u_int>> getRobotPosition(int level);
    std::vector<std::pair<u_int,u_int>> getRobotTargets(int level);
    std::vector<std::vector<char>> getMap(int level);
    u_int getNumberOfRobots(int level);

    u_int getMapNumber();



};

#endif