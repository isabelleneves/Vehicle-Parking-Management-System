#include "DoublyLinkedList.h"

int main() {

    DoublyLinkedList vehicles;

    vehicles.addVehicle("ABC123");
    vehicles.addVehicle("DEF456");
    vehicles.addVehicle("GHI789");

    std::cout << std::endl;

    vehicles.displayForward();
    vehicles.displayBackward();

    return 0;
}
