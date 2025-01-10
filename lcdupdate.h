#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include <Wire.h>
#include "LiquidCrystal_I2C.h"
#include "Arduino.h"

// Often, the I2C address for a 2004A display with PCF8574 is 0x27 or 0x3F.
// If you are unsure, run an I2C scanner or try these addresses.
#define LCD_I2C_ADDRESS 0x27  

// Create a 20x4 LCD object
LiquidCrystal_I2C lcd(LCD_I2C_ADDRESS, 20, 4);

float temp = 0.0f;
float humidity = 0.0f;

void lcdupdate_sketch(void *pvParameter) {
  // Cast the parameter to a QueueHandle_t
  QueueHandle_t tempQueue = (QueueHandle_t)pvParameter;

lcd.backlight();  // Turn on the LCD backlight
lcd.clear();      // clear the display
  
  while (true) {
    // Wait indefinitely for a new temperature value
    if (xQueueReceive(tempQueue, &temp, portMAX_DELAY) == pdTRUE) {
      Serial.print("lcdupdate -> Received temperature: ");
      Serial.println(temp);
      lcd.setCursor(0, 0);
      lcd.print(temp);
      lcd.print(" C");
      vTaskDelay(pdMS_TO_TICKS(100));  // short delay for other tasks to run
    } // close if

    // Wait indefinitely for a new humidity value
    if (xQueueReceive(tempQueue, &humidity, portMAX_DELAY) == pdTRUE) {
      Serial.print("lcdupdate -> Received humidity: ");
      Serial.println(humidity);
      lcd.setCursor(9, 0);
      lcd.print(humidity);
      lcd.print(" %rH");
      vTaskDelay(pdMS_TO_TICKS(100));  // short delay for other tasks to run
    } // close if


  vTaskDelay(pdMS_TO_TICKS(2000));
  } // close while
}
 

