#ifndef LCD_HPP
#define LCD_HPP

#include <Adafruit_ST7735.h> // Changed from ST7789
#include <Adafruit_GFX.h>

// LCD Pins (keep same hardware configuration)
#define TFT_CS        9
#define TFT_RST       8
#define TFT_DC        10
#define TFT_BACKLIGHT 7

// Color definitions (keep your custom colors)
#define ST77XX_AMBER 0xD0E0
#define ST77XX_BLKAMBER 0x2000

// Change display type to ST7735
extern Adafruit_ST7735 tft;

void initDisplay(void);

#endif