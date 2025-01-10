This program serves as a baseline code for running multiple parallel tasks on a single dual-core ESP32-S3

This setup has 5 total tasks

(1) Led1 blinking at a specified rate different from task2 and task3 - pin assignment and duration of blink-rate is self documenting in the code

(2) Led2 blinking at a specified rate different from task1 and task3

(3) Led3 blinking at a specified rate diferent from task 1 and task 2

(4) a AHT20 temperature sensor connected to the ESP32 via the I2C (SDA/SCL) ports taking temperature and humidity readings at a specified interval

(5) a 2004A LCD display connected via I2C to the ESP32 (with external 5v power) and common ground to the USB 5V feed.  The 3.3v I2C signals from the ESP32-S3 are compatable signal levels to the display.  The display is set to show the temperature value from the queue and set to read the queue at a specified interval.

This specific project by itself is not accomplishing much that cannot be achieved with a single loop program.  

The value of this example provides the code for having multiple tasks running in realtime that can run independently and non-blocking while having the ability to pass information between tasks via queues.  Queues are better practice over global variables w/ semaphores.

As the ESP32 is dual core, it is technically possible to use both cores.  For the moment, the tasks are all assigned to core1 as it is understood that core0 is used for Wifi and Bluetooth and other RTOS functionality and overcommitment of core0 can result in system-crashes. 

Improvements needed: 

(a) separate each of the tasks code into both a <file.h> and a <file.cpp> for best practice 
(b) modify the queue to permit humidity values to be exchanged instead of only temperature
(c) adjust the LCD display to clear & update only the sections of the display that need to be updated when there is a change in temperature (or other, etc)
(d) determine if both the <Arduino.h> and the <FreeRTOS.h files> are required or one or the other is sufficient - this is difficult to understand based on other examples on the web
(e) (include motor controls) or other rotary switch inputs
(f) measure / determine memory use and allocated mempry for each task.  Currently values are guesstimated
(g) further error checking for queue setup / failure / retry



