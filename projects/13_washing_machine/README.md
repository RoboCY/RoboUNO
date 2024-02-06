# Project #13: Washing Machine

This project simulates a washing machine controller implemented on an Arduino board. The washing machine has a temperature setting, a mode setting (whites or colored), and a start button. The washing cycle consists of four steps: pre-wash, wash, spin, and rinse. 

The `handleButtonPress` function is responsible for handling the button presses. It first checks if the temperature up or down buttons are pressed. If either button is pressed, it changes the temperature by a step size defined by `TEMPERATURE_STEP`. The `constrain` function is used to ensure that the temperature stays within the defined minimum and maximum limits. If the color toggle button is pressed, it toggles the `isWhites` boolean variable, which represents the mode of the washing machine. If the start button is pressed, it calls the `startWashingCycle` function to start the washing cycle.

The `updateDisplay` function is used to update the OLED display with the current settings. It first clears the display, then prints the current temperature and the mode (whites or colored) on the display. The `WashCycleStep` enum is used to represent the different steps of the washing cycle with four possible values: `PRE_WASH`, `WASH`, `SPIN`, and `RINSE`.

The `startWashingCycle` function is used to start the washing cycle. It sets the `isRunning` boolean variable to true, records the current time as the start time of the washing cycle and the current cycle step, and sets the current step to pre-wash. It then calls the `updateDisplay` function to update the display.

The `activateAlarm` function is used to activate the alarm when the washing is done. It uses the `tone` function to generate a sound on the buzzer pin at a frequency defined by `BUZZER_FREQ`. It repeats this three times, with a delay of 500 milliseconds between each beep.

