/**
 * function: 
 *            1. I2c slave to sent PWM to motor control or turn on/off light with PWM
 *            2. Use EEPROM to rewrite its I2c address
 *            3. simple blink on command to check if it's alive
 * 
 * How to write Servo microseconds for channel 1
 *    1. send 0x02
 *    2. send value
 *    
 * How to write Servo microseconds for channel 2
 *    1. send 0x03
 *    2. send value
 *    
 * How to change address
 *    1. send 0xCE
 *    2. send new address, like 0x06
 *    
 * How to use check alive
 *    1. send 0x10
 *    2. send how many times to blink
 */

#include "TinyWireS.h"                  // wrapper class for I2C slave routines
#include <EEPROM.h>



#define ledPin 1

#define CH1pin 1      //cannot be 0
#define CH2pin 3      //cannot be 0
#define CH3pin 4      //cannot be 0
#define CH4pin 5      //to use this pin, need to set the reset settings of chinese clone digispark

#define numOfCH 4
int ArrMicros[numOfCH] = {1500,1500,1500,1500};
int ArrCHpin[numOfCH] = {CH1pin,CH2pin,CH3pin,CH4pin};
unsigned long startOfInterval = 0;
int arrIndex = 0; 



void setup() {
  // put your setup code here, to run once:
  byte I2C_SLAVE_ADDR = 0;
  I2C_SLAVE_ADDR = EEPROM.read(0);         //get its own slave address from EEPROM
  if(I2C_SLAVE_ADDR > 127 || I2C_SLAVE_ADDR < 1) {
    I2C_SLAVE_ADDR = 127;
  }

  TinyWireS.begin(I2C_SLAVE_ADDR);      // init I2C Slave mode

  pinMode(ledPin, OUTPUT);
  pinMode(CH2pin, OUTPUT);
  pinMode(CH3pin, OUTPUT);
  pinMode(CH4pin, OUTPUT);
  
  Blink(2); 
}



void loop() {
  // put your main code here, to run repeatedly:
  if (TinyWireS.available()){           // got I2C input!
    //Blink(3);
    byte byteCommand = TinyWireS.receive();     //get command to turn motor
    
    if(byteCommand == 0x11) {            //command set value to write Servo microseconds
      int _micros = 0;
      _micros = TinyWireS.receive() << 8;
      _micros += TinyWireS.receive();      
      arrInsert(_micros, CH1pin);
    
    } else if(byteCommand == 0x12) {
      int _micros = 0;
      _micros = TinyWireS.receive() << 8;
      _micros += TinyWireS.receive();      
      arrInsert(_micros, CH2pin);

    } else if(byteCommand == 0x13) {
      int _micros = 0;
      _micros = TinyWireS.receive() << 8;
      _micros += TinyWireS.receive();      
      arrInsert(_micros, CH3pin);

    } else if(byteCommand == 0x14) {
      int _micros = 0;
      _micros = TinyWireS.receive() << 8;
      _micros += TinyWireS.receive();      
      arrInsert(_micros, CH4pin);
        
      
    } else if(byteCommand == 0xCE) {            //command to change address
      byte newAddress = TinyWireS.receive();    //new address value
      //Write value
      EEPROM.put(0, newAddress);                //change address value
      Blink(1000);    
      delay(1000);
      
    } else if(byteCommand == 0x10) {            //blink check to see if alive
      byte times = TinyWireS.receive();         //receive how many times to blink
      Blink(times);
    }
  }

 

  
/*
  //write Servo microseconds
  digitalWrite(servoPinCh1, HIGH);
  digitalWrite(servoPinCh2, HIGH);
  if(servoMicrosCh1 > servoMicrosCh2) {
    delayMicroseconds(servoMicrosCh2);
    digitalWrite(servoPinCh2, LOW);
    delayMicroseconds(servoMicrosCh1 - servoMicrosCh2);
    digitalWrite(servoPinCh1, LOW);
  } else {
    delayMicroseconds(servoMicrosCh1);
    digitalWrite(servoPinCh1, LOW);
    delayMicroseconds(servoMicrosCh2 - servoMicrosCh1);
    digitalWrite(servoPinCh2, LOW);
  }
  delayMicroseconds(20000 - servoMicrosCh1 - servoMicrosCh2);
  */

  const long interval = 20000;

  if((micros()-startOfInterval) >= interval) {
    for(int i=0; i<numOfCH; i++) {
      digitalWrite(ArrCHpin[i], HIGH);
    }
    startOfInterval = micros();

    delayMicroseconds(ArrMicros[0]);
    digitalWrite(ArrCHpin[0], LOW);
   
    delayMicroseconds(ArrMicros[1] - ArrMicros[0]);
    digitalWrite(ArrCHpin[1], LOW);

    delayMicroseconds(ArrMicros[2] - ArrMicros[1]);
    digitalWrite(ArrCHpin[2], LOW);

    delayMicroseconds(ArrMicros[3] - ArrMicros[2]);
    digitalWrite(ArrCHpin[3], LOW);
  }
}


void arrInsert(int micros, int CHpin) {
   for(int i=0;i<numOfCH;i++) {                     //replace old micros with new micros
    if(ArrCHpin[i] == CHpin || ArrCHpin[i] == 0) {
      ArrMicros[i] = micros;
    }
  }
  dualBubbleSort(ArrMicros, numOfCH, ArrCHpin);
}

void dualBubbleSort(int arBased[], int arBasedLength, int ar2[]) {        //sorting base on arBased, ar2 will be arranged how the arBased is arranged
  for (int i = (arBasedLength - 1); i >= 0; i--) {
    for (int j = 1; j <= i; j++) {
      if (arBased[j-1] > arBased[j]) {
        int temp1 = arBased[j-1];
        arBased[j-1] = arBased[j];
        arBased[j] = temp1;

        int temp2 = ar2[j-1];
        ar2[j-1] = ar2[j];
        ar2[j] = temp2;
      } 
    } 
  } 
}

void Blink(byte times){ 
  for (byte i=0; i< times; i++){
    digitalWrite(ledPin,HIGH);
    delay (175);
    digitalWrite(ledPin,LOW);
    delay (175);
  }
}
