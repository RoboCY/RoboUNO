# Project #15: Night Light

This sketch is designed to control an "Auto Night Light" system that uses a light sensor to automatically adjust the brightness of a NeoPixel LED strip based on ambient light conditions. The system also includes an OLED display to show the current light intensity, light threshold, and user brightness settings.

The `setPixelsColor(uint32_t color)` function is used to change the color of the NeoPixel LED strip. It takes a 32-bit unsigned integer as an argument, which represents the color in RGB format. The function iterates over each pixel in the strip (the number of pixels is defined by the `NUMPIXELS` constant) and sets its color using the `setPixelColor` method from the `Adafruit_NeoPixel` library. After all pixels have been updated, the `show` method is called to apply the changes.

The `changeBrightness(int b)` function is used to adjust the brightness of the NeoPixel LED strip. It takes an integer argument `b` that represents the desired brightness level (from 0 to 255). The function uses the `setBrightness` method from the `Adafruit_NeoPixel` library to set the brightness, and then calls the `show` method to apply the change.

These functions are called in the main loop of the program, where the brightness and color of the LED strip are adjusted based on the readings from the light sensor and the user's settings. The user can adjust the brightness and the light threshold (the level of ambient light at which the LED strip turns on) using four buttons. The current settings and light intensity are displayed on the OLED screen.