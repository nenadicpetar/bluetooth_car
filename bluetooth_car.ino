#include <FastLED.h>
#include <AFMotor.h>

#define frontNUM_LEDS 24
#define backNUM_LEDS 14

CRGB frontleds[frontNUM_LEDS];
CRGB backleds[backNUM_LEDS];


//initial motors pin
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

#define frontStrip 2
#define backLED 13
#define vrijeme 60
#define brzina 100

char command;

void setup()
{
  Serial.begin(9600);  //Set the baud rate to your Bluetooth module.
  pinMode(frontStrip, OUTPUT);
  pinMode(backLED, OUTPUT);

  FastLED.addLeds<WS2812, frontStrip, GRB>(frontleds, frontNUM_LEDS);
  FastLED.addLeds<WS2812, backLED, GRB>(backleds, backNUM_LEDS);
}

void loop() {
  if (Serial.available() > 0) {
    command = Serial.read();
    Stop(); //initialize with motors stoped
    //Change pin mode only if new command is different from previous.
    //Serial.println(command);
    switch (command) {
      case 'F':
        forward();
        break;
      case 'B':
        back();
        break;
      case 'L':
        left();
        break;
      case 'R':
        right();
        break;
      case 'G':
        forwardLeft();
        break;
      case 'I':
        forwardRight();
        break;
      case 'H':
        backLeft();
        break;
      case 'J':
        backRight();
        break;
      case 'W':
        frontLightOn();
        break;
      case 'w':
        frontLightOff();
        break;
      case 'U':
        backLightOn();
        break;
      case 'u':
        backLightOff();
        break;
    }
  }
}

void forward()
{
  motor1.setSpeed(brzina); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(brzina); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise
  motor3.setSpeed(brzina);//Define maximum velocity
  motor3.run(FORWARD); //rotate the motor clockwise
  motor4.setSpeed(brzina);//Define maximum velocity
  motor4.run(FORWARD); //rotate the motor clockwise
}

void back()
{
  motor1.setSpeed(brzina); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(brzina); //Define maximum velocity
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.setSpeed(brzina); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(brzina); //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
}

void left()
{
  motor1.setSpeed(brzina); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(brzina); //Define maximum velocity
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.setSpeed(brzina); //Define maximum velocity
  motor3.run(FORWARD);  //rotate the motor clockwise
  motor4.setSpeed(brzina); //Define maximum velocity
  motor4.run(FORWARD);  //rotate the motor clockwise
}

void right()
{
  motor1.setSpeed(brzina); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(brzina); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise
  motor3.setSpeed(brzina); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(brzina); //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
}

void Stop()
{
  motor1.setSpeed(0); //Define minimum velocity
  motor1.run(RELEASE); //stop the motor when release the button
  motor2.setSpeed(0); //Define minimum velocity
  motor2.run(RELEASE); //rotate the motor clockwise
  motor3.setSpeed(0); //Define minimum velocity
  motor3.run(RELEASE); //stop the motor when release the button
  motor4.setSpeed(0); //Define minimum velocity
  motor4.run(RELEASE); //stop the motor when release the button
}

void forwardRight() {
  motor1.setSpeed(brzina);
  motor1.run(FORWARD);
  motor2.setSpeed(brzina);
  motor2.run(FORWARD);
  motor3.setSpeed(brzina / 3.1);
  motor3.run(FORWARD);
  motor4.setSpeed(brzina / 3.1);
  motor4.run(FORWARD);
}

void forwardLeft() {
  motor1.setSpeed(brzina / 3.1);
  motor1.run(FORWARD);
  motor2.setSpeed(brzina / 3.1);
  motor2.run(FORWARD);
  motor3.setSpeed(brzina);
  motor3.run(FORWARD);
  motor4.setSpeed(brzina);
  motor4.run(FORWARD);
}

void backRight() {
  motor1.setSpeed(brzina);
  motor1.run(BACKWARD);
  motor2.setSpeed(brzina);
  motor2.run(BACKWARD);
  motor3.setSpeed(brzina / 3.1);
  motor3.run(BACKWARD);
  motor4.setSpeed(brzina / 3.1);
  motor4.run(BACKWARD);
}

void backLeft() {
  motor1.setSpeed(brzina / 3.1);
  motor1.run(BACKWARD);
  motor2.setSpeed(brzina / 3.1);
  motor2.run(BACKWARD);
  motor3.setSpeed(brzina);
  motor3.run(BACKWARD);
  motor4.setSpeed(brzina);
  motor4.run(BACKWARD);
}

void frontLightOn() {
  for(int i = 0; i <= ((frontNUM_LEDS/2)-1); i++){
    frontleds[i] = CRGB(5, 5, 5);
    frontleds[(frontNUM_LEDS/2-1)+((frontNUM_LEDS/2)-i)] = CRGB(5, 5, 5);
    FastLED.show();
    delay(40);
  }
  delay(100);
  for (int i = ((frontNUM_LEDS/2)-1); i >=0; i--) {
    frontleds[i] = CRGB(200, 200, 200);
    frontleds[(frontNUM_LEDS/2-1)+((frontNUM_LEDS/2)-i)] = CRGB(200, 200, 200);
    FastLED.show();
    delay(40);
  }
}

void frontLightOff() {
  for(int i = ((frontNUM_LEDS/2)-1); i >= 0; i--){
    frontleds[i] = CRGB(5, 5, 5);
    frontleds[(frontNUM_LEDS/2-1)+((frontNUM_LEDS/2)-i)] = CRGB(5, 5, 5);
    FastLED.show();
    delay(40);
  }
  delay(100);
  for (int i = 0; i <= ((frontNUM_LEDS/2)-1); i++) {
    frontleds[i] = CRGB(0, 0, 0);
    frontleds[(frontNUM_LEDS/2-1)+((frontNUM_LEDS/2)-i)] = CRGB(0, 0, 0);
    FastLED.show();
    delay(40);
  }
}

void backLightOn() {
  for(int j =((backNUM_LEDS/2)-1); j >= 0; j--){
    backleds[j] = CRGB(5, 0, 0);
    backleds[(backNUM_LEDS/2-1)+((backNUM_LEDS/2)-j)] = CRGB(5, 0, 0);
    FastLED.show();
    delay(40);
  }
  delay(100);
  for(int j = 0; j <= ((backNUM_LEDS/2)-1); j++){
    backleds[j] = CRGB(255, 0, 0);
    backleds[(backNUM_LEDS/2-1)+((backNUM_LEDS/2)-j)] = CRGB(255, 0, 0);
    FastLED.show();
    delay(40);
  }
}

void backLightOff() {
  for(int j = 0; j <= ((backNUM_LEDS/2)-1); j++){
    backleds[j] = CRGB(5, 0, 0);
    backleds[(backNUM_LEDS/2-1)+((backNUM_LEDS/2)-j)] = CRGB(5, 0, 0);
    FastLED.show();
    delay(40);
  }
  delay(100);
  for(int j =((backNUM_LEDS/2)-1); j >= 0; j--){
    backleds[j] = CRGB(0, 0, 0);
    backleds[(backNUM_LEDS/2-1)+((backNUM_LEDS/2)-j)] = CRGB(0, 0, 0);
    FastLED.show();
    delay(40);
  }
}

void brakeOn() {
  fill_solid(backleds, backNUM_LEDS, CRGB(255, 0, 0));
  FastLED.show();
}
