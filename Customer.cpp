//
// Created by Geshlee Ruiz on 2/20/25.
//

#include "Customer.h" //include class

#include <random> //Ran generator

static std::random_device ran;
static std::mt19937 gen(ran());

Customer::Customer() {
    std::uniform_int_distribution<int> itemDist(0,8); //Ran generator to choose item
    std::uniform_int_distribution<int> returnDist(0,1); //Ran generator to determine return or purchase
    
    itemNumber = itemDist(gen);
    itemPrice = storePrices[itemNumber]; //Determines price of item
    isReturn = returnDist(gen);
}

int Customer::getItem() const{ //Gets item number
    return itemNumber;
}
double Customer::getPrice() const{ //Gets price of item
    return itemPrice;
}
bool Customer::getIsReturn() const{ //Gets return status
    return isReturn;
}
std::ostream& operator << (std::ostream& os, const Customer& c) { //Prints the customer info
    os << (c.getIsReturn() == 1 ? "Returning " : "Purchasing ") << "item " << c.getItem() << "|" << (c.getIsReturn() == 1 ? " -" : " +") << c.getPrice() << "\n";
    return os;
}
