#include "lcd.hpp"
#include <SPI.h>

// Initialize with ST7735 constructor
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void initDisplay(void) {
	// Initialize with appropriate settings for 7735S
	tft.initR(INITR_BLACKTAB); // Common initialization for ST7735S
	tft.setRotation(3);        // Adjust rotation if needed

	tft.fillScreen(ST77XX_BLKAMBER);
	tft.enableDisplay(true);
	Serial.print("Display Initialized with ST7735S!");
}