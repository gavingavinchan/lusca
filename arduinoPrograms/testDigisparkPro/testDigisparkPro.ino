#include "TinyWireS.h"                  // wrapper class for I2C slave routines
#include <EEPROM.h>
#define ledPin 1

void setup() {
  pinMode(ledPin,OUTPUT);
  TinyWireS.begin(0x45);      // init I2C Slave mode
  TinyWireS.onReceive(receiveEvent);
}

void receiveEvent(uint8_t howMany)
{
  Blink(2);
}

void loop() {
  // put your main code here, to run repeatedly:
  TinyWireS_stop_check();
}

void Blink(byte times){ 
  for (byte i=0; i< times; i++){
    digitalWrite(ledPin,HIGH);
    tws_delay(175);
    digitalWrite(ledPin,LOW);
    tws_delay(175);
  }
}
