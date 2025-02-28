//
// Created by Geshlee Ruiz on 2/20/25.
//

/*

*/

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <ostream>

class Customer {
private:
    int itemNumber;
    double itemPrice;
    bool isReturn;

    static constexpr double storePrices[] = {1.99, 4.99, 9.99, 14.99, 19.99, 24.99, 49.99, 99.99, 249.99};

public:
    Customer();

    [[nodiscard]] int getItem() const;
    [[nodiscard]] double getPrice() const;
    [[nodiscard]] bool getIsReturn() const;

    friend std::ostream& operator << (std::ostream& os, const Customer& c);
};


#endif //CUSTOMER_H
