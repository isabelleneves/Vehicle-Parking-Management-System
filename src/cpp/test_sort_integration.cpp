#include "ParkingSystem.h"

int main() {

    ParkingSystem parking;

    // Create three different vehicle types
    Vehicle::Motorcycle motorcycle("ABC123");
    Vehicle::Car car("DEF456");
    Vehicle::Bus bus("GHI789");

    cout << "\nVEHICLE PARKING TEST" << endl;

    // Park vehicles in a different order
    parking.parkVehicle(motorcycle);
    parking.parkVehicle(car);
    parking.parkVehicle(bus);

    cout << "\nVEHICLE RECORDS" << endl;
    parking.displayVehicleRecords();

    cout << "\nSORTING TEST" << endl;
    parking.displayVehiclesSortedByType();

    return 0;
}