#include <Servo.h>

//Array of LED pins and their position in degrees
const int led[] = {2,3,4,6,7};
const int ledPos[] = {170, 130, 90, 50, 10};
const int arrLen = sizeof(led)/sizeof(int); //Number of LEDs

//Pins for LDR, servo and motor
const int ldrPin = 0;
const int servoPin = 13;
const int motorPin = 10;

Servo servo; //Declare Servo object

int active; //The index of the LED the servo is pointing to
int target = 0; //The index of the LED that the user should point to to pass the level. Initialized to 0

const int originalSpeed = 4000; //The original time the user has before losing
const int speedIncrement = 100; //How much to decrease this time by after every 'level'

int speed = originalSpeed; //The time the user has for that specific level

const int requiredMatches = 5; //The number of continuous matches a user needs before completing the level
int matches = 0; //The number of continuous matches the user has. Initialized to zero

const int userVariance = 10; //Amount of 'wiggle-room' the user has

//The range of LDR values the motor should respond to
int minLdr = 550;
int maxLdr = 800;

unsigned long time = millis(); //The time at the start of the level. Uses unsigned long as int fails after ~32 seconds


void setup() {
  Serial.begin(9600);
  for (int i = 0; i < arrLen; i++) {
    //Set all LED pins to OUTPUT. Set all to off
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], LOW);
  }

  pinMode(servoPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  servo.attach(servoPin); //Initialize servo
  randomSeed(1); //Set random seed to from analog pin 1. This pin should not be used
}


int selectedLed(int position, int variance) {
  //Position: position of servo
  //Variance: amount of 'wiggle room' the user has for there to be a match. The range is double the variance
  for (int i = 0; i < arrLen; i++) {
    if (abs(ledPos[i] - position) < variance) {
      return i;
      //Returns either the index of the LED or -1 if there are no matches
    }
  }
  return -1; //No match, return -1
}


void flashLed(int time, int number, bool spinMotor) {
  //Time: time between flashes
  //Number: number of times to turn on and off
  //spinMotor: if the motor should spin or not
  if (spinMotor) {
    digitalWrite(motorPin, HIGH); //Turns the motor on until the end of the function
  }

  for (int i = 0; i < number; i++) {
    for (int j = 0; j < arrLen; j++) {
      digitalWrite(led[j], HIGH);
    }
    delay(time);
    for (int j = 0; j < arrLen; j++) {
      digitalWrite(led[j], LOW);
    }
    delay(time);
  }

  if (spinMotor) {
    digitalWrite(motorPin, LOW);
  }
}


void loop() {
  digitalWrite(led[target], LOW); //Turn the pervious target LED off

  target = random(0, arrLen); //Set target LED to random integer and turn that LED on
  digitalWrite(led[target], HIGH); 
  
  time = millis(); //Set the time at the start of the loop
  while (millis() - time < speed) {
    //Continue through the loop until the time since when the function started is greater than the time the user has to complete the level
    delay(50); //Delay of 50 milliseconds each time it goes through the loop. Makes setting `requiredMatches` easier. 
    int ldrVal = constrain(analogRead(ldrPin), minLdr, maxLdr); //Get the value of the LDR, and constrain it.
    int pos = map(ldrVal, maxLdr, minLdr, 0, 180); //Constrained, so pos will always be between 0 and 180

    servo.write(pos); //Servo postiion mapped to the LED value
    active = selectedLed(pos, userVariance); //Find which LED the servo is pointing to

    if (active == target) {
      matches++; //Increase the amount of matches if servo pointing at the right LED
    }
    else {
      matches = 0; //If not pointing, set matches to 0- `matches` measures the number of continuous matches to ensure the servo is relatively static
    }
    
    if (matches >= requiredMatches) {
      //If more matches than required, exit loop
      break;
    }
  }
 
  if (matches < requiredMatches) {
     //If exited because the user ran out of time, and not because the user got the required number of matches
    speed = originalSpeed; //Restart- set speed to the original speed
    flashLed(100, 5, true); //Flash the LEDs 5 times
    delay(1000); //Wait 1 second so the user can prepare
  }
  
  else {
    speed -= speedIncrement; //Decrease speed to increase difficulty

    if (speed < speedIncrement) {
      //If, in the next level, the speed would be less than 0
      flashLed(80, 10, true); //Flash the LED, spin the motor
      speed = originalSpeed; //Restart the game
      delay(2000);
    }
  }
}

