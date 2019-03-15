
#include <Wire.h>
#include <EEPROM.h>

#define BUFFER_SIZE 16
#define ledPin 13

//const byte regSize = 210;
//volatile byte i2cRegs[int(regSize)];
volatile byte command = 0;

bool execute = false;
byte NEW_SLAVE_ADDR = 0; 
byte cmd = 0;

byte pHByte[2] = {0, 0};
byte TempByte[2] = {0, 0};

/*
void Blink(byte times){ 
  for (byte i=0; i< times; i++){
    digitalWrite(ledPin,HIGH);
    delay(175);
    digitalWrite(ledPin,LOW);
    delay(175);
  }
  
}*/

void executeCommand() {
  int pHA = 6767;
  int TempA = 6868;
  //int pHA = analogRead(2);
  //int TempA = analogRead(3);

  pHByte[0] = (pHA >> 8) & 0xFF;
  pHByte[1] = (pHA) & 0xFF;
  //delay(50);

  TempByte[0] = (TempA >> 8) & 0xFF;
  TempByte[1] = (TempA) & 0xFF;
 
  /*if(command == 0xCE) {
    EEPROM.put(0, NEW_SLAVE_ADDR);
    delay(1000);
  }*/

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
  //delay(100); 
  command = Wire.read();
  
  executeCommand();

  /*digitalWrite(ledPin, HIGH);   // sets the LED on
  delay(1000);                  // waits for a second
  digitalWrite(ledPin, LOW);    // sets the LED off
  delay(1000);       


  while(numBytes--) {
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
void requestEvent() {
  if(command == 0x67) {
    Wire.write(pHByte[0]);
    //TinyWireS.send(100);
    //TinyWireS.send(200);
    Wire.write(pHByte[1]);
 
  } else if(command == 0x68) {
    Wire.write(TempByte[0]);
    Wire.write(TempByte[1]);
  } else if(command == 0x69) {
    Wire.write(pHByte[0]);
    Wire.write(pHByte[1]);
    Wire.write(TempByte[0]);
    Wire.write(TempByte[1]);
    }
}
  
  /*TinyWireS.send(i2cRegs[regPosition]);
  regPosition++;
  if(regPosition >= regSize) {
    regPosition = 0;
    }

  */
void setup() {
  volatile byte SLAVE_ADDR = 0x14;
  /*SLAVE_ADDR = EEPROM.read(0);
  if(SLAVE_ADDR > 127 || SLAVE_ADDR < 1) {
    SLAVE_ADDR = 100;
  }*/

  Wire.begin(SLAVE_ADDR);

  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);

  pinMode(4, INPUT);
  pinMode(3, INPUT);

  pinMode(ledPin,OUTPUT);

  }

void loop() {
  if(execute) {
    executeCommand();
    execute = false;
    }
  }
