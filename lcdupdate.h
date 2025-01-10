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

// Initialize the LCD
//lcd.init();     
//lcd.backlight();  // Turn on the LCD backlight
// Clear the display 
//lcd.clear();

float temp = 0.0f;

void lcdupdate_sketch(void *pvParameter) {
  // Cast the parameter to a QueueHandle_t
  QueueHandle_t tempQueue = (QueueHandle_t)pvParameter;
  
  
  while (true) {
    // Wait indefinitely for a new temperature value
    if (xQueueReceive(tempQueue, &temp, portMAX_DELAY) == pdTRUE) {
      Serial.print("DisplayTask -> Received temperature: ");
      Serial.println(temp);

      // Update the LCD
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Temp: ");
      lcd.print(temp);
      lcd.print(" C");

      // Short delay to allow other tasks to run
      vTaskDelay(pdMS_TO_TICKS(100));
    } // close if
  } // close while
}
 
