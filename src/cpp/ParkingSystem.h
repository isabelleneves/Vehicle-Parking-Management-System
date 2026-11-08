#ifndef PARKING_SYSTEM_H
#define PARKING_SYSTEM_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum class SpaceType {
    Compact,
    Large
};

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

class ParkingSystem {
public:
    vector<ParkingFloor> floors;

    ParkingSystem() {
        floors.emplace_back(1);
        floors.emplace_back(2);
    }

   bool occupySpace(int floorNumber, int rowNumber, int spaceNumber, string registration) {

    if (floorNumber < 1 || floorNumber > floors.size()) {
        cout << "Invalid floor!" << endl;
        return false;
    }

    ParkingFloor& floor = floors[floorNumber - 1];

    if (rowNumber < 1 || rowNumber > floor.rows.size()) {
        cout << "Invalid row!" << endl;
        return false;
    }

    ParkingRow& row = floor.rows[rowNumber - 1];

    if (spaceNumber < 1 || spaceNumber > row.spaces.size()) {
        cout << "Invalid parking space!" << endl;
        return false;
    }

    ParkingSpace& space = row.spaces[spaceNumber - 1];

    if (space.occupied) {
        cout << "This space is already occupied!" << endl;
        return false;
    }

    space.occupied = true;
    space.registrationNumber = registration;

    cout << "Vehicle " << registration
         << " parked successfully!" << endl;

    return true;
}

    void displayParking() {
        for (const auto& floor : floors) {
            cout << "Floor " << floor.floorNumber << endl;

            for (const auto& row : floor.rows) {
                cout << "  Row " << row.rowNumber << ": ";

                for (const auto& space : row.spaces) {
                    cout << (space.type == SpaceType::Compact
                        ? "[Compact"
                        : "[Large");

                    if (space.occupied) {
    cout << " - Occupied: " << space.registrationNumber << "] ";
} else {
    cout << " - Available] ";
}
                }

                cout << endl;
            }
        }
    }
};
#endif
