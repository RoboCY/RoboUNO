/*
  Mood Light
  Description: 
  Hardware: RoboUNO (on-board NeoPixel strip connected to pin D8) and onboard buttons on D7, D6, D4, and D2
  Library: Adafruit NeoPixel library
  Difficulty: XX/10
  Author: ROBO
  Date: September 2023
*/

#include <Adafruit_NeoPixel.h>

#define PIXELS_PIN 8 // Define the pin where our NeoPixels are connected
#define NUMPIXELS 3  // Define the number of NeoPixels in our strip

#define BUZZER_PIN 9 // Buzzer pin, connected to pin D9

// Define the button pins
#define BUTTON_A 7
#define BUTTON_B 6
#define BUTTON_C 4
#define BUTTON_D 2

#define BUZZER_FREQ 1000 // Define the frequency for the buzzer in Hertz

int userBrightness = 60;
int userDegrees = 180;

// Initialize the NeoPixels
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIXELS_PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  Serial.begin(9600); // initialize serial communication at 9600 bits per second
  Serial.println("Mood Light!");

  pinMode(BUTTON_A, INPUT_PULLUP); // Set the buttons as inputs with pull-up resistors
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);
  pinMode(BUTTON_D, INPUT_PULLUP);

  pinMode(BUZZER_PIN, OUTPUT); // Initialize buzzer pin as an output

  pixels.begin();            // Initialize the NeoPixel strip
  changeBrightness(userBrightness); // Set the brightness (0-255)
  changeColor(userDegrees);
}


void loop() {
  if (digitalRead(BUTTON_A) == LOW) {
    userBrightness += 20;
    userBrightness = constrain(userBrightness, 20, 255);
    changeBrightness(userBrightness);
    delay(200); // Debounce delay
  }
  if (digitalRead(BUTTON_B) == LOW) {
    userDegrees += 5;
    userDegrees = constrain(userDegrees, 0, 255);
    changeColor(userDegrees);
    delay(200); // Debounce delay
  }    
  if (digitalRead(BUTTON_C) == LOW) {
    userBrightness -= 20;
    userBrightness = constrain(userBrightness, 20, 255);
    changeBrightness(userBrightness);
    delay(200); // Debounce delay
  }
  if (digitalRead(BUTTON_D) == LOW) {
    userDegrees -= 5;
    userDegrees = constrain(userDegrees, 0, 255);
    changeColor(userDegrees);
    delay(200); // Debounce delay
  }
}


void changeBrightness(int b) {
  pixels.setBrightness(b);
  pixels.show();
}


void changeColor(uint32_t degrees) {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, degToColor(degrees));
  }
  pixels.show();
}


uint32_t degToColor(int deg){
  deg = map(deg, 0, 255, 0, 191);  // Map deg to a value between 0 and 191
  if (deg < 64) {
    return pixels.Color(deg * 4, 255 - deg * 4, 0);
  } else if (deg < 128) {
    deg -= 64;
    return pixels.Color(255 - deg * 4, 0, deg * 4);
  } else if (deg < 192) {
    deg -= 128;
    return pixels.Color(0, deg * 4, 255 - deg * 4);
  } else {
    deg -= 192;
    return pixels.Color(deg * 4, 255 - deg * 4, deg * 4);
  }
}


