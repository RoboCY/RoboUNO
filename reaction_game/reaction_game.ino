/*
  Reaction Game
  Description:
  Hardware: RoboUNO (on-board NeoPixel strip connected to pin D8), buzzer on D9 and onboard buttons on D7, D6, D4, and D2
  Library: Adafruit NeoPixel library
  Difficulty: XX/10
  Author: ROBO
  Date: September 2023
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define SCREEN_ADDRESS 0x3C

#include <Adafruit_NeoPixel.h>

#define PIXELS_PIN 8  // Define the pin where our NeoPixels are connected
#define NUM_PIXELS 3  // Define the number of NeoPixels in our strip

#define BUZZER_PIN 9  // Buzzer pin, connected to pin D9

// Define the button pins
#define BUTTON_A 7
#define BUTTON_B 6
#define BUTTON_C 4
#define BUTTON_D 2

#define NOTE_C 523  // Frequency for note C in Hertz
#define NOTE_D 587  // Frequency for note D in Hertz
#define NOTE_F 698  // Frequency for note F in Hertz

uint8_t activePixel = 0;  // Initialize the counter variable
bool gameIsRunning = false;
unsigned long int onTime = 0;
unsigned long int pressTime = 0;

// Define the colors using RGB values (0-255)
uint32_t onColor = Adafruit_NeoPixel::Color(0, 255, 0);
uint32_t offColor = Adafruit_NeoPixel::Color(0, 0, 0);

// Initialize the NeoPixels
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIXELS, PIXELS_PIN, NEO_GRB + NEO_KHZ800);

// Initialize the display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

void setup() {
  Serial.begin(9600);  // initialize serial communication at 9600 bits per second
  Serial.println("Reaction Game!");

  pinMode(BUTTON_A, INPUT_PULLUP);  // Set the buttons as inputs with pull-up resistors
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);
  pinMode(BUTTON_D, INPUT_PULLUP);

  pinMode(BUZZER_PIN, OUTPUT);  // Initialize buzzer pin as an output

  // Initialize with the I2C address of your OLED screen
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  // display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Reaction Game!");
  display.setCursor(0, 16);
  display.println("Press D to start...");
  display.display();

  // neopixels
  pixels.begin();            // Initialize the NeoPixel strip
  pixels.setBrightness(50);  // Set the brightness (0-255)
  pixels.clear();
  pixels.show();
}

void loop() {
  if (!gameIsRunning) {
      if (digitalRead(BUTTON_D) == LOW) { 
        startRound();
      }
  } else {
      if (digitalRead(BUTTON_A) == LOW && activePixel == 2) {
        endRound();
      }
      else if (digitalRead(BUTTON_B) == LOW && activePixel == 1) {
        endRound();
      }
      else if (digitalRead(BUTTON_C) == LOW && activePixel == 0) {
        endRound();
      }
  }
}

void buzzerBeep(int freq) {
  tone(BUZZER_PIN, freq);
  delay(200);
  noTone(BUZZER_PIN);
}

void startRound() {
  display.clearDisplay();
  display.setCursor(50,10);
  display.println(String("GO!"));
  display.display();
  onTime = millis();
  buzzerBeep(NOTE_C);  // activate the buzzer  
  gameIsRunning = true;
  activePixel = random(3);
  pixels.clear();
  pixels.setPixelColor(activePixel, onColor);
  pixels.show();
}

void endRound() {
  pressTime = millis();
  display.clearDisplay();
  display.setCursor(0,0);
  display.println(String("Reaction time: " + String(pressTime - onTime) + "ms"));
  display.setCursor(0, 16);
  display.println("Press D to go again.");  
  display.display();
  pixels.clear();
  pixels.show();
  gameIsRunning = false;
  buzzerBeep(NOTE_F);  // activate the buzzer  
}
