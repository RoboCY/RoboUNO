/*
  Buzzer Toggle
  Description: This sketch activates and deactivates the buzzer at a specified frequency and at a specified interval.
  Hardware: RoboUNO (on-board buzzer connected to pin D9)
  Library: -
  Difficulty: XX/10
  Author: ROBO
  Date: August 11, 2023
*/

#define BUZZER_PIN 9         // Define the pin for the buzzer
#define BUZZER_FREQ 1000     // Define the frequency for the buzzer in Hertz
#define BUZZ_DURATION 500    // Define the buzz duration in milliseconds
#define PAUSE_DURATION 1000  // Define the duration between buzzes in milliseconds

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);  // Set the buzzer pin as an output
}

void loop() {
  tone(BUZZER_PIN, BUZZER_FREQ);  // Activate the buzzer
  delay(BUZZ_DURATION);           // Delay for buzz duration
  noTone(BUZZER_PIN);             // Turn off the buzzer
  delay(PAUSE_DURATION);          // Delay before the next buzz
}