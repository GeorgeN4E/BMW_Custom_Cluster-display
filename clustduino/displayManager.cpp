#include "displayManager.hpp"
#include "multiGaugeScreen.hpp"
#include "alternateScreen.hpp"
#include <Arduino.h>

enum ScreenMode {
  MULTI_GAUGE,
  ALTERNATE_SCREEN
};

ScreenMode currentScreen = MULTI_GAUGE;
const int buttonPin = 2; // Change as needed for your wiring
bool buttonPressed = false;

void beginDisplays() {
  pinMode(buttonPin, INPUT_PULLUP);
  // Initialize static elements for the default screen
  initMultiGaugeScreen();
}

void runDisplayManager() {
  // Simple button debouncing and screen toggle
  if (digitalRead(buttonPin) == LOW) {
    if (!buttonPressed) {
      Serial.print("BuTtOn PrEsSeD \n");
      buttonPressed = true;
      // Toggle the screen mode
      currentScreen = (currentScreen == MULTI_GAUGE) ? ALTERNATE_SCREEN : MULTI_GAUGE;
      // Reinitialize static elements for the newly active screen
      if (currentScreen == MULTI_GAUGE)
        initMultiGaugeScreen();
      else
        initAlternateScreen();
    }
  } else {
    buttonPressed = false;
  }
  
  // Update the dynamic content for the active screen
  if (currentScreen == MULTI_GAUGE)
    displayMultiGaugeScreen();
  else
    displayAlternateScreen();
  
  delay(100); // Adjust refresh rate as needed
}
