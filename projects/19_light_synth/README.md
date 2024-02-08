# Project #19: Light Synth

In this project we create light synthesizer, a device that generates sound based on the intensity of light it detects.

We start by including necessary libraries and defining constants for the OLED display and the light sensor. The Adafruit_SSD1306 library is used for the OLED display, and the SparkFun_VEML6030_Ambient_Light_Sensor library is used for the light sensor. The display and light sensor are then initialized with their respective parameters.

The light sensor's gain and integration time are set. The gain determines the sensor's sensitivity to light, and the integration time determines how long the sensor collects light for each reading. These values can be adjusted to optimize the sensor's performance for different lighting conditions.

We also define constants for the frequencies of musical notes and arrays to store these frequencies for major and minor scales. The `mode` variable is used to switch between these scales and a mode where the frequency is directly proportional to the light intensity.

In the `setup()` function, the program initializes the serial communication, sets the button and buzzer pins, and checks if the light sensor and display are working correctly. If the light sensor or display fails to initialize, the program enters an infinite loop, effectively halting the execution.

In the `loop()` function, which is the main program loop in Arduino, the program reads the state of the buttons to change the mode and reads the light intensity from the sensor. Depending on the mode, the program maps the light intensity to a note in the major or minor scale or a frequency, and plays this note or frequency using the `playNote()` function.

The `playNote()` function uses the `tone()` function from the Arduino library to generate a square wave of the specified frequency on the buzzer pin. This produces the sound corresponding to the note or frequency.

Finally, the program updates the display to show the current mode and waits for a short delay before the next iteration of the loop. This delay helps to debounce the buttons and prevent rapid changes in the light intensity from causing erratic behavior.