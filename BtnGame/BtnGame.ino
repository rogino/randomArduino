#include <LiquidCrystal_I2C.h>
#include <limits.h>


const int btnPin = 12;
//Button connected to ground, 5v and 4k7 resistor. LCD connected to 20, 21 (SCL, SDA), 5v and gnd

unsigned long startTime = 0; //The time in which the measurement starts
unsigned long bestTime = ULONG_MAX; //The shortest time. initialized to be biggest so that anything (should) be smaller
char str[16]; //Enough characters to fit on one line


LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

unsigned long waitForBtn() {
  while (digitalRead(btnPin) == LOW) {
    delay(1); //read every millisecond
  }
  unsigned long value = millis() - startTime;
  //Find difference
  lcd.clear();
  sprintf(str, "Time: %lums", value);
  lcd.print(str);
  //sprintf to have variable
  if (value < bestTime) {
    //Change best time if required
    bestTime = value;
  }
  return value;
}



void setup() {
  pinMode(btnPin, INPUT); //pin mode
  Serial.begin(9600); //Used to type in characters
  lcd.begin(16,2); //initialize the lcd for 16 chars 2 lines, turn on backlight
  lcd.backlight();
  lcd.print("Click to begin"); //Initial text
  while (digitalRead(btnPin) == LOW) {
    //Keep inside setup and show text until button is pressed
    delay(1);
  }
}


void loop() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Three");
  delay(1000);
  lcd.setCursor(0,0);
  lcd.print("Two  "); //Spaces so there is no need for a lcd.clear()
  delay(1000);
  lcd.setCursor(0,0);
  lcd.print("One   ");
  lcd.setCursor(0,0);

  int waitTime = random(50, 3000);
  unsigned long waitStart = millis();
  bool cheated = false;
  while (millis() - waitStart <  waitTime) {
    if (digitalRead(btnPin) == HIGH) {
      //Stop people from pressing from the start
      lcd.clear();
      lcd.print("Too early"); //On first line.
      cheated = true;
      delay(500); //Show text for 500 milliseconds
      break; //Exit loop
    }
    delay(1);
  }
  //delay(random(50, 3000)); //Between 0.05 and 3 seconds
  unsigned long result = 0;
  if (!cheated) {
    lcd.print("BANG!");
    startTime = millis(); //start the time. Here instead of in function to increase accuracy
    unsigned long result = waitForBtn();
    //Get time
  }
  delay(200); //wait 0.2s. Removing this is really bad for some reason

  int counter = 0; //Counter for while(true) loop
  int len = 900; //Length of time for text to be flashing between two states
  lcd.setCursor(0,1); //Set to go to second line/row
  while (digitalRead(btnPin) == LOW) {
    //Once button is pressed, restart
    if (counter % len == 0) {
      //If counter is either 0 or len, it will update text. In these cases, clear the line
      lcd.setCursor(0,1);
      lcd.print("                ");//clear second line: 16 spaces
      lcd.setCursor(0,1); //Move cursor to second line
    }

    if (counter == len) {
      //Second line switches between two values. Update when equals
      lcd.print("Click to restart");
    }
    else if (counter == 0) {
      //Update counter when modulus is 0
      sprintf(str, "Best: %lums", bestTime);
      lcd.print(str); //Best time
    }
    
    //update counter
    counter = (counter + 1)%(len * 2);
    delay(1);
  }
}
