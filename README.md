# MultiGauge Display for ST7735 Display
## **PROTOTYPE**

## Overview
This project is a multi-gauge display system designed for an ST7735 TFT screen, using an **Arduino-based** microcontroller. It retrieves sensor data from a CAN simulator and displays multiple automotive parameters, such as **boost pressure, torque, oil pressure, and coolant temperature**.

**Soon** will use MCP2515 canbus sniffer with a Raspberry PI pico to fetch real-time data from the car and use it as a secondary screen to display important engine data. 

## Demo
![](https://github.com/GeorgeN4E/BMW_Custom_Cluster-display/blob/main/media/demo.gif)

Note: The display's framerate is actually higher, but the GIF format makes it appear choppy.

## Features as of **now**
- Uses **Adafruit GFX** and **Adafruit ST7735** libraries for display handling.
- Reads real-time data frsom the **CAN bus simulator**.
- Displays sensor values dynamically on a **1-bit canvas**.
- Static icons representing different gauges.
- Uses **efficient rendering** to update only necessary portions of the screen.

## Hardware Requirements
- **Microcontroller** (Arduino, ESP32, Raspberry Pi Pico, etc.)
- **Adafruit ST7735 TFT Display** (160x80 resolution)
- **MCP2515 CAN Module** (or equivalent CAN simulator)

## Software Requirements
- Arduino IDE
- Required Libraries:
  - Adafruit GFX
  - Adafruit ST7735
  - Custom **CanSimulator** class

## Setup & Usage
1) **Install Required Libraries** in the Arduino IDE.

2) **Connect the ST7735 display** to your microcontroller:
   - **VCC** → 5V
   - **GND** → GND
   - **SCK** → SPI Clock (SCL)
   - **SDA** → SPI MOSI
   - **A0 (DC)** → Data/Command Pin
   - **RST** → Reset
   - **CS** → Chip Select
   
3) **Flash the code** to the microcontroller.

4) The screen should initialize and display real-time gauge data.

## Troubleshooting
- **Blank Screen?** Ensure SPI connections are correct and display power is stable.
- **No Text?** Check that `GFXcanvas1` is being drawn correctly using `drawBitmap()`.
- **Incorrect Values?** Verify CAN simulator data updates and `canSimulator.update()` is being called.
