# Project #11: Hello Display

This sketch simply displays a "Hello World!" message on an OLED screen. It is the perfect project to get you started using an I2C display. The OLED screen is controlled by the SSD1306 driver, and the Adafruit_SSD1306 and Adafruit_GFX libraries are used to interface with it.

At the beginning of the code, the necessary libraries are included. The `Wire.h` library is for I2C communication, which is used to communicate with the OLED screen. The `Adafruit_GFX.h` and `Adafruit_SSD1306.h` libraries are for controlling the OLED screen.

Next, some constants are defined for the OLED screen. `SCREEN_WIDTH` and `SCREEN_HEIGHT` are set to the dimensions of the screen in pixels, and `SCREEN_ADDRESS` is set to the I2C address of the screen.

An instance of the `Adafruit_SSD1306` class is created named `display`. This object is initialized with the screen width, screen height, and a reference to the Wire object for I2C communication.

In the `setup()` function, serial communication is started at a baud rate of 9600, and a message "Screen Hello!" is printed to the serial monitor. The OLED screen is then initialized with its I2C address. If the initialization fails, an error message is printed to the serial monitor and the program enters an infinite loop, effectively halting the program.

The display is then cleared, and some settings are set for the text that will be displayed. The text color is set to white, the text size is set to 1 (which is the smallest size), and the cursor is moved to the top-left corner of the screen. The message "Hello World!" is then printed to the screen, and the `display()` function is called to update the screen with the new content.

The `loop()` function is empty except for a 50 millisecond delay. This means that after the initial setup, and displaying the message on the display, the program doesn't perform any more actions.

