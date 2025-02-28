//
// Created by Geshlee Ruiz on 2/20/25.
//

#ifndef CHECKOUTLINE_H
#define CHECKOUTLINE_H

#include "Customer.h"

#include <queue> //Uses queue to simulate a checkout line

class Store; //uses store methods to process

class CheckoutLine {
private:
    int checkoutLineId;
    static int nextId;
    std::queue<Customer> customers;

public:
    CheckoutLine();

    Customer dequeueCustomer();

    void processCustomers(Store& s, int phase);
    void phase1(Store& s);
    void phase2(Store& s);
    void phase3(Store& s);
    void phase4(Store& s);
    [[nodiscard]] bool hasCustomers() const;
    [[nodiscard]] int getId() const;

    friend std::ostream& operator << (std::ostream& os, const CheckoutLine& cl);

};



#endif //CHECKOUTLINE_H

