#include "TinyWireS.h"                  // wrapper class for I2C slave routines
#include <EEPROM.h>
#define ledPin 1

void setup() {
  byte I2C_SLAVE_ADDR = 0;
  I2C_SLAVE_ADDR = EEPROM.read(0);         //get its own slave address from EEPROM
  if(I2C_SLAVE_ADDR > 127 || I2C_SLAVE_ADDR < 1) {
    I2C_SLAVE_ADDR = 127;
  }
  TinyWireS.begin(I2C_SLAVE_ADDR);      // init I2C Slave mode
  pinMode(ledPin, OUTPUT);
  Blink(2); 
}

int voltage = 0;
void loop() {
  // put your main code here, to run repeatedly:
  if (TinyWireS.available()){           // got I2C input!
    byte byteCommand = TinyWireS.receive();     //get command to turn motor
    if(byteCommand == 0x99) {            //analog write from i2c read
      voltage = analogRead(3);
      // voltage = 1023;
      TinyWireS.send( (byte)((voltage & 0xff00)>>8) );
      TinyWireS.send((byte)(voltage & 0xff));
      //TinyWireS.send( 0x78 );
      //TinyWireS.send (0x23);
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
