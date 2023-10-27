/*
  Smart Environment Meter
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


// Initialize the display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);


Adafruit_BME280 bme; // use I2C interface 0x77
Adafruit_Sensor *bme_temp = bme.getTemperatureSensor();
Adafruit_Sensor *bme_pressure = bme.getPressureSensor();
Adafruit_Sensor *bme_humidity = bme.getHumiditySensor();


void setup() {
    Wire.begin();
    Serial.begin(9600); // initialize serial communication at 9600 bits per second
    Serial.println("Smart Environment Meter!");

    // Initialize with the I2C address of your OLED screen
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }    
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.display();

    if (!bme.begin()) {
        Serial.println(F("Could not find a valid BME280 sensor, check wiring!"));
        for(;;); // Don't proceed, loop forever
    }
      
}

void loop() {
    // read the sensor values
    sensors_event_t temp_event, pressure_event, humidity_event;
    bme_temp->getEvent(&temp_event);
    bme_pressure->getEvent(&pressure_event);
    bme_humidity->getEvent(&humidity_event);

    // print the values to the serial for plotting
    Serial.print(F("Temperature-*C:"));
    Serial.print(temp_event.temperature);
    Serial.print(",");
    Serial.print(F("Humidity-%:"));
    Serial.print(humidity_event.relative_humidity);
    Serial.print(",");
    Serial.print(F("Pressure-hPa-p100:"));
    Serial.println(pressure_event.pressure / 100);

    // display the values on the screen
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Temperature: " + String(round(temp_event.temperature)) + "C");
    display.setCursor(0, 10);
    display.println("Humidity: " + String(round(humidity_event.relative_humidity)) + "%");
    display.setCursor(0, 20);
    display.println("Pressure: " + String(round(pressure_event.pressure)) + "hPa");
    display.display();

    delay(250);
}


