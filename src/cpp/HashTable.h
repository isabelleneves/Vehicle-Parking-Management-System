#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class HashTable {

private:
    std::unordered_map<std::string, std::string> vehicles;

public:

    void insert(std::string registration, std::string vehicleType) {

        vehicles[registration] = vehicleType;

        std::cout << "Vehicle added to hash table: "
                  << registration << std::endl;
    }

    bool search(std::string registration) {

        auto vehicle = vehicles.find(registration);

        if (vehicle != vehicles.end()) {

            std::cout << "Vehicle found: "
                      << vehicle->first << " - "
                      << vehicle->second << std::endl;

            return true;
        }

        std::cout << "Vehicle not found: "
                  << registration << std::endl;

        return false;
    }

    bool getVehicleType(std::string registration, std::string& vehicleType) {

        auto vehicle = vehicles.find(registration);

        if (vehicle != vehicles.end()) {

            vehicleType = vehicle->second;
            return true;
        }

        return false;
    }

    std::vector<std::pair<std::string, std::string>> getAllVehicles() {

        std::vector<std::pair<std::string, std::string>> result;

        for (const auto& vehicle : vehicles) {

            result.push_back(vehicle);
        }

        return result;
    }

    void display() {

        std::cout << "Vehicles in hash table:" << std::endl;

        for (const auto& vehicle : vehicles) {

            std::cout << vehicle.first
                      << " - "
                      << vehicle.second
                      << std::endl;
        }
    }
};

#endif