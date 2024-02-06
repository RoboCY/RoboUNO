# Project #10: Burglar Alarm

This Arduino sketch is designed to create a buzzer alarm system that responds to a specific sequence of button presses. The sequence is defined by the `expectedSequence` array. If the sequence is entered correctly, the buzzer beeps twice and the NeoPixels turn green. If the sequence is incorrect, the buzzer activates and the NeoPixels turn red. If an incorrect sequence is entered three times in a row, the alarm is activated.

The `checkSequence` function is responsible for comparing the sequence of button presses with the expected sequence. It iterates over the `buttonPressSequence` array and compares each element with the corresponding element in the `expectedSequence` array. If it finds a mismatch, it increments the `falseSequenceCounter` and checks if it has reached 3 (indicating three consecutive incorrect sequences). If so, it calls the `activateAlarm` function and resets the `falseSequenceCounter`. If not, it calls the `activateWarning` function. If the entire sequence is correct, it resets the `falseSequenceCounter`, prints a success message to the serial monitor, lights the NeoPixels green, and makes the buzzer beep twice.

The `activateWarning` function is called when an incorrect sequence is entered but the `falseSequenceCounter` is less than 3. It lights the NeoPixels red and activates the buzzer for a second, then turns off the lights and the buzzer.

The `activateAlarm` function is called when an incorrect sequence is entered three times consecutively. It activates a more intense alarm, which consists of alternating between lighting the NeoPixels red and activating the buzzer, and turning off the lights and the buzzer. This alternation happens 8 times, creating a flashing effect.

The `fillPixels` function is a utility function that sets all the NeoPixels to a specified color. It iterates over all the pixels, sets their color using the `setPixelColor` method, and then calls the `show` method to update the actual lights.