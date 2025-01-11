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
uint16_t distance = 0.0f;

  // Cast the parameter to a QueueHandle_t
extern QueueHandle_t tempQueue; // = (QueueHandle_t)pvParameter;
extern QueueHandle_t tofQueue;  //= (QueueHandle_t)pvParameter;


void lcdupdate_sketch(void *pvParameter) {
  // Cast the parameter to a QueueHandle_t
//  QueueHandle_t tempQueue = (QueueHandle_t)pvParameter;
//  QueueHandle_t tofQueue  = (QueueHandle_t)pvParameter;

  // Setup start here
  //pinMode(LED_2_PIN, OUTPUT);
  //Serial.begin(115200); 
  //delay(100);  // Give time for the Serial to initialize

  //Wire.begin();

  // Initialize the SSD1306 display
  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  else {
    Serial.println("SSD1306 initialized successfully!");
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
      vTaskDelay(pdMS_TO_TICKS(10));  // short delay for other tasks to run
    } // close if

    // Wait indefinitely for a new humidity value
    if (xQueueReceive(tempQueue, &humidity, portMAX_DELAY) == pdTRUE) {
      Serial.print("lcdupdate -> Received humidity: ");
      Serial.print(humidity);
      Serial.println(" rH");
      display.setCursor(0,18);
      display.print(humidity);
      display.println(" %");
      vTaskDelay(pdMS_TO_TICKS(10));  // short delay for other tasks to run
    } // close if

    // Wait indefinitely for a new tof measurement value
    if (xQueueReceive(tofQueue, &distance, portMAX_DELAY) == pdTRUE) {
      Serial.print("lcdupdate -> Received distance: ");
      Serial.print(distance);
      Serial.println(" mm");
      display.setCursor(0,38);
      display.print(distance);
      display.println(" mm");
      vTaskDelay(pdMS_TO_TICKS(10));  // short delay for other tasks to run
    } // close if

    display.display();

    vTaskDelay(pdMS_TO_TICKS(10));
  } // close while
}
 

