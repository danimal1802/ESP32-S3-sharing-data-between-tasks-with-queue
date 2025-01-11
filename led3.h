#define LED_3_PIN 3

void led3_sketch(void *parameter) {
    // Setup start here
    pinMode(LED_3_PIN, OUTPUT);
    
    // End of your setup
    
    // Loop function, run repeatedly
    for (;;) {
        int led = digitalRead(LED_3_PIN);
        digitalWrite(LED_3_PIN, !led);
        delay(700); // Allow other tasks to run, adjust as needed
    }
}
