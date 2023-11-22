// Define the GPIO pin for the LED and touch sensor
#define LED_PIN 25        // Replace with the actual GPIO pin for the LED
#define TOUCH_SENSOR_PIN 2 // Replace with the actual GPIO pin for the touch sensor

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(TOUCH_SENSOR_PIN, INPUT);
}

void loop() {
  // Check if touch is detected
  if (digitalRead(TOUCH_SENSOR_PIN) == HIGH) {
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
    delay(100);
  }
}
