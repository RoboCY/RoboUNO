/*
  Traffic Light Simulation using NeoPixels
  Description: This sketch simulates a set of traffic lights using NeoPixels.
  Hardware: RoboUNO (on-board NeoPixel strip connected to pin D8)
  Library: Adafruit NeoPixel library
  Difficulty: XX/10
  Author: ROBO
  Date: August 11, 2023
*/

#include <Adafruit_NeoPixel.h>

#define PIXELS_PIN 8        // Define the pin where our NeoPixels are connected
#define NUMPIXELS 3  // Define the number of NeoPixels in our strip

// Traffic light timings (in milliseconds)
#define RED_DURATION 5000         // Red light duration
#define RED_YELLOW_DURATION 1000  // Red-Yellow light duration
#define YELLOW_DURATION 1000      // Yellow light duration
#define GREEN_DURATION 5000       // Green light duration

#define RED_PIXEL 0     // Red light pixel index
#define YELLOW_PIXEL 1  // Yellow light pixel index
#define GREEN_PIXEL 2   // Green light pixel index

// Define the colors using RGB values (0-255)
uint32_t redColor = Adafruit_NeoPixel::Color(255, 0, 0);
uint32_t yellowColor = Adafruit_NeoPixel::Color(255, 255, 0);
uint32_t greenColor = Adafruit_NeoPixel::Color(0, 255, 0);
uint32_t offColor = Adafruit_NeoPixel::Color(0, 0, 0);


// Initialize the NeoPixels
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIXELS_PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  pixels.begin();            // Initialize the NeoPixel strip
  pixels.setBrightness(50);  // Set the brightness (0-255)
}


void loop() {
  // Red
  pixels.setPixelColor(RED_PIXEL, redColor);
  pixels.setPixelColor(YELLOW_PIXEL, offColor);
  pixels.setPixelColor(GREEN_PIXEL, offColor);
  pixels.show();
  delay(RED_DURATION);

  // Red-Yellow
  pixels.setPixelColor(RED_PIXEL, redColor);
  pixels.setPixelColor(YELLOW_PIXEL, yellowColor);
  pixels.setPixelColor(GREEN_PIXEL, offColor);
  pixels.show();
  delay(RED_YELLOW_DURATION);

  // Green
  pixels.setPixelColor(RED_PIXEL, offColor);
  pixels.setPixelColor(YELLOW_PIXEL, offColor);
  pixels.setPixelColor(GREEN_PIXEL, greenColor);
  pixels.show();
  delay(GREEN_DURATION);

  // Yellow
  pixels.setPixelColor(RED_PIXEL, offColor);
  pixels.setPixelColor(YELLOW_PIXEL, yellowColor);
  pixels.setPixelColor(GREEN_PIXEL, offColor);
  pixels.show();
  delay(YELLOW_DURATION);
}
