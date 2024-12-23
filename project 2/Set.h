#ifndef SET_H
#define SET_H

#include <iostream>
#include <string>

using ItemType = std::string; // Replace int with the appropriate type

class Set {
private:
    struct Node {
        ItemType value;
        Node* next;
        Node* prev;
    };

    Node* head;

public:
    Set();
    ~Set();
    Set(const Set& other);
    Set& operator=(const Set& other);

    bool empty() const;
    int size() const;
    bool insert(const ItemType& value);
    bool erase(const ItemType& value);
    bool contains(const ItemType& value) const;
    bool get(int pos, ItemType& value) const;
    void swap(Set& other);
    void dump() const;
};

void unite(const Set& s1, const Set& s2, Set& result);
void inOnlyOne(const Set& s1, const Set& s2, Set& result);

#endif // SET_H
