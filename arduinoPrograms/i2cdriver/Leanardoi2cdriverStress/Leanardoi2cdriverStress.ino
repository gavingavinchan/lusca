#include <Wire.h>


byte command = 0;

void receiveEvent() {
  command = Wire.read();
  }

  
void requestEvent() {
  Wire.write(command);
}

void setup() {
  // put your setup code here, to run once:
  Wire.begin(0x35);
  
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}


void loop() {
  }
