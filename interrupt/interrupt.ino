#include <Arduino.h>
#include <LowPower.h>
//#include "pico/stdlib.h"
//#include "hardware/gpio.h"

#define LED_PIN 25
#define TOUCH_SENSOR_PIN 2

volatile bool touchDetected = false;

void setup() {
    pinMode(LED_PIN, OUTPUT);
    pinMode(TOUCH_SENSOR_PIN, INPUT_PULLUP); // Internal pull-up to keep the pin high when not touched

    attachInterrupt(digitalPinToInterrupt(TOUCH_SENSOR_PIN), touchInterrupt, FALLING); // Interrupt on falling edge

    delay(1000); // Allow time for sensor initialization, adjust as needed
}

void loop() {
    // Check if touch is detected
    if (touchDetected) {
        touchDetected = false; // Reset the flag
        // LED is off, breathe effect
        for (int i = 0; i < 255; ++i) {
            analogWrite(LED_PIN, i);
            delayMicroseconds(5000);
        }
        for (int i = 255; i >= 0; --i) {
            analogWrite(LED_PIN, i);
            delayMicroseconds(5000);
        }
    } else {
        // LED is on, no touch detected
        analogWrite(LED_PIN, 0); // Turn off the LED

        // Put the device to sleep using LowPower library
        lowPowerSleep();
        // The program resumes from here when it wakes up
    }
}

void touchInterrupt() {
    touchDetected = true; // Set the flag to indicate touch detected
}

// Sleep function for low power mode
void lowPowerSleep() {
    //LowPower.sleep(10000); // Sleep for 10 seconds, adjust as needed
}
