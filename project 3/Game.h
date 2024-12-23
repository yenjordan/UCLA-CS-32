#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Level.h"
#include "Player.h"
#include <string>

#include <vector>

class Game
{
public:
    Game(int goblinSmellDistance);
    ~Game();
    void play();

private:
    int currentLevel;
    Level* level;
    Player* player;
    std::vector<std::string> statusMessages;  // Store multiple status messages
};



#endif // GAME_INCLUDED
