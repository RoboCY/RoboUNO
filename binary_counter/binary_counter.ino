/*
  Binary Counter
  Description: 
  Hardware: RoboUNO (on-board NeoPixel strip connected to pin D8), buzzer on D9 and onboard buttons on D7, D6, D4, and D2
  Library: Adafruit NeoPixel library
  Difficulty: XX/10
  Author: ROBO
  Date: September 2023
*/

#include <Adafruit_NeoPixel.h>

#define PIXELS_PIN 8  // Define the pin where our NeoPixels are connected
#define NUM_PIXELS 3  // Define the number of NeoPixels in our strip

#define BUZZER_PIN 9  // Buzzer pin, connected to pin D9

// Define the button pins
#define BUTTON_A 7
#define BUTTON_B 6
#define BUTTON_C 4
#define BUTTON_D 2

#define BUZZER_FREQ 1000  // Define the frequency for the buzzer in Hertz

int counter = 0;  // Initialize the counter variable


// Define the colors using RGB values (0-255)
uint32_t onColor = Adafruit_NeoPixel::Color(0, 255, 0);
uint32_t offColor = Adafruit_NeoPixel::Color(0, 0, 0);


// Initialize the NeoPixels
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIXELS, PIXELS_PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  Serial.begin(9600);  // initialize serial communication at 9600 bits per second
  Serial.println("Binary Counter!");

  pinMode(BUTTON_A, INPUT_PULLUP);  // Set the buttons as inputs with pull-up resistors
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);
  pinMode(BUTTON_D, INPUT_PULLUP);

  pinMode(BUZZER_PIN, OUTPUT);  // Initialize buzzer pin as an output

  pixels.begin();            // Initialize the NeoPixel strip
  pixels.setBrightness(50);  // Set the brightness (0-255)
}


void loop() {
  // read the button states
  if (digitalRead(BUTTON_A) == LOW || digitalRead(BUTTON_B) == LOW) {
    counter++;     // increment the counter
    buzzerBeep();  // activate the buzzer
  }
  if (digitalRead(BUTTON_C) == LOW || digitalRead(BUTTON_D) == LOW) {
    counter--;     // decrement the counter
    buzzerBeep();  // activate the buzzer
  }

  counter = constrain(counter, 0, 7);  // keep the value of the counter between 0 and 7
  displayBinary(counter);              // show the number as binary on the LED strip
  Serial.println(counter);
}


void buzzerBeep() {
  tone(BUZZER_PIN, BUZZER_FREQ);
  delay(200);
  noTone(BUZZER_PIN);
}


// display an integer number as binary on the Neopixel strip
void displayBinary(int number) {
  for (int i = NUM_PIXELS - 1; i >= 0; i--) {  // Start from the right-most pixel
    int bitValue = (number >> i) & 1;          // Extract the i-th bit
    if (bitValue == 1) {
      pixels.setPixelColor(NUM_PIXELS - 1 - i, onColor);  // Red color for '1'
    } else {
      pixels.setPixelColor(NUM_PIXELS - 1 - i, offColor);  // Off (black) color for '0'
    }
  }
  pixels.show();
}
