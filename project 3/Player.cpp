#include "Player.h"
#include "Monster.h"
#include "Level.h"
#include "Weapon.h"
#include "Scroll.h"
#include "utilities.h"
#include <cstdlib>
#include <iostream>

Player::Player(Level* level)
    : Actor(level->getPlayerX(), level->getPlayerY(), 20, 2, 2, 2, 0, '@'), m_level(level), m_maxHitPoints(20) {
    // Initially equipped with a short sword
    m_weapon = new Weapon(0, 0, "short sword", "slashes short sword", 0, 2);
    m_inventory.push_back(m_weapon); // Add the initial weapon to the inventory
}


std::string Player::attackMonster(Monster* monster, std::vector<std::string>& statusMessages) {
    if (monster && isAlive() && monster->isAlive()) {
        std::string attackMessage = attack(monster, m_weapon, "Player");
        if (!monster->isAlive()) {
            m_level->removeMonster(monster); // Use m_level pointer
            monster = nullptr; // Set monster to nullptr after deletion
        }
        statusMessages.push_back(attackMessage);
    }
    return "";
}


void Player::handleInput(bool& displayInventoryFlag, bool& needRedisplay, std::vector<std::string>& statusMessages) {
    char ch = getCharacter();
    switch (ch) {
        case ARROW_LEFT:
        case ARROW_RIGHT:
        case ARROW_UP:
        case ARROW_DOWN:
            move(ch, statusMessages);
            needRedisplay = true;
            break;
        case 'q':
            exit(0);
        case '>':
            if (m_level->getPlayerX() == m_level->getStairX() && m_level->getPlayerY() == m_level->getStairY() && m_level->getCurrentLevel() < 4) {
                m_level->advanceLevel();
                needRedisplay = true;
            }
            break;
        case 'g':
            pickUpObject(needRedisplay, statusMessages);
            needRedisplay = true;
            break;
        case 'i':
            displayInventoryFlag = !displayInventoryFlag;
            if (displayInventoryFlag) {
                displayInventory();
                needRedisplay = false;
            } else {
                needRedisplay = true;
            }
            break;
        case 'w':
            wieldWeapon(needRedisplay, statusMessages);
            needRedisplay = true;
            break;
        case 'r':
            readScroll(needRedisplay, statusMessages);
            needRedisplay = true;
            break;
        case 'c': // New case to set strength and maximum hit points
            setStrengthPoints(9);
            setMaxHitPoints(50);
            needRedisplay = true;
            break;
        default:
            break;
    }
}




void Player::move(char direction, std::vector<std::string>& statusMessages) {
    int newX = m_level->getPlayerX(), newY = m_level->getPlayerY();
    switch (direction) {
    case ARROW_LEFT:
        newX -= 1;
        break;
    case ARROW_RIGHT:
        newX += 1;
        break;
    case ARROW_UP:
        newY -= 1;
        break;
    case ARROW_DOWN:
        newY += 1;
        break;
    }

    if (m_level->isWalkable(newX, newY)) {
        m_level->movePlayer(newX, newY);
    } else {
        Monster* monster = m_level->getMonsterAt(newX, newY);
        if (monster) {
            std::string attackMessage = attackMonster(monster, statusMessages);
            if (!attackMessage.empty()) {
                statusMessages.push_back(attackMessage);
            }
            // Ensure the monster is not accessed after attackMonster call
            monster = nullptr;
        }
    }
}


void Player::pickUpObject(bool& needRedisplay, std::vector<std::string>& statusMessages) {
    GameObject* object = m_level->getObjectAt(m_level->getPlayerX(), m_level->getPlayerY());
    if (object) {
        if (object->getSymbol() == '&') {
            std::cout << "\nYou pick up the golden idol" << std::endl;
            std::cout << "Congratulations, you won!" << std::endl;
            std::cout << "Press q to exit game." << std::endl;
            char ch;
            std::cin >> ch;
            if (ch == 'q')
                exit(0);
        } else {
            // Add object to inventory before removing it from the level
            addItem(object);
            statusMessages.push_back("You pick up " + object->getName());
            m_level->removeObjectAt(m_level->getPlayerX(), m_level->getPlayerY());
            needRedisplay = true;
        }
    }
}


void Player::displayInventory() const {
    clearScreen();
    std::cout << "\nInventory:\n";
    char label = 'a';
    for (const auto& item : m_inventory) {
        std::cout << "  " << label++ << ". " << item->getName() << "\n";
    }
}


void Player::addItem(GameObject* item) {
    if (m_inventory.size() < 26) { // a-z is 26 items
        m_inventory.push_back(item);
    } else {
        std::cout << "Your inventory is full!\n";
    }
}


void Player::wieldWeapon(bool& needRedisplay, std::vector<std::string>& statusMessages) {
    displayInventory();
    char choice;
    std::cin >> choice;

    if (choice >= 'a' && choice <= 'z') {
        int index = choice - 'a';
        if (index < m_inventory.size() && dynamic_cast<Weapon*>(m_inventory[index])) {
            m_weapon = dynamic_cast<Weapon*>(m_inventory[index]);
            statusMessages.push_back("You are wielding " + m_weapon->getName());
        } else if (index < m_inventory.size()) {
            statusMessages.push_back("You can't wield a " + m_inventory[index]->getName());
        } else {
            needRedisplay = true;
            return;
        }
    } else {
        needRedisplay = true;
        return;
    }
    needRedisplay = true;
}

void Player::readScroll(bool& needRedisplay, std::vector<std::string>& statusMessages) {
    displayInventory();
    char choice;
    std::cin >> choice;

    if (choice >= 'a' && choice <= 'z') {
        int index = choice - 'a';
        if (index < m_inventory.size() && dynamic_cast<Scroll*>(m_inventory[index])) {
            Scroll* scroll = dynamic_cast<Scroll*>(m_inventory[index]);
            switch (scroll->getScrollType()) {
                case Scroll::TELEPORTATION:
                    statusMessages.push_back("You read the scroll called " + scroll->getName() + "\nYou feel your body wrenched in space and time.");
                    handleTeleportation();
                    break;
                case Scroll::IMPROVE_ARMOR:
                    statusMessages.push_back("You read the scroll called " + scroll->getName() + "\nYour armor glows blue.");
                    handleImproveArmor();
                    break;
                case Scroll::RAISE_STRENGTH:
                    statusMessages.push_back("You read the scroll called " + scroll->getName() + "\nYour muscles bulge.");
                    handleRaiseStrength();
                    break;
                case Scroll::ENHANCE_HEALTH:
                    statusMessages.push_back("You read the scroll called " + scroll->getName() + "\nYou feel your heart beating stronger.");
                    handleEnhanceHealth();
                    break;
                case Scroll::ENHANCE_DEXTERITY:
                    statusMessages.push_back("You read the scroll called " + scroll->getName() + "\nYou feel like less of a klutz.");
                    handleEnhanceDexterity();
                    break;
            }
            // Remove the scroll from inventory
            m_inventory.erase(m_inventory.begin() + index);
            delete scroll; // Free the memory
        } else if (index < m_inventory.size()) {
            statusMessages.push_back("You can't read a " + m_inventory[index]->getName());
        } else {
            needRedisplay = true;
            return;
        }
    } else {
        needRedisplay = true;
        return;
    }
    needRedisplay = true;
}


void Player::setMaxHitPoints(int maxHP) {
    m_maxHitPoints = maxHP;
    if (m_hitPoints > m_maxHitPoints) {
        m_hitPoints = m_maxHitPoints;
    } else if (m_hitPoints < m_maxHitPoints) {
        m_hitPoints = m_maxHitPoints; // This ensures the current HP is set to max HP if it's less
    }
}


void Player::setStrengthPoints(int sp) {
    m_strengthPoints = sp;
}


bool Player::isAlive() const {
    return m_hitPoints > 0;
}

void Player::handleTeleportation() {
    int newX, newY;
    do {
        newX = rand() % Level::LEVEL_WIDTH;
        newY = rand() % Level::LEVEL_HEIGHT;
    } while (!m_level->isWalkable(newX, newY) || m_level->getMonsterAt(newX, newY) != nullptr);

    m_level->movePlayer(newX, newY);
}

void Player::handleImproveArmor() {
    setArmorPoints(getArmorPoints() + rand() % 3 + 1);
}

void Player::handleRaiseStrength() {
    setStrengthPoints(getStrengthPoints() + rand() % 3 + 1);
}

void Player::handleEnhanceHealth() {
    m_maxHitPoints += rand() % 6 + 3;
}

void Player::handleEnhanceDexterity() {
    setDexterityPoints(getDexterityPoints() + 1);
}