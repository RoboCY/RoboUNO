# Project #18: Light Tracker

This sketch is for an Arduino-based sunlight intensity tracker using a RoboUNO microcontroller, an OLED display, and a Sparkfun Light Sensor. The code includes two libraries: Adafruit_SSD1306 for the OLED display and SparkFun_VEML6030_Ambient_Light_Sensor for the light sensor.

The code starts by defining constants and initializing the OLED display and the light sensor. The display is initialized with a screen width of 128 pixels and a height of 32 pixels. The light sensor is initialized with a gain of 0.125 and an integration time of 100 milliseconds. The gain and integration time are used to adjust the sensitivity and resolution of the light sensor.

In the `setup()` function, the Wire library is started for I2C communication, and the serial communication is started at 9600 bits per second. The light sensor and the OLED display are then initialized. If the initialization of either component fails, an error message is printed to the serial monitor and the program enters an infinite loop.

In the `loop()` function, the light intensity is read from the light sensor and passed to the `renderSensorReadingScreen()` function, which displays the light intensity on the OLED display. The display is updated every 100 milliseconds.

The `renderSensorReadingScreen()` function first updates the y-axis limits of the graph based on the current light intensity value. It then clears the display and writes the label and sampling rate of the sensor reading. It also draws the y-axis of the graph and updates the graph with the current light intensity value.

The `updateChart()` function updates a circular buffer with the current light intensity value and draws the line graph based on the data in the buffer. The graph is drawn from right to left, with the most recent readings on the right.

The `drawChartLine()` function draws a vertical line at the given x position and with a height proportional to the light intensity value. The `countDigits()` function counts the number of digits in a given integer, and the `write()` function writes a string of text to the display at a given position and with a given font size.