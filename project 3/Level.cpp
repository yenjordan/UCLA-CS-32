#include "Level.h"
#include "Weapon.h"
#include "Scroll.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

Level::Level(int currentLevel) : currentLevel(currentLevel) {
    srand(time(nullptr));
    generateLevel();
}

Level::~Level() {
    for (Monster* monster : monsters) {
        delete monster;
    }
    for (GameObject* object : gameObjects) {
        delete object;
    }
}

void Level::generateLevel() {
    level.assign(LEVEL_HEIGHT, vector<char>(LEVEL_WIDTH, '#'));
    originalLevel.assign(LEVEL_HEIGHT, vector<char>(LEVEL_WIDTH, '#')); // Initialize originalLevel

    vector<Room> rooms;
    generateRooms(5, rooms);

    if (currentLevel < 4) {
        int stairRoomIndex = rand() % rooms.size();
        stairY = rooms[stairRoomIndex].y + rand() % rooms[stairRoomIndex].height;
        stairX = rooms[stairRoomIndex].x + rand() % rooms[stairRoomIndex].width;
        level[stairY][stairX] = '>';
        originalLevel[stairY][stairX] = '>'; // Store in originalLevel
    }

    int playerRoomIndex = rand() % rooms.size();
    playerX = rooms[playerRoomIndex].x + rand() % rooms[playerRoomIndex].width;
    playerY = rooms[playerRoomIndex].y + rand() % rooms[playerRoomIndex].height;
    level[playerY][playerX] = '@';
    originalLevel[playerY][playerX] = ' '; // Store player's initial position as empty in originalLevel

    generateCorridors(rooms);

    int numMonsters = randInt(2, 5 * (currentLevel + 1) + 1);
    placeMonsters(numMonsters);

    int numObjects = randInt(2, 3);
    placeGameObjects(numObjects);
}

void Level::moveMonster(Monster* monster, int newX, int newY) {
    int oldX = monster->getX();
    int oldY = monster->getY();
    
    // Restore the original character at the old position
    level[oldY][oldX] = originalLevel[oldY][oldX];
    
    // Save the character at the new position before placing the monster
    originalLevel[newY][newX] = level[newY][newX];
    
    // Move the monster to the new position
    monster->setPosition(newX, newY);
    level[newY][newX] = monster->getSymbol();
}


void Level::generateRooms(int numRooms, vector<Room>& rooms) {
    for (int i = 0; i < numRooms; ++i) {
        int width = rand() % 6 + 4;
        int height = rand() % 6 + 4;
        int x = rand() % (LEVEL_WIDTH - width - 2) + 1;
        int y = rand() % (LEVEL_HEIGHT - height - 2) + 1;

        Room room = {x, y, width, height};

        if (canPlaceRoom(room)) {
            placeRoom(room);
            rooms.push_back(room);
        }
    }
}

bool Level::canPlaceRoom(const Room& room) const {
    for (int row = room.y; row < room.y + room.height; ++row) {
        for (int col = room.x; col < room.x + room.width; ++col) {
            if (row < 0 || row >= LEVEL_HEIGHT || col < 0 || col >= LEVEL_WIDTH || level[row][col] != '#') {
                return false;
            }
        }
    }
    return true;
}

void Level::placeRoom(const Room& room) {
    for (int row = room.y; row < room.y + room.height; ++row) {
        for (int col = room.x; col < room.x + room.width; ++col) {
            level[row][col] = ' ';
            originalLevel[row][col] = ' '; // Update originalLevel
        }
    }
}

void Level::generateCorridors(const vector<Room>& rooms) {
    for (size_t i = 0; i < rooms.size() - 1; ++i) {
        int startX = rooms[i].x + rooms[i].width / 2;
        int startY = rooms[i].y + rooms[i].height / 2;
        int endX = rooms[i + 1].x + rooms[i + 1].width / 2;
        int endY = rooms[i + 1].y + rooms[i + 1].height / 2;

        for (int x = min(startX, endX); x <= max(startX, endX); ++x) {
            level[startY][x] = ' ';
            originalLevel[startY][x] = ' '; // Update originalLevel
        }

        for (int y = min(startY, endY); y <= max(startY, endY); ++y) {
            level[y][endX] = ' ';
            originalLevel[y][endX] = ' '; // Update originalLevel
        }
    }
}

void Level::placeMonsters(int numMonsters) {
    for (Monster* monster : monsters) {
        delete monster;
    }
    monsters.clear();

    while (numMonsters > 0) {
        int x = rand() % LEVEL_WIDTH;
        int y = rand() % LEVEL_HEIGHT;
        if (level[y][x] == ' ') {
            Monster* monster = nullptr;
            int currentLevel = getCurrentLevel();

            if (currentLevel >= 3) {
                switch (rand() % 4) {
                    case 0: monster = new Bogeyman(x, y); break;
                    case 1: monster = new Dragon(x, y); break;
                    case 2: monster = new Goblin(x, y); break;
                    case 3: monster = new Snakewoman(x, y); break;
                }
            } else if (currentLevel == 2) {
                switch (rand() % 3) {
                    case 0: monster = new Bogeyman(x, y); break;
                    case 1: monster = new Goblin(x, y); break;
                    case 2: monster = new Snakewoman(x, y); break;
                }
            } else {
                switch (rand() % 2) {
                    case 0: monster = new Goblin(x, y); break;
                    case 1: monster = new Snakewoman(x, y); break;
                }
            }

            if (monster != nullptr) {
                monsters.push_back(monster);
                level[y][x] = monster->getSymbol();
                originalLevel[y][x] = ' '; // Store original character in originalLevel
                numMonsters--;
            }
        }
    }
}

void Level::placeGameObjects(int numObjects) {
    for (GameObject* object : gameObjects) {
        delete object;
    }
    gameObjects.clear();

    if (currentLevel >= 4) {
        int idolX, idolY;
        while (true) {
            idolX = rand() % LEVEL_WIDTH;
            idolY = rand() % LEVEL_HEIGHT;
            if (level[idolY][idolX] == ' ') {
                level[idolY][idolX] = '&';
                originalLevel[idolY][idolX] = '&'; // Store in originalLevel
                GameObject* idol = new GameObject(idolX, idolY, '&', "golden idol");
                gameObjects.push_back(idol);
                break;
            }
        }
    }

    while (numObjects > 0) {
        int x = rand() % LEVEL_WIDTH;
        int y = rand() % LEVEL_HEIGHT;
        if (level[y][x] == ' ') {
            GameObject* object = nullptr;
            if (rand() % 2 == 0) {
                switch (rand() % 3) { // Reduced the number of possible weapons
                    case 0: object = new Weapon(x, y, "mace", "swings mace", 0, 2); break;
                    case 1: object = new Weapon(x, y, "short sword", "slashes short sword", 0, 2); break;
                    case 2: object = new Weapon(x, y, "long sword", "slashes long sword", 2, 4); break;
                    // Removed magic axe and magic fangs of sleep
                }
                level[y][x] = ')';
                originalLevel[y][x] = ')'; // Store in originalLevel
            } else {
                switch (rand() % 4) { // Reduced the number of possible scrolls
                    case 0: object = new Scroll(x, y, "scroll of improve armor", Scroll::IMPROVE_ARMOR); break;
                    case 1: object = new Scroll(x, y, "scroll of raise strength", Scroll::RAISE_STRENGTH); break;
                    case 2: object = new Scroll(x, y, "scroll of enhance health", Scroll::ENHANCE_HEALTH); break;
                    case 3: object = new Scroll(x, y, "scroll of enhance dexterity", Scroll::ENHANCE_DEXTERITY); break;
                    // Removed scroll of teleportation
                }
                level[y][x] = '?';
                originalLevel[y][x] = '?'; // Store in originalLevel
            }
            gameObjects.push_back(object);
            numObjects--;
        }
    }
}


bool Level::isWalkable(int x, int y) const {
    return x >= 0 && x < LEVEL_WIDTH && y >= 0 && y < LEVEL_HEIGHT && (level[y][x] == ' ' || level[y][x] == '>' || level[y][x] == '&' || level[y][x] == ')' || level[y][x] == '?');
}

void Level::movePlayer(int newX, int newY) {
    bool objectFound = false;

    if (playerX == stairX && playerY == stairY) {
        level[playerY][playerX] = currentLevel < 4 ? '>' : '&';
    } else {
        for (auto* object : gameObjects) {
            if (object->getX() == playerX && object->getY() == playerY) {
                level[playerY][playerX] = object->getSymbol();
                objectFound = true;
                break;
            }
        }
        if (!objectFound) {
            level[playerY][playerX] = ' ';
        }
    }

    playerX = newX;
    playerY = newY;
    level[playerY][playerX] = '@';
}

int Level::getPlayerX() const {
    return playerX;
}

int Level::getPlayerY() const {
    return playerY;
}

int Level::getStairX() const {
    return stairX;
}

int Level::getStairY() const {
    return stairY;
}

int Level::getCurrentLevel() const {
    return currentLevel;
}

void Level::advanceLevel() {
    for (Monster* monster : monsters) {
        delete monster;
    }
    monsters.clear();
    
    for (GameObject* object : gameObjects) {
        delete object;
    }
    gameObjects.clear();

    currentLevel++;
    generateLevel();
}


Monster* Level::getMonsterAt(int x, int y) const {
    for (Monster* monster : monsters) {
        if (monster->getX() == x && monster->getY() == y) {
            return monster;
        }
    }
    return nullptr;
}

void Level::removeMonster(Monster* monster) {
    int x = monster->getX();
    int y = monster->getY();

    auto it = std::find(monsters.begin(), monsters.end(), monster);
    if (it != monsters.end()) {
        // Restore original character in the level grid
        level[y][x] = originalLevel[y][x];

        // Determine the type of monster and handle the drops
        if (dynamic_cast<Bogeyman*>(monster)) {
            if (randInt(1, 10) == 1) {
                placeItemAt(x, y, new Weapon(x, y, "magic axe", "swings magic axe", 5, 5));
            }
        } else if (dynamic_cast<Snakewoman*>(monster)) {
            if (randInt(1, 3) == 1) {
                placeItemAt(x, y, new Weapon(x, y, "magic fangs of sleep", "bites with magic fangs", 3, 2));
            }
        } else if (dynamic_cast<Dragon*>(monster)) {
            Scroll::ScrollType scrollType = static_cast<Scroll::ScrollType>(randInt(0, 4));
            std::string scrollName;
            switch (scrollType) {
                case Scroll::TELEPORTATION: scrollName = "scroll of teleportation"; break;
                case Scroll::IMPROVE_ARMOR: scrollName = "scroll of improve armor"; break;
                case Scroll::RAISE_STRENGTH: scrollName = "scroll of raise strength"; break;
                case Scroll::ENHANCE_HEALTH: scrollName = "scroll of enhance health"; break;
                case Scroll::ENHANCE_DEXTERITY: scrollName = "scroll of enhance dexterity"; break;
            }
            placeItemAt(x, y, new Scroll(x, y, scrollName, scrollType));
        } else if (dynamic_cast<Goblin*>(monster)) {
            if (randInt(1, 3) == 1) {
                if (randInt(1, 2) == 1) {
                    placeItemAt(x, y, new Weapon(x, y, "magic axe", "swings magic axe", 5, 5));
                } else {
                    placeItemAt(x, y, new Weapon(x, y, "magic fangs of sleep", "bites with magic fangs", 3, 2));
                }
            }
        }

        delete *it; // Free the memory
        monsters.erase(it); // Remove the pointer from the vector
    }
}


void Level::removeObjectAt(int x, int y) {
    for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
        if ((*it)->getX() == x && (*it)->getY() == y) {
            gameObjects.erase(it); // Remove from the level, but do not delete as it's now in the player's inventory
            return;
        }
    }
}


GameObject* Level::getObjectAt(int x, int y) const {
    for (GameObject* object : gameObjects) {
        if (object->getX() == x && object->getY() == y) {
            return object;
        }
    }
    return nullptr;
}

bool Level::canSmellPlayer(int x, int y, int steps) const {
    int playerX = getPlayerX();
    int playerY = getPlayerY();
    int distance = abs(playerX - x) + abs(playerY - y);
    return distance <= steps;
}

void Level::printLevel(int levelNumber, int playerHP, int playerArmor, int playerStrength, int playerDexterity) const {
    clearScreen();
    for (int row = 0; row < LEVEL_HEIGHT; ++row) {
        for (int col = 0; col < LEVEL_WIDTH; ++col) {
            cout << level[row][col];
        }
        cout << endl;
    }

    cout << "Level: " << getCurrentLevel() << ", ";
    cout << "Hit points: " << playerHP << ", ";
    cout << "Armor: " << playerArmor << ", ";
    cout << "Strength: " << playerStrength << ", ";
    cout << "Dexterity: " << playerDexterity << endl;
}

void Level::placeItemAt(int x, int y, GameObject* item) {
    if (level[y][x] == ' ') { // Ensure the position is empty
        gameObjects.push_back(item);
        level[y][x] = item->getSymbol();
        originalLevel[y][x] = item->getSymbol(); // Update original level
    } else {
        delete item; // If position is not empty, delete the item
    }
}