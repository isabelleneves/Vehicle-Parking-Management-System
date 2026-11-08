#include <iostream>
#include <windows.h>
#include <cstring>

int main() {

    HANDLE sharedMemory;
    char* sharedData;

    sharedMemory = CreateFileMappingA(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        256,
        "ParkingSharedMemory"
    );

    if (sharedMemory == NULL) {
        std::cout << "Could not create shared memory!" << std::endl;
        return 1;
    }

    sharedData = (char*)MapViewOfFile(
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

    strcpy_s(sharedData, 256, "Vehicle ABC123 is parked!");

    std::cout << "Shared Memory Test" << std::endl;
    std::cout << "Message stored: " << sharedData << std::endl;

    UnmapViewOfFile(sharedData);
    CloseHandle(sharedMemory);

    return 0;
}
