/*
  Simple Egg Timer
  Description: Select between soft, medium, and hard-boiled egg, and the buzzer will sound when your egg is ready.
  Hardware: RoboUNO (on-board NeoPixel strip connected to pin D8), buzzer on D9 and onboard buttons on D7, D6, D4, and D2
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

int cookingTimes[] = {300, 420, 540}; // Cooking times in seconds for soft, medium, and hard-boiled egg
int selectedOption = 0;               // Default option is soft-boiled
bool isCooking = false;
unsigned long int endTime = 0;

// Define the colors using RGB values (0-255)
uint32_t redColor = Adafruit_NeoPixel::Color(255, 0, 0);
uint32_t yellowColor = Adafruit_NeoPixel::Color(255, 255, 0);
uint32_t greenColor = Adafruit_NeoPixel::Color(0, 255, 0);
uint32_t offColor = Adafruit_NeoPixel::Color(0, 0, 0);


// Initialize the NeoPixels
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIXELS_PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  Serial.begin(9600); // initialize serial communication at 9600 bits per second
  Serial.println("Egg Timer!");

  pinMode(BUTTON_A, INPUT_PULLUP); // Set the buttons as inputs with pull-up resistors
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);
  pinMode(BUTTON_D, INPUT_PULLUP);

  pinMode(BUZZER_PIN, OUTPUT); // Initialize buzzer pin as an output

  pixels.begin();            // Initialize the NeoPixel strip
  pixels.setBrightness(50);  // Set the brightness (0-255)
}


void loop() {
  if(!isCooking) {
    if (digitalRead(BUTTON_A) == LOW) {
      selectedOption = 0;
      Serial.println("Soft-boiled selected.");
      delay(200); // Debounce delay
    }
    if (digitalRead(BUTTON_B) == LOW) {
      selectedOption = 1;
      Serial.println("Medium-boiled selected.");
      delay(200); // Debounce delay
    }    
    if (digitalRead(BUTTON_C) == LOW) {
      selectedOption = 2;
      Serial.println("Hard-boiled selected.");
      delay(200); // Debounce delay
    }

    fillPixels(offColor);
    pixels.setPixelColor(2-selectedOption, redColor);
    pixels.show();

    if (digitalRead(BUTTON_D) == LOW) {
      startTimer();
    }    
  }
  else {
    if(endTime <= millis()) {
      Serial.println("Your egg is ready!\n");
      activateAlarm();
      isCooking = false;
    }
  }
}


void startTimer() {
  fillPixels(offColor);
  pixels.setPixelColor(2 - selectedOption, greenColor);
  pixels.show();
  endTime = millis() + (cookingTimes[selectedOption] * 1000);
  isCooking = true;
  Serial.println("\nEgg timer started...");
}


void activateAlarm() {
  for (int i = 0; i < 3; i++) {
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
