#include <iostream>
#include <serial/serial.h>  // Cross-platform serial communication library

// Define the data structure
struct SensorData {
    uint8_t header = 0xAA;       // Header byte to identify the start of a packet
    uint16_t temperature;        // Temperature value (2 bytes)
    uint16_t rpm;                // RPM value (2 bytes)
    uint8_t fuelLevel;           // Fuel level (1 byte)
    uint16_t speed;              // Speed (2 bytes)
    uint8_t checksum;            // Checksum for error detection (1 byte)
};

// Function to calculate the checksum
uint8_t calculateChecksum(const SensorData& data) {
    uint8_t checksum = 0;
    const uint8_t* bytes = reinterpret_cast<const uint8_t*>(&data);
    for (size_t i = 0; i < sizeof(SensorData) - 1; i++) {
        checksum += bytes[i];
    }
    return checksum;
}

int main() {
    // Create a SensorData packet
    SensorData data;
    data.temperature = 25;  // Example temperature
    data.rpm = 3000;        // Example RPM
    data.fuelLevel = 75;    // Example fuel level
    data.speed = 60;        // Example speed
    data.checksum = calculateChecksum(data);

    // Open the serial port
    serial::Serial mySerial("/dev/ttyUSB0", 115200, serial::Timeout::simpleTimeout(1000));  // Replace "/dev/ttyUSB0" with your port

    if (!mySerial.isOpen()) {
        std::cerr << "Error opening serial port!" << std::endl;
        return 1;
    }

    // Send the packet to the Arduino
    mySerial.write(reinterpret_cast<uint8_t*>(&data), sizeof(SensorData));

    std::cout << "Data sent successfully!" << std::endl;

    // Close the serial port
    mySerial.close();
    return 0;
}