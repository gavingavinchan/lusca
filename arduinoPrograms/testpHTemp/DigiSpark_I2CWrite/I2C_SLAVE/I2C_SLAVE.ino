#include "TinyWireS.h"

#define SLAVE_ADDR 0x50

void setup()
{
  TinyWireS.begin(SLAVE_ADDR);
  TinyWireS.onRequest(requestEvent);
  pinMode(4, INPUT);
  pinMode(3, INPUT);
}


void loop()
{
}

void requestEvent()
{
  int pHA = analogRead(2);
  int TempA = analogRead(3);

  byte pHBit[2] = {0, 0};
  // extract the last right 8 digits and  by ANDing 0xFF (binary: 11111111). That way the left 8 bits are cut out
  pHBit[0] = (pHA >> 8) & 0xFF;
  // it is already placed at the far right we don't need to shift anything, just AND with 0xFF.
  pHBit[1] = (pHA) & 0xFF;

  byte TempBit[2] = {0, 0};
  TempBit[0] = (TempA >> 8) & 0xFF;
  TempBit[1] = (TempA) & 0xFF;

  TinyWireS.send(pHBit[0]);
  TinyWireS.send(pHBit[1]);
  TinyWireS.send(TempBit[0]);
  TinyWireS.send(TempBit[1]);
}
