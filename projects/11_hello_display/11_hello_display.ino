/*
  Screen Hello
  Description:
  Hardware: RoboUNO, OLED Display
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


// Initialize the display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

void setup() {
  Serial.begin(9600);  // initialize serial communication at 9600 bits per second
  Serial.println("Screen Hello!");

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
  display.println("Hello World!");
  display.display();
}


void loop() {
  delay(50);
}
