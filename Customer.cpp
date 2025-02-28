//
// Created by Geshlee Ruiz on 2/20/25.
//

#include "Customer.h"

#include <random>

static std::random_device ran;
static std::mt19937 gen(ran());

Customer::Customer() {
    std::uniform_int_distribution<int> itemDist(0,8);
    std::uniform_int_distribution<int> returnDist(0,1);
    itemNumber = itemDist(gen);
    itemPrice = storePrices[itemNumber];
    isReturn = returnDist(gen);
}

int Customer::getItem() const{
    return itemNumber;
}
double Customer::getPrice() const{
    return itemPrice;
}
bool Customer::getIsReturn() const{
    return isReturn;
}
std::ostream& operator << (std::ostream& os, const Customer& c) {
    os << (c.getIsReturn() == 1 ? "Returning " : "Purchasing ") << "item " << c.getItem() << "|" << (c.getIsReturn() == 1 ? " -" : " +") << c.getPrice() << "\n";
    return os;
}