#ifndef PLAYER_H
#define PLAYER_H

#include "Actor.h"
#include "Level.h"
#include "Weapon.h"
#include <vector>
#include <string>

class Player : public Actor {
public:
    Player(Level* level);
    void handleInput(bool& displayInventoryFlag, bool& needRedisplay, std::vector<std::string>& statusMessages);
    void move(char direction, std::vector<std::string>& statusMessages);
    void displayInventory() const;
    void addItem(GameObject* item);
    void pickUpObject(bool& needRedisplay, std::vector<std::string>& statusMessages);

    void setMaxHitPoints(int maxHP);
    void setStrengthPoints(int sp);
    bool isAlive() const; // Check if the player is alive

private:
    std::string attackMonster(Monster* monster, std::vector<std::string>& statusMessages);
    void wieldWeapon(bool& needRedisplay, std::vector<std::string>& statusMessages);
    void readScroll(bool& needRedisplay, std::vector<std::string>& statusMessages);

    Level* m_level; 
    Weapon* m_weapon; 
    std::vector<GameObject*> m_inventory;
    int m_maxHitPoints;

    void handleTeleportation();
    void handleImproveArmor();
    void handleRaiseStrength();
    void handleEnhanceHealth();
    void handleEnhanceDexterity();
};



#endif
