/* Digispark program for controlling electromagnets(EM) independently
 *  
 * followed example from https://github.com/rambo/TinyWire/blob/rollback/TinyWireS/examples/attiny85_i2c_slave_task/attiny85_i2c_slave_task.ino
 * 
 * To turn on Left EM, pin 1
 *    Master send 0x21, then send strength value 0~255 (0=no attraction, 255=max attraction)
 *  
 * To turn on Right EM, pin 3
 *    Master send 0x22, then send strength value 0~255 (0=no attraction, 255=max attraction)
 * 
 * 
 * To blink LED, pin 1
 *    Master send 0x10, then send number of times to blink
 *    
 * To Ping and request voltage on pin 4
 *    Master send 0x99, then read high byte, then read low byte
 *    
 * To change I2C Address    
 *    Master send 0xCE, then send new address 
 *    
 *    
 * Note: the way this code is written does not allow slave to read more than two bytes from master(register and value)
 *       may need i2cRegs[] to be 2D array
 */


#include "TinyWireS.h"                  // wrapper class for I2C slave routines
#include <EEPROM.h>

#define TWI_RX_BUFFER_SIZE 16

#define ledPin 1
#define leftEM 1
#define rightEM 3
#define VDpin 2     //voltage divider pin, P4

const byte regSize = 210;       //0xce = 206 so 210 for some redundace
volatile byte i2cRegs[int(regSize)];
volatile byte regPosition =0;

bool execute = false;



void Blink(byte times){ 
  for (byte i=0; i< times; i++){
    digitalWrite(ledPin,HIGH);
    tws_delay(175);
    digitalWrite(ledPin,LOW);
    tws_delay(175);
  }
}

byte rp =0;
void executeCommand() {
  byte rp = regPosition;
  if(rp == 0x21) {
    analogWrite(leftEM, i2cRegs[rp]);
  } else if(rp == 0x22) {
    analogWrite(rightEM, i2cRegs[rp]);
  } else if(rp == 0x10) {
    Blink(i2cRegs[rp]);
  } else if(rp == 0x99) {
    long raw = analogRead(VDpin);
    i2cRegs[rp] = raw >> 8;             //high byte
    i2cRegs[rp+1] = raw & 0xFF;         //low byte     hahaha low B
  } else if(rp == 0xCE) {
    EEPROM.put(0, i2cRegs[rp]);                //change address value
    Blink(1000);    
    delay(1000);
  }
  /*
  switch(regPosition) {
    case 0x21 : {
      analogWrite(leftEM, i2cRegs[regPosition]);
      break;
    }
    case 0x22 : {
      analogWrite(rightEM, i2cRegs[regPosition]);
      break;
    }
    case 0x10 : {
      Blink(i2cRegs[regPosition]);
    }
    case 0x99: {             //0x99
      //byte raw = analogRead(VDpin);
      byte raw = 985;
      i2cRegs[regPosition] = (raw >> 8) & 0xFF;   //high byte
      i2cRegs[regPosition++] = raw & 0xFF;        //low byte     hahaha low B
      Blink(1);
      break;
    }
    case 0xCE : {
      EEPROM.put(0, i2cRegs[regPosition]);                //change address value
      Blink(1000);    
      delay(1000);
    }
    default: {
      //Blink(1);
      break;
    }
  }
  */
}


void requestEvent() {
  if(regPosition == 0x90) {
    TinyWireS.send(i2cRegs[regPosition]);
    TinyWireS.send(i2cRegs[regPosition+1]);
  } else if(regPosition == 0x99) {
    TinyWireS.send(i2cRegs[regPosition]);
    TinyWireS.send(i2cRegs[regPosition+1]);
  }


  /*
  TinyWireS.send(i2cRegs[regPosition]);
  //TinyWireS.send(regPosition);
  regPosition++;
  if(regPosition >= regSize) {
    regPosition =0;
  }
  */
}



void receiveEvent(byte numBytes) {
  if(numBytes < 1) {
    //no bytes, sanity check
    return;
  }
  if(numBytes > TWI_RX_BUFFER_SIZE) {
    //more bytes than expected
    return;
  }

  execute = true;

  regPosition = TinyWireS.receive();
  numBytes--;

  if(!numBytes) {
    //no bytes left
    return;
  }

  
  int i = regPosition;
  while(numBytes--) {
    i2cRegs[i] = TinyWireS.receive();
    i++;
    
   /*
     * cannot read more than one byte from master, otherwise will need 2d array
    regPosition++;
    if(regPosition >= regSize) {
      regPosition =0;
    }
    */
  }
}



void setup() {
  volatile byte I2C_SLAVE_ADDR = 0;
  I2C_SLAVE_ADDR = EEPROM.read(0);         //get its own slave address from EEPROM
  if(I2C_SLAVE_ADDR > 127 || I2C_SLAVE_ADDR < 1) {
    I2C_SLAVE_ADDR = 100;
  }
  TinyWireS.begin(I2C_SLAVE_ADDR);      // init I2C Slave mode
  
  TinyWireS.onReceive(receiveEvent);
  TinyWireS.onRequest(requestEvent);

  pinMode(leftEM,OUTPUT);
  pinMode(rightEM,OUTPUT);

}


void loop() {
  if(execute) {       //ok
    executeCommand();
    execute = false;
  }
  TinyWireS_stop_check();
}
