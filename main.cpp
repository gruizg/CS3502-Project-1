#include <iostream>
#include "Customer.h"
#include "Store.h"

int main() {

    int lines;
    std::cout << "Department Store Simulator\n";

    std::cout << "How many lines will your store have? ";
    std::cin >> lines;
    std::cout << "Running store...\n";

    Store myStore(lines);
    myStore.runStore();
    return 0;
}
