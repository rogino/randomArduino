int x,y;
int xPin = 0;
int yPin = 1;

int rPin = 7;
int gPin = 12;
int bPin = 3;
bool direction = 1;
int counter = 0;
void setup() {
    pinMode(rPin,OUTPUT);
    pinMode(gPin,OUTPUT);
    pinMode(bPin,OUTPUT);
    
}

void loop() {
    if (counter < 0 || counter > 255) {
        direction = !direction;
    }
    x = map(analogRead(xPin),0,1023,0,255);
    y = map(analogRead(yPin),0,1023,0,255);
    
    setLED(x,y,counter);
    if(direction) {
        counter++;
    }
    else {
        counter--;
    }
    delay(10);
}


void setLED(int r, int g, int b) {
  analogWrite(rPin, r);
  analogWrite(gPin, g);
  analogWrite(bPin, b);
}

