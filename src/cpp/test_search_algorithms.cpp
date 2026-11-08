#include "SearchAlgorithms.h"

int main() {

    std::vector<std::string> vehicles = {
        "GHI789",
        "ABC123",
        "DEF456",
        "JKL012",
        "MNO345"
    };

    std::cout << "SEARCH ALGORITHMS TEST" << std::endl;
    std::cout << "----------------------" << std::endl;

    // Linear Search
    int linearResult =
        SearchAlgorithms::linearSearch(vehicles, "DEF456");

    std::cout << "Linear Search: "
              << (linearResult != -1 ? "Vehicle found!" : "Vehicle not found!")
              << std::endl;

    // Binary Search
    int binaryResult =
        SearchAlgorithms::binarySearch(vehicles, "DEF456");

    std::cout << "Binary Search: "
              << (binaryResult != -1 ? "Vehicle found!" : "Vehicle not found!")
              << std::endl;

    // Hash Search
    HashTable hashTable;

    hashTable.insert("ABC123", "Motorcycle");
    hashTable.insert("DEF456", "Car");
    hashTable.insert("GHI789", "Bus");

    std::cout << std::endl << "Hash Search:" << std::endl;

    SearchAlgorithms::hashSearch(hashTable, "DEF456");

    return 0;
}
