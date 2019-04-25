#include <EEPROM.h>
#include <TinyWireS.h>

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
    delay(250);
    digitalWrite(ledPin,LOW);
    delay(250);
  }
}

void executeCommand() {
  if(command == 0xCE) {
    EEPROM.put(0, commandADDR);
    // delay(1000);
    Blink(100);
    TinyWireS.send(commandADDR);
  }

  //int pHA = 6767;
  //int TempA = 6868;
  int pHA = analogRead(2);  //pin4
  int TempA = analogRead(3); //pin3

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

  command = TinyWireS.receive();
  numBytes--;
  
  while(numBytes--) {
    commandADDR = TinyWireS.receive();
  }
  
  executeCommand();
}

void requestEvent() {
  if(command == 0x67) {
    TinyWireS.send(pHByte[0]);
    //TinyWireS.send(100);
    //TinyWireS.send(200);
    TinyWireS.send(pHByte[1]);
  } else if(command == 0x68) {
    TinyWireS.send(TempByte[0]);
    TinyWireS.send(TempByte[1]);
  } else if(command == 0x69) {
    TinyWireS.send(pHByte[0]);
    TinyWireS.send(pHByte[1]);
    TinyWireS.send(TempByte[0]);
    TinyWireS.send(TempByte[1]);
    }
    else{
      //TinyWireS.send(command);
      //TinyWireS.send(commandADDR);
    }
}

void setup() {
  volatile byte SLAVE_ADDR = 0;
  SLAVE_ADDR = EEPROM.read(0);
  if(SLAVE_ADDR > 127 || SLAVE_ADDR < 1) {
    SLAVE_ADDR = 100;
  }

  TinyWireS.begin(SLAVE_ADDR);

  TinyWireS.onReceive(receiveEvent);
  TinyWireS.onRequest(requestEvent);

  pinMode(4, INPUT);
  pinMode(3, INPUT);

  pinMode(ledPin,OUTPUT);
  Blink(2);
  }

void loop() {

}











  
