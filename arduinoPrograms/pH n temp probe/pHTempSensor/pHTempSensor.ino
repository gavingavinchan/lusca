#include <EEPROM.h>
#include <TinyWireS.h>

#define BUFFER_SIZE 16

//const byte regSize = 210;
//volatile byte i2cRegs[int(regSize)];
volatile byte command = 0;

bool execute = false;

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
  }

byte cmd = 0;
byte pHByte[2] = {0, 0};
byte TempByte[2] = {0, 0};
void executeCommand() {
  byte cmd = command;
  if(cmd == 0x67) {
    int pHA = analogRead(2); //pH read
    // extract the last right 8 digits and  by ANDing 0xFF (binary: 11111111). That way the left 8 bits are cut out
    pHByte[0] = (pHA >> 8) & 0xFF;
    // it is already placed at the far right we don't need to shift anything, just AND with 0xFF.
    pHByte[1] = (pHA) & 0xFF;
    
  } else if (cmd == 0x68) {
    int TempA = analogRead(3); //Temp Read
    TempByte[0] = (TempA >> 8) & 0xFF;
    TempByte[1] = (TempA) & 0xFF;
    
  } else if (cmd == 0x69) {
    int pHA = analogRead(2);
    int TempA = analogRead(3);

    pHByte[0] = (pHA >> 8) & 0xFF;
    pHByte[1] = (pHA) & 0xFF;

    TempByte[0] = (TempA >> 8) & 0xFF;
    TempByte[1] = (TempA) & 0xFF;
  } else if(cmd == 0xCE) {
    EEPROM.put(0, NEW_SLAVE_ADDR);
    delay(1000);
    }
}

void loop() {
  if(execute) {
    executeCommand();
    execute = false;
    TinyWireS_stop_check();
    }
  }
NEW_SLAVE_ADDR = 0; 
void receiveEvent(byte numBytes) {
  if(numBytes < 1) {
    //sanity check
    return;
    }

  if(numBytes > BUFFER_SIZE) {
    //more bytes than expected 
    return;
    }

  execute = true;

  command = TinyWireS.receive();

  if(command == 0x67) {
    byte pHByte[2] = {0, 0};
  } else if(command == 0x68) {
    byte TempByte[2] = {0, 0};
  } else if(command == 0x69) {
    byte pHByte[2] = {0, 0};
    byte TempByte[2] = {0, 0};
  } else if(command == 0xCE) {
    NEW_SLAVE_ADDR = TinyWireS.receive();
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
}

void requestEvent() {
  if(command == 0x67) {
    TinyWireS.send(pHByte[0]);
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
}
  
  /*TinyWireS.send(i2cRegs[regPosition]);
  regPosition++;
  if(regPosition >= regSize) {
    regPosition = 0;
    }

  */
  }











  
