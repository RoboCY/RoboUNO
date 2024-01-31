/*
  Light Synth
  Description:
  Hardware: RoboUNO, OLED Display, on-board buzzer on D9, Sparkfun Light Sensor
  Library: Adafruit_GFX, Adafruit_SSD1306, SparkFun_VEML6030_Ambient_Light_Sensor
  Difficulty: XX/10
  Author: ROBO
  Date: October 2023
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "SparkFun_VEML6030_Ambient_Light_Sensor.h"


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

// Define the button pins
#define BUTTON_A 7
#define BUTTON_B 6
#define BUTTON_C 4
#define BUTTON_D 2

#define BUZZER_PIN 9 // Buzzer pin, connected to pin D9

// define the musical notes' frequencies
#define NOTE_C 523
#define NOTE_D 587
#define NOTE_E 659
#define NOTE_F 698
#define NOTE_G 784
#define NOTE_A 880
#define NOTE_B 987
#define NOTE_E_FLAT 622
#define NOTE_A_FLAT 830
#define NOTE_B_FLAT 932

// Notes for two octaves (C4 to B4 and C5 to B5)
int notesMajor[] = {NOTE_C, NOTE_D, NOTE_E, NOTE_F, NOTE_G, NOTE_A, NOTE_B,
              2 * NOTE_C, 2 * NOTE_D, 2 * NOTE_E, 2 * NOTE_F, 2 * NOTE_G, 2 * NOTE_A, 2 * NOTE_B};

int notesMinor[] = {NOTE_C, NOTE_D, NOTE_E_FLAT, NOTE_F, NOTE_G, NOTE_A_FLAT, NOTE_B_FLAT,
              2 * NOTE_C, 2 * NOTE_D, 2 * NOTE_E_FLAT, 2 * NOTE_F, 2 * NOTE_G, 2 * NOTE_A_FLAT, 2 * NOTE_B_FLAT};

int numberOfNotes = sizeof(notesMajor) / sizeof(notesMajor[0]);

int mode = 0; // the synth mode


void setup() {
    Wire.begin();
    Serial.begin(9600); // initialize serial communication at 9600 bits per second
    Serial.println("Light Synth!");

    pinMode(BUTTON_A, INPUT_PULLUP); // Set the buttons as inputs with pull-up resistors
    pinMode(BUTTON_B, INPUT_PULLUP);
    pinMode(BUTTON_C, INPUT_PULLUP);
    pinMode(BUTTON_D, INPUT_PULLUP);

    pinMode(BUZZER_PIN, OUTPUT); // Set the buzzer pin as an output

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
    display.display();
}


void loop() {
    // mode toggle
    if (digitalRead(BUTTON_A) == LOW || digitalRead(BUTTON_B) == LOW) {
        mode++;
        delay(100); // Debounce delay
    }
    if(digitalRead(BUTTON_C) == LOW || digitalRead(BUTTON_D) == LOW) {
        mode--;
        delay(100); // Debounce delay
    }

    // constrain the mode value
    if(mode < 0)
        mode = 2;
    if(mode > 2)
        mode = 0;

    lightIntensity = lightSensor.readLight(); // read light intensity

    String modeString = "";

    if(mode == 0) {
        int lightToNote = map(lightIntensity, 1, 12000, 0, numberOfNotes-1);
        playNote(notesMajor[lightToNote]);
        modeString = "MAJOR";
    }
    else if(mode == 1) {
        int lightToNote = map(lightIntensity, 1, 12000, 0, numberOfNotes - 1);
        playNote(notesMinor[lightToNote]);
        modeString = "MINOR";
    }
    else {
        int lightToTone = map(lightIntensity, 1, 12000, 100, 1000);
        playNote(lightToTone);
        modeString = "FREQUENCY";
    }


    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 2);
    display.println("Mode:");
    display.setTextSize(2);
    display.setCursor(0, 14);
    display.println(String(modeString));    
    display.display();

    delay(100);
}


void playNote(int n) {
    tone(BUZZER_PIN, n);
}