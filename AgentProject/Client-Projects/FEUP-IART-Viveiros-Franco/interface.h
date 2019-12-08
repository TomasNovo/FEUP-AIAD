#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>
#include "Node.h"

using namespace std;

void info();
int algorithm_menu();
void agent(string map);
void options();
void agent_menu();
void play_menu();
Node* play_loop(Node* rootNode);
int play(string map);
int menu();
void flashingAnimation(Node* node);
void walkingAnimation(Node* node1, Node* node2);
void printPath(Node* node);
void printMap(Node* node);
void printPath2(Node* node);
void printPath3(Node* node);


#endif