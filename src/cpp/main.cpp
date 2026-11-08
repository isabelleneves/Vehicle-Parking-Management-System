#include "ParkingSystem.h"

int main() {
    ParkingSystem parking;

    Vehicle::Motorcycle motorcycle("ABC123");
    Vehicle::Car car("DEF456");
    Vehicle::Bus bus("GHI789");

    cout << "VEHICLE PARKING MANAGEMENT SYSTEM" << endl;
    cout << "---------------------------------" << endl;

    parking.parkVehicle(motorcycle);
    parking.parkVehicle(car);
    parking.parkVehicle(bus);

    cout << endl << "PARKING STATUS" << endl;

    parking.displayParking();

    return 0;
}

