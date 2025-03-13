/*#include "lcd.hpp"
#include "multiGaugeScreen.hpp"

void setup() {
  Serial.begin(115200);
  initDisplay();
}

void loop() {
  displayMultiGaugeScreen();
  delay(100); // Adjust refresh rate
}
*/

#include "multiGaugeScreen.hpp"
#include "canSimulator.hpp"

CanSimulator canSimulator; // Define global instance

void setup() {
    Serial.begin(115200);
    initDisplay();
    canSimulator.begin();
    displayMultiGaugeScreen();
}

void loop() {
    
    //should be here but to be static I will put it in setup
    //displayMultiGaugeScreen();
    delay(100);
}