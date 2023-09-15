/*
  Police Siren
  Description:
  Hardware: RoboUNO (on-board NeoPixel strip connected to pin D8) and buzzer on D9
  Library: Adafruit NeoPixel library
  Difficulty: XX/10
  Author: ROBO
  Date: September 2023
*/

#include <Adafruit_NeoPixel.h>

#define BUZZER_PIN 9
#define PIXELS_PIN 8
#define NUMPIXELS 3

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIXELS_PIN, NEO_GRB + NEO_KHZ800);

// Define the colors using RGB values (0-255)
uint32_t redColor = Adafruit_NeoPixel::Color(255, 0, 0);
uint32_t blueColor = Adafruit_NeoPixel::Color(0, 0, 255);

const int sirenTones[] = {861, 659}; // Musical notes for the siren sound
const int sirenDuration = 200; // Duration of each note in milliseconds

void setup() {
  Serial.begin(9600); // initialize serial communication at 9600 bits per second
  Serial.println("Police Siren!");

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  policeSiren();
}

void policeSiren() {
  for (int i = 0; i < 2; i++) {
    tone(BUZZER_PIN, sirenTones[i]);
    if (i % 2 == 0) {
      strip.setPixelColor(0, redColor); // Red
      strip.setPixelColor(1, blueColor); // Blue
      strip.setPixelColor(2, redColor); // Red
    } else {
      strip.setPixelColor(0, blueColor); // Blue
      strip.setPixelColor(1, redColor); // Red
      strip.setPixelColor(2, blueColor); // Blue
    }
    strip.show();
    delay(sirenDuration);
    noTone(BUZZER_PIN);
    delay(sirenDuration);
  }
}
