#include <Servo.h>
const int led[] = {2, 4, 5, 7};
const int ldr = 0;
int active = 0; //Initialize at 0
const int arrLen = sizeof(led)/sizeof(int);
const int servo1Pin = 8;
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
  randomSeed(15);
}

int rotation = 0;
bool fowards = true;
void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(ldr));
  digitalWrite(led[active], LOW); //Turn off LED
  active = random(0, arrLen);
  digitalWrite(led[active], HIGH);
  servo1.write(map(analogRead(ldr), 700, 800, 0, 180));
  delay(random(50, 250));
}
