#include <Arduino.h>

#define LED_2_PIN 16

void led2_sketch(void *parameter) {
    // Setup start here
    pinMode(LED_2_PIN, OUTPUT);
    
    // End of your setup
    
    // Loop function, run repeatedly
    for (;;) {
        int led = digitalRead(LED_2_PIN);
        digitalWrite(LED_2_PIN, !led);
        delay(200); // Allow other tasks to run, adjust as needed
    }
}
