# Project #01: Hello World!

First off, the purpose of this sketch is to print a message "Hello World!" along with a counter value to the serial monitor once every second.

The sketch begins with a multi-line comment that provides some metadata about the sketch, such as its description, the hardware it's intended for, its difficulty level, the author, and the date it was written. The global variable `counter` is declared and initialized to 0. This variable is used to keep track of how many times the main loop of the program has executed.

The `setup()` function is a special function in Arduino that is run once when the program starts. In this function, the serial communication is initialized with a baud rate of 9600 bits per second using `Serial.begin(9600)`. This sets up the Arduino to send and receive data at this rate.

The `loop()` function is another special function in Arduino that is run repeatedly after `setup()` finishes. In this function, the `counter` variable is incremented by 1 each time the function is run. Then, a message "Hello World!" along with the current value of `counter` is printed to the serial monitor using `Serial.println()`. The `String(counter)` part converts the integer counter to a string so it can be concatenated with the "Hello World!" message. After printing the message, the program pauses for 1000 milliseconds (or 1 second) using `delay(1000)`. This causes the message to be printed once every second.

The `Serial.println()` function sends data to the serial monitor, which is a separate window that acts like a simple terminal. This is useful for debugging and seeing the output of your program in real time.