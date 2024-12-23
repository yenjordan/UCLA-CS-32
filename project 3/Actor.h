#ifndef ACTOR_H
#define ACTOR_H

#include <string> // Include this for std::string

class Weapon;

class Actor {
public:
    Actor(int x, int y, int hitPoints, int armorPoints, int strengthPoints, int dexterityPoints, int sleepTime, char symbol);
    virtual ~Actor() {}

    int getX() const;
    int getY() const;
    int getHitPoints() const;
    int getArmorPoints() const;
    int getStrengthPoints() const;
    int getDexterityPoints() const;
    int getSleepTime() const;
    char getSymbol() const;

    void setPosition(int x, int y);
    void setHitPoints(int hp);
    void setArmorPoints(int ap);
    void setStrengthPoints(int sp);
    void setDexterityPoints(int dp);
    void setSleepTime(int st);

virtual std::string attack(Actor* target, Weapon* weapon, const std::string& attackerName);
    bool isAlive() const;

protected:
    int m_x;
    int m_y;
    int m_hitPoints;
    int m_armorPoints;
    int m_strengthPoints;
    int m_dexterityPoints;
    int m_sleepTime;
    char m_symbol;
};

#endif // ACTOR_H
