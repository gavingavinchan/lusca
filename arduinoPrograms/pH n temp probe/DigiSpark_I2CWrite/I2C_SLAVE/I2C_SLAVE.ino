#include "TinyWireS.h"

#define SLAVE_ADDR 0x50

void setup()
{
  TinyWireS.begin(SLAVE_ADDR);
  TinyWireS.onRequest(requestEvent);
  pinMode(4, INPUT);
}


void loop()
{
}

void requestEvent()
{
  int sensorValue = analogRead(2);

  byte HighLow[2] = {0, 0};
  // extract the last right 8 digits and  by ANDing 0xFF (binary: 11111111). That way the left 8 bits are cut out
  HighLow[0] = (sensorValue >> 8) & 0xFF;
  // it is already placed at the far right we don't need to shift anything, just AND with 0xFF.
  HighLow[1] = (sensorValue) & 0xFF;

  TinyWireS.send(HighLow[0]);
  TinyWireS.send(HighLow[1]);
}
