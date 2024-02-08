# Project #17: Altitude Logger

This sketch creates an Arduino-based altitude logger that uses a BME280 sensor and an OLED display. The code is divided into two main parts: the setup and the loop.

The setup part initializes the hardware and checks if the devices are connected properly. We start by including the necessary libraries for the Wire (for I2C communication), Adafruit_GFX and Adafruit_SSD1306 (for the OLED display), and Adafruit_BME280 (for the BME280 sensor). We then define some constants and initialize the display and the BME280 sensor. The sea level pressure is defined as a constant and is used later to calculate the altitude. The display is initialized with its width, height, and I2C address. The BME280 sensor is initialized without any specific address, which means it will use the default I2C address (0x77).

The setup function begins the Wire library and starts serial communication at 9600 bits per second. We then attempt to initialize the display and the BME280 sensor. If either of these fail to initialize, an error message is printed to the serial monitor and the program enters an infinite loop, effectively halting execution.

The loop part of the code is where the altitude is read from the sensor, compared to the minimum and maximum recorded altitudes, and then displayed. The altitude is read from the BME280 sensor using the readAltitude function, which takes the sea level pressure as a parameter. The current altitude is then compared to the minimum and maximum recorded altitudes, and these values are updated if necessary. The current, minimum, and maximum altitudes are then printed to the serial monitor for debugging purposes.

The display is cleared and the current, minimum, and maximum altitudes are displayed on the OLED screen. The altitudes are rounded to the nearest whole number and displayed in meters. The display is then updated to show the new values. The loop then pauses for 2 seconds before repeating.

This code is a good example of how to use an Arduino, a BME280 sensor, and an OLED display to create a simple altitude logger. It demonstrates how to read from a sensor, how to use the serial monitor for debugging, and how to display information on an OLED screen.