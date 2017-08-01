#include <Servo.h>
const int led[] = {3, 4, 5, 6};
const int ledPos[] = {60, 80, 100, 120};
const int ldr = 5;
int active = -1; //Initialize at 0
const int arrLen = sizeof(led)/sizeof(int);
const int servo1Pin = 2;
const int motorPin = 10;
Servo servo1;
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  for (int i = 0; i < arrLen; i++) {
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], LOW);
  }
  pinMode(servo1Pin, OUTPUT);
  servo1.attach(servo1Pin);
  //servo1.write(130);
  randomSeed(1);
  pinMode(motorPin, OUTPUT);

//  for (int i = 0; i < 1023; i++) {
//    Serial.println(map(i,200,1000,60,120));
//    delay(10);
//  }
}

int selectedLed(int position, int variance) {
  for (int i = 0; i < arrLen; i++) {
    if (abs(ledPos[i] - position) < variance) {
      return i;
    }
  }
  return -1; //No match, return -1
}

void motorCountdown(int num) {
  for (int i = 0; i < num; i++) {
   digitalWrite(motorPin,HIGH);
    delay(300);
    digitalWrite(motorPin, LOW);
    if (i < num - 1) {
      delay(700);
    }
  }
}

void flashLed(int time, int number) {
  analogWrite(motorPin, 100);
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
  analogWrite(motorPin, 0);
}


int matches = 0;
int requiredMatches = 8;
int target = 0;
unsigned long time = millis();
int originalSpeed = 10000;
int speed = originalSpeed;
int speedIncrement = 50;

int minLdr = 480;
int maxLdr = 580;


void loop() {
  //motorCountdown(3);
  digitalWrite(led[target], LOW);
  target = random(0, arrLen);
  digitalWrite(led[target], HIGH);
  time = millis();
  Serial.println(time);
  Serial.println("Started");
  Serial.println(millis()-time);
  while (millis() - time < speed) {
    Serial.println(millis()-time);
    delay(50);
    int ldrVal = constrain(analogRead(ldr), minLdr, maxLdr);
    int pos = map(ldrVal, maxLdr, minLdr, 50, 130);

    servo1.write(pos);
    active = selectedLed(pos, 10);
    /*Serial.println(active);
    Serial.println(target);*/
    if (active == target) {
      matches++;
      /*
      Serial.println("Match");
      Serial.println(matches);
      Serial.println(requiredMatches);*/
    }
    else {
      matches = 0;
      /*
      Serial.println("not match");
      Serial.println(matches);*/
    }
    
    if (matches >= requiredMatches) {
      //If more matches than rquired, exit loop
      break;
    }
  }
 
  if (matches < requiredMatches) {
     //If exited because faliure
    //Set back to original speed
    speed = originalSpeed;
    flashLed(100, 5);
    delay(1000);
  }
  
  else {
    speed -= speedIncrement;
    //decrease speed: increase difficulty
  }
  Serial.println("exited");
}

