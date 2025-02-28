/*
Driver class to run simulation of a store. Store consists of customers that are processed through checkout lines.
*/

#include <iostream>
#include "Store.h"

int main() {

    //Implements user input to allow test cases with different numbers of checkout lines
    int lines;
    int phase;
    std::cout << "Department Store Simulator\n";

    std::cout << "How many lines will your store have? ";
    std::cin >> lines;
    std::cout << "Which phase to run? (1-4)";
    std::cin >>phase;
    std::cout << "Running store...\n";

    //Create store and call method to run store simulation
    Store myStore(lines);
    myStore.runStore(phase);

    return 0;
}
