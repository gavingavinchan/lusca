
#include <Wire.h>
#define SLAVE_ADDR 0x70

long bitshift(byte byte1, byte byte2) {
  long Nobitshift = (byte1 << 8) | byte2;
  return Nobitshift;
  }

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  Serial.println("start of setup");
}

void loop() {
  // put your main code here, to run repeatedly:
 
  Wire.beginTransmission(SLAVE_ADDR);
  byte command67 = 0x67;
  Wire.write(command67);
  Wire.endTransmission();
  //delay(100);

  
  Wire.requestFrom(SLAVE_ADDR, 2);

  byte pHByte[2] = {0, 0};
  while(Wire.available()) {
    //if(Wire.read() == 1) {
      pHByte[0] = Wire.read();
      pHByte[1] = Wire.read();
  }

  
  Serial.print("0x67 pH: ");
  Serial.print(pHByte[0]);
  Serial.print("\t");
  Serial.print(pHByte[1]);
  Serial.print("\t");
  Serial.print(bitshift(pHByte[0], pHByte[1]));

  
  

  Wire.beginTransmission(SLAVE_ADDR);
  byte command68 = 0x68;
  Wire.write(command68);
  Wire.endTransmission();
 // delay(100);

  Wire.requestFrom(SLAVE_ADDR, 2);

  byte TempByte[2] = {0, 0};
  while(Wire.available()) {
    TempByte[0] = Wire.read();
    TempByte[1] = Wire.read();
  }
  Serial.print("\t 0x68 Temp: ");
  Serial.print(bitshift(TempByte[0], TempByte[1]));



  Wire.beginTransmission(SLAVE_ADDR);
  byte command69 = 0x69;
  Wire.write(command69);
  Wire.endTransmission();
  //delay(100);
  
  Wire.requestFrom(SLAVE_ADDR, 4);

  while(Wire.available()) {
    pHByte[0] = Wire.read();
    pHByte[1] = Wire.read();
    TempByte[0] = Wire.read();
    TempByte[1] = Wire.read();
  }
  Serial.print("\t 0x69 pH: ");
  Serial.print(pHByte[0]);
  Serial.print("\t");
  Serial.print(pHByte[1]);
  Serial.print("\t");
  Serial.print(bitshift(pHByte[0], pHByte[1]));
  Serial.print("\t 0x69 Temp: ");
  Serial.print(TempByte[0]);
  Serial.print("\t");
  Serial.print(TempByte[1]);
  Serial.print("\t");
  Serial.print(bitshift(TempByte[0], TempByte[1]));



  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(0xCE);
  Wire.write(0x70);
  Wire.endTransmission();
  //delay(1000);
  int x = 0;
  Wire.requestFrom(SLAVE_ADDR, 1);

  while(Wire.available()) {
    Serial.print("\t");
    Serial.print("commandADDR Denary : ");
    Serial.print("\t");
    Serial.print(x = (byte)Wire.read());
    Serial.print("\t");
    Serial.print("commandADDR Hex");
    Serial.print("\t");
    Serial.print(x, HEX);
  }
  Serial.println();
  
}
