#ifndef LEVEL_INCLUDED
#define LEVEL_INCLUDED

#include <vector>
#include <string>
#include "GameObject.h"
#include "Monster.h"
#include "utilities.h"
using namespace std;

class Player;

struct Room {
    int x, y;
    int width, height;
};

class Level {
public:
    static const int LEVEL_HEIGHT = 18;
    static const int LEVEL_WIDTH = 70;
    
    Level(int currentLevel);
    ~Level();
    void generateLevel();
void printLevel(int levelNumber, int playerHP, int playerArmor, int playerStrength, int playerDexterity) const;    bool isWalkable(int x, int y) const;
    void movePlayer(int newX, int newY);
    int getPlayerX() const;
    int getPlayerY() const;
    int getStairX() const;
    int getStairY() const;
    int getCurrentLevel() const;
    void advanceLevel();

    Monster* getMonsterAt(int x, int y) const;
    void removeMonster(Monster* monster);

    GameObject* getObjectAt(int x, int y) const;
    void removeObjectAt(int x, int y);

    bool canSmellPlayer(int x, int y, int steps) const;

    void moveMonster(Monster* monster, int newX, int newY);

    vector<Monster*> monsters;
    vector<GameObject*> gameObjects;

    void placeItemAt(int x, int y, GameObject* item);

private:
    void generateRooms(int numRooms, vector<Room> &rooms);
    void generateCorridors(const vector<Room> &rooms);
    void placeMonsters(int numMonsters);
    void placeGameObjects(int numObjects);
    bool canPlaceRoom(const Room &room) const;
    void placeRoom(const Room &room);

    int currentLevel;
    int playerX, playerY;
    int stairX, stairY;
    vector<vector<char> > level;
    vector<vector<char> > originalLevel; // Add this to store original characters
};

#endif // LEVEL_INCLUDED
