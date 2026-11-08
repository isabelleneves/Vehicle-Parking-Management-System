#include <iostream>
#include <windows.h>

int main() {

    HANDLE pipe = CreateNamedPipeA(
        "\\\\.\\pipe\\ParkingMessagePipe",
        PIPE_ACCESS_INBOUND,
        PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
        1,
        256,
        256,
        0,
        NULL
    );

    if (pipe == INVALID_HANDLE_VALUE) {
        std::cout << "Error creating named pipe!" << std::endl;
        return 1;
    }

    std::cout << "MESSAGE PASSING SERVER" << std::endl;
    std::cout << "Waiting for a client..." << std::endl;

    BOOL connected = ConnectNamedPipe(pipe, NULL);

    if (connected || GetLastError() == ERROR_PIPE_CONNECTED) {

        char buffer[256] = {};
        DWORD bytesRead = 0;

        BOOL success = ReadFile(
            pipe,
            buffer,
            sizeof(buffer) - 1,
            &bytesRead,
            NULL
        );

        if (success && bytesRead > 0) {
            std::cout << "Message received:" << std::endl;
            std::cout << buffer << std::endl;
        }
    }

    FlushFileBuffers(pipe);
    DisconnectNamedPipe(pipe);
    CloseHandle(pipe);

    return 0;
}
