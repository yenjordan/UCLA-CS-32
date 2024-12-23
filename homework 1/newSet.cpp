#include "newSet.h"
#include <iostream>

Set::Set(int maxItems) : m_size(0), m_capacity(maxItems) {
    if (maxItems < 0) {
        std::cout << "Error: Max items cannot be negative." << std::endl;
        exit(1);
    }
    m_items = new ItemType[m_capacity];
}

Set::Set(const Set& other) : m_size(other.m_size), m_capacity(other.m_capacity) {
    m_items = new ItemType[m_capacity];
    for (int i = 0; i < m_size; ++i)
        m_items[i] = other.m_items[i];
}

Set& Set::operator=(const Set& other) {
    if (this != &other) {
        ItemType* temp = new ItemType[other.m_capacity];
        for (int i = 0; i < other.m_size; ++i)
            temp[i] = other.m_items[i];
        delete[] m_items;
        m_items = temp;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
    }
    return *this;
}

Set::~Set() {
    delete[] m_items;
}

bool Set::empty() const {
    return size() == 0;
}

int Set::size() const {
    return m_size;
}

bool Set::insert(const ItemType& value) {
    if (contains(value) || m_size >= m_capacity)
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
    ItemType* tempItems = m_items;
    m_items = other.m_items;
    other.m_items = tempItems;

    int tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;

    int tempCapacity = m_capacity;
    m_capacity = other.m_capacity;
    other.m_capacity = tempCapacity;
}
