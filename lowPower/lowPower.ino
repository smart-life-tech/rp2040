#include <ArduinoLowPower.h>

#define LED_PIN 25
#define TOUCH_SENSOR_PIN 2

unsigned long lastTouchTime = 0;
const unsigned long sleepDelay = 10000; // 10 seconds

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(TOUCH_SENSOR_PIN, INPUT);
}

void loop() {
  // Check if touch is detected
  if (digitalRead(TOUCH_SENSOR_PIN) == HIGH) {
    lastTouchTime = millis(); // Update the last touch time
    // LED is off, breathe effect
    for (int i = 0; i < 255; ++i) {
      analogWrite(LED_PIN, i);
      delay(5);
    }
    for (int i = 255; i >= 0; --i) {
      analogWrite(LED_PIN, i);
      delay(5);
    }
  } else {
    // LED is on, no touch detected
    analogWrite(LED_PIN, 0); // Turn off the LED

    // Check if it's time to go to sleep
    if (millis() - lastTouchTime >= sleepDelay) {
      // Put the device to sleep
      LowPower.sleep();
      // The program resumes from here when it wakes up
    }

    delay(100);
  }
}
