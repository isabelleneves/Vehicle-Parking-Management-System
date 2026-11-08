#include <iostream>
#include <windows.h>
#include <cstring>

int main() {

    std::cout << "MESSAGE PASSING CLIENT" << std::endl;
    std::cout << "Connecting to the server..." << std::endl;

    if (!WaitNamedPipeA("\\\\.\\pipe\\ParkingMessagePipe", 10000)) {
        std::cout << "Could not connect to the server!" << std::endl;
        return 1;
    }

    HANDLE pipe = CreateFileA(
        "\\\\.\\pipe\\ParkingMessagePipe",
        GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if (pipe == INVALID_HANDLE_VALUE) {
        std::cout << "Error opening the pipe!" << std::endl;
        return 1;
    }

    const char* message = "Vehicle DEF456 - Car";

    DWORD bytesWritten = 0;

    BOOL success = WriteFile(
        pipe,
        message,
        static_cast<DWORD>(strlen(message) + 1),
        &bytesWritten,
        NULL
    );

    if (success) {
        std::cout << "Message sent successfully!" << std::endl;
    } else {
        std::cout << "Error sending message!" << std::endl;
    }

    CloseHandle(pipe);

    return 0;
}
