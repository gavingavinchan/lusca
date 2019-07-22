#include <EEPROM.h>
#include <TinyWireS.h>

#define channelA_D 3
#define channelA_A 1
#define channelB_D 5
#define channelB_A 4


//const byte regSize = 210;
//volatile byte i2cRegs[int(regSize)];
volatile byte command = 0;
volatile byte commandADDR = 0;
volatile byte echoLow = 0;
volatile byte echoHigh = 0;

void Blink(byte times){ 
  for (byte i=0; i< times; i++){
    digitalWrite(1,HIGH);
    delay(250);
    digitalWrite(1,LOW);
    delay(250);
  }
}

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
  //digitalWrite(1,HIGH);
  if(command == 0x21) {
    //digitalWrite(1,LOW);
    EMon(true, commandADDR);
  } else if(command == 0x22) {
    EMon(false, commandADDR);
  }
  if(command == 0xCE) {
    EEPROM.put(0, commandADDR);
    // delay(1000);
    // Blink(100);
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
    if(command == 0x90){
      if (numBytes > 0) {
        echoHigh = TinyWireS.receive();
      }else{
        echoLow = TinyWireS.receive();
      }
    } else {
      commandADDR = TinyWireS.receive();
    }
  }
  
  executeCommand();
}

void requestEvent() {
  if (command == 0x90){
    TinyWireS.send(echoHigh);
    TinyWireS.send(echoLow);
  }else
    TinyWireS.send(commandADDR);
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

  pinMode(channelA_D,OUTPUT);
  pinMode(channelA_A,OUTPUT);
  pinMode(channelB_D,OUTPUT);
  pinMode(channelB_A,OUTPUT);

  delay(1000);
}

void loop() {

}











  
