/*
  Auto Night Light
  Description:
  Hardware: RoboUNO, on-board NeoPixel strip, OLED Display, Sparkfun Light Sensor
  Library: Adafruit_GFX, Adafruit_SSD1306, Adafruit NeoPixel, SparkFun_VEML6030_Ambient_Light_Sensor
  Difficulty: XX/10
  Author: ROBO
  Date: October 2023
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "SparkFun_VEML6030_Ambient_Light_Sensor.h"
#include <Adafruit_NeoPixel.h>


// Initialize the NeoPixels
#define PIXELS_PIN 8 // Define the pin where our NeoPixels are connected
#define NUMPIXELS 3  // Define the number of NeoPixels in our strip
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIXELS_PIN, NEO_GRB + NEO_KHZ800);

// Initialize the display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

// initialize the light sensor
#define AL_ADDR 0x48
SparkFun_Ambient_Light lightSensor(AL_ADDR);
// Possible values: .125, .25, 1, 2
// Both .125 and .25 should be used in most cases except darker rooms.
// A gain of 2 should only be used if the sensor will be covered by a dark
// glass.
float gain = .125;
// Possible integration times in milliseconds: 800, 400, 200, 100, 50, 25
// Higher times give higher resolutions and should be used in darker light.
int time = 100;

long lightIntensity = 0; // Initialize the light intensity variable
int lightToggleThreshold = 20;

int userBrightness = 60;

// Define the button pins
#define BUTTON_A 7
#define BUTTON_B 6
#define BUTTON_C 4
#define BUTTON_D 2

uint32_t onColor = Adafruit_NeoPixel::Color(255, 255, 255);
uint32_t offColor = Adafruit_NeoPixel::Color(0, 0, 0);

void setup() {
    Wire.begin();
    Serial.begin(9600); // initialize serial communication at 9600 bits per second
    Serial.println("Auto Night Light!");

    pinMode(BUTTON_A, INPUT_PULLUP); // Set the buttons as inputs with pull-up resistors
    pinMode(BUTTON_B, INPUT_PULLUP);
    pinMode(BUTTON_C, INPUT_PULLUP);
    pinMode(BUTTON_D, INPUT_PULLUP);

    pixels.begin();             // Initialize the NeoPixel strip
    changeBrightness(userBrightness); // Set the brightness (0-255)
    setPixelsColor(offColor);

    // initialize the light sensor component
    if (lightSensor.begin())
        Serial.println("Light sensor initialized!");
    else {
        Serial.println("Could not communicate with the sensor!");
        for (;;);
    }

    // set the gain and integration time for the light sensor
    lightSensor.setGain(gain);
    lightSensor.setIntegTime(time);

    // Initialize with the I2C address of your OLED screen
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }

    // display
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Auto Night Light!");
    display.display();
}

void loop() {

    if (digitalRead(BUTTON_A) == LOW) {
        userBrightness += 10;
        userBrightness = constrain(userBrightness, 20, 255);
        changeBrightness(userBrightness);
        delay(100); // Debounce delay
    }
    if (digitalRead(BUTTON_C) == LOW) {
        userBrightness -= 10;
        userBrightness = constrain(userBrightness, 20, 255);
        changeBrightness(userBrightness);
        delay(100); // Debounce delay
    }

    if (digitalRead(BUTTON_B) == LOW) {
        lightToggleThreshold++;
        lightToggleThreshold = constrain(lightToggleThreshold, 1, 40);
        delay(100); // Debounce delay
    }
    if (digitalRead(BUTTON_D) == LOW) {
        lightToggleThreshold--;
        lightToggleThreshold = constrain(lightToggleThreshold, 1, 40);
        delay(100); // Debounce delay
    }

    lightIntensity = lightSensor.readLight(); // read light intensity

    // turn the pixels on if the light intensity is lower than the threshold
    if(lightIntensity <= lightToggleThreshold) {
        setPixelsColor(onColor);
    }
    else {
        setPixelsColor(offColor);
    }

    // print parameters on the screen
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Light intensity:" + String(lightIntensity));
    display.setCursor(0, 10);
    display.println("Light threshold:" + String(lightToggleThreshold));
    display.setCursor(0, 20);
    display.println("Brightness:" + String(userBrightness));
    // display.println("Brightness:" + String(((float)userBrightness / 255) * 100) + "%");
    display.display();

    delay(250);
}


// change the color of the neopixel strip
void setPixelsColor(uint32_t color) {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, color);
  }
  pixels.show();
}

void changeBrightness(int b) {
  pixels.setBrightness(b);
  pixels.show();
}