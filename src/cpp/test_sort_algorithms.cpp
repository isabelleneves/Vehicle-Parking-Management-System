#include <iostream>
#include <vector>
#include <string>

#include "SortAlgorithms.h"
#include "Vehicle.h"

int main() {

    std::cout << "SORTING ALGORITHMS TEST" << std::endl;
    std::cout << "-----------------------" << std::endl;

    std::vector<std::string> vehicles = {
        "GHI789", "ABC123", "MNO345", "DEF456"
    };

    std::vector<std::string> bubbleVehicles = vehicles;
    std::vector<std::string> selectionVehicles = vehicles;
    std::vector<std::string> insertionVehicles = vehicles;

    // Bubble Sort
    SortAlgorithms::bubbleSort(bubbleVehicles);

    // Selection Sort
    SortAlgorithms::selectionSort(selectionVehicles);

    // Insertion Sort
    SortAlgorithms::insertionSort(insertionVehicles);

    std::cout << "Bubble Sort: ";

    for (const auto& registration : bubbleVehicles) {
        std::cout << registration << " ";
    }

    std::cout << std::endl;

    std::cout << "Selection Sort: ";

    for (const auto& registration : selectionVehicles) {
        std::cout << registration << " ";
    }

    std::cout << std::endl;

    std::cout << "Insertion Sort: ";

    for (const auto& registration : insertionVehicles) {
        std::cout << registration << " ";
    }

    std::cout << std::endl << std::endl;

    // Test sorting vehicles by type
    std::vector<Vehicle*> parkingVehicles;

    parkingVehicles.push_back(new Vehicle::Bus("GHI789"));
    parkingVehicles.push_back(new Vehicle::Motorcycle("ABC123"));
    parkingVehicles.push_back(new Vehicle::Car("DEF456"));

    // Sort vehicles alphabetically by type
    SortAlgorithms::sortByVehicleType(
        parkingVehicles,
        [](const Vehicle* a, const Vehicle* b) {
            return a->getType() < b->getType();
        }
    );

    std::cout << "Vehicles sorted by type:" << std::endl;

    for (const auto& vehicle : parkingVehicles) {
        std::cout << vehicle->getType()
                  << " - "
                  << vehicle->getRegistrationNumber()
                  << std::endl;
    }

    // Free allocated memory
    for (auto vehicle : parkingVehicles) {
        delete vehicle;
    }

    return 0;
}