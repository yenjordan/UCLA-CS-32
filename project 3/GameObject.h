// GameObject.h

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>

class GameObject {
public:
    GameObject(int x, int y, char symbol, const std::string& name);
    virtual ~GameObject() {} // Add a virtual destructor

    int getX() const;
    int getY() const;
    char getSymbol() const;
    const std::string& getName() const;

    void setPosition(int x, int y);

private:
    int m_x;
    int m_y;
    char m_symbol;
    std::string m_name;
};

#endif // GAMEOBJECT_H
