#include <Wire.h>

#include <EEPROM.h>

#define TWI_RX_BUFFER_SIZE 16

#define ledPin 1
#define leftEM 1
#define rightEM 3
#define VDpin 4     //voltage divider pin

const byte regSize = 210;       //0xce = 206 so 210 for some redundace
volatile byte i2cRegs[int(regSize)];
volatile byte regPosition =0;

bool execute = false;


byte rp =0;
void executeCommand() {
  byte rp = regPosition;
  //rp = regPosition;
  //Blink(1);
  //tws_delay(2000);
  Serial.println("executeCommand");
  Serial.print("regPosition: ");
  Serial.println(regPosition);
  if(regPosition == 0x21) {
    analogWrite(leftEM, i2cRegs[regPosition]);
    Serial.print("0x21 in: ");
    Serial.println(i2cRegs[regPosition]);
  } else if(rp == 0x22) {
    analogWrite(rightEM, i2cRegs[regPosition]);
  } else if(rp == 0x10) {
    //Blink(i2cRegs[regPosition]);
  } else if(regPosition == 0x99) {
    //byte raw = analogRead(VDpin);
    //Blink(1);
    long raw = 985;
    i2cRegs[regPosition] = raw >> 8;   //high byte
    i2cRegs[regPosition+1] = raw & 0xFF;        //low byte     hahaha low B
    Serial.println("in 0x99");
    Serial.println(regPosition);
    Serial.println(i2cRegs[regPosition]);
    Serial.println(i2cRegs[regPosition+1]);
  } else if(rp == 0xCE) {
    EEPROM.put(0, i2cRegs[regPosition]);                //change address value
    //Blink(1000);    
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
  //TinyWireS.send(i2cRegs[regPosition]);
  //TinyWireS.send(regPosition);
  regPosition++;
  if(regPosition >= regSize) {
    regPosition =0;
  }
}



void receiveEvent(byte numBytes) {
  //Serial.println("recieved");
  if(numBytes < 1) {
    //no bytes, sanity check
    return;
  }
  if(numBytes > TWI_RX_BUFFER_SIZE) {
    //more bytes than expected
    return;
  }

  execute = true;


  regPosition = Wire.read();
  //Serial.println(regPosition);
  numBytes--;

  if(!numBytes) {
    //no bytes left
    return;
  }

  while(numBytes--) {
    i2cRegs[regPosition] = Wire.read();
    
    regPosition++;
    if(regPosition >= regSize) {
      regPosition =0;
    }
  }
}



void setup() {
  volatile byte I2C_SLAVE_ADDR = 0x15;

  Wire.begin(I2C_SLAVE_ADDR);      // init I2C Slave mode
  Serial.begin(57600);
  Serial.println("start");
  
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);

  pinMode(leftEM,OUTPUT);
  pinMode(rightEM,OUTPUT);

}


void loop() {
  if(execute) {       //ok
    executeCommand();
    execute = false;
    Serial.println("execute");
  }
  //TinyWireS_stop_check();
}
