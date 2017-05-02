const int RLED = 13;
const int GLED = 12;
const int BLED = 11;

void setup() { 
pinMode(RLED,OUTPUT);
pinMode(GLED,OUTPUT);
pinMode(BLED,OUTPUT);
  
}

void loop() { 
  for (int i = 0; i < 360; i++) {
    setHue(i);
    delay(10);
  }
}

int hueHelper(int t) {
 // return t/60 * 255;
  return map(t,0, 60,0,255); //Changes 0-60 range to 0-255
}

void setHue(int hue) {
  //0-360
  hue = hue%360;
  int temp;
  if (hue < 60) {
    temp = hueHelper(hue);
    setLED(255,temp,0);
  }
  else if (hue < 120){
    temp = hue-60;
    temp = 255 - hueHelper(temp);
    setLED(temp,255,0);
  }
  else if (hue < 180) {
    temp = hue - 120;
    temp = hueHelper(temp);
    setLED(0,255,temp);
  }
  else if (hue < 240) {
    temp = hue - 180;
    temp = 255 - hueHelper(temp);
    setLED(0,temp,255);
  }
  else if (hue < 300) {
    temp = hue - 240;
    temp = hueHelper(temp);
    setLED(temp,0,255);
  }
  else {
    temp = hue - 300;
    temp = 255 - hueHelper(temp);
    setLED(255,0,temp);
  }
}


void setLED(int r, int g, int b) {
  analogWrite(RLED, r);
  analogWrite(GLED, g);
  analogWrite(BLED, b);
}

