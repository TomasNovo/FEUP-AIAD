#include "Map.h"

using namespace std;

Map::Map(string file)
{
    ifstream maps_file("res/maps.txt");
    string line;
    if (maps_file.is_open())
    {
        int map_quantity;
        maps_file >> map_quantity;
        while (map_quantity--)
        {
            u_int sizeX, sizeY;
            maps_file >> sizeX >> sizeY;
            //Guardar size X e Y no array de tamanhos
            this->sizes.push_back(make_pair(sizeX, sizeY));

            u_int n_robots;
            maps_file >> n_robots;
            vector<pair<u_int, u_int>> robot_positions, robot_targets;
            for (u_int i = 0; i < n_robots; i++)
            {
                u_int positionX, positionY, targetX, targetY;
                maps_file >> positionX >> positionY >> targetX >> targetY;
                robot_positions.push_back(make_pair(positionX, positionY));
                robot_targets.push_back(make_pair(targetX, targetY));
            }
            
            u_int n_robots_no_target;
            maps_file >> n_robots_no_target;
            for (u_int i = 0; i < n_robots_no_target; i++)
            {
                u_int positionX, positionY;
                maps_file >> positionX >> positionY;
                robot_positions.push_back(make_pair(positionX, positionY));
            }
            this->robot_positions.push_back(robot_positions);
            this->robot_targets.push_back(robot_targets);

            this->number_of_robots.push_back(n_robots+n_robots_no_target);
            vector<vector<char>> matrix;
            for (u_int i = 0; i < sizeY; i++)
            {
                vector<char> temp;
                matrix.push_back(temp);
            }
            char ler;
            for (u_int i = 0; i < sizeY; i++)
            {
                for (u_int j = 0; j < sizeX; j++)
                {
                    maps_file >> ler;
                    matrix[i].push_back(ler);
                }
            }
            this->map.push_back(matrix);
        }
    }
    else
    {
        cout << "Unable to locate maps file" << endl;
        exit(1);
    }
}

void Map::printMap(int level, vector<pair<u_int, u_int>> robot_positions)
{   clearScreen();
    vector<vector<char>> matrix = this->map[level];
    char letra_grande = 'A';
    char letra_pequena = 'a';
    for (u_int i = 0; i <this->robot_targets[level].size(); i++)
    {
        u_int posX = this->robot_targets[level][i].first, posY = this->robot_targets[level][i].second;
        matrix[posY][posX] = letra_pequena;
        letra_pequena += 1;
    }
    for (u_int i = 0; i < robot_positions.size(); i++)
    {
        u_int posX = robot_positions[i].first, posY = robot_positions[i].second;
        matrix[posY][posX] = letra_grande;
        letra_grande += 1;
    }

    for (u_int i = 0; i < matrix.size(); i++)
    {
        for (u_int j = 0; j < matrix[i].size(); j++)
        {
            if(matrix[i][j]=='.')
                cout << " "  << ' ';
            else
                cout << " " << matrix[i][j];
        }
        cout << endl;
    }
    cout << endl;
}
vector<vector<char>> Map::getCharMap(int level, vector<pair<u_int, u_int>> robot_positions)
{   
    vector<vector<char>> matrix = this->map[level];
    char letra_grande = 'A';
    char letra_pequena = 'a';
    for (u_int i = 0; i <this->robot_targets[level].size(); i++)
    {
        u_int posX = this->robot_targets[level][i].first, posY = this->robot_targets[level][i].second;
        matrix[posY][posX] = letra_pequena;
        letra_pequena += 1;
    }
    for (u_int i = 0; i < robot_positions.size(); i++)
    {
        u_int posX = robot_positions[i].first, posY = robot_positions[i].second;
        matrix[posY][posX] = letra_grande;
        letra_grande += 1;
    }

    return matrix;
}

void Map::printMap(int level)
{
    clearScreen();
    vector<vector<char>> matrix = this->map[level];
    char letra_grande = 'A';
    char letra_pequena = 'a';
    for (u_int i = 0; i < this->robot_positions[level].size(); i++)
    {
        u_int posX = this->robot_positions[level][i].first, posY = this->robot_positions[level][i].second;
        matrix[posY][posX] = letra_grande;
        letra_grande += 1;
    }

    for (u_int i = 0; i <this->robot_targets[level].size(); i++)
    {
        u_int posX = this->robot_targets[level][i].first, posY = this->robot_targets[level][i].second;
        matrix[posY][posX] = letra_pequena;
        letra_pequena += 1;
    }
    for (u_int i = 0; i < matrix.size(); i++)
    {
        for (u_int j = 0; j < matrix[i].size(); j++)
        {
            if(matrix[i][j]=='.')
                cout << ' ';
            else
                cout << matrix[i][j];
        }
        cout << endl;
    }
}

std::vector<std::pair<u_int,u_int>> Map::getRobotPosition(int level)
{
    return this->robot_positions[level];
}

std::vector<std::pair<u_int,u_int>> Map::getRobotTargets(int level)
{
    return this->robot_targets[level];
}

u_int Map::getNumberOfRobots(int level)
{
    return this->number_of_robots[level];
}

vector<vector<char>> Map::getMap(int level)
{
    return this->map[level];
}

u_int Map::getMapNumber()
{
    return this->map.size();
}