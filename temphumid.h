#include <Adafruit_AHTX0.h>

Adafruit_AHTX0 aht;


void temphumid_sketch(void *pvParameter) {
    // Setup start here
    //pinMode(LED_2_PIN, OUTPUT);
    //Serial.begin(115200); 
    //delay(100);  // Give time for the Serial to initialize

    // Initialize I2C communication
    // If your board uses different pins for SDA/SCL, specify them:
    // e.g.: Wire.begin(20, 21);
    //Wire.begin();
    
    // Initialize the AHT20 sensor
    if (!aht.begin()) {
      Serial.println("Failed to find AHT20 sensor! Check wiring/I2C address.");
      while (1) {
        delay(10);  // Halt program
      }
    }
    Serial.println("AHT20 initialized successfully!");

    QueueHandle_t tempQueue = (QueueHandle_t)pvParameter;    

    sensors_event_t humidity, temp;

    // End of your setup

    // Loop function, run repeatedly
    while (true) {
      // Request a reading
      aht.getEvent(&humidity, &temp);

      // Print temperature (in °C) and humidity (%)
      Serial.print("Temperature: ");
      Serial.print(temp.temperature);
      Serial.print(" °C,  Humidity: ");
      Serial.print(humidity.relative_humidity);
      Serial.println(" %");

      // Send the temperature to the queue
      if (xQueueSend(tempQueue, &temp.temperature, 0) == pdTRUE) {
        Serial.print("temphumid -> Sent temperature: ");
        Serial.println(temp.temperature);
      } else {
        Serial.println("MeasureTask -> Queue is full, could not send data.");
      }
      // Send the humidity to the queue
      if (xQueueSend(tempQueue, &humidity.relative_humidity, 0) == pdTRUE) {
        Serial.print("temphumid -> Sent humidity: ");
        Serial.println(humidity.relative_humidity);
      } else {
        Serial.println("temphumid -> Queue is full, could not send data.");
      }


      vTaskDelay(pdMS_TO_TICKS(100)); 
    }
}
