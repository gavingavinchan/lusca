/**
 * function: 
 *            1. I2c slave to sent PWM to motor control or turn on/off light with PWM
 *            2. Use EEPROM to rewrite its I2c address
 *            3. simple blink on command to check if it's alive
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

#define ledPin 1
#define BIGLED 1

void setup() {
  // put your setup code here, to run once:
  byte I2C_SLAVE_ADDR = 0;
  I2C_SLAVE_ADDR = EEPROM.read(0);         //get its own slave address from EEPROM
  if(I2C_SLAVE_ADDR > 127 || I2C_SLAVE_ADDR < 1) {
    I2C_SLAVE_ADDR = 127;
  }
  TinyWireS.begin(I2C_SLAVE_ADDR);      // init I2C Slave mode
  Blink(2); 
  pinMode(ledPin, OUTPUT);
}


void loop() {
  // put your main code here, to run repeatedly:
  if (TinyWireS.available()){           // got I2C input!
    byte byteCommand = TinyWireS.receive();     //get command to turn motor
    if(byteCommand == 0x05) {            //analog write from i2c read
      analogWrite(BIGLED, TinyWireS.receive());

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
}

void Blink(byte times){ 
  for (byte i=0; i< times; i++){
    digitalWrite(ledPin,HIGH);
    delay (175);
    digitalWrite(ledPin,LOW);
    delay (175);
  }
}

byte mapPower(byte value) {           //map power from byte form with a range of 0~255 to PWM form 255~0~255
  return 2*abs((int)value-127);
}


