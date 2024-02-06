# Project #12: Display Counter

This sketch is for an application that displays a number on a display. It uses an OLED display, at least two buttons, and a buzzer. The application increments or decrements a counter based on button presses and displays the current count on the OLED screen. It also makes a beep sound using the buzzer whenever a button is pressed.

The code starts by including necessary libraries and defining constants for the screen dimensions, screen address, buzzer pin, button pins, and buzzer frequency. It then initializes the OLED display and a counter variable.

In the `setup()` function, it initializes serial communication, sets the button pins as inputs with pull-up resistors, and the buzzer pin as an output. It also initializes the OLED display and prints initial instructions on it.

The `loop()` function continuously checks the state of the buttons. If button A or B is pressed (read as LOW because of the pull-up resistors), it increments the counter, activates the buzzer, displays the counter on the screen, and prints the counter to the serial monitor. If button C or D is pressed, it does the same but decrements the counter instead.

The `buzzerBeep()` function generates a tone on the buzzer pin at the defined frequency, waits for 200 milliseconds, and then stops the tone. This creates a beep sound whenever a button is pressed.

The `displayCounter()` function updates the display with the current counter value. It first clears the display, then sets the text size and cursor position to print "Counter:". It then changes the text size, sets the cursor position again, and prints the counter value. Finally, it calls `display.display()` to update the OLED screen with the new content.