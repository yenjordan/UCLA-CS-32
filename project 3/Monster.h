#ifndef MONSTER_H
#define MONSTER_H

#include "Actor.h"
#include <string>
#include <vector>
#include <utility>

class Player;
class Weapon;
class Level;

class Monster : public Actor {
public:
    Monster(int x, int y, char symbol);
    virtual ~Monster(); // Declare the virtual destructor

    void attackPlayer(Player* player, std::vector<std::string>& statusMessages);
    virtual void move(Level* level, Player* player, std::vector<std::string>& statusMessages); // Add statusMessages parameter
    virtual std::string getName() const = 0; // Add pure virtual getName method
    Weapon* getWeapon() const;

protected:
    Weapon* m_weapon;
};

class Bogeyman : public Monster {
public:
    Bogeyman(int x, int y);
    void move(Level* level, Player* player, std::vector<std::string>& statusMessages) override; // Override move method
    std::string getName() const override; // Override getName
};

class Dragon : public Monster {
public:
    Dragon(int x, int y);
    std::string getName() const override; // Override getName
};

class Goblin : public Monster {
public:
    Goblin(int x, int y);
    void move(Level* level, Player* player, std::vector<std::string>& statusMessages) override; // Override move method
    std::string getName() const override; // Override getName
};

class Snakewoman : public Monster {
public:
    Snakewoman(int x, int y);
    void move(Level* level, Player* player, std::vector<std::string>& statusMessages) override; // Override move method
    std::string getName() const override; // Override getName
};

#endif // MONSTER_H
