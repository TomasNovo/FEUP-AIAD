#include "Node.h"

using namespace std;

Node::Node(vector<pair<u_int, u_int>> robotsCoords, vector<vector<char>> map_char, Node *parent) : G(0),
                                                                                                   H(0),
                                                                                                   robotsCoords(robotsCoords),
                                                                                                   parent(parent),
                                                                                                   move(pair<u_int, char>(0, 'f')),
                                                                                                   map_char(map_char)
{
}
Node::Node(vector<pair<u_int, u_int>> robotsCoords, vector<vector<char>> map_char,vector<pair<u_int, char>> moves) : G(0),
                                                                                                   H(0),
                                                                                                   robotsCoords(robotsCoords),
                                                                                                   moves(moves),
                                                                                                   map_char(map_char)
{
}

u_int Node::getScore() const
{
    return (G + H);
}

