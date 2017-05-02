int motorLeft = 8;
int motorRight = 9;
void setup() {
  // put your setup code here, to run once:
  pinMode(motorLeft, OUTPUT);
  pinMode(motorRight, OUTPUT);
}

void setMotors(int l, int r) {
  if (0 <= l && 0 <= r && l <= 255 && r <=255) {
    analogWrite(motorLeft, l);
    analogWrite(motorRight, r);
  }
}
void goForwards(int speed, int length) {
  setMotors(speed,speed);
  delay(length);
  setMotors(0,0);
}

void turnLeft(int length) {
  setMotors(0,255);
  delay(length);
  setMotors(0,0);
}

void turnRight(int length) {
  setMotors(255,0);
  delay(length);
  setMotors(0,0);
}

void loop() {
//  // put your main code here, to run repeatedly:
    goForwards(255,4000);
    turnRight(3000);
    //turnLeft(3000);
    goForwards(0,2000);

//  for (int i = 0; i < 255; i++) {
//    setMotors(i,i);
//    delay(10);
//  }
//  delay(100);
//  for (int i = 255; i > 0; i--) {
//    setMotors(i,i);
//    delay(10);
//  }
//  delay(100);
//  digitalWrite(motorLeft,HIGH);
//  delay(1000);
//  digitalWrite(motorLeft,LOW);
//  delay(1000);
}
