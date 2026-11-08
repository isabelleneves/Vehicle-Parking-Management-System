#include "ParkingSystem.h"

int main() {
    ParkingSystem parking;

    // Occupy all compact spaces in the first row
    parking.occupySpace(1, 1, 1, "CAR001");
    parking.occupySpace(1, 1, 2, "CAR002");
    parking.occupySpace(1, 1, 3, "CAR003");

    Vehicle::Car car("DEF456");

    cout << endl << "CAR PARKING TEST" << endl;

    parking.parkVehicle(car);

    cout << endl << "PARKING STATUS" << endl;
    parking.displayParking();

    return 0;
}