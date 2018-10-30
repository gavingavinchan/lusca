/**
 * function: 
 *            1. I2c slave to sent PWM to motor control or turn on/off light with PWM
 *            2. Use EEPROM to rewrite its I2c address
 *            3. simple blink on command to check if it's alive
 * 
 * How to send byte value to turn motor or turn on/off light
 *    1. send 0x00
 *    2. send value, range: ccw 0~255 cw,   127 for stop; approach 0 = ccw; approach 255 = cw
 *    
 * How to write Servo microseconds for channel 1
 *    1. send 0x02
 *    2. send value
 *    
 * How to write Servo microseconds for channel 2
 *    1. send 0x03
 *    2. send value
 *    
 * How to analog write on pin 1, need to DISABLE servoMicros
 *    1. send 0x05
 *    2. send value 0~255
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

#include <SoftSerial.h>
#include <TinyPinChange.h>

/*
The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)
 * 
 */
SoftSerial mySerial(1, 3); // RX, TX

#define ledPin 1

void Blink(byte times){ 
  for (byte i=0; i< times; i++){
    digitalWrite(ledPin,HIGH);
    delay (175);
    digitalWrite(ledPin,LOW);
    delay (175);
  }
}

void setup() {
  // put your setup code here, to run once:
  byte I2C_SLAVE_ADDR = 0;
  I2C_SLAVE_ADDR = EEPROM.read(0);         //get its own slave address from EEPROM
  if(I2C_SLAVE_ADDR > 127 || I2C_SLAVE_ADDR < 1) {
    I2C_SLAVE_ADDR = 127;
  }
  TinyWireS.begin(I2C_SLAVE_ADDR);      // init I2C Slave mode
  //pinMode(3, OUTPUT);
  //digitalWrite(4, LOW);
  pinMode(ledPin, OUTPUT);
  Blink(3); 


  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  //mySerial.write(0xFA);
}

int servoMicrosCh1 = 0;
int servoMicrosCh2 = 0;

void loop() {
  // put your main code here, to run repeatedly:
  if (TinyWireS.available()){           // got I2C input!
    //Blink(3);
    byte byteCommand = TinyWireS.receive();     //get command to turn motor

   
    if(byteCommand == 0x06) {            //serial write from i2c read
        int sound = TinyWireS.receive();
        //Blink(1);
        
        mySerial.write(byte(0x7E));
        mySerial.write(byte(0xFF));
        mySerial.write(byte(0x06));
        mySerial.write(byte(0x03));
        mySerial.write(byte(0x00));
        mySerial.write(byte(0x00));
        mySerial.write(sound);
        int checksum = 0 - (int)(0xFF+0x06+0x03+sound);
        mySerial.write(highByte(checksum));
        mySerial.write(lowByte(checksum));
        mySerial.write(byte(0xEF));

        //delay(2000);

    } else if(byteCommand == 0x07) {            //serial write from i2c read
        
        mySerial.write(byte(0x7E));
        mySerial.write(byte(0xFF));
        mySerial.write(byte(0x06));
        mySerial.write(byte(0x16));
        mySerial.write(byte(0x00));
        mySerial.write(byte(0x00));
        mySerial.write(byte(0x00));
        int checksum = 0 - (int)(0xFF+0x06+0x16);
        mySerial.write(highByte(checksum));
        mySerial.write(lowByte(checksum));
        mySerial.write(byte(0xEF));

        //delay(2000);

    } else if(byteCommand == 0xCE) {            //command to change address
      byte newAddress = TinyWireS.receive();    //new address value
      //Write value
      EEPROM.put(0, newAddress);                //change address value
      //Blink(1000);    
      delay(1000);
      
    } else if(byteCommand == 0x10) {            //blink check to see if alive
      byte times = TinyWireS.receive();         //receive how many times to blink
      //Blink(times);
    }
  }

}


