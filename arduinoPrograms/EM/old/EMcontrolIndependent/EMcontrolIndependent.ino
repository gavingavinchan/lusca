#include <EEPROM.h>
#include <TinyWireS.h>

#define BUFFER_SIZE 16
#define ledPin 1

#define channelA_D 3
#define channelA_A 1
#define channelB_D 5
#define channelB_A 4

//const byte regSize = 210;
//volatile byte i2cRegs[int(regSize)];
volatile byte command = 0;
volatile byte commandADDR = 0;


void EMon(bool _channel, int _value){
  int valueOnOrigin = (_value-127)*2;
  if(valueOnOrigin>255) {valueOnOrigin = 255;}
  if(_channel) {
    if(valueOnOrigin>0) {
     digitalWrite(channelA_D, HIGH);
     analogWrite(channelA_A, 255-valueOnOrigin);
    } else {
     digitalWrite(channelA_D, LOW);
     analogWrite(channelA_A, -valueOnOrigin);
    }
  } else {
    if(valueOnOrigin>0) {
     digitalWrite(channelB_D, HIGH);
     analogWrite(channelB_A, 255-valueOnOrigin);
    } else {
     digitalWrite(channelB_D, LOW);
     analogWrite(channelB_A, -valueOnOrigin);
    }
  }
}


void executeCommand() {
  if(command == 0x21) {
    EMon(true, 255);
  } else if(command == 0xCE) {
    EEPROM.put(0, commandADDR);
    TinyWireS.send(commandADDR);
  }
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
  //analogWrite(1, 255);
  executeCommand();
}

void requestEvent() {}

void setup() {
  volatile byte SLAVE_ADDR = 0;
  SLAVE_ADDR = EEPROM.read(0);
  if(SLAVE_ADDR > 127 || SLAVE_ADDR < 1) {
    SLAVE_ADDR = 100;
  }

  TinyWireS.begin(SLAVE_ADDR);

  TinyWireS.onReceive(receiveEvent);
  TinyWireS.onRequest(requestEvent);

  pinMode(channelA_D,OUTPUT);
  pinMode(channelA_A,OUTPUT);
  pinMode(channelB_D,OUTPUT);
  pinMode(channelB_A,OUTPUT);

  analogWrite(1, 255);
}

void loop() {

}
