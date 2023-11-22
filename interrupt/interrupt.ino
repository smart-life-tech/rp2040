#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define LED_PIN 25
#define TOUCH_SENSOR_PIN 2

volatile bool touchDetected = false;

void setup() {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_init(TOUCH_SENSOR_PIN);
    gpio_set_dir(TOUCH_SENSOR_PIN, GPIO_IN);
    gpio_pull_up(TOUCH_SENSOR_PIN);

    // Configure interrupt for falling edge on touch sensor pin
    gpio_set_irq_enabled_with_callback(TOUCH_SENSOR_PIN, GPIO_IRQ_EDGE_FALL, true, &touchInterrupt);

    sleep_ms(1000); // Allow time for sensor initialization, adjust as needed
}

void loop() {
    // Check if touch is detected
    if (touchDetected) {
        touchDetected = false; // Reset the flag
        // LED is off, breathe effect
        for (int i = 0; i < 255; ++i) {
            gpio_put(LED_PIN, i);
            sleep_ms(5);
        }
        for (int i = 255; i >= 0; --i) {
            gpio_put(LED_PIN, i);
            sleep_ms(5);
        }
    } else {
        // LED is on, no touch detected
        gpio_put(LED_PIN, 0); // Turn off the LED

        // Put the device to sleep
        sleep();
        // The program resumes from here when it wakes up
    }
}

void touchInterrupt(uint gpio, uint32_t events) {
    touchDetected = true; // Set the flag to indicate touch detected
}
