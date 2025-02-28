//
// Created by Geshlee Ruiz on 2/20/25.
//

#ifndef CHECKOUTLINE_H
#define CHECKOUTLINE_H

#include "Customer.h"
#include <queue>

class Store;

class CheckoutLine {
private:
    int checkoutLineId;
    static int nextId;
    std::queue<Customer> customers;

public:
    CheckoutLine();

    Customer dequeueCustomer();

    void processCustomers(Store& s);
    [[nodiscard]] bool hasCustomers() const;
    [[nodiscard]] int getId() const;

    friend std::ostream& operator << (std::ostream& os, const CheckoutLine& cl);

};



#endif //CHECKOUTLINE_H
