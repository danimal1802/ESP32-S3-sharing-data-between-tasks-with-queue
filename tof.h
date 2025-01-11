#include <VL53L1X.h>

// Create an instance of the VL53L1X class
VL53L1X distanceSensor;

void tof_sketch(void *pvParameter) {
  // Initialize serial communication for debugging
  //Serial.begin(115200);
  //while (!Serial) {
  //  // Wait for serial port to be available (helpful in some environments)
  //}

  // Initialize I2C
  //Wire.begin();  // On most ESP32-S3 boards, SDA=GPIO8 and SCL=GPIO9 by default
                 // Check your board's pinout if using custom hardware

  // Set a timeout in case the sensor never becomes ready
  distanceSensor.setTimeout(500);

   // Initialize the sensor
  while (!distanceSensor.init()) {
    Serial.println("Failed to detect and initialize VL53L1X sensor!");
    vTaskDelay(pdMS_TO_TICKS(2000));
  }

  Serial.println("VL53L1X initialized successfully!");

  // Optional sensor configurations
  // Long distance mode for up to 4m (depending on conditions)
  distanceSensor.setDistanceMode(VL53L1X::Long);

  // Set measurement timing budget (time the sensor takes for one measurement)
  // in microseconds (typical values: 20000 to 100000)
  distanceSensor.setMeasurementTimingBudget(50000);

  // Start continuous measurements at a given interval (in ms)
  // Alternatively, you could call distanceSensor.read() once per loop without continuous mode
  distanceSensor.startContinuous(50);

  Serial.println("VL53L1X is initialized and continuous mode has started.");

  QueueHandle_t tofQueue = (QueueHandle_t)pvParameter; 

  while (true) {
    // Read the distance measurement in millimeters
    uint16_t distance = distanceSensor.read();
  
    // Print distance value
    // The sensor returns a distance in millimeters
    if (!distanceSensor.timeoutOccurred()) {
      Serial.print("tof-Distance (mm): ");
      Serial.println(distance);
            // Send the temperature to the queue
      if (xQueueSend(tofQueue, &distance, 0) == pdTRUE) {
        Serial.print("tof -> Sent distance: ");
        Serial.println(distance);
      } else {
        Serial.println("MeasureTask -> Queue is full, could not send data.");
      }
    } else {
      Serial.println("tof-Sensor timeout!");
    }

    vTaskDelay(pdMS_TO_TICKS(500));
  }
}
