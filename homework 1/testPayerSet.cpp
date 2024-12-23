#include "PayerSet.h"
#include <iostream>
#include <cassert>

int main() {
    PayerSet payerSet;

    // Test empty PayerSet
    assert(payerSet.size() == 0);

    // Test adding account numbers
    assert(payerSet.add(123456789));
    assert(payerSet.add(987654321));
    assert(payerSet.add(555555555));

    // Test size after adding
    assert(payerSet.size() == 3);

    // Test printing
    std::cout << "Printing payer set:" << std::endl;
    payerSet.print();

    std::cout << "All tests passed!" << std::endl;

    return 0;
}
