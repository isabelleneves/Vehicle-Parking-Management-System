#include "BinarySearchTree.h"

int main() {

    BinarySearchTree vehicles;

    vehicles.insert("ABC123");
    vehicles.insert("GHI789");
    vehicles.insert("DEF456");

    std::cout << std::endl;

    vehicles.display();

    std::cout << std::endl;

    if (vehicles.search("DEF456")) {
        std::cout << "Vehicle DEF456 found!" << std::endl;
    } else {
        std::cout << "Vehicle DEF456 not found!" << std::endl;
    }

    if (vehicles.search("XYZ999")) {
        std::cout << "Vehicle XYZ999 found!" << std::endl;
    } else {
        std::cout << "Vehicle XYZ999 not found!" << std::endl;
    }

    return 0;
}
