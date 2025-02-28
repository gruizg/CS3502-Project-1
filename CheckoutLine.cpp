//
// Created by Geshlee Ruiz on 2/20/25.
//

#include "CheckoutLine.h"
#include "Store.h"

#include <iostream>
#include <random>
#include <mutex>
#include <thread>

static std::random_device ran;
static std::mt19937 gen(ran());

std::mutex mutexA;
std::mutex mutexB;

int CheckoutLine::nextId = 1;

CheckoutLine::CheckoutLine() {
    checkoutLineId = nextId;
    nextId++;

    std::uniform_int_distribution<int> customerDist(2,5);
    int size = customerDist(gen);
    for (int i = 0; i < size; i++) {
        customers.push(Customer());
    }

}

Customer CheckoutLine::dequeueCustomer() {
    if (customers.empty()) {
        throw std::runtime_error("Line is empty");
    }

    Customer c = customers.front();
    customers.pop();
    return c;
}

void CheckoutLine::processCustomers(Store& s) {
    while (hasCustomers()) {
        Customer c = dequeueCustomer();

        if (c.getIsReturn()) {
            std::unique_lock<std::mutex> lock1(mutexA);
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            std::unique_lock<std::mutex> lock2(mutexB);
            s.refund(c);
        }
        else {
            std::unique_lock<std::mutex> lock2(mutexB);
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            std::unique_lock<std::mutex> lock1(mutexA);
            s.purchase(c);
        }
        
        std::cout << "Processing line " << getId() << " " << c << "\n";
        std::cout << "Store Balance: " << s.getBalance();
    }
}

bool CheckoutLine::hasCustomers() const {
    return !customers.empty();
}

int CheckoutLine::getId() const{
    return checkoutLineId;
}

std::ostream& operator << (std::ostream& os, const CheckoutLine& cl) {
    os << cl.getId() << " ";
    return os;
}


