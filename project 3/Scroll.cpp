// Scroll.cpp

#include "Scroll.h"

Scroll::Scroll(int x, int y, const std::string& name, ScrollType type)
    : GameObject(x, y, '?', name), m_type(type) {}

Scroll::ScrollType Scroll::getScrollType() const { return m_type; }
