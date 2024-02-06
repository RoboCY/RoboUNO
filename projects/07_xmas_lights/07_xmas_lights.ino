/*
  Christmas Lights
  Description: 
  Hardware: RoboUNO (on-board NeoPixel strip connected to pin D8) and onboard buttons on D7, D6, D4, and D2
  Library: Adafruit NeoPixel library
  Difficulty: XX/10
  Author: ROBO
  Date: September 2023
*/

#include <Adafruit_NeoPixel.h>

#define PIXELS_PIN     8  // Define the pin where the NeoPixels are connected
#define NUM_PIXELS     3  // Number of NeoPixels in your setup
#define DELAY_MS       100 // Delay between blinks in milliseconds

// Define the button pins
#define BUTTON_A 7
#define BUTTON_B 6
#define BUTTON_C 4
#define BUTTON_D 2

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIXELS, PIXELS_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600); // initialize serial communication at 9600 bits per second

  pinMode(BUTTON_A, INPUT_PULLUP); // Set the buttons as inputs with pull-up resistors
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);
  pinMode(BUTTON_D, INPUT_PULLUP);

  pixels.begin();
  pixels.show(); // Initialize all pixels to 'off'
}


void loop() {
  if (digitalRead(BUTTON_A) == LOW) {
    for (int i = 0; i < 20; i++) {
      blink();
    }
  }
  if (digitalRead(BUTTON_B) == LOW) {
    for (int i = 0; i < 5; i++) {
      wipe();
    }
  }    
  if (digitalRead(BUTTON_C) == LOW) {
    for (int i = 0; i < 10; i++) {
      row();
    }
  }
  if (digitalRead(BUTTON_D) == LOW) {
    for (int i = 0; i < 2; i++) {
      rainbowCycle(10);
    }
  }
  pixels.clear();
  pixels.show();
  delay(10);
}

void blink() {
  // Turn all pixels off
  for (int i = 0; i < NUM_PIXELS; i++) {
    pixels.setPixelColor(i, 0, 0, 0); // R, G, B = 0 (off)
  }
  pixels.show();
  delay(DELAY_MS);

  // Turn random pixel on
  int randomPixel = random(NUM_PIXELS);
  pixels.setPixelColor(randomPixel, wheel(random(255))); // Set to random color from the wheel
  pixels.show();
  delay(DELAY_MS);
}


void row() {
  for (int i = 0; i < NUM_PIXELS; i++) {
    // Turn on the current pixel
    pixels.setPixelColor(i, wheel(random(255))); // Set to random color from the wheel
    pixels.show();
    delay(DELAY_MS);

    // Turn off the current pixel
    pixels.setPixelColor(i, 0, 0, 0); // R, G, B = 0 (off)
    pixels.show();

    // Delay between pixels
    delay(DELAY_MS);
  }
}


void wipe() {
  colorWipe(pixels.Color(255, 0, 0), DELAY_MS); // Red
  colorWipe(pixels.Color(0, 255, 0), DELAY_MS); // Green
  colorWipe(pixels.Color(0, 0, 255), DELAY_MS); // Blue
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<pixels.numPixels(); i++) {
    pixels.setPixelColor(i, color);
    pixels.show();
    delay(wait);
  }
}


void rainbowCycle(int wait) {
  int totalSteps = 255;
  for(int j=0; j<totalSteps; j++) {
    for(int i=0; i<pixels.numPixels(); i++) {
      pixels.setPixelColor(i, wheel(((i * 256 / pixels.numPixels()) + j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}

uint32_t wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
