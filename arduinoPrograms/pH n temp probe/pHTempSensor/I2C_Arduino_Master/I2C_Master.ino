#include <Wire.h>

#define SLAVE_ADDR 0x14

int pHValue[2] = {0, 0};
int TempValue[2] = {0, 0};

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  Serial.println("start of setup:");
  
}

void loop()
{
  Wire.beginTransmission(SLAVE_ADDR);
  byte command = 0x69;
  Wire.write(command);
  Wire.endTransmission();
  
  Wire.requestFrom(SLAVE_ADDR,4);
  
  while(Wire.available()) {
    pHValue[0] = Wire.read();
    pHValue[1] = Wire.read();
    TempValue[0] = Wire.read();
    TempValue[1] = Wire.read();
  
    int pHValue_NoBit = (pHValue[0] << 8) |  pHValue[1];
    int TempValue_NoBit = (TempValue[0] << 8) | TempValue[1];
    // shift the msb for eight digits to the right, creating an 16 digits binary number with 8 zeros at the right side. 
    // Those zeros are then overwritten with the lsb

    Serial.print("pH value: ");
    Serial.print(pHValue_NoBit);
    Serial.print("\t TempValue: ");
    Serial.println(TempValue_NoBit);

    delay(100);
   
  }

}
