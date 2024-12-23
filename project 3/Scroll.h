// Scroll.h

#ifndef SCROLL_H
#define SCROLL_H

#include "GameObject.h"

class Scroll : public GameObject {
public:
    enum ScrollType {
        TELEPORTATION,
        IMPROVE_ARMOR,
        RAISE_STRENGTH,
        ENHANCE_HEALTH,
        ENHANCE_DEXTERITY
    };

    Scroll(int x, int y, const std::string& name, ScrollType type);

    ScrollType getScrollType() const;

private:
    ScrollType m_type;
};

#endif // SCROLL_H
