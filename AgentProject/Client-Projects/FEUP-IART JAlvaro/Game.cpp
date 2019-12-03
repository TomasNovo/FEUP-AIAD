#include "Game.h"
#include "Node.h"

using namespace std;

Game::Game(string file)
{
    this->map = new Map(file);
}

void Game::loop()
{
    cin.ignore(256, '\n');
    while (this->player->makeMove())
    {
        if (this->player->checkEndGame())
            return;
    }
}


void Game::menu()
{
    string read;
    while (true)
    {
        clearScreen();

        int playerChoice, levelChoice = -1, algorithmChoice, heuristicChoice;

        cout << "  _____       _           _     _           _                _       _   _     " << endl;
        cout << " |  __ \\     | |         | |   | |         | |              (_)     | | | |    " << endl;
        cout << " | |__) |___ | |__   ___ | |_  | |     __ _| |__  _   _ _ __ _ _ __ | |_| |__  " << endl;
        cout << " |  _  // _ \\| '_ \\ / _ \\| __| | |    / _` | '_ \\| | | | '__| | '_ \\| __| '_ \\ " << endl;
        cout << " | | \\ \\ (_) | |_) | (_) | |_  | |___| (_| | |_) | |_| | |  | | | | | |_| | | |" << endl;
        cout << " |_|  \\_\\___/|_.__/ \\___/ \\__| |______\\__,_|_.__/ \\__, |_|  |_|_| |_|\\__|_| |_|" << endl;
        cout << "                                                   __/ |                       " << endl;
        cout << "                                                  |___/                       " << endl;
        do
        {
        cout << "Choose the game mode:" << endl;
        cout << "1 - Human" << endl;
        cout << "2 - PC" << endl;
        cout << "0 - Exit" << endl;
        cout << endl << "Game Mode: ";
            cin >> read;
        } while (!is_number(read));
        playerChoice = stoi(read);

        if (playerChoice == 0)
            return;
        else if (playerChoice == 1)
        {
            player = new Human(this->levelChoose() - 1, this->map);
            this->loop();

            cout << "Press ENTER to continue" << endl;

            cin.get();
        }
        else if (playerChoice == 2)
        {
            levelChoice = this->levelChoose();

            do
            {
            cout << "Choose the algorithm:" << endl;
            cout << "0 - Depth-First Search" << endl;
            cout << "1 - Breadth-First Search" << endl;
            cout << "2 - A* (A-Star)" << endl;
            cout << "3 - Iterative Deepening Depth-First Search" << endl;
            cout << "4 - Greedy Algorithm" << endl;
            cout << "Algorithm: ";
                cin >> read;
            } while (!is_number(read));
            algorithmChoice = stoi(read);
            if(algorithmChoice == 2){
                cout << endl;
                cout << "Choose the heristic" << endl;
                cout << "0 - Optimistic" << endl;
                cout << "1 - Realistic" << endl;
                cout << endl << "Heuristic: ";
                cin >> heuristicChoice;
                AI::setHeuristic((HEURISTIC)heuristicChoice);
            }
            player = new AI(levelChoice - 1, this->map, algorithmChoice);
            this->loop();

            cout << "Press ENTER to continue" << endl;

            cin.get();
        }
        else
        {
            continue;
        }
    }
}

int Game::levelChoose()
{
    int levelChoice = 0;
    string read;
    while (!(levelChoice > 0 && levelChoice <= (int)this->map->getMapNumber()))
    {
        do
        {
            cout << "There are " << this->map->getMapNumber() << " levels available" << endl;
            cout << "Choose the level (int):";
            cin >> read;
        } while (!is_number(read));
        levelChoice = stoi(read);
    }
    return levelChoice;
}