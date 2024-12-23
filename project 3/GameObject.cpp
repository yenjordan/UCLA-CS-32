// GameObject.cpp

#include "GameObject.h"

GameObject::GameObject(int x, int y, char symbol, const std::string& name)
    : m_x(x), m_y(y), m_symbol(symbol), m_name(name) {}

int GameObject::getX() const { return m_x; }
int GameObject::getY() const { return m_y; }
char GameObject::getSymbol() const { return m_symbol; }
const std::string& GameObject::getName() const { return m_name; }

void GameObject::setPosition(int x, int y) {
    m_x = x;
    m_y = y;
}
