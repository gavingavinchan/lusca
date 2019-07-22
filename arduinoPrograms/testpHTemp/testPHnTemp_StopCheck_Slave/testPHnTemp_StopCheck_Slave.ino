#include <Wire.h>
#define SLAVE_ADDR 0x14

byte pHByte[2] = {0, 0};
byte TempByte[2] = {0, 0};

/*
void executeCommand() {
  int pHA = 400;
  int TempA = 656;
  //int pHA = analogRead(2);  //pin4
  //int TempA = analogRead(3); //pin3

  pHByte[0] = (pHA >> 8) & 0xFF;
  pHByte[1] = (pHA) & 0xFF;

  TempByte[0] = (TempA >> 8) & 0xFF;
  TempByte[1] = (TempA) & 0xFF;
  }

void receiveEvent(byte numBytes) {
  if(numBytes < 1) {
    //sanity check
    return;
  }

  command = Wire.receive();
  numBytes--;
  
  while(numBytes--) {
    commandADDR = Wire.receive();
  }
  
  executeCommand();
}
*/

void requestEvent() {
  int pHA = 400;
  int TempA = 656;

  pHByte[0] = (pHA >> 8) & 0xFF;
  pHByte[1] = (pHA) & 0xFF;

  TempByte[0] = (TempA >> 8) & 0xFF;
  TempByte[1] = (TempA) & 0xFF;
  
  Wire.write(pHByte[0]);
  Wire.write(pHByte[1]);
  Wire.write(TempByte[0]);
  Wire.write(TempByte[1]);
}

void setup() {
  Wire.begin(SLAVE_ADDR);

  Wire.onRequest(requestEvent);

}

void loop() {
}
