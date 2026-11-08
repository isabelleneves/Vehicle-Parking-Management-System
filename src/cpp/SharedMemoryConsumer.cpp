#include <iostream>
#include <windows.h>

int main() {

    HANDLE sharedMemory = OpenFileMappingA(
        FILE_MAP_ALL_ACCESS,
        FALSE,
        "ParkingSharedMemory"
    );

    if (sharedMemory == NULL) {
        std::cout << "Could not open shared memory!" << std::endl;
        std::cout << "Make sure the producer is running first." << std::endl;
        return 1;
    }

    char* sharedData = (char*)MapViewOfFile(
        sharedMemory,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        256
    );

    if (sharedData == NULL) {
        std::cout << "Could not access shared memory!" << std::endl;
        CloseHandle(sharedMemory);
        return 1;
    }

    std::cout << "CONSUMER PROCESS" << std::endl;
    std::cout << "Message received from shared memory:" << std::endl;
    std::cout << sharedData << std::endl;

    UnmapViewOfFile(sharedData);
    CloseHandle(sharedMemory);

    return 0;
}