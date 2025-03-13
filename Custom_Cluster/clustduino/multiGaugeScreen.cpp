#include "multiGaugeScreen.hpp"
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

// Display dimensions (rotated 80x160)
#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 80

//0x0 corner
#define screen0_x = 
#define screen0_y = 

// Canvas dimensions
#define multiGaugeCanvasHeight 55
#define multiGaugeCanvasWidth 60
GFXcanvas1 multiGaugeCanvas(multiGaugeCanvasWidth, multiGaugeCanvasHeight);

// Timing and state variables
uint32_t flashTimer[4] = {millis(), millis(), millis(), millis()};
bool flashState[4] = {false, false, false, false};
bool shouldFlash[4] = {false, false, false, false};

// Measurement tracking
float boostMax = 0;
float torqueMax = 0;

// External dependencies
extern CanSimulator canSimulator;
extern Adafruit_ST7735 tft;

// Forward declaration
void updateGauge(int x, int y, int index, float value, int decimals, bool showMax);

void displayMultiGaugeScreen(void) {
    canSimulator.update();

    // Clear screen and setup
    tft.fillScreen(ST77XX_BLKAMBER);
    multiGaugeCanvas.setFont(&Slimlines12pt7b);
    multiGaugeCanvas.setTextSize(1);

    // Grid layout calculations
    const int gridX = SCREEN_WIDTH / 2;
    const int gridY = SCREEN_HEIGHT / 2;
    
    /*
    //DEBUG HOW TO ALIGN icons
    uint16_t aa = tft.color565(128, 0, 0);
    uint16_t bb = tft.color565(0, 128, 0);
    uint16_t cc = tft.color565(0, 0, 128);
    uint16_t dd = tft.color565(128, 128, 0);
    tft.setCursor(0,0);
    tft.fillRect(0, 26, 40, 40, aa);
    tft.fillRect(80,26, 40, 40, bb);
    tft.fillRect(0, 66, 40, 40, cc);
    tft.fillRect(80,66, 40, 40, dd);
    */

    tft.setCursor(0,0);
    tft.drawBitmap(0, 26, gauge_logo_turbo,         gauge_logo_bitmap_width, gauge_logo_bitmap_height, ST77XX_AMBER);
    tft.drawBitmap(80,26, gauge_logo_bitmap_1,      gauge_logo_bitmap_width, gauge_logo_bitmap_height, ST77XX_AMBER);
    tft.drawBitmap(0, 66, gauge_logo_bitmap_2,      gauge_logo_bitmap_width, gauge_logo_bitmap_height, ST77XX_AMBER);
    tft.drawBitmap(80,66, gauge_logo_coolant_temp,  gauge_logo_bitmap_width, gauge_logo_bitmap_height, ST77XX_AMBER);

    // Update max values
    boostMax = max(boostMax, canSimulator.boostPressure);
    torqueMax = max(torqueMax, canSimulator.torquelbf);

    // Warning thresholds
    shouldFlash[0] = (canSimulator.boostPressure > 12);   // Boost
    shouldFlash[1] = (canSimulator.torquelbf > 170);      // Torque
    shouldFlash[2] = (canSimulator.oilPressure < 22);     // Oil
    shouldFlash[3] = (canSimulator.coolantF > 220);       // Coolant

    // Update flash states
    for(int i = 0; i < 4; i++) {
        if(millis() - flashTimer[i] > 500) {
            flashState[i] = !flashState[i];
            flashTimer[i] = millis();
        }
    }

    // Display positions (adjusted for 80x160)
    const int col1 = 5;    // Left column
    const int col2 = 45;   // Right column
    const int row1 = 5;    // Top row
    const int row2 = 85;   // Bottom row
/*
    // Update gauges
    updateGauge(col1, row1, 0, canSimulator.boostPressure, 1, true);
    updateGauge(col2, row1, 1, canSimulator.torquelbf, (canSimulator.torquelbf >= 100) ? 0 : 1, false);
    updateGauge(col1, row2, 2, canSimulator.oilPressure, 0, false);
    updateGauge(col2, row2, 3, canSimulator.coolantF, 0, false);
*/
    // Reset max values if warnings clear
    if(!shouldFlash[0] && (millis() - flashTimer[0] > 5000)) boostMax = 0;
    if(!shouldFlash[1] && (millis() - flashTimer[1] > 5000)) torqueMax = 0;
}

void updateGauge(int x, int y, int index, float value, int decimals, bool showMax) {
    multiGaugeCanvas.fillScreen(ST77XX_BLACK);
    multiGaugeCanvas.setCursor(0, 18);
    
    if(shouldFlash[index] && !flashState[index]) {
        multiGaugeCanvas.print("--");
    } else {
        if(showMax) {
            multiGaugeCanvas.print(value, decimals);
        } else {
            multiGaugeCanvas.print((int)value);
        }
    }
    
    tft.drawBitmap(x, y, multiGaugeCanvas.getBuffer(), 
                  multiGaugeCanvasWidth, multiGaugeCanvasHeight, 
                  ST77XX_AMBER, ST77XX_BLKAMBER);
}