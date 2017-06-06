#include <LiquidCrystal_I2C.h>
#include <limits.h>


const int btnPin = 12;
//Button connected to ground, 5v and 4k7 resistor. LCD connected to 20, 21 (SCL, SDA), 5v and gnd


LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
void setup() {
  pinMode(btnPin, INPUT);   
  Serial.begin(9600);  // Used to type in characters
  lcd.begin(16,2);   // initialize the lcd for 16 chars 2 lines, turn on backlight
  lcd.backlight();
  lcd.print("Click to begin");
  while (digitalRead(btnPin) == LOW) {
    delay(1);
  }

}
unsigned long startTime = 0;
unsigned long bestTime = ULONG_MAX; //The best time. initialized to be biggest
char str[16];

unsigned long waitForBtn() {
  if (digitalRead(btnPin) == HIGH) {
    //Stop people from pressing the whole time
    lcd.clear();
    lcd.print("Too early");
    delay(500);
    return 0;
  }
  startTime = millis(); //start time
  while (digitalRead(btnPin) == LOW) {
    delay(1); //read every millisecond
  }
  unsigned long value = millis() - startTime;
  lcd.clear();
  sprintf(str, "Time: %lums", value);
  lcd.print(str);
  if (value < bestTime) {
    bestTime = value; //change value of bestTime to new bestTime
  }
  return value; //return difference
}


void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Three");
  delay(1000);
  lcd.setCursor(0,0);
  lcd.print("Two  ");
  delay(1000);
  lcd.setCursor(0,0);
  lcd.print("One   ");
  lcd.setCursor(0,0);
  delay(random(50, 3000));
  lcd.print("BANG!");
  unsigned long result = waitForBtn();

  
  delay(200);
  int counter = 0;

  int len = 700;
  while (digitalRead(btnPin) == LOW) {
    lcd.setCursor(0,1);
    if (counter % len == 0) {
      lcd.print("                ");//clear second line: 16 spaces
      lcd.setCursor(0,1); //Second line
      Serial.print("HERE");

    }
    if (counter == len) {
      //update every second
      lcd.print("Click to restart");
    }
    else if (counter == 0) {
      sprintf(str, "Best: %lums", bestTime);
      lcd.print(str);
    }
    //update counter
    counter = (counter + 1)%(len * 2);
   
    delay(1);
  }
}
