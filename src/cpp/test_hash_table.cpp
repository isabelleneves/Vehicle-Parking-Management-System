#include "HashTable.h"

int main() {

    HashTable vehicles;

    std::cout << "HASH TABLE TEST" << std::endl;
    std::cout << "---------------" << std::endl;

    // Register vehicles
    vehicles.insert("ABC123", "Motorcycle");
    vehicles.insert("DEF456", "Car");
    vehicles.insert("GHI789", "Bus");

    std::cout << std::endl;

    // Search for existing vehicles
    vehicles.search("ABC123");
    vehicles.search("DEF456");
    vehicles.search("GHI789");

    std::cout << std::endl;

    // Search for a vehicle that does not exist
    vehicles.search("XYZ999");

    std::cout << std::endl;

    // Display all registered vehicles
    vehicles.display();

    return 0;
}
