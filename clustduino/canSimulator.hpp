#pragma once

class CanSimulator {
public:
    void begin();
    void update();
    
    // Simulated values
    float torquelbf;
    float oilPressure;
    float coolantF;
    float boostPressure;

private:
    unsigned long lastUpdate = 0;
    const unsigned long updateInterval = 100; // Update every second
};

extern CanSimulator canSimulator;  // Declaration of the global instance
