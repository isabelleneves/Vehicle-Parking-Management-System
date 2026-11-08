#include "ParkingSystem.h"

int main() {
    ParkingSystem parking;

    cout << "VEHICLE PARKING MANAGEMENT SYSTEM" << endl;
    cout << "---------------------------------" << endl;

    parking.occupySpace(1, 1, 1, "ABC123");
    parking.occupySpace(1, 1, 2, "DEF456");
    parking.occupySpace(1, 1, 1, "GHI789");

    cout << endl << "PARKING STATUS" << endl;

    parking.displayParking();

    return 0;
}