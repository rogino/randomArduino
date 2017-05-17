#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h> 


const int trigPin = 9;
const int echoPin = 10;
const int SDAPin = 1;
const int SCLPin = 0;
const float cmPerUS = 0.0342; //Speed of sound in centimeters per microsecond
long duration;
int distance;
//LiquidCrystal_I2C lcd(0x20, 4, 5, 6, 0, 1, 2, 3, 7, NEGATIVE);
//LiquidCrystal_I2C lcd(0x20, 16, 2);
LiquidCrystal_I2C lcd(0x20, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.begin(16, 2);
  lcd.setBacklight(1);
  lcd.clear();
  delay(1000);
  lcd.home();
  lcd.print("Hello World");
  Serial.begin(9600);
}



void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * cmPerUS / 2;
  //shiftArr(arrInput, distance); //Read input
  Serial.print("Distance: "); Serial.print(distance); Serial.print("cm\n");

  delay(30);
}

