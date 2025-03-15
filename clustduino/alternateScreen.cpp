#include "alternateScreen.hpp"
#include "lcd.hpp"
#include <Adafruit_ST7735.h>

extern Adafruit_ST7735 tft;

void initAlternateScreen() {
  tft.fillScreen(ST77XX_BLACK);
  // Draw any static elements for the alternate screen here if needed
}

void displayAlternateScreen() {
  tft.setCursor(0, 0);
  tft.setTextColor(ST77XX_AMBER);
  tft.setTextSize(1);
  tft.print("Alternate Screen");
}
