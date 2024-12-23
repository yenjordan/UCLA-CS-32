#ifndef WEAPON_H
#define WEAPON_H

#include "GameObject.h"

class Weapon : public GameObject {
public:
    Weapon(int x, int y, const std::string& name, const std::string& action, int dexterityBonus, int damageAmount);

    int getDexterityBonus() const;
    int getDamageAmount() const;
    const std::string& getAction() const;

private:
    int m_dexterityBonus;
    int m_damageAmount;
    std::string m_action;
};

#endif // WEAPON_H
