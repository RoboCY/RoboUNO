/*
  Buzzer Alarm
  Description:  This Arduino sketch expects a specific sequence of 4 button presses. If the sequence is 
                incorrect it activates the buzzer and lights the NeoPixels in red. If the sequence
                is correct, the buzzer beeps twice and the NeoPixels turn green. Entering an incorrect
                sequence 3 times in a row, will activate the alarm. The sequence is defined by the 
                'expectedSequence' array.
  Hardware: RoboUNO (on-board NeoPixels on D8, buzzer on D9 and onboard buttons on D7, D6, D4, and D2)
  Library: Adafruit NeoPixel library
  Difficulty: XX/10
  Author: ROBO
  Date: August 11, 2023
*/

#include <Adafruit_NeoPixel.h>
#define PIXELS_PIN 8  // Define the pin where our NeoPixels are connected
#define NUMPIXELS 3   // Define the number of NeoPixels in our strip

#define BUZZER_PIN 9  // Buzzer pin, connected to pin D9

// Define the button pins
#define BUTTON_A 7
#define BUTTON_B 6
#define BUTTON_C 4
#define BUTTON_D 2

#define BUZZER_FREQ 1000  // Define the frequency for the buzzer in Hertz

// Define the colors using RGB values (0-255)
uint32_t redColor = Adafruit_NeoPixel::Color(255, 0, 0);
uint32_t yellowColor = Adafruit_NeoPixel::Color(255, 255, 0);
uint32_t greenColor = Adafruit_NeoPixel::Color(0, 255, 0);
uint32_t offColor = Adafruit_NeoPixel::Color(0, 0, 0);

// Initialize the NeoPixels
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIXELS_PIN, NEO_GRB + NEO_KHZ800);

// Define the button and buzzer pins
const int buttonPins[] = { BUTTON_A, BUTTON_B, BUTTON_C, BUTTON_D };
const int numButtons = sizeof(buttonPins) / sizeof(buttonPins[0]);

// Define the expected button sequence
const int expectedSequence[] = { BUTTON_C, BUTTON_A, BUTTON_D, BUTTON_B };
const int sequenceLength = sizeof(expectedSequence) / sizeof(expectedSequence[0]);

// Variables to keep track of the button sequence
int buttonPressIndex = 0;
int buttonPressSequence[sequenceLength];
int falseSequenceCounter = 0;

void setup() {
  pinMode(BUTTON_A, INPUT_PULLUP);  // Set the buttons as inputs with pull-up resistors
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);
  pinMode(BUTTON_D, INPUT_PULLUP);

  pinMode(BUZZER_PIN, OUTPUT);  // Initialize buzzer pin as an output

  // Initialize button sequence array
  for (int i = 0; i < sequenceLength; i++) {
    buttonPressSequence[i] = 0;
  }

  Serial.begin(9600);        // Start serial communication
  pixels.begin();            // Initialize the NeoPixel strip
  pixels.setBrightness(50);  // Set the brightness (0-255)
  fillPixels(offColor);
}

void loop() {
  // Check for button presses
  for (int i = 0; i < numButtons; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      // Button i has been pressed
      buttonPressSequence[buttonPressIndex] = buttonPins[i];
      buttonPressIndex++;
      // Check if the button sequence is complete
      if (buttonPressIndex == sequenceLength) {
        checkSequence();
        buttonPressIndex = 0;  // Reset button index
      } else {
        tone(BUZZER_PIN, BUZZER_FREQ);
        fillPixels(yellowColor);
        delay(200);  // Debounce delay
        noTone(BUZZER_PIN);
        fillPixels(offColor);
      }
    }
  }
}

void checkSequence() {
  // Compare the button sequence with the expected sequence
  for (int i = 0; i < sequenceLength; i++) {
    if (buttonPressSequence[i] != expectedSequence[i]) {
      // Incorrect sequence
      falseSequenceCounter++;
      if (falseSequenceCounter == 3) {
        activateAlarm();
        falseSequenceCounter = 0;
      } else {
        activateWarning();
      }
      return;
    }
  }

  // correct sequence
  falseSequenceCounter = 0;
  Serial.println("Correct sequence!");

  fillPixels(greenColor);

  // Correct sequence, double beep
  tone(BUZZER_PIN, BUZZER_FREQ);
  delay(100);
  noTone(BUZZER_PIN);
  delay(100);
  tone(BUZZER_PIN, BUZZER_FREQ);
  delay(100);
  noTone(BUZZER_PIN);

  delay(2000);
  fillPixels(offColor);
}

void activateWarning() {
  fillPixels(redColor);
  tone(BUZZER_PIN, BUZZER_FREQ);
  delay(1000);
  noTone(BUZZER_PIN);
  fillPixels(offColor);
}

void activateAlarm() {
  for (int i = 0; i < 8; i++) {
    fillPixels(redColor);
    tone(BUZZER_PIN, BUZZER_FREQ);
    delay(500);
    fillPixels(offColor);
    noTone(BUZZER_PIN);
    delay(500);
  }  
}


void fillPixels(uint32_t color) {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, color);
  }
  pixels.show();
}
