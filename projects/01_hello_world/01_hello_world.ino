/*
  Hello World!
  Description: A simple sketch that prints some text 1 time per second.
  Hardware: RoboUNO
  Library: -
  Difficulty: 1/10
  Author: ROBO
  Date: August 11, 2023
*/

int counter = 0;  // The counter variable helps to see how many times our loop has executed

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);  // initialize serial communication at 9600 bits per second
}

// the loop routine runs over and over again forever:
void loop() {
  counter++;                                          // increase the value of the counter variable by 1 every time the loop is executed
  Serial.println("Hello World! " + String(counter));  // print a message and the value of the counter
  delay(1000);                                        // sleep for 1000 millisecons or 1 second
}
