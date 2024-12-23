// Game.cpp

#include "Game.h"
#include "utilities.h"
#include <iostream>
using namespace std;

Game::Game(int goblinSmellDistance) : currentLevel(0) {
    level = new Level(currentLevel);
    player = new Player(level);
}

void Game::play() {
    bool displayInventoryFlag = false;
    bool needRedisplay = true;

    while (true) {
        if (!displayInventoryFlag && needRedisplay) {
            clearScreen();
            level->printLevel(
                currentLevel,
                player->getHitPoints(),
                player->getArmorPoints(),
                player->getStrengthPoints(),
                player->getDexterityPoints()
            );
            if (!statusMessages.empty()) {
                for (const auto& message : statusMessages) {
                    std::cout << "\n" << message << "\n";
                }
                statusMessages.clear(); // Clear the status messages after displaying them
            }
            needRedisplay = false;
        }

        player->handleInput(displayInventoryFlag, needRedisplay, statusMessages);

        if (!player->isAlive()) { // Check if the player is alive
            exit(0); // Exit the game
        }

        if (!displayInventoryFlag) {
            for (auto* monster : level->monsters) {
                if (monster->isAlive()) {
                    int playerX = player->getX();
                    int playerY = player->getY();
                    int monsterX = monster->getX();
                    int monsterY = monster->getY();

                    if (abs(monsterX - playerX) <= 1 && abs(monsterY - playerY) <= 1) {
                        monster->attackPlayer(player, statusMessages);
                    } else {
                        monster->move(level, player, statusMessages);
                    }
                }
            }
        }

        if (!displayInventoryFlag) {
            needRedisplay = true;
        }
    }
}





Game::~Game() {
    delete level;
    delete player;
}
