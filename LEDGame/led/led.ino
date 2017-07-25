#include <Servo.h>
int led[] = {3, 4, 5, 6};
int active = 0; //Initialize at 0
int arrLen = sizeof(led)/sizeof(int);
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  for (int i = 0; i < arrLen; i++) {
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], LOW);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led[active], LOW); //Turn off LED
  active = random(0, arrLen);
  digitalWrite(led[active], HIGH);
  delay(random(100, 500));
}
