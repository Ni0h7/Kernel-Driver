#include <windows.h>
#include <stdio.h>
#include <iostream>

int main() {
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    std::cout << "This works" << std::endl;
    HANDLE hDevice = CreateFile(L"\\\\.\\BufferDevice", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hDevice == INVALID_HANDLE_VALUE) {
        printf("Failed to open device\n");
        return 1;
    }

    CHAR writeBuffer[] = "Hello, world!";
    DWORD bytesWritten;
    if (!WriteFile(hDevice, writeBuffer, sizeof(writeBuffer) - 1, &bytesWritten, NULL)) {
        printf("WriteFile failed\n");
        CloseHandle(hDevice);
        return 1;
    }

    CHAR readBuffer[256];
    DWORD bytesRead;
    if (!ReadFile(hDevice, readBuffer, sizeof(readBuffer) - 1, &bytesRead, NULL)) {
        printf("ReadFile failed\n");
        CloseHandle(hDevice);
        return 1;
    }

    // Null-terminate the read buffer
    readBuffer[bytesRead] = '\0';
    printf("Read: %s\n", readBuffer);

    CloseHandle(hDevice);
    return 0;
}
