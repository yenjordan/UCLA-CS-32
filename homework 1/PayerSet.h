#ifndef PAYERSET_H
#define PAYERSET_H

#include "Set.h"

class PayerSet
{
public:
    PayerSet();  // Create an empty payer set.

    bool add(unsigned long accountNum);
    // If specified account number is not currently in this payer set 
    // and there is room in the payer set, add that account number to
    // the payer set and return true.  Otherwise, make no change to
    // this payer set and return false.

    int size() const;
    // Return the number of account numbers in the PayerSet.

    void print() const;
    // Write to cout every account number in the PayerSet exactly
    // once, one per line.  Write no other text.  The lines need
    // not be in any particular order.

private:
    Set m_accounts;
};

#endif // PAYERSET_H
