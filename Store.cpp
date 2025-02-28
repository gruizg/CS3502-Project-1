//
// Created by Geshlee Ruiz on 2/20/25.
//

#include "Store.h" //Include class

#include <iostream> //IO and Threads
#include <thread> 

double Store::storeBalance = 10000; //Starting store balance

Store::Store(int numLines) { //Creates checkout lines
    for (int i = 0; i < numLines;i++) {
        checkoutLines.emplace_back();
    }
}

void Store::purchase(Customer c) { //Adds to balance after a purchase
    storeBalance += c.getPrice();
}

void Store::refund(Customer c) { //Subtracts from balance after refund
    storeBalance -= c.getPrice();
}

double Store::getBalance() const { //Returns the balance
    return storeBalance;
}

void Store::runStore(int phase) { //Passes the lines to threads and begins
    std::cout << "Store balance : " << storeBalance << "\n";
    std::vector<std::thread> lines;

    for (auto& line : checkoutLines) {
        lines.emplace_back(&CheckoutLine::processCustomers, &line, std::ref(*this), phase);
    }

    for (auto& t : lines) {
        if (t.joinable()) {
            t.join();
        }
    }
}
