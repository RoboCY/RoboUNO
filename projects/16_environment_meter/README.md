# Project #16: Environment Meter

In this sketch we create a smart environment meter using an Arduino board (RoboUNO), an OLED display, and a BME280 sensor. The BME280 sensor is a combined digital humidity, pressure, and temperature sensor that communicates over the I2C interface.

The code begins by including necessary libraries: `Wire.h` for I2C communication, `Adafruit_GFX.h` and `Adafruit_SSD1306.h` for controlling the OLED display, and `Adafruit_BME280.h` for interfacing with the BME280 sensor.

Next, the code defines constants for the OLED display's width, height, and I2C address. It then initializes the display and the BME280 sensor. The BME280 sensor's temperature, pressure, and humidity sensors are accessed and their references are stored in `bme_temp`, `bme_pressure`, and `bme_humidity`respectively.

In the `setup()` function, the I2C interface and serial communication are initiated. The OLED display is then set up. If the display or the BME280 sensor fails to initialize, the program will print an error message to the serial monitor and halt execution.

The `loop()` function is where the sensor readings are taken and displayed. It begins by declaring three `sensors_event_t` variables to hold the temperature, pressure, and humidity data. The `getEvent()` method is called on each sensor to populate these variables with the current sensor readings.

The sensor readings are then printed to the serial monitor in a comma-separated format. This is useful for logging data or for plotting the sensor readings over time.

Next, the sensor readings are displayed on the OLED screen. The `clearDisplay()` method is called to clear the screen, then the `setCursor()` method is used to position the text cursor, and the `println()` method is used to print the sensor readings to the screen. The `display()` method is then called to update the screen with the new data.

Finally, the `delay(250)` call pauses the program for 250 milliseconds before the next loop iteration. This is done to prevent the sensor and display from updating too rapidly.