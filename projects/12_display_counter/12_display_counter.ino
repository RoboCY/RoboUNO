/*
  Screen Counter
  Description:
  Hardware: RoboUNO, onboard buttons on D7, D6, D4, and D2, OLED Display, onboard buzzer
  Library: Adafruit_GFX, Adafruit_SSD1306
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

#define BUZZER_PIN 9  // Buzzer pin, connected to pin D9

// Define the button pins
#define BUTTON_A 7
#define BUTTON_B 6
#define BUTTON_C 4
#define BUTTON_D 2

#define BUZZER_FREQ 1000  // Define the frequency for the buzzer in Hertz

// Initialize the display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

int counter = 0;  // Initialize the counter variable


void setup() {
  Serial.begin(9600);  // initialize serial communication at 9600 bits per second
  Serial.println("Screen Counter!");

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
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Press A or B to");
  display.setCursor(0, 8);
  display.println("increase the counter.");  
  display.setCursor(0, 16);
  display.println("Press C or D to");
  display.setCursor(0, 24);
  display.println("decrease the counter.");    
  display.display();
}


void loop() {
  // read the button states
  if (digitalRead(BUTTON_A) == LOW || digitalRead(BUTTON_B) == LOW) {
    counter++;     // increment the counter
    buzzerBeep();  // activate the buzzer
    displayCounter();  // show the number on the screen
    Serial.println(counter);        
  }
  if (digitalRead(BUTTON_C) == LOW || digitalRead(BUTTON_D) == LOW) {
    counter--;     // decrement the counter
    buzzerBeep();  // activate the buzzer
    displayCounter();  // show the number on the screen
    Serial.println(counter);    
  }
  delay(50);
}


void buzzerBeep() {
  tone(BUZZER_PIN, BUZZER_FREQ);
  delay(200);
  noTone(BUZZER_PIN);
}


// display the counter on the screen
void displayCounter() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 16);
  display.println("Counter:");
  display.setTextSize(2);
  display.setCursor(55, 12);
  display.println(String(counter));
  display.display();
}
