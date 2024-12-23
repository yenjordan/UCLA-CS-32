#include "Weapon.h"

Weapon::Weapon(int x, int y, const std::string& name, const std::string& action, int dexterityBonus, int damageAmount)
    : GameObject(x, y, ')', name), m_action(action), m_dexterityBonus(dexterityBonus), m_damageAmount(damageAmount) {}

int Weapon::getDexterityBonus() const {
    return m_dexterityBonus;
}

int Weapon::getDamageAmount() const {
    return m_damageAmount;
}

const std::string& Weapon::getAction() const {
    return m_action;
}
