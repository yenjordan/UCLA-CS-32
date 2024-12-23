#include "PayerSet.h"
#include <iostream>

PayerSet::PayerSet() {}

bool PayerSet::add(unsigned long accountNum) {
    return m_accounts.insert(accountNum);
}

int PayerSet::size() const {
    return m_accounts.size();
}

void PayerSet::print() const {
    ItemType value;
    for (int i = 0; i < m_accounts.size(); ++i) {
        if (m_accounts.get(i, value))
            std::cout << value << std::endl;
    }
}
