#include <SPI.h>
#include <mcp_can.h>

#define CAN0_INT 20  // Interrupt pin
#define SPI_CS_PIN 17 // Chip Select pin

MCP_CAN CAN0(SPI_CS_PIN);

void setup() {
    Serial.begin(115200);
    while (!Serial);

    // Initialize MCP2515 at 500kbps
    if (CAN0.begin(MCP_ANY, CAN_125KBPS, MCP_8MHZ) == CAN_OK)
        Serial.println("MCP2515 Initialized Successfully!");
    else
        Serial.println("MCP2515 Initialization Failed!");

    CAN0.setMode(MCP_NORMAL);
}

void loop() {
    if (!digitalRead(CAN0_INT)) {  // If MCP2515 has data
        long unsigned int rxId;
        unsigned char len;
        unsigned char rxBuf[8];

        CAN0.readMsgBuf(&rxId, &len, rxBuf);

        Serial.print("ID: ");
        Serial.print(rxId, HEX);
        Serial.print(" DATA: ");

        for (int i = 0; i < len; i++) {
            Serial.print(rxBuf[i], HEX);
            Serial.print(" ");
        }
        Serial.println();  // Newline for proper formatting
    }
}
