#ifndef PARKINGSYSTEM_H
#define PARKINGSYSTEM_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

#include "Vehicle.h"
#include "DoublyLinkedList.h"
#include "BinarySearchTree.h"
#include "HashTable.h"
#include "SearchAlgorithms.h"
#include "SortAlgorithms.h"

using namespace std;

// Parking space types
enum class SpaceType {
    Compact,
    Large
};

// Parking space
class ParkingSpace {
public:
    int spaceNumber;
    SpaceType type;
    bool occupied;
    string registrationNumber;

    ParkingSpace(int number, SpaceType spaceType) {
        spaceNumber = number;
        type = spaceType;
        occupied = false;
        registrationNumber = "";
    }
};

// Parking row
class ParkingRow {
public:
    int rowNumber;
    vector<ParkingSpace> spaces;

    ParkingRow(int number) {
        rowNumber = number;

        for (int i = 1; i <= 8; i++) {
            SpaceType type = (i <= 3)
                ? SpaceType::Compact
                : SpaceType::Large;

            spaces.emplace_back(i, type);
        }
    }
};

// Parking floor
class ParkingFloor {
public:
    int floorNumber;
    vector<ParkingRow> rows;

    ParkingFloor(int number) {
        floorNumber = number;

        rows.emplace_back(1);
        rows.emplace_back(2);
    }
};

// Main parking system
class ParkingSystem {
public:
    vector<ParkingFloor> floors;

    DoublyLinkedList vehicleList;
    BinarySearchTree vehicleTree;
    HashTable vehicleHash;

    ParkingSystem() {
        floors.emplace_back(1);
        floors.emplace_back(2);
    }

    // Register vehicle in all data structures
    void registerVehicle(const Vehicle& vehicle) {
        string registration = vehicle.getRegistrationNumber();
        string type = vehicle.getType();
        string existingType;

        if (vehicleHash.getVehicleType(registration, existingType)) {
            cout << "Vehicle is already registered!" << endl;
            return;
        }

        vehicleList.addVehicle(registration);
        vehicleTree.insert(registration);
        vehicleHash.insert(registration, type);

        cout << "Vehicle registered in all data structures!" << endl;
    }

    // Automatically park a vehicle
    void parkVehicle(const Vehicle& vehicle) {
        string registration = vehicle.getRegistrationNumber();
        string existingType;

        if (registration.empty()) {
            cout << "Invalid registration number!" << endl;
            return;
        }

        if (vehicleHash.getVehicleType(registration, existingType)) {
            cout << "Vehicle is already registered!" << endl;
            return;
        }

        // Bus needs five consecutive large spaces
        if (vehicle.getType() == "Bus") {
            for (auto& floor : floors) {
                for (auto& row : floor.rows) {

                    int availableSpaces = 0;

                    for (auto& space : row.spaces) {
                        if (space.type == SpaceType::Large &&
                            !space.occupied) {
                            availableSpaces++;
                        } else {
                            availableSpaces = 0;
                        }

                        if (availableSpaces == 5) {
                            int start = space.spaceNumber - 4;

                            for (int i = start - 1; i < start + 4; i++) {
                                row.spaces[i].occupied = true;
                                row.spaces[i].registrationNumber =
                                    registration;
                            }

                            cout << "Bus parked successfully in five "
                                    "consecutive large spaces!" << endl;

                            registerVehicle(vehicle);
                            return;
                        }
                    }
                }
            }

            cout << "No five consecutive large spaces "
                    "available for the bus!" << endl;
            return;
        }

        // Cars and motorcycles
        if (vehicle.getType() == "Car" ||
            vehicle.getType() == "Motorcycle") {

            for (auto& floor : floors) {
                for (auto& row : floor.rows) {
                    for (auto& space : row.spaces) {

                        if (!space.occupied) {
                            space.occupied = true;
                            space.registrationNumber = registration;

                            cout << vehicle.getType()
                                 << " parked successfully in space "
                                 << space.spaceNumber << endl;

                            registerVehicle(vehicle);
                            return;
                        }
                    }
                }
            }

            cout << "No compatible parking space available!" << endl;
            return;
        }

        cout << "Invalid vehicle type!" << endl;
    }

    // Park a vehicle in a selected space using drag-and-drop
    bool occupySpace(int floorNumber,
                     int rowNumber,
                     int spaceNumber,
                     const Vehicle& vehicle) {

        // Validate floor
        if (floorNumber < 1 ||
            floorNumber > static_cast<int>(floors.size())) {
            return false;
        }

        ParkingFloor& floor = floors[floorNumber - 1];

        // Validate row
        if (rowNumber < 1 ||
            rowNumber > static_cast<int>(floor.rows.size())) {
            return false;
        }

        ParkingRow& row = floor.rows[rowNumber - 1];

        // Validate space
        if (spaceNumber < 1 ||
            spaceNumber > static_cast<int>(row.spaces.size())) {
            return false;
        }

        string registration = vehicle.getRegistrationNumber();
        string type = vehicle.getType();
        string existingType;

        // Prevent empty or duplicate registration
        if (registration.empty() ||
            vehicleHash.getVehicleType(registration, existingType)) {
            return false;
        }

        ParkingSpace& space = row.spaces[spaceNumber - 1];

        // Selected space must be available
        if (space.occupied) {
            return false;
        }

        // Bus parking
        if (type == "Bus") {
            if (space.type != SpaceType::Large) {
                return false;
            }

            int start = spaceNumber - 1;

            if (start + 5 > static_cast<int>(row.spaces.size())) {
                return false;
            }

            // Check all five spaces before parking
            for (int i = start; i < start + 5; i++) {
                if (row.spaces[i].type != SpaceType::Large ||
                    row.spaces[i].occupied) {
                    return false;
                }
            }

            // Occupy five consecutive large spaces
            for (int i = start; i < start + 5; i++) {
                row.spaces[i].occupied = true;
                row.spaces[i].registrationNumber = registration;
            }
        }
        else if (type == "Car" || type == "Motorcycle") {
            // Cars and motorcycles can use compact or large spaces
            space.occupied = true;
            space.registrationNumber = registration;
        }
        else {
            return false;
        }

        // Register the vehicle in all data structures
        registerVehicle(vehicle);

        cout << type << " " << registration
             << " parked successfully using drag-and-drop!"
             << endl;

        return true;
    }

    // Search for a vehicle using its registration number
    bool searchVehicle(string registration) {
        return vehicleHash.search(registration);
    }

    // Compare three search algorithms
    void searchVehicleWithAlgorithms(string registration) {
        vector<string> registrations;

        // Collect unique registrations
        for (const auto& floor : floors) {
            for (const auto& row : floor.rows) {
                for (const auto& space : row.spaces) {
                    if (space.occupied) {
                        if (find(
                                registrations.begin(),
                                registrations.end(),
                                space.registrationNumber
                            ) == registrations.end()) {

                            registrations.push_back(
                                space.registrationNumber
                            );
                        }
                    }
                }
            }
        }

        cout << "\nSearching for vehicle: "
             << registration << endl;

        // Linear search
        int linearResult =
            SearchAlgorithms::linearSearch(
                registrations,
                registration
            );

        cout << "Linear Search: "
             << (linearResult >= 0 ? "Found" : "Not found")
             << endl;

        // Binary search requires sorted data
        vector<string> sortedRegistrations = registrations;

        sort(
            sortedRegistrations.begin(),
            sortedRegistrations.end()
        );

        int binaryResult =
            SearchAlgorithms::binarySearch(
                sortedRegistrations,
                registration
            );

        cout << "Binary Search: "
             << (binaryResult >= 0 ? "Found" : "Not found")
             << endl;

        // Hash search
        SearchAlgorithms::hashSearch(
            vehicleHash,
            registration
        );
    }

    // Sort vehicle records by type
    void displayVehiclesSortedByType() {
        vector<pair<string, string>> vehicles =
            vehicleHash.getAllVehicles();

        SortAlgorithms::sortByVehicleType(
            vehicles,
            [](const pair<string, string>& first,
               const pair<string, string>& second) {
                return first.second < second.second;
            }
        );

        cout << "\nVehicles sorted by type:" << endl;

        for (const auto& vehicle : vehicles) {
            cout << "Registration: " << vehicle.first
                 << " | Type: " << vehicle.second
                 << endl;
        }
    }

    // Display records stored in the data structures
    void displayVehicleRecords() {
        cout << "\n--- Doubly Linked List ---" << endl;
        vehicleList.displayForward();

        cout << "\n--- Binary Search Tree ---" << endl;
        vehicleTree.display();

        cout << "\n--- Hash Table ---" << endl;
        vehicleHash.display();
    }

    // Display the parking layout
    void displayParking() {
        cout << "\n===== PARKING LAYOUT =====" << endl;

        for (const auto& floor : floors) {
            cout << "\nFloor " << floor.floorNumber << endl;

            for (const auto& row : floor.rows) {
                cout << "Row " << row.rowNumber << endl;

                for (const auto& space : row.spaces) {
                    cout << "Space " << space.spaceNumber
                         << " ("
                         << (space.type == SpaceType::Compact
                                 ? "Compact"
                                 : "Large")
                         << ") - ";

                    if (space.occupied) {
                        cout << "Occupied by "
                             << space.registrationNumber;
                    } else {
                        cout << "Available";
                    }

                    cout << endl;
                }
            }
        }
    }
};

#endif