//
// Created by Geshlee Ruiz on 2/20/25.
//

#include "CheckoutLine.h" //include classes 
#include "Store.h"

#include <iostream> //IO, Ran generator, Mutexes, Threads
#include <random>
#include <mutex>
#include <thread>

static std::random_device ran; //Ran generator
static std::mt19937 gen(ran());

std::mutex transactionMutex; //Mutex for Phase 2
std::mutex mutexA; //Mutexes for Phase 3
std::mutex mutexB;
std::mutex printMutex; //Additional Mutex for Phase 4

int CheckoutLine::nextId = 1; 

CheckoutLine::CheckoutLine() { //Constructor that generates random # of customers for each line. 
    checkoutLineId = nextId;
    nextId++;

    std::uniform_int_distribution<int> customerDist(2,5);
    int size = customerDist(gen);
    for (int i = 0; i < size; i++) {
        customers.push(Customer());
    }

}

Customer CheckoutLine::dequeueCustomer() { //Removes customers from lines
    if (customers.empty()) {
        throw std::runtime_error("Line is empty");
    }

    Customer c = customers.front();
    customers.pop();
    return c;
}

void CheckoutLine::processCustomers(Store& s, int phase) { //Chooses which Phase to run

    Store mystore = s;
    switch (phase) {
        case 1:
            phase1(s);
        break;
        case 2:
            phase2(s);
        break;
        case 3:
            phase3(s);
        break;
        case 4:
            phase4(s);
        break;
    }

}
void CheckoutLine::phase1(Store& s) { //Phase 1 allows any access to increase or decrease store balance
    while (hasCustomers()) {
        Customer c = dequeueCustomer(); //Pulls customer and passes to make a transaction

        if (c.getIsReturn()) {
            s.refund(c);
        }
        else {
            s.purchase(c);
        }

        std::cout << "Processing line " << getId() << " " << c << "\n"; //Prints balance status and customer attributes
        std::cout << "Store Balance: " << s.getBalance() << "\n";
    }
}
void CheckoutLine::phase2(Store& s) { //Phase 2 mutex locks before every transaction, ensuring only one can adjust the balance at a time.
    while (hasCustomers()) {
        Customer c = dequeueCustomer();

        std::unique_lock<std::mutex> transactionLock(transactionMutex);

        if (c.getIsReturn()) {
            s.refund(c);
        }
        else {
            s.purchase(c);
        }

        std::cout << "Processing line " << getId() << " " << c << "\n";
        std::cout << "Store Balance: " << s.getBalance() << "\n";

    }
}
void CheckoutLine::phase3(Store& s) { //Phase 3 creates seperate mutexes for purchase and refund to in theory allow concurrency of a purchase and a refund, rather than one tranaction at a time
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
void CheckoutLine::phase4(Store& s) { //Phase 4 fixes the deadlock by checking lock availability first, if second lock fails ,first is unlocked and yields
    while (hasCustomers()) {
        Customer c = dequeueCustomer();

        if (c.getIsReturn()) {
            while (!mutexA.try_lock()) {}
            while (!mutexB.try_lock()) {
                mutexA.unlock();
                std::this_thread::yield();
            }
        } else {
            while (!mutexB.try_lock()) {}
            while (!mutexA.try_lock()) {
                mutexB.unlock();
                std::this_thread::yield();
            }
        }

        if (c.getIsReturn()) {
            s.refund(c);
        } else {
            s.purchase(c);
        }

        mutexA.unlock();
        mutexB.unlock();

        {
            std::lock_guard<std::mutex> printLock(printMutex); //Ensures print will complete before the next
            std::cout << "Processing line " << getId() << " " << c << "\n";
            std::cout << "Store Balance: " << s.getBalance() << "\n";
        }
    }
}

bool CheckoutLine::hasCustomers() const { //Checks there are customers left to process
    return !customers.empty();
}

int CheckoutLine::getId() const{ //Gets id of checkout line
    return checkoutLineId;
}

std::ostream& operator << (std::ostream& os, const CheckoutLine& cl) {
    os << cl.getId() << " ";
    return os;
}
