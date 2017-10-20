#include <dht.h>

#include <LiquidCrystal_I2C.h>
#include <limits.h>
#include <IRLibAll.h>

#define DHT11_PIN 
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address


int ldrPin[] = {2, 1, 0, 3};
//int ldrDir[] = {0, 90, 180, 270};
const int ldrLen = sizeof(ldrPin)/sizeof(const int);
int ldrVal[ldrLen] = {0};
const int forwardsIndex = 2;

const int irPin = 5; //7 on PCB, use wire to bridge
const int tempSensorPin = 13;

const int driveLPin = 6; //x on PBC, brige
const int hDrive1 = 8;
const int hDrive2 = 9;
char line[16];


void setup() {
  Serial.begin(9600);
  // for (int i = 0; i < ldrLen; i++) {
  //   pinMode(ldrPin[i], INPUT);
  // }
  pinMode(driveLPin, OUTPUT);
  pinMode(hDrive1, OUTPUT);
  pinMode(hDrive2, OUTPUT);

  pinMode(irPin, OUTPUT);
}

void rotate(int speed) {
  analogWrite(driveLPin, speed);
  analogWrite(hDrive1, speed);
  analogWrite(hDrive2, 0); //Set one to ground
  //hDrive pins should be reversed. Don't know which way is fowards yet though
}

void forwards(int speed) {
  bool hDir = false;
  analogWrite(driveLPin, speed);
  analogWrite(hDrive1, hDir?speed:0);
  analogWrite(hDrive2, hDir?0:speed);
}


void updateLDR() {
  for (int i = 0; i < ldrLen; i++) {
    ldrVal[i] = analogRead(ldrPin[i]);
  }
}

void maxLightForwards(int threshold) {
  int prevVal = 0;
  int numTimesIndexTheSame = 0;
  while(true) {
    delay(10);
    if (prevVal == getLargestIndex()) numTimesIndexTheSame++;
    if (numTimesIndexTheSame > threshold && getLargestIndex() == forwardsIndex) break;
    else rotate(1);//rotate very slowly
  }
}


int getLargestIndex() {
  int largestIndex = -1;
  int largestVal = INT_MIN; //Set to smallest number
  for(int i = 0; i < ldrLen; i++) {
    if (largestVal < ldrVal[i]) {
      largestVal = ldrVal[i];
      largestIndex = i;
    }
  }
  return largestIndex;
}

void loop() {
  maxLightForwards(10);
  forwards(5);
}

