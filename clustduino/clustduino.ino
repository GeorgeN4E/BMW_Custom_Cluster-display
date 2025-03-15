/*#include "lcd.hpp"
#include "multiGaugeScreen.hpp"

void setup() {
  Serial  .begin(115200);
  initDisplay();
}

void loop() {
  displayMultiGaugeScreen();
  delay(100); // Adjust refresh rate
}
*/

#include "lcd.hpp"
#include "displayManager.hpp"

void setup() {
  Serial.begin(115200);
  initDisplay();  // Make sure lcd.hpp declares this function.
  beginDisplays();
}

void loop() {
  runDisplayManager();
}
