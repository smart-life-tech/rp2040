#include <Arduino.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define LED_PIN 25
#define TOUCH_SENSOR_PIN 2

volatile bool touchDetected = false;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(TOUCH_SENSOR_PIN, INPUT_PULLUP); // Internal pull-up to keep the pin high when not touched

  attachInterrupt(digitalPinToInterrupt(TOUCH_SENSOR_PIN), touchInterrupt, FALLING); // Interrupt on falling edge

  delay(1000); // Allow time for sensor initialization, adjust as needed
}

void loop()
{
  // Check if touch is detected
  if (touchDetected)
  {
    touchDetected = false; // Reset the flag
    // LED is off, breathe effect
    for (int i = 0; i < 255; ++i)
    {
      analogWrite(LED_PIN, i);
      delay(5);
    }
    for (int i = 255; i >= 0; --i)
    {
      analogWrite(LED_PIN, i);
      delay(5);
    }
  }
  else
  {
    // LED is on, no touch detected
    analogWrite(LED_PIN, 0); // Turn off the LED

    // Put the device to sleep
    lowPowerSleep();
    // The program resumes from here when it wakes up
  }
}

void touchInterrupt()
{
  touchDetected = true; // Set the flag to indicate touch detected
}

// Sleep function for low power mode
void lowPowerSleep()
{
  // Note: Arduino RP2040 core provides the sleep function
  sleep(1); // Sleep for 1 second, adjust as needed
}
