#include "canSimulator.hpp"
#include <Arduino.h>

// Global instance definition
CanSimulator canSimulator;

void CanSimulator::begin() {
    randomSeed(analogRead(A0)); // Seed random with an unconnected analog pin
}

void CanSimulator::update() {
    if(millis() - lastUpdate >= updateInterval) {
        // Generate realistic random values
        torquelbf   = random(150, 200);
        oilPressure = random(20, 30);
        coolantF    = random(200, 230);
        boostPressure = random(5, 15);
        lastUpdate = millis();
    }
}
