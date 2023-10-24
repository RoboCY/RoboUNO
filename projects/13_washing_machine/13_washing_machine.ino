/*
  Washing Machine
  Description:
  Hardware: RoboUNO, onboard buttons on D7, D6, D4, and D2, OLED Display, onboard buzzer
  Library: Adafruit_GFX, Adafruit_SSD1306
  Difficulty: XX/10
  Author: ROBO
  Date: October 2023
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define SCREEN_ADDRESS 0x3C

#define BUTTON_TEMP_UP 7
#define BUTTON_TEMP_DOWN 4
#define BUTTON_COLOR_TOGGLE 2
#define BUTTON_START 6

#define BUZZER_PIN 9 // Buzzer pin, connected to pin D9
#define BUZZER_FREQ 1000

#define TEMPERATURE_MAX 90
#define TEMPERATURE_MIN 30
#define TEMPERATURE_STEP 10

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT);

int currentTemperature = TEMPERATURE_MIN;
bool isWhites = true;
bool isRunning = false;
unsigned long washingStartTime = 0;
unsigned long cycleStartTime = 0;
const unsigned long CYCLE_DURATION = 5000; // 5 seconds per step
enum WashCycleStep { PRE_WASH, WASH, SPIN, RINSE };
WashCycleStep currentStep = PRE_WASH;

void setup() {
  Serial.begin(9600);  // initialize serial communication at 9600 bits per second
  Serial.println("Washing Machine!");
  // Initialize the OLED screen
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("A/C: temp up/down");
  display.setCursor(0, 10);
  display.print("D: toggle mode");
  display.setCursor(0, 20);
  display.print("B: start");
  display.display();
  pinMode(BUTTON_TEMP_UP, INPUT_PULLUP);
  pinMode(BUTTON_TEMP_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_COLOR_TOGGLE, INPUT_PULLUP);
  pinMode(BUTTON_START, INPUT_PULLUP);
}

void loop() {
  if (!isRunning) {
    handleButtonPress();
  } 
  else {
    unsigned long cycleElapsedTime = millis() - cycleStartTime;
    unsigned long washingElapsedTime = millis() - washingStartTime;
    if (cycleElapsedTime >= CYCLE_DURATION) {
      // Switch to the next cycle step
      switch (currentStep) {
        case PRE_WASH:
          currentStep = WASH;
          break;
        case WASH:
          currentStep = SPIN;
          break;
        case SPIN:
          currentStep = RINSE;
          break;
        case RINSE:
          // Washing is complete
          isRunning = false;
          display.clearDisplay();
          display.setCursor(0, 0);
          display.println("Washing Done");
          display.display();
          activateAlarm();
          break;
      }
      // Reset the timer for the next step
      cycleStartTime = millis();
    } 
    else {
      int remainingTime = ((CYCLE_DURATION * 4) - washingElapsedTime) / 1000;
      display.clearDisplay();
      display.setCursor(0, 0);
      display.print("Step: ");
      switch (currentStep) {
        case PRE_WASH:
          display.println("Pre-wash");
          break;
        case WASH:
          display.println("Washing");
          break;
        case SPIN:
          display.println("Spinning");
          break;
        case RINSE:
          display.println("Rinsing");
          break;
      }
      display.setCursor(0, 10);
      display.print("Time Remaining: ");
      display.print(remainingTime);
      display.print("s");
      display.display();
    }
  }
}

void handleButtonPress() {
  int tempChange = 0;
  if (digitalRead(BUTTON_TEMP_UP) == LOW) {
    tempChange = TEMPERATURE_STEP;
  } else if (digitalRead(BUTTON_TEMP_DOWN) == LOW) {
    tempChange = -TEMPERATURE_STEP;
  }

  if (tempChange != 0) {
    currentTemperature = constrain(currentTemperature + tempChange, TEMPERATURE_MIN, TEMPERATURE_MAX);
    updateDisplay();
    delay(300);
  }

  if (digitalRead(BUTTON_COLOR_TOGGLE) == LOW) {
    isWhites = !isWhites;
    updateDisplay();
    delay(300);
  }

  if (digitalRead(BUTTON_START) == LOW) {
    startWashingCycle();
  }
}

void updateDisplay() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Temperature: ");
  display.print(currentTemperature);
  display.print(" C");
  display.setCursor(0, 10);
  display.print("Mode: ");
  display.print(isWhites ? "Whites" : "Colored");
  display.display();
}

void startWashingCycle() {
  isRunning = true;
  washingStartTime = millis();
  cycleStartTime = millis();
  currentStep = PRE_WASH;
  updateDisplay();
}

void activateAlarm() {
  for (int i = 0; i < 3; i++) {
    tone(BUZZER_PIN, BUZZER_FREQ);
    delay(500);
    noTone(BUZZER_PIN);
    delay(500);
  }  
}