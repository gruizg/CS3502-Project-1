//
// Created by Geshlee Ruiz on 2/20/25.
//

#include "Store.h"

#include <iostream>
#include <thread>

double Store::storeBalance = 10000;

Store::Store(int numLines) {
    for (int i = 0; i < numLines;i++) {
        checkoutLines.emplace_back();
    }
}

void Store::purchase(Customer c) {
    storeBalance += c.getPrice();
}

void Store::refund(Customer c) {
    storeBalance -= c.getPrice();
}

double Store::getBalance() const {
    return storeBalance;
}

void Store::runStore() {
    std::cout << "Store balance : " << storeBalance << "\n";
    std::vector<std::thread> lines;

    for (auto& line : checkoutLines) {
       lines.emplace_back(&CheckoutLine::processCustomers, &line, std::ref(*this));
    }

    for (auto& t : lines) {
        if (t.joinable()) {
            t.join();
        }
    }
}
