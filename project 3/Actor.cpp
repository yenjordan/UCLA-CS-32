#include "Actor.h"
#include "Weapon.h"
#include "utilities.h"
#include "Monster.h" // Ensure this is included to use Monster
#include <iostream>

Actor::Actor(int x, int y, int hitPoints, int armorPoints, int strengthPoints, int dexterityPoints, int sleepTime, char symbol)
    : m_x(x), m_y(y), m_hitPoints(hitPoints), m_armorPoints(armorPoints), m_strengthPoints(strengthPoints),
      m_dexterityPoints(dexterityPoints), m_sleepTime(sleepTime), m_symbol(symbol) {}

int Actor::getX() const { return m_x; }
int Actor::getY() const { return m_y; }
int Actor::getHitPoints() const { return m_hitPoints; }
int Actor::getArmorPoints() const { return m_armorPoints; }
int Actor::getStrengthPoints() const { return m_strengthPoints; }
int Actor::getDexterityPoints() const { return m_dexterityPoints; }
int Actor::getSleepTime() const { return m_sleepTime; }
char Actor::getSymbol() const { return m_symbol; }

void Actor::setPosition(int x, int y) {
    m_x = x;
    m_y = y;
}

void Actor::setHitPoints(int hp) {
    m_hitPoints = hp;
}

void Actor::setArmorPoints(int ap) {
    m_armorPoints = ap;
}

void Actor::setStrengthPoints(int sp) {
    m_strengthPoints = sp;
}

void Actor::setDexterityPoints(int dp) {
    m_dexterityPoints = dp;
}

void Actor::setSleepTime(int st) {
    m_sleepTime = st;
}

std::string Actor::attack(Actor* target, Weapon* weapon, const std::string& attackerName) {
    if (!target || !weapon || !isAlive()) return "";

    int attackerPoints = m_dexterityPoints + weapon->getDexterityBonus();
    int defenderPoints = target->getDexterityPoints() + target->getArmorPoints();
    
    std::string targetName = "Player";
    if (Monster* monsterTarget = dynamic_cast<Monster*>(target)) {
        targetName = monsterTarget->getName();
    }
    
    std::string actionMessage;
    if (randInt(1, attackerPoints) >= randInt(1, defenderPoints)) {
        int damagePoints = randInt(0, m_strengthPoints + weapon->getDamageAmount() - 1);
        target->setHitPoints(target->getHitPoints() - damagePoints);
        
        actionMessage = attackerName + " " + weapon->getAction() + " at the " + targetName + " and hits.";
        
        if (!target->isAlive()) {
            actionMessage = attackerName + " " + weapon->getAction() + " at the " + targetName + " dealing a final blow.";
        }

        if (weapon->getName() == "magic fangs of sleep" && randInt(1, 5) == 1) {
            int sleepTime = randInt(2, 6);
            if (target->getSleepTime() < sleepTime) {
                target->setSleepTime(sleepTime);
                actionMessage += " putting the " + targetName + " to sleep.";
            }
        }
    } else {
        actionMessage = attackerName + " " + weapon->getAction() + " at the " + targetName + " and misses.";
    }

    return actionMessage;
}



bool Actor::isAlive() const {
    return m_hitPoints > 0;
}
