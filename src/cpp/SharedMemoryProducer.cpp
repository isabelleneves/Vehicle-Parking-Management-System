#include <iostream>
#include <windows.h>
#include <cstring>

int main() {

    HANDLE sharedMemory = CreateFileMappingA(
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

    strcpy_s(sharedData, 256, "Vehicle ABC123 - Motorcycle");

    std::cout << "PRODUCER PROCESS" << std::endl;
    std::cout << "Vehicle information saved in shared memory." << std::endl;
    std::cout << "Keep this window open while the consumer reads the data." << std::endl;
    std::cout << "Press ENTER to close the producer." << std::endl;

    std::cin.get();

    UnmapViewOfFile(sharedData);
    CloseHandle(sharedMemory);

    return 0;
}

