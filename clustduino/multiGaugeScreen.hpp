#pragma once

// Include necessary headers (fonts, bitmaps, etc.) in your actual file
#include <Adafruit_ST7735.h>

void initMultiGaugeScreen();
void displayMultiGaugeScreen();
void updateGauge(int x, int y, int index, float value, int decimals, bool showMax);
