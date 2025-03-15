#include <iostream>
#include <fstream>
#include <windows.h>

int main() {
    const char* portName = "COM6";  // Change this to match your Pico's COM port

    // Open the serial port
    HANDLE hSerial = CreateFileA(portName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: Cannot open serial port!" << std::endl;
        return 1;
    }

    // Configure serial port settings
    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error: Cannot get serial port state!" << std::endl;
        CloseHandle(hSerial);
        return 1;
    }
    dcbSerialParams.BaudRate = CBR_115200;  // Match Pico baud rate
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.Parity = NOPARITY;
    dcbSerialParams.StopBits = ONESTOPBIT;
    SetCommState(hSerial, &dcbSerialParams);

    std::ofstream outputFile("can_log.txt", std::ios::app);
    if (!outputFile) {
        std::cerr << "Error: Cannot open file!" << std::endl;
        CloseHandle(hSerial);
        return 1;
    }

    char buffer[128];
    DWORD bytesRead;

    std::cout << "Listening on " << portName << "..." << std::endl;

    while (true) {
        if (ReadFile(hSerial, buffer, sizeof(buffer) - 1, &bytesRead, NULL)) {
            buffer[bytesRead] = '\0';
            std::cout << buffer;  // Show received data
            outputFile << buffer; // Save to file
            outputFile.flush();
        }
    }

    CloseHandle(hSerial);
    outputFile.close();
    return 0;
}
