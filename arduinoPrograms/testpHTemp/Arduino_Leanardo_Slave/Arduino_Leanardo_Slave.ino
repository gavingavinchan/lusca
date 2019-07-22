#include <Wire.h>
#include <EEPROM.h>

#define BUFFER_SIZE 16
#define ledPin 1

//const byte regSize = 210;
//volatile byte i2cRegs[int(regSize)];
volatile byte command = 0;
volatile byte commandADDR = 0;

byte pHByte[2] = {0, 0};
byte TempByte[2] = {0, 0};

void Blink(byte times){ 
  for (byte i=0; i< times; i++){
    digitalWrite(ledPin,HIGH);
    delay(175);
    digitalWrite(ledPin,LOW);
    delay(175);
  }
}

void executeCommand() {
  byte cmd = command;
  if(cmd == 0x67) {
    int pHA = analogRead(A0); //pH read
    // extract the last right 8 digits and  by ANDing 0xFF (binary: 11111111). That way the left 8 bits are cut out
    pHByte[0] = (pHA >> 8) & 0xFF;
    // it is already placed at the far right we don't need to shift anything, just AND with 0xFF.
    pHByte[1] = (pHA) & 0xFF;
    
  } else if (cmd == 0x68) {
    int TempA = analogRead(A5); //Temp Read
    TempByte[0] = (TempA >> 8) & 0xFF;
    TempByte[1] = (TempA) & 0xFF;
    
  } else if (cmd == 0x69) {
    analogRead(A0);
    //delay(2000);
    int pHA = analogRead(A0);
    analogRead(A5);
    //delay(2000);
    int TempA = analogRead(A5);
/*
    Serial.print("A1: ");
    Serial.print(pHA);
    Serial.print("\t");
    Serial.print("A5: ");
    Serial.println(TempA);
*/
    pHByte[0] = (pHA >> 8) & 0xFF;
    pHByte[1] = (pHA) & 0xFF;

    TempByte[0] = (TempA >> 8) & 0xFF;
    TempByte[1] = (TempA) & 0xFF;
  } else if(cmd == 0xCE) {
    EEPROM.put(0, commandADDR);
    delay(1000);
    Blink(1000);
  }

}

void receiveEvent(byte numBytes) {
  if(numBytes < 1) {
    //sanity check
    return;
    }

  if(numBytes > BUFFER_SIZE) {
    //more bytes than expected 
    return;
    }
  command = Wire.read();

  numBytes--;
  
  while(numBytes--) {
    commandADDR = Wire.read();
  }

  executeCommand();
  


 /* while(numBytes--) {
    if(command == 0x67) {
    pHByte[2] = {0, 0};
  } else if(command == 0x68) {
    TempByte[2] = {0, 0};
  } else if(command == 0x69) {
    pHByte[2] = {0, 0};
    TempByte[2] = {0, 0};
  } else if(command == 0xCE) {
    NEW_SLAVE_ADDR = TinyWireS.receive();
    }
 */
}
  /*numBytes--;
  if(!numBytes) {
    //no bytes left
    return;
    }
  while(numBytes--) {
    i2cRegs[regPosition] = TinyWireS.receive();
}
*/

void requestEvent() {
  if(command == 0x67) {
    Wire.write(pHByte[0]);
    Wire.write(pHByte[1]);
  } else if(command == 0x68) {
    Wire.write(TempByte[0]);
    Wire.write(TempByte[1]);
  } else if(command == 0x69) {
    Blink(10);
    Wire.write(pHByte[0]);
    Wire.write(pHByte[1]);
    Wire.write(TempByte[0]);
    Wire.write(TempByte[1]);
  } else {
    Wire.write(commandADDR);
  }
}
  
  /*TinyWireS.send(i2cRegs[regPosition]);
  regPosition++;
  if(regPosition >= regSize) {
    regPosition = 0;
    }

  */
void setup() {
  volatile byte SLAVE_ADDR = 0;
  SLAVE_ADDR = EEPROM.read(0);
  if(SLAVE_ADDR > 127 || SLAVE_ADDR < 1) {
    SLAVE_ADDR = 100;
  }

  Wire.begin(0x64);

  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);

  pinMode(4, INPUT);
  pinMode(3, INPUT);

  pinMode(ledPin,OUTPUT);

  Serial.begin(9600);
  }

void loop() {
  }











  
