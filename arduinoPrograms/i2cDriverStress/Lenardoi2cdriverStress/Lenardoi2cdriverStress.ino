#include <EEPROM.h>
#include <Wire.h>

byte command = 0;


void receiveEvent(byte numBytes) {
  command = Wire.read();
 }

void requestEvent() {
  Wire.write(command);
 }



void setup() {
  byte SLAVE_ADDR = EEPROM.read(0);
  Wire.begin(SLAVE_ADDR);

  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}


void loop() {
}
