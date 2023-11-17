/*
  Sunlight Intensity Tracker
  Description:
  Hardware: RoboUNO, OLED Display, Sparkfun Light Sensor
  Library: Adafruit_SSD1306, SparkFun_VEML6030_Ambient_Light_Sensor
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



int chartMargin = 0;
int chartWidth = SCREEN_WIDTH-(chartMargin*2);
int _circularBuffer[SCREEN_WIDTH]; //fast way to store values 
int _curWriteIndex = 0; // tracks where we are in the circular buffer

int _graphHeight = SCREEN_HEIGHT-6;        
int _minGraphValue = 0;        
int _maxGraphValue = 100;



void setup() {
    Wire.begin();
    Serial.begin(9600); // initialize serial communication at 9600 bits per second
    Serial.println("Sunlight Intensity Tracker!");

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


    lightIntensity = lightSensor.readLight(); // read light intensity

  renderSensorReadingScreen("LIGHT SENSOR", "", float(lightIntensity/100), 100);
  // renderSensorReadingScreen("LIGHT SENSOR", "", 1, 100);

    // display.clearDisplay();
    // display.setTextSize(1);
    // display.setCursor(0, 2);
    // display.println("Intensity:");
    // display.setTextSize(2);
    // display.setCursor(0, 14);
    // display.println(String(lightIntensity));
    // display.display();

    delay(100);
}


void renderSensorReadingScreen(String label, String symbol, float value, float readingDelay) {
    // update limits for y-axis min/max
    if(value-2 < _minGraphValue) {
        _minGraphValue = value-2;
    }    
    if(value+2 > _maxGraphValue) {
        _maxGraphValue = value+2;
    }

    if(_minGraphValue == -2 || _minGraphValue == -1) {
        _minGraphValue = 0;
    }
    if(_maxGraphValue == 102 || _maxGraphValue == 101) {
        _maxGraphValue = 100;
    }    
    // calculate chartMargin and chartWidth based on min and max values (number of characters including '-' sign)
    int digitsMin = countDigits(_minGraphValue);
    int digitsMax = countDigits(_maxGraphValue);
    int digits = (digitsMin > digitsMax) ? digitsMin : digitsMax;
    chartMargin = digits * 4;
    chartWidth = SCREEN_WIDTH-(chartMargin*2);

    display.clearDisplay();
    String sr = getSamplingRateStr(readingDelay);
    write(0, 4, 1, String(label + " " + sr));
    // write(12, 20, 1, "");
    // drawLine(chartMargin, 6, SCREEN_WIDTH, 6);
    drawLine(chartMargin, 6, chartMargin, 32);

    // drawLine(SCREEN_WIDTH-(chartMargin), 6, SCREEN_WIDTH-(chartMargin), 32);
    updateChart(value, symbol);
    display.display();
}


void drawLine(int x0, int y0, int x1, int y1) {
    display.drawLine(x0, y0, x1, y1, SSD1306_WHITE);
}



String getSamplingRateStr(int delay) {
    String samplingRateStr = "";
    float delaySeconds = (float)delay/1000;
    if(delaySeconds < 60) {
        samplingRateStr = String(delaySeconds, 2) + "s.";
    }
    else if(delaySeconds < 3600) {
        float delayMinutes = (float)delaySeconds/60;
        samplingRateStr = String(delayMinutes, 2) + "m.";
    }
    else {
        float delayHours = (float)delaySeconds/60/60;
        samplingRateStr = String(delayHours, 2) + "h.";
    }
    // float readsPerSecond = 1/(delay / 1000);
    // write(70, 4, 1, samplingRateStr);
    return samplingRateStr;
}



void updateChart(int analogVal, String symbol) {

    _circularBuffer[_curWriteIndex++] = analogVal;

    // Set the circular buffer index back to zero when it reaches the 
    // right of the screen
    if(_curWriteIndex >= chartWidth){
        _curWriteIndex = 0;
    }
    
    write(0, 11, 1, String(_maxGraphValue));
    write(0, 30, 1, String(_minGraphValue));
    

    // Draw the line graph based on data in _circularBuffer
    int xPos = chartMargin; 
    for (int i = _curWriteIndex; i < chartWidth; i++){
        int analogVal = _circularBuffer[i];
        drawChartLine(xPos, analogVal);
        xPos++;
    }
    
    for(int i = 0; i < _curWriteIndex; i++){
        int analogVal = _circularBuffer[i];
        drawChartLine(xPos, analogVal);
        xPos++;;
    }

    int valueYPos = map(analogVal, _minGraphValue, _maxGraphValue, 0, _graphHeight);
    valueYPos = _graphHeight - valueYPos;
    write((SCREEN_WIDTH-chartMargin)-(symbol.length()*4), valueYPos, 1, String(analogVal) + symbol);


}


/**
 * Draw the line at the given x position and analog value
 */
void drawChartLine(int xPos, int analogVal){

    int lineHeight = map(analogVal, _minGraphValue, _maxGraphValue, 0, _graphHeight);
    int yPos = display.height() - (lineHeight + 1);
    if(true) {
        display.drawFastVLine(xPos, yPos, lineHeight, SSD1306_WHITE);
    }
    else {
        display.drawPixel(xPos, yPos, SSD1306_WHITE);
    }

}



int countDigits(int val) {
    int count = 1;

    if(val < -1000) { count = 5; }
    else if(val <= -100) { count = 4; }
    else if(val <= -10) { count = 3; }
    else if(val <= -1) { count = 2; }
    else if(val >= 1000) { count = 4; }
    else if(val >= 100) { count = 3; }
    else if(val >= 10) { count = 2; }
    else if(val >= 1) { count = 1; }

    return count;
}


void write(int x, int y, int fontSize, String text) {
    display.setTextSize(fontSize);
    display.setCursor(x,y);
    display.println(text);
}
