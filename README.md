# ESP32 WebServer Documentation
This document provides instructions on setting up and using an ESP32 WebServer to control LEDs using different modes.
# Introduction
The ESP32 WebServer allows you to control LEDs connected to GPIO pins through a web interface. This project demonstrates how to create different endpoints to perform actions such as turning LEDs off, blinking, and alternating the states of LEDs.

# Hardware Requirements
1. ESP32 Development Board
2. 3 LEDs 
3. 3 Resistors
Breadboard and jumper wires
# Software Requirements
1. Arduino IDE
2. WiFi and WebServer libraries

# Wiring
Connect the LEDs to GPIO pins according to the following configuration:

Red LED: GPIO pin 5
Green LED: GPIO pin 4
Yellow LED: GPIO pin 2

# Usage
1. Upload the code to the ESP32 Development Board via the Arduino IDE(ensure to put your SSID and Password).
2. Open the Serial Monitor to view the board's IP address once connected to the WiFi network.
3. Access the web interface by typing the IP address in a web browser.
The web interface provides the following buttons:
Blink: Toggle blinking mode for LEDs.
Alternate: Alternate between turning on the Red and Yellow LEDs.
OFF: Turn off all LEDs.
Click on the desired button to control the LEDs according to the selected mode.
