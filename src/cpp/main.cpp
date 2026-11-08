#include <iostream>
#include "Vehicle.h"

using namespace std;

int main() {

    Vehicle::Motorcycle motorcycle("ABC123");
    Vehicle::Car car("DEF456");
    Vehicle::Bus bus("GHI789");

    cout << "VEHICLE REGISTRATION TEST" << endl;
    cout << "-------------------------" << endl;

    cout << motorcycle.getType() << " - "
         << motorcycle.getRegistrationNumber() << endl;

    cout << car.getType() << " - "
         << car.getRegistrationNumber() << endl;

    cout << bus.getType() << " - "
         << bus.getRegistrationNumber() << endl;

    return 0;
}