#include <Stepper.h>

const int internalStepsPerRev = 32;
const int stepsPerRev = internalStepsPerRev * 64;

Stepper stepper(internalStepsPerRev,8,10,9,11);
//Stepper object
const int joyX = 0;
const int joyY = 1;
const int btn = 7;
void setup() {
  // put your setup code here, to run once:
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode (btn,INPUT);
  pinMode(joyX, INPUT);
  pinMode(joyY, INPUT);
  Serial.begin(9600);
}

void runStepper(int motorSpeed, int numSteps, int delayTime) {
  //motorSpeed = rpm
  //numSteps = stepsToTake
  //float timeForOneStep = 60.0/motorSpeed;
  stepper.setSpeed(motorSpeed);
  stepper.step(numSteps);
  delay(delayTime);
}

bool mode = 1;
bool wasPressed = 0;

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(btn) == HIGH && !wasPressed){
    mode=!mode;
    wasPressed = 1;
     
  }
  else if (digitalRead(btn) == LOW){
    wasPressed = 0;
  }
  int maxSpeed = 700;
  int maxPower = 200;
  Serial.print(digitalRead(btn));
  //Serial.print(mode);
  
  if (mode){
    int joyVal = map(analogRead(joyX), 0, 1024, -maxSpeed, maxSpeed);
    int dir = joyVal > 0 ?1:-1;
    runStepper(abs(joyVal), dir, 1);
  }
  else {
    Serial.print("Here\n");
    int joyVal = map(analogRead(joyY), 0, 1024, -maxPower, maxPower);
    int dir = joyVal > 0 ?1:-1;
    runStepper(abs(joyVal), dir, 1);
  }
  delay(10);

}

