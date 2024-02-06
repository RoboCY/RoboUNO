# Project #07: Christmas Lights

This sketch is designed to control a strip of NeoPixels (individually addressable RGB LEDs) to create various lighting effects. It uses the Adafruit NeoPixel library to interface with the hardware.

The `blink()` function first turns off all the pixels by setting their color to (0,0,0), which represents black or off in RGB color space. It then selects a random pixel using the `random(NUM_PIXELS)` function and sets its color to a random color from the color wheel, which is a function that returns an RGB color based on an input between 0 and 255.

The `row()` function iterates over all the pixels in the strip. For each pixel, it sets the color to a random color from the color wheel, shows the change, waits for a specified delay, then turns off the pixel before moving to the next one. This creates an effect of a colored light moving along the strip.

The `wipe()` function creates a color wipe effect. It calls the `colorWipe()` function three times with different colors (red, green, and blue). The `colorWipe()` function itself iterates over all the pixels, setting each one to the specified color and showing the change before waiting for a specified delay. This creates an effect of a wave of color moving along the strip.

The `rainbowCycle()` function creates a rainbow cycle effect. It iterates over a total of 255 steps, and for each step, it sets each pixel's color based on its position in the strip and the current step, creating a moving rainbow effect.

The `wheel()` function is a helper function that takes a position on a color wheel (0-255) and returns an RGB color. It divides the color wheel into three sections for red, green, and blue, and calculates the color based on the input position. This function is used to generate colors for the various lighting effects.