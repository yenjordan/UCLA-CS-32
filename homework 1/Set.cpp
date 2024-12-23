#include "Set.h"
#include <iostream>
#include <cassert>
using namespace std;

Set::Set() : m_size(0) {}

bool Set::empty() const {
    return size() == 0;
}

int Set::size() const {
    return m_size;
}

bool Set::insert(const ItemType& value) {
    if (contains(value) || m_size >= DEFAULT_MAX_ITEMS)
        return false;
    m_items[m_size++] = value;
    return true;
}

bool Set::erase(const ItemType& value) {
    for (int i = 0; i < m_size; ++i) {
        if (m_items[i] == value) {
            m_items[i] = m_items[m_size - 1];
            --m_size;
            return true;
        }
    }
    return false;
}

bool Set::contains(const ItemType& value) const {
    for (int i = 0; i < m_size; ++i) {
        if (m_items[i] == value)
            return true;
    }
    return false;
}

bool Set::get(int i, ItemType& value) const {
    if (i >= 0 && i < m_size) {
        value = m_items[m_size - i - 1];
        return true;
    }
    return false;
}

void Set::swap(Set& other) {
    for (int i = 0; i < DEFAULT_MAX_ITEMS; ++i) {
        ItemType temp = m_items[i];
        m_items[i] = other.m_items[i];
        other.m_items[i] = temp;
    }
}

void Set::dump() const {
    for (int i = 0; i < m_size; ++i) {
        std::cerr << m_items[i] << std::endl;
    }
}
