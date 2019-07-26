#include <Wire.h>
#include <EEPROM.h>

#define BUFFER_SIZE 16
#define ledPin 13
#define TEMP_PIN A2
#define PH_PIN A1

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
  if(command == 0xCE) {
    EEPROM.put(0, commandADDR);
    Blink(100);
  } else {
    int pHA = analogRead(PH_PIN);
    int TempA = analogRead(TEMP_PIN);
  
    pHByte[0] = (pHA >> 8) & 0xFF;
    pHByte[1] = (pHA) & 0xFF;
  
    TempByte[0] = (TempA >> 8) & 0xFF;
    TempByte[1] = (TempA) & 0xFF;
  }
}

void receiveEvent(byte numBytes) {
  if(numBytes < 1) {
    //sanity check
    return;
    }
  
  command = Wire.read();

  while(Wire.available()) {
    commandADDR = Wire.read();
  }

  executeCommand();
}

void requestEvent() {
  if(command == 0x67) {
    Wire.write(pHByte[0]);
    Wire.write(pHByte[1]);
  } else if(command == 0x68) {
    Wire.write(TempByte[0]);
    Wire.write(TempByte[1]);
  } else if(command == 0x69) {
    Wire.write(pHByte[0]);
    
    Wire.write(pHByte[1]);
    Wire.write(TempByte[0]);
    Wire.write(TempByte[1]);
  } else {
    //Wire.write(commandADDR);
  }
}
  
void setup() {
  volatile byte SLAVE_ADDR = 0;
  SLAVE_ADDR = EEPROM.read(0);
  if(SLAVE_ADDR > 127 || SLAVE_ADDR < 1) {
    SLAVE_ADDR = 0x31;
  }

  Wire.begin(SLAVE_ADDR);
  
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);

  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin, HIGH);
}

void loop() {
}











  
