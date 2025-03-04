//
// Created by Geshlee Ruiz on 2/20/25.
//

#ifndef STORE_H
#define STORE_H

#include "Customer.h" //Include class files
#include "CheckoutLine.h"


class Store {
private:
    static double storeBalance;
    std::vector<CheckoutLine> checkoutLines; //Vector to hold checkout lines

public:
    explicit Store(int numLines);

    void purchase(Customer c);
    void refund(Customer c);
    [[nodiscard]] double getBalance() const;

    void runStore(int phase);
};



#endif //STORE_H
