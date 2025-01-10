// 2025 01 09 - Daniel Mitchell - iotcloudlabs.com
// This sketch and supporting files 
// is a working example of multiple parallel working tasks
// each task is split out into a separate file to keep the code as clean and easy to read and debug as possible
// One task is sharing temperature data to another task via a task-queue
// Initial concept credited to "The Las Outpost Workshop" Youtube tutorial : https://youtu.be/382p1NT1Wcs
// 10 Jan 2025 
// 

// System libraries
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include <Wire.h>

// Project libraries
#include "led1.h"       // Sketch
#include "led2.h"       // Sketch
#include "led3.h"       // Sketch
#include "temphumid.h"  // Sketch
#include "lcdupdate.h"  // Sketch

// Create a queue handle (global to main)
static QueueHandle_t tempQueue = NULL;

void setup() {
  Serial.begin(115200);
  delay(100);

  // Initialize I2C (using default pins on ESP32-S3: SDA=GPIO20, SCL=GPIO21)
  Wire.begin();

  // Create the queue to hold up to 5 float values (the temperature)
  tempQueue = xQueueCreate(5, sizeof(float));    

  xTaskCreatePinnedToCore(
      led1_sketch,  // Task function
      "taskName",   // Task name
      8192,         // Stack size
      NULL,         // Task input parameters
      1,            // Task priority, be carefull when changing this
      NULL,         // Task handle, add one if you want control over the task (resume or suspend the task)
      1             // Core to run the task on
  );

  xTaskCreatePinnedToCore(
      led2_sketch,  // Task function
      "taskName",   // Task name
      8192,         // Stack size
      NULL,         // Task input parameters
      1,            // Task priority, be carefull when changing this
      NULL,         // Task handle, add one if you want control over the task (resume or suspend the task)
      1             // Core to run the task on
  );

  xTaskCreatePinnedToCore(
      led3_sketch,     // Task function
      "taskName",      // Task name
      8192,            // Stack size
      NULL,            // Task input parameters
      1,               // Task priority, be carefull when changing this
      NULL,            // Task handle, add one if you want control over the task (resume or suspend the task)
      1                // Core to run the task on
  );

  xTaskCreatePinnedToCore(
      temphumid_sketch,   // Task function
      "taskName",         // Task name
      16192,              // Stack size
      (void*)tempQueue,   // Task input parameters
      1,                  // Task priority, be carefull when changing this
      NULL,               // Task handle, add one if you want control over the task (resume or suspend the task)
      1                   // Core to run the task on
  );

  xTaskCreatePinnedToCore(
      lcdupdate_sketch,   // Task function
      "taskName",         // Task name
      16192,              // Stack size
      (void*)tempQueue,   // Task input parameters
      1,                  // Task priority, be carefull when changing this
      NULL,               // Task handle, add one if you want control over the task (resume or suspend the task)
      1                   // Core to run the task on
  );
} // close setup

void loop()
{
}
