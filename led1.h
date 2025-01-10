#include <Arduino.h>

#define LED_1_PIN 5

void led1_sketch(void *parameter) {
    // Setup start here
    pinMode(LED_1_PIN, OUTPUT);
    
    // End of your setup
    
    // Loop function, run repeatedly
    for (;;) {
        int led = digitalRead(LED_1_PIN);
        digitalWrite(LED_1_PIN, !led);
        delay(400); // Allow other tasks to run, adjust as needed
    }
}
