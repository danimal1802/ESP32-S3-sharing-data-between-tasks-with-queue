This program serves as a baseline code for running multiple parallel tasks on a single dual-core ESP32-S3

For this project - the Arduino IDE (board manager 3) was used to program the ESP32-S3 and relies on a few other libraries (e.g. Wire.h) included with this IDE

This setup has 6 total tasks

(1) Led1 blinking at a specified rate different from task2 and task3 - pin assignment and duration of blink-rate is self documenting in the code

(2) Led2 blinking at a specified rate different from task1 and task3

(3) Led3 blinking at a specified rate diferent from task 1 and task 2

(4) a AHT20 temperature sensor connected to the ESP32 via the I2C (SDA/SCL) ports taking temperature and humidity readings at a specified interval

(5) a SSD1306 OLED display connected via I2C to the ESP32.  This replaces the earlier project iteration that used the 2004A LCD display that required an external 5v power supply and had occasional signal problems with 3.3 V SDA/SCL logic levels  The 3.3v I2C signals from the ESP32-S3 are in theory compatable signal levels to the LCD display but the behavior was intermittent.  The display is set to show the temperature (C) and humidity values from the 2-deep queue and set to read the queue at a specified interval longer than the sensor read time (to avoid full queue and loss of 2-value sync).  The display also shows the VL53L1X time-of=flight distance via a second queue. 

(6) a VL53L1X time of flight laster sensor for measuring distance to an object

This specific project by itself is not accomplishing much that cannot be achieved with a single loop program.  

However, the real value of this example provides the code for later creating more complex projects having multiple tasks (controls, displays, calculations, sensors, etc) running simultaneously and run non-blocking while having the ability to pass information between tasks via queues.  Queues are better practice over global variables w/ semaphores.  The goal is to use these files for more complex devices and functionality without having to rework all of the settings and code for simple inter-task communications.

As the ESP32 is dual core, it is technically possible to use both cores.  For the moment, the tasks are all assigned to core1 as it is understood that core0 is used for Wifi and Bluetooth and other RTOS functionality and overcommitment of core0 can result in system-crashes. 

Improvements needed: 

(a) separate each of the tasks code into both a <file.h> and a <file.cpp> for best practice 
(b) ~~modify the queue to permit also humidity values to be exchanged instead of only temperature~~
(c) ~~adjust the LCD display to clear & update only the sections of the display that need to be updated when there is a change in temperature (or other, etc)!!
(d) determine if both the <Arduino.h> and the <FreeRTOS.h files> are required or one or the other is sufficient - this is difficult to understand based on other examples on the web
(e) (include motor controls) or other rotary switch inputs
(f) measure / determine memory use and allocated mempry for each task.  Currently values are guesstimated
(g) further error checking for queue setup / failure / retry
(h) further understand the crossover of command differences for FreeRTOS such as delay vs vTaskDelay ...  https://www.freertos.org/Documentation/00-Overview
(i) ~~include multiple queues and with different lengths and purposes~~
(j) ~~rationalize and minimize library and includes for code~~


  recommended settings in Arduino IDE

Upload speed 921600

USB Mode : Hardware CDC and JTAG

USB CDC on Boot : Enabled

USB Firmware MSC : disabled

USB DFU on boot : disabled

Upload Mode: UART0/Hardware CDC

CPU frequency 240Mhz

Flash Mode: QIO 80Mhz

Flash size: 16MB

Partition scheme: any should work

PSRAM: OPI PSRAM
