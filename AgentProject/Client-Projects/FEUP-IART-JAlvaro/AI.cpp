#include "AI.h"
#include <algorithm>
#include <queue>

using namespace std;

HEURISTIC AI::heuristic = REALISTIC;

AI::AI(int level, Map *map, int algorithm) : Player(level, map),
                                             algorithm(algorithm)
{
    this->alg_calculated = this->computeSolution();
    this->index_sol = 0;
}

AI::AI(int level, vector<pair<u_int, u_int>> robot_pos, Map *map) : Player(level, map, robot_pos)
{
    this->expancoes = 0;
    cout << "Computing a Solution. Wait a few seconds" << endl;
    this->start = chrono::high_resolution_clock::now();
    this->robot_positions = robot_pos;
    this->alg_calculated = this->astar();
    this->end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = this->end - this->start;
    cout << "Solution computed with " << this->expancoes << " nodes searched" << endl;
    cout << "Solution with " << this->best_move.size() << " movements" << endl;
    cout << "Solution took " << elapsed.count() << " seconds" << endl;
}

bool AI::is_number(const std::string &s)
{
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

bool AI::makeMove()
{

    if (this->alg_calculated)
    {

        this->map->printMap(this->level, this->robot_positions);
        cout << "Press ENTER to get next step" << endl;

        cin.get();
        if (this->index_sol >= this->best_move.size())
        {
            this->map->printMap(this->level, this->robot_positions);
            this->alg_calculated = false;
            return false;
        }
        u_int robot_number = this->best_move[this->index_sol].first;
        char direction = this->best_move[this->index_sol].second;
        switch (direction)
        {
        case 't':
        case 'T':
        case 'u':
        case 'U':
            this->PlayTop(robot_number);
            break;
        case 'b':
        case 'B':
        case 'd':
        case 'D':
            this->PlayBottom(robot_number);
            break;
        case 'r':
        case 'R':
            this->PlayRight(robot_number);
            break;
        case 'l':
        case 'L':
            this->PlayLeft(robot_number);
            break;
        }

        this->index_sol++;
        if (this->index_sol >= this->best_move.size())
        {
            this->map->printMap(this->level, this->robot_positions);
            this->alg_calculated = false;
            return false;
        }
    }
    else
    {
        cout << "Solution not found! " << endl;
        return false;
    }
    return true;
}

bool AI::computeSolution()
{
    this->expancoes = 0;
    bool solutionFound = false;
    this->map->printMap(this->level, this->robot_positions);
    cout << "Computing a Solution. Wait a few seconds" << endl;
    this->start = chrono::high_resolution_clock::now();
    switch (this->algorithm)
    {
    case DFS:
        solutionFound = this->dfs();
        break;
    case BFS:
        solutionFound = this->bfs();
        break;
    case ASTAR:
        solutionFound = this->astar();
        break;
    case IDFS:
        solutionFound = this->iterativeDfs();
        break;
    case GREEDY:
        solutionFound = this->greedy();
        break;
    default:
        cout << "Invalid Algorithm" << endl;
        exit(0);
    }
    this->end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = this->end - this->start;
    if (solutionFound)
    {
        cout << "Solution computed with " << this->expancoes << " nodes searched" << endl;
        cout << "Solution with " << this->best_move.size() << " movements" << endl;
        cout << "Solution took " << elapsed.count() << " seconds" << endl;

        cout << "Press ENTER to continue" << endl;

        cin.get();
    }
    return solutionFound;
}

bool AI::alreadyBeenOn(std::map<Info, u_int> &visited, u_int max_search, u_int i, pair<u_int, u_int> position, vector<pair<u_int, u_int>> robot_positions)
{
    robot_positions[i] = position;
    u_int profundidade;
    bool existe;
    try
    {
        profundidade = visited.at(robot_positions);
        existe = true;
    }
    catch (const std::out_of_range &e)
    {
        visited[robot_positions] = max_search;
        profundidade = max_search;
        existe = false;
    }
    if (existe && profundidade <= max_search)
        return true;
    else
        return false;
}

bool AI::dfs()
{
    std::map<Info, u_int> visited;
    Info novo(this->robot_positions);
    visited[novo] = 0;
    vector<pair<u_int, char>> moves;
    this->best_move.clear();
    this->best_custo = INT_MAX;
    string ler;
    do
    {
        cout << "Max Depth Limit: ";
        cin >> ler;
    } while (!is_number(ler));
    this->limite = stoi(ler);
    cout << "Searching ..." << endl;
    this->expancoes = 0;
    this->start = chrono::high_resolution_clock::now();
    return this->dfs(1, this->map_char, this->robot_positions, visited, moves);
}

bool AI::dfs(int custo, vector<vector<char>> map_char, vector<pair<u_int, u_int>> robot_positions, std::map<Info, u_int> &visited, vector<pair<u_int, char>> moves)
{
    char directions[] = {'t', 'l', 'b', 'r'};
    if (custo > (int)this->limite)
        return false;
    if (this->checkEndGame(robot_positions))
    {
        this->best_custo = custo;
        this->best_move = moves;
        return true;
    }

    for (u_int i = 0; i < robot_positions.size(); i++)
    {
        pair<u_int, u_int> current_position = robot_positions[i];

        for (u_int j = 0; j < 4; j++)
        {
            pair<u_int, u_int> move = this->getNewCoords(map_char, i, j, robot_positions);
            if (move != current_position && !this->alreadyBeenOn(visited, custo, i, move, robot_positions))
            {
                this->expancoes++;
                vector<pair<u_int, u_int>> copy_robot_positions = robot_positions;
                vector<pair<u_int, char>> copy_moves = moves;
                vector<vector<char>> copy_map_char = map_char;
                copy_moves.push_back(make_pair(i, directions[j]));
                this->replacePosition(i, current_position, move, copy_robot_positions, copy_map_char);
                if (this->dfs(custo + 1, copy_map_char, copy_robot_positions, visited, copy_moves))
                    return true; //houve_sol = true;
            }
        }
    }
    return false;
}

bool AI::iterativeDfs()
{
    std::map<Info, u_int> visited;
    Info novo(this->robot_positions);
    visited[novo] = 0;
    vector<pair<u_int, char>> moves;
    this->best_move.clear();
    this->best_custo = INT_MAX;
    this->limite = 1;
    u_int max_limite;
    string ler;
    do
    {
        cout << "Max Depth: ";
        cin >> ler;
    } while (!is_number(ler));
    max_limite = stoi(ler);
    this->start = chrono::high_resolution_clock::now();
    cout << "Depth Level: " << this->limite << endl;
    while (!this->dfs(1, this->map_char, this->robot_positions, visited, moves))
    {
        this->limite++;
        if (this->limite > max_limite)
            return false;
        visited.clear();
        Info novo2(this->robot_positions);
        visited[novo2] = 0;
        this->best_move.clear();
        this->best_custo = INT_MAX;
        cout << "Depth Level: " << this->limite << endl;
    }
    return true;
}

bool AI::astar()
{
    this->best_custo=INT_MAX;
    this->best_move.clear();
    set<Node> openSet, closedSet;
    vector<pair<u_int, char>> moves;
    Node inicial(this->robot_positions, this->map_char,moves);
    priority_queue<pair<u_int,Node>> queue;
    openSet.insert(inicial);
    queue.push(make_pair(0,inicial));

    while (!openSet.empty() && !queue.empty())
    {
        Node current=queue.top().second;
        queue.pop();
        this->expancoes++;
        //cout << this->expancoes << " " << current.moves.size() << " " << queue.size() << " " << current.G <<  endl;
        if (this->checkEndGame(current.robotsCoords) && (int)current.moves.size()<this->best_custo)
        {
            this->best_move=current.moves;
            this->best_custo=current.moves.size();
            break; //Change this to continue to only get one solution that may be no optimal
        }
        if((int)current.G>this->best_custo)
        {
            break;
        }
        //log n ^ 2
        closedSet.insert(current);
        openSet.erase(current);

        for (u_int i = 0; i < this->robot_positions.size(); ++i)
        {
            for (int j = 0; j < 4; j++)
            {
                //Constante
                pair<u_int, u_int> newCoordinates = getNewCoords(i, j, current);
                vector<vector<char>> new_char_map = current.map_char;
                vector<pair<u_int, u_int>> newRobotCoords = current.robotsCoords;
                this->replacePosition(i, current.robotsCoords[i], newCoordinates, newRobotCoords, new_char_map);
                Node pesquisa(newRobotCoords,new_char_map,current.moves);
                //log n
                if (detectCollision(current.robotsCoords[i], newCoordinates) || closedSet.find(pesquisa)!=closedSet.end())
                {
                    continue;
                }

                u_int novo_g = current.G + 1;
                u_int novo_h = computeHeuristic(pesquisa);
                u_int totalCost = novo_g+novo_h;
                //log n
                set<Node>::iterator successor = openSet.find(pesquisa);
                if (successor == openSet.end() || totalCost < successor->getScore()) // Se não existir ou se o score for menor que o já existe
                {
                    pesquisa.moves.push_back(pair<u_int, char>(i, numToPlay(j)));
                    pesquisa.G = novo_g;
                    pesquisa.H = novo_h;
                    // log n ^ 2
                    queue.push(make_pair(-totalCost,pesquisa));
                    openSet.insert(pesquisa);
                }
            }
        }
    }
    if(this->best_move.size()!=0)
        return true;
    else
        return false;
}

bool AI::greedy()
{
    Node *current = nullptr;
    set<Node *> openSet, closedSet;
    openSet.insert(new Node(this->robot_positions, this->map_char));

    while (!openSet.empty())
    {
        current = *openSet.begin();
        this->expancoes++;
        for (auto node : openSet)
        {
            if (node->getScore() <= current->getScore())
            {

                current = node;
            }
        }
        if (this->checkEndGame(current->robotsCoords))
        {
            break;
        }
        closedSet.insert(current);
        openSet.erase(std::find(openSet.begin(), openSet.end(), current));
        for (u_int i = 0; i < this->robot_positions.size(); ++i)
        {
            for (int j = 0; j < 4; j++)
            {
                pair<u_int, u_int> newCoordinates = getNewCoords(i, j, current);
                vector<vector<char>> new_char_map = current->map_char;
                vector<pair<u_int, u_int>> newRobotCoords = current->robotsCoords;
                this->replacePosition(i, current->robotsCoords[i], newCoordinates, newRobotCoords, new_char_map);
                if (detectCollision(current->robotsCoords[i], newCoordinates) ||
                    findNodeOnList(closedSet, newRobotCoords))
                {
                    continue;
                }

                Node *successor = findNodeOnList(openSet, newRobotCoords);
                if (successor == nullptr)
                {
                    successor = new Node(newRobotCoords, new_char_map, current);
                    successor->move = pair<u_int, char>(i, numToPlay(j));
                    successor->H = computeHeuristic(successor);

                    openSet.insert(successor);
                }
            }
        }
    }
    if (!this->checkEndGame(current->robotsCoords))
    {
        return false;
    }
    while (current != nullptr)
    {
        if (current->move.second != 'f')
        {
            this->best_move.insert(this->best_move.begin(), current->move);
        }
        current = current->parent;
    }
    releaseNodes(openSet);
    releaseNodes(closedSet);

    return true;
}

pair<u_int, u_int> AI::getNewCoords(int robotIndex, int direction, Node *node)
{
    pair<u_int, u_int> newCoords;
    switch (direction)
    {
    case 0:
        newCoords = this->MoveTop(node->map_char, robotIndex, node->robotsCoords);

        break;
    case 1:
        newCoords = this->MoveLeft(node->map_char, robotIndex, node->robotsCoords);

        break;
    case 2:
        newCoords = this->MoveBottom(node->map_char, robotIndex, node->robotsCoords);

        break;
    case 3:
        newCoords = this->MoveRight(node->map_char, robotIndex, node->robotsCoords);

        break;
    }
    return newCoords;
}
pair<u_int, u_int> AI::getNewCoords(int robotIndex, int direction, Node node)
{
    pair<u_int, u_int> newCoords;
    switch (direction)
    {
    case 0:
        newCoords = this->MoveTop(node.map_char, robotIndex, node.robotsCoords);

        break;
    case 1:
        newCoords = this->MoveLeft(node.map_char, robotIndex, node.robotsCoords);

        break;
    case 2:
        newCoords = this->MoveBottom(node.map_char, robotIndex, node.robotsCoords);

        break;
    case 3:
        newCoords = this->MoveRight(node.map_char, robotIndex, node.robotsCoords);

        break;
    }
    return newCoords;
}

pair<u_int, u_int> AI::getNewCoords(vector<vector<char>> map, int robotIndex, int direction, vector<pair<u_int, u_int>> robotsCoords)
{
    pair<u_int, u_int> newCoords;
    switch (direction)
    {
    case 0:
        newCoords = this->MoveTop(map, robotIndex, robotsCoords);
        break;
    case 1:
        newCoords = this->MoveLeft(map, robotIndex, robotsCoords);
        break;
    case 2:
        newCoords = this->MoveBottom(map, robotIndex, robotsCoords);
        break;
    case 3:
        newCoords = this->MoveRight(map, robotIndex, robotsCoords);
        break;
    }
    return newCoords;
}

Node *AI::findNodeOnList(set<Node *> &nodes, vector<pair<u_int, u_int>> robotsCoords)
{
    for (auto node : nodes)
    {
        if (node->robotsCoords == robotsCoords)
        {
            return node;
        }
    }
    return nullptr;
}

void AI::releaseNodes(set<Node *> &nodes)
{
    for (auto it = nodes.begin(); it != nodes.end();)
    {
        delete *it;
        it = nodes.erase(it);
    }
}

bool AI::detectCollision(pair<u_int, u_int> oldCoords, pair<u_int, u_int> newCoords)
{
    if ((oldCoords.first == newCoords.first) && (oldCoords.second == newCoords.second))
    {
        return true;
    }
    return false;
}

char AI::numToPlay(int num)
{
    char play = 's';
    switch (num)
    {
    case 0:
        play = 't';
        break;
    case 1:
        play = 'l';
        break;
    case 2:
        play = 'b';
        break;
    case 3:
        play = 'r';
        break;
    }
    return play;
}

bool AI::bfs()
{
    queue<pair<vector<pair<u_int, u_int>>, vector<pair<u_int, char>>>> myqueue;
    vector<pair<u_int, char>> moves;
    std::map<Info, u_int> visited;
    myqueue.push(make_pair(this->robot_positions, moves));
    u_int profundidade = 1;

    while (!myqueue.empty())
    {
        if (this->checkEndGame(myqueue.front().first))
        {
            this->best_custo = profundidade;
            this->best_move = myqueue.front().second;
            break;
        }

        vector<pair<u_int, u_int>> current_positions = myqueue.front().first;
        Info novo(current_positions);
        visited[novo] = 0;
        vector<pair<u_int, char>> current_moves = myqueue.front().second;
        if (profundidade != myqueue.front().second.size())
        {
            profundidade = myqueue.front().second.size();
            cout << "Depth Level: " << myqueue.front().second.size() << endl;
        }
        myqueue.pop();
        this->expancoes++;

        vector<vector<char>> char_map = this->map->getCharMap(this->level, current_positions);

        for (u_int i = 0; i < current_positions.size(); i++)
        {

            pair<u_int, u_int> position = current_positions[i];

            pair<u_int, u_int> top_move = this->MoveTop(char_map, i, current_positions);
            if (top_move != position && !this->alreadyBeenOn(visited, profundidade, i, top_move, current_positions))
            {
                vector<pair<u_int, u_int>> robot_positions_new = current_positions;
                vector<pair<u_int, char>> current_moves_new = current_moves;
                current_moves_new.push_back(make_pair(i, 't'));
                robot_positions_new[i] = top_move;
                myqueue.push(make_pair(robot_positions_new, current_moves_new));
            }
            pair<u_int, u_int> bottom_move = this->MoveBottom(char_map, i, current_positions);
            if (bottom_move != position && !this->alreadyBeenOn(visited, profundidade, i, bottom_move, current_positions))
            {
                vector<pair<u_int, u_int>> robot_positions_new = current_positions;
                vector<pair<u_int, char>> current_moves_new = current_moves;
                current_moves_new.push_back(make_pair(i, 'b'));
                robot_positions_new[i] = bottom_move;
                myqueue.push(make_pair(robot_positions_new, current_moves_new));
            }
            pair<u_int, u_int> left_move = this->MoveLeft(char_map, i, current_positions);
            if (left_move != position && !this->alreadyBeenOn(visited, profundidade, i, left_move, current_positions))
            {
                vector<pair<u_int, u_int>> robot_positions_new = current_positions;
                vector<pair<u_int, char>> current_moves_new = current_moves;
                current_moves_new.push_back(make_pair(i, 'l'));
                robot_positions_new[i] = left_move;
                myqueue.push(make_pair(robot_positions_new, current_moves_new));
            }
            pair<u_int, u_int> right_move = this->MoveRight(char_map, i, current_positions);
            if (right_move != position && !this->alreadyBeenOn(visited, profundidade, i, right_move, current_positions))
            {
                vector<pair<u_int, u_int>> robot_positions_new = current_positions;
                vector<pair<u_int, char>> current_moves_new = current_moves;
                current_moves_new.push_back(make_pair(i, 'r'));
                robot_positions_new[i] = right_move;
                myqueue.push(make_pair(robot_positions_new, current_moves_new));
            }
        }
    }
    return true;
}

void AI::TranslateToBestMove(Node *node)
{

    this->best_move.clear();

    while (node != nullptr)
    {
        if (node->move.second != 'f')
        {
            this->best_move.insert(this->best_move.begin(), node->move);
        }
        node = node->parent;
    }
}

bool AI::get_best_move()
{
    pair<u_int, char> move = this->best_move[0];
    cout << "Hint: " << this->transformNumberToChar(move.first) << move.second << endl;
    return true;
}

u_int AI::computeHeuristic(Node *node)
{
    switch (heuristic)
    {
    case OPTIMISTIC:
        return optimistic(node);
    case REALISTIC:
        return realistic(node);
    default:
        return realistic(node);
    }
}

void AI::setHeuristic(HEURISTIC h)
{
    heuristic = h;
}

u_int AI::optimistic(Node *node)
{
    vector<pair<u_int, u_int>> targets = this->map->getRobotTargets(this->level);
    u_int h = 0;
    int deltaX, deltaY;
    for (unsigned int i = 0; i < targets.size(); i++)
    {
        deltaX = abs(((int)(node->robotsCoords[i].first)) - ((int)(targets[i].first)));
        deltaY = abs(((int)(node->robotsCoords[i].second)) - ((int)(targets[i].second)));
        if (deltaX != 0)
        {
            h++;
        }
        if (deltaY != 0)
        {
            h++;
        }
    }
    return h;
}

u_int AI::realistic(Node *node)
{
    vector<vector<char>> map = node->map_char;
    bool sameColumn = true;
    bool sameLine = true;
    int start, end, index;
    vector<pair<u_int, u_int>> targets = this->map->getRobotTargets(this->level);
    u_int h = 0;
    int deltaX, deltaY;
    for (unsigned int i = 0; i < targets.size(); i++)
    {
        deltaX = abs(((int)(node->robotsCoords[i].first)) - ((int)(targets[i].first)));
        deltaY = abs(((int)(node->robotsCoords[i].second)) - ((int)(targets[i].second)));
        if (deltaX != 0)
        {
            sameColumn = false;
            h++;
        }
        if (deltaY != 0)
        {
            sameLine = false;
            h++;
        }

        if (sameColumn && !sameLine)
        {

            index = node->robotsCoords[i].first;
            if (node->robotsCoords[i].second < targets[i].second)
            {
                start = node->robotsCoords[i].second;
                end = targets[i].second;
            }
            else
            {
                end = node->robotsCoords[i].second;
                start = targets[i].second;
            }
            while (start < end)
            {
                if (map[start][index] != '.')
                {
                    h+=2;
                    break;
                }
                start++;
            }
        }

        else if (sameLine && !sameColumn)
        {
            index = node->robotsCoords[i].second;

            if (node->robotsCoords[i].first < targets[i].first)
            {
                start = node->robotsCoords[i].first;
                end = targets[i].first;
            }
            else
            {
                end = node->robotsCoords[i].first;
                start = targets[i].first;
            }
            while (start < end)
            {
                if (map[index][start] != '.')
                {
                    h+=2;
                    break;
                }
                start++;
            }
        }

        sameColumn = true;
        sameLine = true;
    }
    return h;
}

u_int AI::computeHeuristic(Node node)
{
    switch (heuristic)
    {
    case OPTIMISTIC:
        return optimistic(node);
    case REALISTIC:
        return realistic(node);
    default:
        return realistic(node);
    }
}

u_int AI::optimistic(Node node)
{
    vector<pair<u_int, u_int>> targets = this->map->getRobotTargets(this->level);
    u_int h = 0;
    int deltaX, deltaY;
    for (unsigned int i = 0; i < targets.size(); i++)
    {
        deltaX = abs(((int)(node.robotsCoords[i].first)) - ((int)(targets[i].first)));
        deltaY = abs(((int)(node.robotsCoords[i].second)) - ((int)(targets[i].second)));
        if (deltaX != 0)
        {
            h++;
        }
        if (deltaY != 0)
        {
            h++;
        }
    }
    return h;
}

u_int AI::realistic(Node node)
{
    vector<vector<char>> map = node.map_char;
    bool sameColumn = true;
    bool sameLine = true;
    int start, end, index;
    vector<pair<u_int, u_int>> targets = this->map->getRobotTargets(this->level);
    u_int h = 0;
    int deltaX, deltaY;
    for (unsigned int i = 0; i < targets.size(); i++)
    {
        deltaX = abs(((int)(node.robotsCoords[i].first)) - ((int)(targets[i].first)));
        deltaY = abs(((int)(node.robotsCoords[i].second)) - ((int)(targets[i].second)));
        if (deltaX != 0)
        {
            sameColumn = false;
            h++;
        }
        if (deltaY != 0)
        {
            sameLine = false;
            h++;
        }

        if (sameColumn && !sameLine)
        {

            index = node.robotsCoords[i].first;
            if (node.robotsCoords[i].second < targets[i].second)
            {
                start = node.robotsCoords[i].second;
                end = targets[i].second;
            }
            else
            {
                end = node.robotsCoords[i].second;
                start = targets[i].second;
            }
            while (start < end)
            {
                if (map[start][index] != '.')
                {
                    h+=2;
                    break;
                }
                start++;
            }
        }

        else if (sameLine && !sameColumn)
        {
            index = node.robotsCoords[i].second;

            if (node.robotsCoords[i].first < targets[i].first)
            {
                start = node.robotsCoords[i].first;
                end = targets[i].first;
            }
            else
            {
                end = node.robotsCoords[i].first;
                start = targets[i].first;
            }
            while (start < end)
            {
                if (map[index][start] != '.')
                {
                    h+=2;
                    break;
                }
                start++;
            }
        }

        sameColumn = true;
        sameLine = true;
    }
    return h;
}