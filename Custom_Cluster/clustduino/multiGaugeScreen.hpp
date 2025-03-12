/*
#ifndef MULTIGAUGESCREEN_HPP
#define MULTIGAUGESCREEN_HPP

#include "images/bitmaps.h"
#include "lcd.hpp"
#include "fonts/Slimlines_MMKJ20pt7b.h"
//#include "canParse.hpp"
//#include "pressureSensorScreen.hpp"


void displayMultiGaugeScreen(void);

#endif
*/

//THIS is for simulation
#pragma once
#include "images/bitmaps.h"
#include "lcd.hpp"
#include "fonts/Slimlines_MMKJ20pt7b.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include "canSimulator.hpp"

extern CanSimulator canSimulator; // Declare global simulator instance

void displayMultiGaugeScreen(void);