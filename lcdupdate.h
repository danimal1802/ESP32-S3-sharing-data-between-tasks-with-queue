#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include <Wire.h>
#include "Arduino.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

// If your SSD1306 is 128x64 pixels
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// I2C address for most 128x64 OLEDs is 0x3C.
// Some displays may use 0x3D. Adjust if needed.
#define OLED_ADDR 0x3C

// Create the display object connected via I2C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

float temp = 0.0f;
float humidity = 0.0f;

void lcdupdate_sketch(void *pvParameter) {
  // Cast the parameter to a QueueHandle_t
  QueueHandle_t tempQueue = (QueueHandle_t)pvParameter;

  Wire.begin();

  // Initialize the SSD1306 display
  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
    // Clear the buffer
  display.clearDisplay();

  // Set text size and color
  display.setTextSize(2);         // Normal 1:1 pixel scale
  display.setTextColor(WHITE);    // Draw white text

  // Set the cursor to top-left corner
  display.setCursor(0, 0);

  while (true) {
    display.clearDisplay();
    // Wait indefinitely for a new temperature value
    if (xQueueReceive(tempQueue, &temp, portMAX_DELAY) == pdTRUE) {
      Serial.print("lcdupdate -> Received temperature: ");
      Serial.println(temp);
      display.setCursor(0,0);
      display.print(temp);
      display.println(" C");
      vTaskDelay(pdMS_TO_TICKS(100));  // short delay for other tasks to run
    } // close if

    // Wait indefinitely for a new humidity value
    if (xQueueReceive(tempQueue, &humidity, portMAX_DELAY) == pdTRUE) {
      Serial.print("lcdupdate -> Received humidity: ");
      Serial.print(humidity);
      Serial.println(" rH");
      display.setCursor(0,27);
      display.print(humidity);
      display.println(" %");
      vTaskDelay(pdMS_TO_TICKS(100));  // short delay for other tasks to run
    } // close if

    display.display();

    vTaskDelay(pdMS_TO_TICKS(2000));
  } // close while
}
 

