/*
  Smart Altitude Logger
  Description:
  Hardware: RoboUNO, OLED Display, BME280 Sensor
  Library: Adafruit_GFX, Adafruit_SSD1306, Adafruit_BME280
  Difficulty: XX/10
  Author: ROBO
  Date: October 2023
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1017) // adjust value based on your local sea level pressure

// Initialize the display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

Adafruit_BME280 bme; // use I2C interface 0x77

float currentAltitude = 0;
float minAltitude = 999999;
float maxAltitude = 0;

void setup()
{
    Wire.begin();
    Serial.begin(9600); // initialize serial communication at 9600 bits per second
    Serial.println("Altitude Logger!");

    // Initialize with the I2C address of your OLED screen
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ;
    }
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.display();

    if (!bme.begin())
    {
        Serial.println(F("Could not find a valid BME280 sensor, check wiring!"));
        for (;;)
            ; // Don't proceed, loop forever
    }
}

void loop()
{
    // read the sensor value
    currentAltitude = bme.readAltitude(SEALEVELPRESSURE_HPA);

    if(currentAltitude < minAltitude) {
      minAltitude = currentAltitude;
    }
    if(currentAltitude > maxAltitude) {
      maxAltitude = currentAltitude;
    }
    // print the values to the serial for plotting
    Serial.print("Altitude = ");
    Serial.print(currentAltitude);
    Serial.println(" meters");

    // display the values on the screen
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Current Alt: " + String(round(currentAltitude)) + "m");
    display.setCursor(0, 10);
    display.println("Minimum Alt: " + String(round(minAltitude)) + "m");
    display.setCursor(0, 20);
    display.println("Maximum Alt: " + String(round(maxAltitude)) + "m");
    display.display();

    delay(2000);
}
