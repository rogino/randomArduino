2 #include <math.h>

const int hBridgeUL = 6;
const int hBridgeUR = 7;
const int hBridgeDL = 8;
const int hBridgeDR = 9;

const int speedCtrlPin = 10; //To control the Vin as it is probably bad to use analogWrite with the H Bridge as a and b might be on at the same time

const int potPin = 11; //Linear potentiometer/slide pot. AnalogRead
const int switchPin = 12; //Switch which determines direction

const int refreshRate = 25;//Run loop every x milliseconds
const int arrLength = 10; //Number of elements to store
int arrInput[arrLength]; //Array to store previous arrLength elements to smooth user input

int getAverage(int *arr) {
    int result = 0;
    for (int i = 0; i < arrLength; i++) {
        result += arr[i]; //Adds up value of array
    }
    return (int) floor((double) result / arrLength); //Get result of division as double, round, cast to int
    
}

int shiftArr(int *arr, int newVal) {
    //Shifts value of arr. e.g. {0,1,2,3,4,5,6,7,8,9} ---> {1,2,3,4,5,6,7,8,9,10}
    for (int i = 1; i < arrLength; i++) {
        arr[i-1] = arr[i]; //Makes the element before equal the current element
    }
    arr[arrLength] = newVal; //Then overwrite the last element with newVal
}

void motorSpeed(bool direction, int speed) {
    analogWrite(speedCtrlPin, speed); //Sets amount of time the motor should recieve power. H Bridge continually on
    if (direction) {
        //One direction
        //Turn off first so there is no short curcuit
        digitalWrite(hBridgeUR, LOW);
        digitalWrite(hBridgeDL, LOW);
        digitalWrite(hBridgeDL, HIGH);
        digitalWrite(hBridgeUR, HIGH);
    }
    else {
        digitalWrite(hBridgeDR, LOW);
        digitalWrite(hBridgeUL, LOW);
        digitalWrite(hBridgeUR, HIGH);
        digitalWrite(hBridgeDL, HIGH);
    }    
}


void setup() {
    pinMode(hBridgeUL, OUTPUT);
    pinMode(hBridgeUR, OUTPUT);
    pinMode(hBridgeDL, OUTPUT);
    pinMode(hBridgeDR, OUTPUT);
    pinMode(speedCtrlPin, OUTPUT);
    pinMode(switchPin, INPUT);
    Serial.begin(9600);
    memset(arrInput, 0, sizeof(arrInput)/sizeof(int)); //Sets all elements of array to 0
}

void loop() {
    shiftArr(arrInput, analogRead(potPin)); //Read input
    int speed = map(getAverage(arrInput), 0, 1023, 0, 255); //Map values from potentiometer to between 0 and 255
    motorSpeed(speed, digitalRead(switchPin));
    delay(refreshRate);
}
