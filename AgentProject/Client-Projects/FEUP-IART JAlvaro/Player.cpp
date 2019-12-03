#include "Player.h"

using namespace std;

Player::Player(int level, Map *map)
{
    this->level = level;
    this->map = map;
    this->robot_positions = map->getRobotPosition(this->level);
    this->number_robots = map->getNumberOfRobots(this->level);
    this->map_char = map->getMap(this->level);
    for(u_int i = 0; i< this->robot_positions.size();i++)
    {
        this->map_char[this->robot_positions[i].second][this->robot_positions[i].first]=this->transformNumberToChar(i);
    }
}

Player::Player(int level, Map *map, vector<pair<u_int,u_int>> robotCoords)
{
    
    this->level = level;
    this->map = map;
    this->robot_positions = robotCoords;
    this->number_robots = map->getNumberOfRobots(this->level);
    this->map_char = map->getMap(this->level);
    
    for(u_int i = 0; i< this->robot_positions.size();i++)
    {
        this->map_char[this->robot_positions[i].second][this->robot_positions[i].first]=this->transformNumberToChar(i);
    }
}

pair<u_int, u_int> Player::MoveTop(int robot_number)
{
    u_int currentX = this->robot_positions[robot_number].first;
    u_int currentY = this->robot_positions[robot_number].second - 1;
    vector<vector<char>> map = this->map_char;
    u_int size1 = map[0].size(), size2 = map.size();
    while (currentX >= 0 && currentX < size1 && currentY >= 0 && currentY < size2)
    {
        if (map[currentY][currentX] == '.' || (map[currentY][currentX] >= 97 && map[currentY][currentX] <= 122))
        {
            currentY--;
        }
        else
        {
            return make_pair(currentX, currentY + 1);
        }
    }
    return make_pair(currentX, currentY);
}

pair<u_int, u_int> Player::MoveBottom(int robot_number)
{
    u_int currentX = this->robot_positions[robot_number].first;
    u_int currentY = this->robot_positions[robot_number].second + 1;
    vector<vector<char>> map = this->map_char;
    u_int size1 = map[0].size(), size2 = map.size();
    while (currentX >= 0 && currentX < size1 && currentY >= 0 && currentY < size2)
    {
        if (map[currentY][currentX] == '.' || (map[currentY][currentX] >= 97 && map[currentY][currentX] <= 122))
        {
            currentY++;
        }
        else
        {
            return make_pair(currentX, currentY - 1);
        }
    }
    return make_pair(currentX, currentY);
}

pair<u_int, u_int> Player::MoveLeft(int robot_number)
{
    u_int currentX = this->robot_positions[robot_number].first - 1;
    u_int currentY = this->robot_positions[robot_number].second;
    vector<vector<char>> map = this->map_char;
    u_int size1 = map[0].size(), size2 = map.size();
    while (currentX >= 0 && currentX < size1 && currentY >= 0 && currentY < size2)
    {
        if (map[currentY][currentX] == '.' || (map[currentY][currentX] >= 97 && map[currentY][currentX] <= 122))
        {
            currentX--;
        }
        else
        {
            return make_pair(currentX + 1, currentY);
        }
    }
    return make_pair(currentX, currentY);
}
pair<u_int, u_int> Player::MoveRight(int robot_number)
{
    u_int currentX = this->robot_positions[robot_number].first + 1;
    u_int currentY = this->robot_positions[robot_number].second;
    vector<vector<char>> map = this->map_char;
    u_int size1 = map[0].size(), size2 = map.size();
    while (currentX >= 0 && currentX < size1 && currentY >= 0 && currentY < size2)
    {
        if (map[currentY][currentX] == '.' || (map[currentY][currentX] >= 97 && map[currentY][currentX] <= 122))
        {
            currentX++;
        }
        else
        {
            return make_pair(currentX - 1, currentY);
        }
    }
    return make_pair(currentX, currentY);
}


pair<u_int, u_int> Player::MoveTop(vector<vector<char>> map_char,int robot_number,vector<pair<u_int,u_int>> robot_positions)
{
    u_int currentX = robot_positions[robot_number].first;
    u_int currentY = robot_positions[robot_number].second - 1;
    vector<vector<char>> map = map_char;
    u_int size1 = map[0].size(), size2 = map.size();
    while (currentX >= 0 && currentX < size1 && currentY >= 0 && currentY < size2)
    {
        if (map[currentY][currentX] == '.' || (map[currentY][currentX] >= 97 && map[currentY][currentX] <= 122))
        {
            currentY--;
        }
        else
        {
            return make_pair(currentX, currentY + 1);
        }
    }
    return make_pair(currentX, currentY);
}

pair<u_int, u_int> Player::MoveBottom(vector<vector<char>> map_char,int robot_number,vector<pair<u_int,u_int>> robot_positions)
{
    u_int currentX = robot_positions[robot_number].first;
    u_int currentY = robot_positions[robot_number].second + 1;
    vector<vector<char>> map =map_char;
    u_int size1 = map[0].size(), size2 = map.size();
    while (currentX >= 0 && currentX < size1 && currentY >= 0 && currentY < size2)
    {
        if (map[currentY][currentX] == '.' || (map[currentY][currentX] >= 97 && map[currentY][currentX] <= 122))
        {
            currentY++;
        }
        else
        {
            return make_pair(currentX, currentY - 1);
        }
    }
    return make_pair(currentX, currentY);
}

pair<u_int, u_int> Player::MoveLeft(vector<vector<char>> map_char,int robot_number,vector<pair<u_int,u_int>> robot_positions)
{
    u_int currentX = robot_positions[robot_number].first - 1;
    u_int currentY = robot_positions[robot_number].second;
    vector<vector<char>> map = map_char;
    u_int size1 = map[0].size(), size2 = map.size();
    while (currentX >= 0 && currentX < size1 && currentY >= 0 && currentY < size2)
    {
        if (map[currentY][currentX] == '.' || (map[currentY][currentX] >= 97 && map[currentY][currentX] <= 122))
        {
            currentX--;
        }
        else
        {
            return make_pair(currentX + 1, currentY);
        }
    }
    return make_pair(currentX, currentY);
}
pair<u_int, u_int> Player::MoveRight(vector<vector<char>> map_char,int robot_number,vector<pair<u_int,u_int>> robot_positions)
{
    u_int currentX = robot_positions[robot_number].first + 1;
    u_int currentY = robot_positions[robot_number].second;
    vector<vector<char>> map = map_char;
    u_int size1 = map[0].size(), size2 = map.size();
    while (currentX >= 0 && currentX < size1 && currentY >= 0 && currentY < size2)
    {
        if (map[currentY][currentX] == '.' || (map[currentY][currentX] >= 97 && map[currentY][currentX] <= 122))
        {
            currentX++;
        }
        else
        {
            return make_pair(currentX - 1, currentY);
        }
    }
    return make_pair(currentX, currentY);
}

bool Player::PlayTop(int robot_number)
{
    u_int currentX = this->robot_positions[robot_number].first;
    u_int currentY = this->robot_positions[robot_number].second - 1;
    vector<vector<char>> map = this->map_char;
    u_int size1 = map[0].size(), size2 = map.size();
    while (currentX >= 0 && currentX < size1 && currentY >= 0 && currentY < size2)
    {
        if (map[currentY][currentX] == '.' || (map[currentY][currentX] >= 97 && map[currentY][currentX] <= 122))
        {
            currentY--;
        }
        else
        {
            this->replacePosition(robot_number,make_pair(this->robot_positions[robot_number].first,this->robot_positions[robot_number].second),make_pair(currentX, currentY + 1));
            return true;
        }
    }
    return false;
}

bool Player::PlayBottom(int robot_number)
{
    u_int currentX = this->robot_positions[robot_number].first;
    u_int currentY = this->robot_positions[robot_number].second + 1;
    vector<vector<char>> map = this->map_char;
    u_int size1 = map[0].size(), size2 = map.size();
    while (currentX >= 0 && currentX < size1 && currentY >= 0 && currentY < size2)
    {
        if (map[currentY][currentX] == '.' || (map[currentY][currentX] >= 97 && map[currentY][currentX] <= 122))
        {
            currentY++;
        }
        else
        {
            this->replacePosition(robot_number,make_pair(this->robot_positions[robot_number].first,this->robot_positions[robot_number].second),make_pair(currentX, currentY - 1));
            return true;
        }
    }
    return false;
}

bool Player::PlayLeft(int robot_number)
{
    u_int currentX = this->robot_positions[robot_number].first - 1;
    u_int currentY = this->robot_positions[robot_number].second;
    vector<vector<char>> map = this->map_char;
    u_int size1 = map[0].size(), size2 = map.size();
    while (currentX >= 0 && currentX < size1 && currentY >= 0 && currentY < size2)
    {
        if (map[currentY][currentX] == '.' || (map[currentY][currentX] >= 97 && map[currentY][currentX] <= 122))
        {
            currentX--;
        }
        else
        {
            this->replacePosition(robot_number,make_pair(this->robot_positions[robot_number].first,this->robot_positions[robot_number].second),make_pair(currentX + 1, currentY));
            return true;
        }
    }
    return false;
}
bool Player::PlayRight(int robot_number)
{
    u_int currentX = this->robot_positions[robot_number].first + 1;
    u_int currentY = this->robot_positions[robot_number].second;
    vector<vector<char>> map = this->map_char;
    u_int size1 = map[0].size(), size2 = map.size();
    while (currentX >= 0 && currentX < size1 && currentY >= 0 && currentY < size2)
    {
        if (map[currentY][currentX] == '.' || (map[currentY][currentX] >= 97 && map[currentY][currentX] <= 122))
        {
            currentX++;
        }
        else
        {
            this->replacePosition(robot_number,make_pair(this->robot_positions[robot_number].first,this->robot_positions[robot_number].second),make_pair(currentX - 1, currentY));
            return true;
        }
    }
    return false;
}


int Player::transformCharToNumber(char ch)
{
    return toupper(ch) - 65;
}
char Player::transformNumberToChar(int number)
{
    return number + 65;
}

void Player::replacePosition(int robot_number,std::pair<u_int,u_int> current,std::pair<u_int,u_int> to)
{
    u_int currentX=current.first,currentY=current.second;
    u_int toX=to.first,toY=to.second;
    char char_robot=this->transformNumberToChar(robot_number);
    this->map_char[currentY][currentX]='.';
    this->map_char[toY][toX]=char_robot;
    this->robot_positions[robot_number] = make_pair(toX, toY);
}

void Player::replacePosition(int robot_number,pair<u_int,u_int> current,pair<u_int,u_int> to,vector<pair<u_int,u_int>> &robot_positions,vector<vector<char>> &map_char)
{
    u_int currentX=current.first,currentY=current.second;
    u_int toX=to.first,toY=to.second;
    char char_robot=this->transformNumberToChar(robot_number);
    map_char[currentY][currentX]='.';
    map_char[toY][toX]=char_robot;
    robot_positions[robot_number] = make_pair(toX, toY);
}

bool Player::checkEndGame()
{
    vector<pair<u_int,u_int>> targets=this->map->getRobotTargets(this->level);
    for(u_int i=0;i<targets.size();i++)
    {
        if(!(targets[i].first==this->robot_positions[i].first && targets[i].second == this->robot_positions[i].second))
            return false;
    }
    return true;
}
bool Player::checkEndGame(vector<pair<u_int,u_int>> robot_pos)
{
    vector<pair<u_int,u_int>> targets=this->map->getRobotTargets(this->level);
    for(u_int i=0;i<targets.size();i++)
    {
        if(!(targets[i].first==robot_pos[i].first && targets[i].second == robot_pos[i].second))
            return false;
    }
    return true;
}