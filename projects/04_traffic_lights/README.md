# Project #04: Traffic Lights

This sketch is designed to simulate a set of traffic lights using NeoPixels. We begin by including the Adafruit NeoPixel library, which provides functions for controlling NeoPixels. It then defines several constants and variables. The `PIXELS_PIN` constant is set to 8, which is the pin where the NeoPixels are connected. The `NUMPIXELS` constant is set to 3, indicating that there are three NeoPixels in the strip.

The next set of constants define the duration of each traffic light state in milliseconds. For example, `RED_DURATION` is set to 5000, meaning the red light will stay on for 5 seconds. The `RED_PIXEL`, `YELLOW_PIXEL`, and `GREEN_PIXEL` constants are set to 0, 1, and 2 respectively, indicating the index of each color in the NeoPixel strip.

The `redColor`, `yellowColor`, `greenColor`, and `offColor` variables are defined using the `Adafruit_NeoPixel::Color` function, which takes RGB values (0-255) as arguments and returns a 32-bit integer representing the color.

The `pixels` object is an instance of the `Adafruit_NeoPixel` class, initialized with the number of pixels, the pin they're connected to, and the type of NeoPixels being used.

In the `setup` function, the NeoPixel strip is initialized with the `pixels.begin()` function, and the brightness is set to 50 (out of a maximum of 255) with the `pixels.setBrightness(50)` function.

The `loop` function, which runs continuously on Arduino platforms, simulates the traffic light sequence. In each state (red, red-yellow, green, yellow), the appropriate pixels are set to their respective colors using the `pixels.setPixelColor` function, the changes are sent to the NeoPixel strip with the `pixels.show()` function, and the program pauses for the duration of the current state using the `delay` function.