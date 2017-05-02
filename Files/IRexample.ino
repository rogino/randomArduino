
#include <IRLibAll.h>


int LED1 = 7;
int LED2 = 12;
IRrecv My_Receiver(2); //Reciever object. Argument is port number
IRdecode My_Decoder;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //Begin serial input at 9600 bits per second (baud)
  My_Receiver.enableIRIn(); //Starts the reciever: probably due to it requiring resources
  pinMode(LED1,OUTPUT); //Makes LED1 act as OUTPUT not INPUT pin
  pinMode(LED2, OUTPUT);
  flash(2,100, LED1); //Notify success
}

int flash(int flashes,int snooze, int port)
{
//  Serial.write("flashes ");
//  Serial.print(flashes);
//  Serial.write("/n");
  
  for (int i=0;i<flashes;i++){
    
    digitalWrite(port, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(snooze);
    digitalWrite(port, LOW);
    delay(snooze);
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  if(My_Receiver.getResults()){
    My_Decoder.decode(); //Decodes the input data
    //My_Decoder.dumpResults(true);
//    Serial.write("value ");
//    Serial.print(My_Decoder.value,HEX);
//    Serial.write("/n");
    int length = 150;
    int num = 0; //Default
    switch(My_Decoder.value) {
      case 0xFF6897:
        num = 0; //0: use second LED
        break;
        
      case 0xFF30CF:  
        num = 1;
        break;  
      case 0xFF18E7:  
        num = 2; 
        break; 
      case 0xFF7A85:  
        num = 3; 
        break;
      case 0xFF10EF:  
        num = 4;
        break;  
      case 0xFF38C7:  
        num = 5; 
        break;
      case 0xFF5AA5:  
        num = 6; 
        break; 
      case 0xFF42BD:  
        num = 7;
        break;
      case 0xFF4AB5:  
        num = 8; 
        break;
      case 0xFF52AD:  
        num = 9;
        break;
    }

    if (num%2) {
      flash(num,length,LED1);
    }
    else {
      flash(num,length,LED2);
    }

  
    //Serial.print(My_Decoder.value);
//    if(My_Decoder.value == 0xFF30CF) flash(1,500);
//    if(My_Decoder.value == 0xFF18E7) flash(2,500);
//    if(My_Decoder.value == 0xFF7A85) flash(3,100);
//    if(My_Decoder.value == 0xFF10EF) flash(4,100);
    delay(500);
    My_Receiver.enableIRIn(); //Resume IR reciever
  }
}


/*
Hexadecimal codes
0xFFA25D: CH-
0xFF629D: CH
0xFFE21D: CH+
0xFF22DD: PREV
0xFF02FD: NEXT
0xFFC23D: PLAY/PAUSE
0xFFE01F: VOL-
0xFFA857: VOL+
0xFF906F: EQ
0xFF6897: 0
0xFF9867: 100+
0xFFB04F: 200+
0xFF30CF: 1
0xFF18E7: 2
0xFF7A85: 3
0xFF10EF: 4
0xFF38C7: 5
0xFF5AA5: 6
0xFF42BD: 7
0xFF4AB5: 8
0xFF52AD: 9
 */
