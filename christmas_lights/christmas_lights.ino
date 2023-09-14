#include <Adafruit_NeoPixel.h>

#define PIN            8  // Define the pin where the NeoPixels are connected
#define NUM_PIXELS     3  // Number of NeoPixels in your setup
#define DELAY_MS       100 // Delay between blinks in milliseconds

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}


void loop() {
  // blink();
  // wipe();
  // row();
  rainbowCycle(10);
}

void blink() {
  // Turn all pixels off
  for (int i = 0; i < NUM_PIXELS; i++) {
    strip.setPixelColor(i, 0, 0, 0); // R, G, B = 0 (off)
  }
  strip.show();
  delay(DELAY_MS);

  // Turn random pixel on
  int randomPixel = random(NUM_PIXELS);
  strip.setPixelColor(randomPixel, wheel(random(255))); // Set to red (you can change the color)
  strip.show();
  delay(DELAY_MS);
}


void row() {
  for (int i = 0; i < NUM_PIXELS; i++) {
    // Turn on the current pixel
    strip.setPixelColor(i, wheel(random(255))); // Set to red (you can change the color)
    strip.show();
    delay(DELAY_MS);

    // Turn off the current pixel
    strip.setPixelColor(i, 0, 0, 0); // R, G, B = 0 (off)
    strip.show();

    // Delay between pixels
    delay(DELAY_MS);
  }
}


void wipe() {
  colorWipe(strip.Color(255, 0, 0), DELAY_MS); // Red
  colorWipe(strip.Color(0, 255, 0), DELAY_MS); // Green
  colorWipe(strip.Color(0, 0, 255), DELAY_MS); // Blue
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}


void rainbowCycle(int wait) {
  int totalSteps = 255;
  for(int j=0; j<totalSteps; j++) {
    for(int i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

uint32_t wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
