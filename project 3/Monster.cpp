#include "Monster.h"
#include "Weapon.h"
#include "Player.h"
#include "Level.h"
#include <cstdlib>
#include <queue>
#include <algorithm>
#include <vector>
#include <climits>
#include <iostream>
using namespace std;

Monster::Monster(int x, int y, char symbol)
    : Actor(x, y, 0, 0, 0, 0, 0, symbol), m_weapon(nullptr) {}

Monster::~Monster() {
    delete m_weapon; // Ensure proper cleanup
}

Weapon* Monster::getWeapon() const {
    return m_weapon;
}

void Monster::attackPlayer(Player* player, std::vector<std::string>& statusMessages) {
    if (player && isAlive()) {
        std::string attackMessage = attack(player, m_weapon, getName());
        statusMessages.push_back(attackMessage);
    }
}

std::string Bogeyman::getName() const {
    return "Bogeyman";
}

std::string Dragon::getName() const {
    return "Dragon";
}

std::string Goblin::getName() const {
    return "Goblin";
}

std::string Snakewoman::getName() const {
    return "Snakewoman";
}

void Monster::move(Level* level, Player* player, std::vector<std::string>& statusMessages) {
    // Default behavior for monsters
}

// In Bogeyman.cpp
Bogeyman::Bogeyman(int x, int y)
    : Monster(x, y, 'B') {
    // Set Bogeyman attributes
    setHitPoints(rand() % 6 + 5); // Random integer from 5 to 10
    setStrengthPoints(rand() % 2 + 2); // Random integer from 2 to 3
    setDexterityPoints(rand() % 2 + 2); // Random integer from 2 to 3
    setArmorPoints(2);
    m_weapon = new Weapon(x, y, "short sword", "slashes short sword", 0, 2);
}

// In Dragon.cpp
Dragon::Dragon(int x, int y)
    : Monster(x, y, 'D') {
    // Set Dragon attributes
    setHitPoints(rand() % 6 + 20); // Random integer from 20 to 25
    setStrengthPoints(4);
    setDexterityPoints(4);
    setArmorPoints(4);
    m_weapon = new Weapon(x, y, "long sword", "swings long sword", 2, 4);
}

// In Goblin.cpp
Goblin::Goblin(int x, int y)
    : Monster(x, y, 'G') {
    // Set Goblin attributes
    setHitPoints(rand() % 6 + 15); // Random integer from 15 to 20
    setStrengthPoints(3);
    setDexterityPoints(1);
    setArmorPoints(1);
    m_weapon = new Weapon(x, y, "short sword", "slashes short sword", 0, 2);
}

// In Snakewoman.cpp
Snakewoman::Snakewoman(int x, int y)
    : Monster(x, y, 'S') {
    // Set Snakewoman attributes
    setHitPoints(rand() % 4 + 3); // Random integer from 3 to 6
    setStrengthPoints(2);
    setDexterityPoints(3);
    setArmorPoints(3);
    m_weapon = new Weapon(x, y, "magic fangs of sleep", "strikes magic fangs", 3, 2);
}

void Bogeyman::move(Level* level, Player* player, std::vector<std::string>& statusMessages) {
    int playerX = level->getPlayerX();
    int playerY = level->getPlayerY();
    int currentX = getX();
    int currentY = getY();

    if (!level->canSmellPlayer(currentX, currentY, 5)) {
        return;
    }

    int deltaX = playerX - currentX;
    int deltaY = playerY - currentY;

    int newX = currentX;
    int newY = currentY;

    if (abs(deltaX) > abs(deltaY)) {
        if (deltaX > 0 && level->isWalkable(currentX + 1, currentY)) {
            newX = currentX + 1;
        } else if (deltaX < 0 && level->isWalkable(currentX - 1, currentY)) {
            newX = currentX - 1;
        }
    } else {
        if (deltaY > 0 && level->isWalkable(currentX, currentY + 1)) {
            newY = currentY + 1;
        } else if (deltaY < 0 && level->isWalkable(currentX, currentY - 1)) {
            newY = currentY - 1;
        }
    }

    if (abs(newX - playerX) <= 1 && abs(newY - playerY) <= 1) {
        attackPlayer(player, statusMessages);
    } else {
        level->moveMonster(this, newX, newY);
    }
}

bool dfs(Level* level, int x, int y, int targetX, int targetY, int steps, std::vector<std::vector<bool>>& visited) {
    // Base cases
    if (steps < 0) return false;
    if (x == targetX && y == targetY) return true;
    if (visited[y][x]) return false;

    visited[y][x] = true;

    // Directions: right, down, left, up
    std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    for (const auto& dir : directions) {
        int newX = x + dir.first;
        int newY = y + dir.second;

        if (level->isWalkable(newX, newY) && dfs(level, newX, newY, targetX, targetY, steps - 1, visited)) {
            return true;
        }
    }

    return false;
}

// Function to determine the optimal move
std::pair<int, int> findOptimalMove(Level* level, int x, int y, int targetX, int targetY, int steps, std::vector<std::vector<bool>>& visited) {
    std::pair<int, int> bestMove = {x, y};
    int minDist = steps + 1;

    // Directions: right, down, left, up
    std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    for (const auto& dir : directions) {
        int newX = x + dir.first;
        int newY = y + dir.second;

        if (level->isWalkable(newX, newY)) {
            std::fill(visited.begin(), visited.end(), std::vector<bool>(Level::LEVEL_WIDTH, false)); // Reset visited
            if (dfs(level, newX, newY, targetX, targetY, steps - 1, visited)) {
                int distance = abs(newX - targetX) + abs(newY - targetY);
                if (distance < minDist) {
                    minDist = distance;
                    bestMove = {newX, newY};
                }
            }
        }
    }

    return bestMove;
}

void Goblin::move(Level* level, Player* player, std::vector<std::string>& statusMessages) {
    int startX = getX();
    int startY = getY();
    int playerX = player->getX();
    int playerY = player->getY();
    int goblinSmellDistance = 15; // Or use the parameter from the Game constructor

    std::vector<std::vector<bool>> visited(Level::LEVEL_HEIGHT, std::vector<bool>(Level::LEVEL_WIDTH, false));
    if (dfs(level, startX, startY, playerX, playerY, goblinSmellDistance, visited)) {
        std::pair<int, int> nextMove = findOptimalMove(level, startX, startY, playerX, playerY, goblinSmellDistance, visited);
        if (nextMove != std::make_pair(startX, startY)) {
            level->moveMonster(this, nextMove.first, nextMove.second);
        }
    }
}

void Snakewoman::move(Level* level, Player* player, std::vector<std::string>& statusMessages) {
    int playerX = level->getPlayerX();
    int playerY = level->getPlayerY();
    int currentX = getX();
    int currentY = getY();

    if (!level->canSmellPlayer(currentX, currentY, 3)) {
        return;
    }

    int deltaX = playerX - currentX;
    int deltaY = playerY - currentY;

    int newX = currentX;
    int newY = currentY;

    if (abs(deltaX) > abs(deltaY)) {
        if (deltaX > 0 && level->isWalkable(currentX + 1, currentY)) {
            newX = currentX + 1;
        } else if (deltaX < 0 && level->isWalkable(currentX - 1, currentY)) {
            newX = currentX - 1;
        }
    } else {
        if (deltaY > 0 && level->isWalkable(currentX, currentY + 1)) {
            newY = currentY + 1;
        } else if (deltaY < 0 && level->isWalkable(currentX, currentY - 1)) {
            newY = currentY - 1;
        }
    }

    if (abs(newX - playerX) <= 1 && abs(newY - playerY) <= 1) {
        attackPlayer(player, statusMessages);
    } else {
        level->moveMonster(this, newX, newY);
    }
}