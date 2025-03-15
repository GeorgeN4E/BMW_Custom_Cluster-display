#include "multiGaugeScreen.hpp"
#include "lcd.hpp"
#include "canSimulator.hpp"
#include "images/bitmaps80_160.h"
#include "fonts/Slimlines12pt7b.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

// Global objects (declared as extern if defined elsewhere)
extern CanSimulator canSimulator;
extern Adafruit_ST7735 tft;

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 80
#define multiGaugeCanvasWidth  40
#define multiGaugeCanvasHeight 40

// Use a 1-bit canvas (binary: each pixel is 0 or 1)
GFXcanvas1 multiGaugeCanvas(multiGaugeCanvasWidth, multiGaugeCanvasHeight);

// Static initialization: draw background and icons once
void initMultiGaugeScreen() {
  tft.fillScreen(ST77XX_BLKAMBER);
  const int square_topleft_x  = 0;
  const int square_topright_x = 80;
  const int square_botleft_x  = 0;
  const int square_botright_x = 80;
  const int square_topleft_y  = 26;
  const int square_topright_y = 26;
  const int square_botleft_y  = 66;
  const int square_botright_y = 66;
  
  tft.drawBitmap(square_topleft_x , square_topleft_y  , gauge_logo_turbo,        gauge_logo_bitmap_width, gauge_logo_bitmap_height, ST77XX_AMBER);
  tft.drawBitmap(square_topright_x, square_topright_y , gauge_logo_piston,       gauge_logo_bitmap_width, gauge_logo_bitmap_height, ST77XX_AMBER);
  tft.drawBitmap(square_botleft_x , square_botleft_y  , gauge_logo_oil_can,      gauge_logo_bitmap_width, gauge_logo_bitmap_height, ST77XX_AMBER);
  tft.drawBitmap(square_botright_x, square_botright_y , gauge_logo_coolant_temp, gauge_logo_bitmap_width, gauge_logo_bitmap_height, ST77XX_AMBER);
}

// Update a single gauge value (dynamic part) using a 1-bit canvas
void updateGauge(int x, int y, int index, float value, int decimals, bool showMax) {
  // For a 1-bit canvas, fill with 0 (which will be drawn as the background color)
  multiGaugeCanvas.fillScreen(0);
  
  // Set font and text size if needed
  multiGaugeCanvas.setFont(&Slimlines12pt7b);
  multiGaugeCanvas.setTextSize(1);
  
  // In a 1-bit canvas, use 1 for the text (foreground) and 0 for background.
  multiGaugeCanvas.setTextColor(1, 0);
  multiGaugeCanvas.setCursor(0, 18);
  
  if(showMax)
    multiGaugeCanvas.print(value, decimals);
  else
    multiGaugeCanvas.print((int)value);
  
  
  // Draw the updated gauge onto the TFT display.
  // Pixels with value 1 will be drawn as ST77XX_AMBER (foreground)
  // Pixels with value 0 will be drawn as ST77XX_BLKAMBER (background)
  tft.drawBitmap(x, y, multiGaugeCanvas.getBuffer(), 
                 multiGaugeCanvasWidth, multiGaugeCanvasHeight, 
                 ST77XX_AMBER, ST77XX_BLKAMBER);
}

// Update dynamic gauge values using sensor data
void displayMultiGaugeScreen() {
  canSimulator.update();
  const int spacing = 44;
  const int square_topleft_x  = 0;
  const int square_topright_x = 80;
  const int square_botleft_x  = 0;
  const int square_botright_x = 80;
  
  updateGauge(square_topleft_x  + spacing, 33, 0, canSimulator.boostPressure, 1, true);
  updateGauge(square_topright_x + spacing, 33, 1, canSimulator.torquelbf, (canSimulator.torquelbf >= 100) ? 0 : 1, false);
  updateGauge(square_botleft_x  + spacing, 73, 2, canSimulator.oilPressure, 0, false);
  updateGauge(square_botright_x + spacing, 73, 3, canSimulator.coolantF, 0, false);
}
