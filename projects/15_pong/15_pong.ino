/*
 * Pong on Arduino UNO and 128*32 display
 * Adapted from https://medium.com/@ruction/arduino-pong-i2c-oled-128x64-bd4185970b50
 */

 
#include <Wire.h>                  // This library allows you to communicate with I2C
#include <Adafruit_GFX.h>          // Adafruit GFX graphics core library
#include <Adafruit_SSD1306.h>      // Driver library for 'monochrome' 128x64 and 128x32 OLEDs


// Define the PINS you're goint to use on your Arduino Nano
int controller1 = 2;               // ANALOG 2
int controller2 = 6;               // ANALOG 3
// int ledPin = 7;                    // DIGITAL 4
int btnPin = 4;                    // DIGITAL 5

// Define variables
int buttonState = 0;               // HIGH = Pressed
int gameState = 0;                 // 0 = Home, 1 = Game, 2 = End

int controllerValue1 = 0;          // variable to store the value coming from the potentiometer
int controllerValue2 = 0;          // variable to store the value coming from the potentiometer

int paddlePositionPlayer1 = 0;
int paddlePositionPlayer2 = 0;  

int scorePlayer1 = 0;    
int scorePlayer2 = 0;

int ballX = 128/2;      
int ballY = 32/2;
int ballSpeedX = 4;
int ballSpeedY = 2;

#define OLED_RESET 4

Adafruit_SSD1306 display(OLED_RESET);
    
#if (SSD1306_LCDHEIGHT != 32)
  #error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif



void setup() {
  // pinMode(ledPin, OUTPUT);
  pinMode(btnPin, INPUT_PULLUP);

  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)
  display.clearDisplay();

//   digitalWrite(ledPin, HIGH);                 // Status led on...
}

void loop() {
 
  // Read controller value and calculate paddle position
  controllerValue1 = analogRead(controller1);
  controllerValue2 = analogRead(controller2);

  paddlePositionPlayer1 = controllerValue1 * (46.0 / 1023.0);
  paddlePositionPlayer2 = controllerValue2 * (46.0 / 1023.0);

  // Set button state
  buttonState = digitalRead(btnPin) ? false : true ;

  if (buttonState == HIGH && gameState == 0) {
      gameState = 1;
      delay(100);
  } else if (buttonState == HIGH && (gameState == 1 || gameState == 2)) {
      gameState = 0;
      scorePlayer1 = 0;
      scorePlayer2 = 0;
      ballX = 128/2;
      ballY = 32/2;
      delay(100);
  }
  
  if (gameState == 0) {
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(37, 6);
    display.println("PONG");
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(27, 20);
    display.println("press start");
    display.display();
    display.clearDisplay();      
  }

  if (gameState == 1) {
    drawField(scorePlayer1, scorePlayer2);
    
    collisionControl();
    drawBall();
    
    display.display();
    display.clearDisplay();
  }

  if (gameState == 2) {
    drawField(scorePlayer1, scorePlayer2);

    display.setTextSize(1);
    display.setTextColor(WHITE);
    
    if (scorePlayer1 == 2) {
      display.setCursor(7, 15);
    } else if (scorePlayer2 == 2) {
      display.setCursor(38, 15);
    }
    display.println("winner!");
    display.display();
    display.clearDisplay();   
  }
}

void drawField(int score1, int score2) {
    display.fillRect(0, round(paddlePositionPlayer1), 2, 9, 1);
    display.fillRect(126, round(paddlePositionPlayer2), 2, 9, 1);
  
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(55, 0);
    display.print(score1);
    display.print(":");
    display.print(score2);

    display.fillRect(63, 12, 1, 5, 1);
    display.fillRect(63, 22, 1, 5, 1);
    display.fillRect(63, 32, 1, 5, 1);
    display.fillRect(63, 42, 1, 5, 1);
    display.fillRect(63, 52, 1, 5, 1);
    display.fillRect(63, 62, 1, 5, 1);
}

void collisionControl() {
  //bounce from top and bottom
  if (ballY >= 32 - 2 || ballY <= 0) {
    ballSpeedY *= -1;
  } 

  //score points if ball hits wall behind player
  if (ballX >= 128 - 2 || ballX <= 0) {
    if (ballSpeedX > 0) {
      scorePlayer1++;
      ballX = 128 / 4;
    }
    if (ballSpeedX < 0) {
      scorePlayer2++;
      ballX = 128 / 4 * 3;
    }  
    if (scorePlayer1 == 4 || scorePlayer2 == 4) {     //set the score to win
      gameState = 2;
    }
  }

  //bounce from player1
  if (ballX >= 0 && ballX <= 2 && ballSpeedX < 0) {
    if (ballY > round(paddlePositionPlayer1) - 2 && ballY < round(paddlePositionPlayer1) + 9) {
      ballSpeedX *= -1;
    }
  }
  //bounce from player2
  if (ballX >= 128-2-2 && ballX <= 128-2 && ballSpeedX > 0) {
    if (ballY > round(paddlePositionPlayer2) - 2 && ballY < round(paddlePositionPlayer2) + 9) {
      ballSpeedX *= -1;
    }

  }
}

void drawBall() {

  display.fillRect(ballX, ballY, 2, 2, 1);
  
  ballX += ballSpeedX;
  ballY += ballSpeedY;
}


// //oled libraries:
// #include <SPI.h>
// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
// //oled vars:
// #define SCREEN_WIDTH 128 // OLED display width, in pixels
// #define SCREEN_HEIGHT 32 // OLED display height, in pixels
// #define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
// #define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// //Button pins:
// const int buttonUP = 6;
// const int buttonDOWN = 2;
// //button vars:
// int lastButtonStateUP = LOW;   // the previous reading from the input pin
// int lastButtonStateDOWN = LOW;   // the previous reading from the input pin
// unsigned long debounceDelay = 10;    // the debounce time; increase if the output flickers

// //GAME vars:
// //scores:
// int player_score = 0;
// int enemy_score = 0;

// //player:
// int player_position_X = 19; // static
// int player_position_Y = 0;
// int player_width = 16;
// int player_thickness = 4;

// //enemy:
// int enemy_position_X = 104; // static
// int enemy_position_Y = 15;
// int enemy_width = 16;
// int enemy_thickness = 4;
// long enemy_last_move_time = 0;
// long enemy_speed_of_moving = 2000;//update time in ms


// //ball:
// //void fillCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color);
// int ball_position_X = SCREEN_HEIGHT-1;
// int ball_position_Y = 31;
// int ball_radius = 1;
// int ball_direction_X = 3;
// int ball_direction_Y = 3;
// int ball_speed = 8;//9,8,7...1
// long ball_last_move_time = 0;


// void setup() {
//   // put your setup code here, to run once:
//   pinMode(buttonUP, INPUT_PULLUP);
//   pinMode(buttonDOWN, INPUT_PULLUP);

//   Serial.begin(9600);
//   Serial.println("Start");

//   //initiate random
//   randomSeed(analogRead(0));
//   ball_direction_X = -3;
//   ball_direction_Y = random(-5, 5);
//   //ball_direction_Y = -5;//test

  

//   // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
//   if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
//     Serial.println(F("SSD1306 allocation failed"));
//     for(;;); // Don't proceed, loop forever
//   }

//   // Show initial display buffer contents on the screen --
//   // the library initializes this with an Adafruit splash screen.
//   display.display();
  

//   // Clear the buffer
//   display.clearDisplay();
  
  
//   //draw lines:
//   display.drawLine(16,  0,  16, SCREEN_HEIGHT-1, SSD1306_WHITE);
//   display.drawLine(111, 0, 111, SCREEN_HEIGHT-1, SSD1306_WHITE);
//   display.display();
  
//   //scores field init:
//   display.setTextSize(2);    
//   display.setTextColor(SSD1306_WHITE); // Draw white text

//   player_score = 8888; // test
//   enemy_score = 8888; // test
//   print_score(player_score, 0);
//   print_score(enemy_score, 115);
  
//   display.setTextSize(3);
//   display.setCursor(28, 0);
//   display.write("Ping");
//   display.setCursor(28, 31);
//   display.write("Pong");
//   display.display();
  
//   display.setTextSize(2);
//   delay(2000); // Pause for 2 seconds
  

//   //NEW GAME:
  
//   // Clear the buffer
//   display.clearDisplay();
  
//   //draw lines:
//   display.drawLine(16,  0,  16, SCREEN_HEIGHT-1, SSD1306_WHITE);
//   display.drawLine(111, 0, 111, SCREEN_HEIGHT-1, SSD1306_WHITE);
//   display.display();
  
//   //Write scores:
//   player_score = 0; //reset player_score
//   enemy_score = 0;  //reset enemy_score
//   print_score(player_score, 0);
//   print_score(enemy_score, 115);
  
//   //Display players:
//   //void fillRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t color);
//   display.fillRect(player_position_X, player_position_Y, player_thickness, player_width, SSD1306_WHITE);
//   display.fillRect(enemy_position_X, enemy_position_Y, enemy_thickness, enemy_width, SSD1306_WHITE);
//   display.display(); // Update screen with each newly-drawn rectangle

  
//   //Display the ball:
//   display.fillCircle(ball_position_X, ball_position_Y, ball_radius, SSD1306_WHITE);
//   display.display();

  
  
//   delay(500); // Pause for 0.5 second  
// }

// void loop() {
//   buttons_check();

//   move_the_ball_and_check_for_collisions();

//   move_enemy();
// }

// void move_enemy(){
//   //enemy:
//   if(millis() > enemy_speed_of_moving+enemy_last_move_time){
//     display.fillRect(enemy_position_X, enemy_position_Y, enemy_thickness, enemy_width, SSD1306_BLACK);
    
//     if(ball_position_Y < enemy_position_Y+enemy_width/2){
//       enemy_position_Y = enemy_position_Y - 3;
//     }else{
//       enemy_position_Y = enemy_position_Y + 3;
//     }

//     //checking if enemy is within the wall:
//     if(enemy_position_Y > 64-player_width) enemy_position_Y = 64-player_width;
//     if(enemy_position_Y < 0) enemy_position_Y = 0;
      
// //    Serial.print("enemy_position_Y: "); Serial.println(enemy_position_Y);
//     display.fillRect(enemy_position_X, enemy_position_Y, enemy_thickness, enemy_width, SSD1306_WHITE);
//     display.display(); // Update screen with each newly-drawn rectangle
//     enemy_last_move_time = millis();
//   }
  
// }

// void move_the_ball_and_check_for_collisions(){
//   //move th ball:
//   if(millis() > ball_speed*20+ball_last_move_time){
//     //erase ball on old position:
//     display.fillCircle(ball_position_X, ball_position_Y, ball_radius, SSD1306_BLACK);
//     display.display();
    
//     //set new posion of the ball:
//     ball_position_X = ball_position_X + ball_direction_X;
    
//     if(ball_position_Y + ball_direction_Y < -1) ball_direction_Y = ball_direction_Y * -1;
//     if(ball_position_Y + ball_direction_Y > 64) ball_direction_Y = ball_direction_Y * -1;
    
//     ball_position_Y = ball_position_Y + ball_direction_Y;
    
//     //draw ball on new position:
//     display.fillCircle(ball_position_X, ball_position_Y, ball_radius, SSD1306_WHITE);
//     display.display();
// //    Serial.print("ball_position_Y: "); Serial.println(ball_position_Y);
//     ball_last_move_time = millis();

//     //Check for player loose:
//     if(ball_position_X < player_position_X){
//       Serial.println("Player lose!");
//       newRound("enemy");//player
//     }
//     //check for collision of the ball and the player:
//     if(player_position_X <= ball_position_X && player_position_X+player_thickness >= ball_position_X
//     && player_position_Y <= ball_position_Y && player_position_Y+player_width >= ball_position_Y){
//       Serial.println("Collision of the ball and the player");
//       //send the ball to enemy with random values:
//       ball_direction_X = 3;
//       ball_direction_Y = random(-5, 5);
//       display.fillRect(player_position_X, player_position_Y, player_thickness, player_width, SSD1306_WHITE);
//       display.display(); // Update screen with each newly-drawn rectangle
      
//     }
//     //check for enemy loose:
//     if(ball_position_X > enemy_position_X+enemy_thickness){
//       Serial.println("Enemy lose!");
//       newRound("player");//enemy
//     }
//     //check for collision of the ball and the enemy:
//     if(enemy_position_X <= ball_position_X && enemy_position_X+enemy_thickness >= ball_position_X
//     && enemy_position_Y <= ball_position_Y && enemy_position_Y+enemy_width >= ball_position_Y){
//       Serial.println("Collision of the ball and the enemy");
//       //send the ball to player with random values:
//       ball_direction_X = -3;
//       ball_direction_Y = random(-5, 5);
//       display.fillRect(enemy_position_X, enemy_position_Y, enemy_thickness, enemy_width, SSD1306_WHITE);
//       display.display(); // Update screen with each newly-drawn rectangle
//     }
//   }
  
// }

// void newRound(String winner){
//   // Clear the buffer
//   display.clearDisplay();
  
//   //draw lines:
//   display.drawLine(16,  0,  16, SCREEN_HEIGHT-1, SSD1306_WHITE);
//   display.drawLine(111, 0, 111, SCREEN_HEIGHT-1, SSD1306_WHITE);
//   display.display();
  
//   //Update scores:
//   if(winner == "enemy"){
//     enemy_score++;
//   }else{
//     player_score++;
//   }
//   print_score(player_score, 0);
//   print_score(enemy_score, 115);

//   //reset gaming vars:
//   //player:
//   player_position_X = 19; // static
//   player_position_Y = 0;
//   player_width = 16;
//   player_thickness = 4;
  
//   //ball:
//   ball_position_X = SCREEN_HEIGHT-1;
//   ball_position_Y = 31;
//   ball_radius = 1;
//   //set random direction for th ball:
  
//   ball_direction_X = -3;
//   ball_direction_Y = random(-5, 5);
//   //ball_direction_Y = -5;//test
//   ball_last_move_time = 0;
  
//   //Display players:
//   //void fillRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t color);
//   display.fillRect(player_position_X, player_position_Y, player_thickness, player_width, SSD1306_WHITE);
//   display.display(); // Update screen with each newly-drawn rectangle

//   //enemy:
//   enemy_position_X = 104; // static
//   enemy_position_Y = 47;
//   enemy_width = 16;
//   enemy_thickness = 4;
//   enemy_last_move_time = 0;

//   //checking for if we need to update enemy_speed_of_moving and ball_speed
//   if((player_score+enemy_score)%5 == 0){
//     //5,10,15 and so on
//     if(ball_speed > 3) ball_speed = ball_speed - 1; //10,9,8...
//     Serial.print("ball_speed: ");Serial.println(ball_speed);
//   }
//   if((player_score+enemy_score)%10 == 0){
//     //10,20,30 and so on
//     if(enemy_speed_of_moving > 1) enemy_speed_of_moving = enemy_speed_of_moving * 0.9; //2000,1800,1620,1458...
//     Serial.print("enemy_speed_of_moving: ");Serial.println(enemy_speed_of_moving);
//   }
  
//   delay(500); // Pause for 0.5 seconds
// }

// void print_score(int temp_num, int X){ //0/115
//   for(int i=48; i>=0; i-=16){
    
//     int num = temp_num % 10;
//     char cstr[16];
//     itoa(num, cstr, 10);
    
//     display.setCursor(X, i);
//     display.write(cstr);
//     display.display();
// //    Serial.println(cstr);
    
//     temp_num = temp_num/10;
//     if(temp_num==0){
//       break;
//     }
//   }
// }

// void buttons_check(){ 
//   if (!digitalRead(buttonUP) && !lastButtonStateUP) {
//     lastButtonStateUP = true;
// //    Serial.println("UP pressed");
//     if(player_position_Y > 0){
//       display.fillRect(player_position_X, player_position_Y, player_thickness, player_width, SSD1306_BLACK);
//       player_position_Y = player_position_Y-3;
//       display.fillRect(player_position_X, player_position_Y, player_thickness, player_width, SSD1306_WHITE);
//       display.display(); // Update screen with each newly-drawn rectangle
//     }
//   }
//   if (digitalRead(buttonUP) && lastButtonStateUP) {
//     lastButtonStateUP = false;
//   }


//   if (!digitalRead(buttonDOWN) && !lastButtonStateDOWN) {
//     lastButtonStateDOWN = true;
// //    Serial.println("DOWN pressed");
//     if(player_position_Y < 64-player_width){
//       display.fillRect(player_position_X, player_position_Y, player_thickness, player_width, SSD1306_BLACK);
//       player_position_Y = player_position_Y+3;
//       display.fillRect(player_position_X, player_position_Y, player_thickness, player_width, SSD1306_WHITE);
//       display.display(); // Update screen with each newly-drawn rectangle
//     }
//   }
//   if (digitalRead(buttonDOWN) && lastButtonStateDOWN) {
//     lastButtonStateDOWN = false;
//   }
// }


// /*
// oled figures:
// https://learn.adafruit.com/adafruit-gfx-graphics-library/graphics-primitives




// */