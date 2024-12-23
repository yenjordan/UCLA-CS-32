#include "Set.h"

Set::Set() : head(nullptr) {} // this initializes an empty set by setting head to nullptr

Set::~Set() {
    // this deallocates memory for all nodes in the linked list by traversing the list and deleting each node
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

Set::Set(const Set& other) : head(nullptr) {
    // this creates a new set that is a copy of the 'other' set by traversing 'other' and inserting each value into the new set
    Node* otherPtr = other.head;
    while (otherPtr != nullptr) {
        insert(otherPtr->value);
        otherPtr = otherPtr->next;
    }
}

Set& Set::operator=(const Set& other) {
    // this assigns the contents of another set ('other') to the current set by creating a temporary set 'temp' and swapping contents with 'temp'
    if (this != &other) {
        Set temp(other);
        swap(temp);
    }
    return *this;
}

bool Set::empty() const {
    // this checks if the set is empty by examining whether the 'head' pointer is nullptr
    return head == nullptr;
}

int Set::size() const {
    // this counts the number of elements in the set by traversing the linked list and counting the nodes
    int count = 0;
    Node* curr = head;
    while (curr != nullptr) {
        count++;
        curr = curr->next;
    }
    return count;
}

bool Set::insert(const ItemType& value) {
    // Check if the value already exists in the set
    if (contains(value)) {
        return false; // Value already exists
    }

    Node* newNode = new Node;
    newNode->value = value;
    newNode->next = nullptr;
    newNode->prev = nullptr;

    // If the list is empty or the new element should be inserted at the beginning
    if (head == nullptr || value >= head->value) {
        newNode->next = head;
        if (head != nullptr) {
            head->prev = newNode;
        }
        head = newNode;
    } else {
        // Traverse the list to find the correct position for insertion
        Node* current = head;
        while (current->next != nullptr && current->next->value > value) {
            current = current->next;
        }

        // Insert the new node after 'current'
        newNode->next = current->next;
        newNode->prev = current;
        if (current->next != nullptr) {
            current->next->prev = newNode;
        }
        current->next = newNode;
    }

    return true;
}


bool Set::erase(const ItemType& value) {
    // this removes an element from the set if it exists
    // it searches for the value in the linked list, removes the corresponding node, and deallocates its memory
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->value == value) {
            if (curr->prev == nullptr) {
                head = curr->next;
            } else {
                curr->prev->next = curr->next;
            }
            if (curr->next != nullptr) {
                curr->next->prev = curr->prev;
            }
            delete curr;
            return true;
        }
        curr = curr->next;
    }
    return false; // Value not found
}

bool Set::contains(const ItemType& value) const {
    // this checks if a value exists in the set by traversing the linked list and comparing each node's value
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->value == value) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

bool Set::get(int pos, ItemType& value) const {
    // this retrieves the value at a specified position in the set
    // it travesres the linked list to the desired position and retrieves the value
    if (pos < 0 || pos >= size()) {
        return false;
    }
    Node* curr = head;
    for (int i = 0; i < pos; i++) {
        curr = curr->next;
    }
    value = curr->value;
    return true;
}

void Set::swap(Set& other) {
    // this swaps the contents of two sets by exchanging their 'head' pointers
    Node* temp = head;
    head = other.head;
    other.head = temp;
}

void Set::dump() const {
    // this prints the values of all elements in the set for debugging purposes
    // it traverses the linked list and prints each node's value to cerr
    Node* curr = head;
    while (curr != nullptr) {
        std::cerr << curr->value << " ";
        curr = curr->next;
    }
    std::cerr << std::endl;
}

void unite(const Set& s1, const Set& s2, Set& result) {
    // this creates a new set containing the union of elements from sets 's1' and 's2'
    // it inserts all elements from 's2' into a temporary set 'temp', then assigns 'temp' to the 'result' set
    Set temp(s1);
    for (int i = 0; i < s2.size(); i++) {
        ItemType value;
        s2.get(i, value);
        temp.insert(value);
    }
    result = temp;
}

void inOnlyOne(const Set& s1, const Set& s2, Set& result) {
    // this creates a new set containing elements that exist in only one of the sets 's1' or 's2', but not both
    // it iterates through both sets, inserting elements into a temporary set 'temp' if they are unique to either set, then assigns 'temp' to the 'result' set
    Set temp;
    for (int i = 0; i < s1.size(); i++) {
        ItemType value;
        s1.get(i, value);
        if (!s2.contains(value)) {
            temp.insert(value);
        }
    }
    for (int i = 0; i < s2.size(); i++) {
        ItemType value;
        s2.get(i, value);
        if (!s1.contains(value)) {
            temp.insert(value);
        }
    }
    result = temp;
}