#include <Wire.h>

#define SLAVE_ADDR 0x50

int value[2] = {0, 0};

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  
}

void loop()
{
  Serial.println("start of loop");
  Wire.requestFrom(SLAVE_ADDR, 2);

  Serial.print("value: ");

  while(Wire.available()) {
    value[0] = Wire.read();
    value[1] = Wire.read();
  
  int analogValue = (value[0] << 8) |  value[1];
  // shift the msb for eight digits to the right, creating an 16 digits binary number with 8 zeros at the right side. 
  // Those zeros are then overwritten with the lsb

  Serial.println(analogValue);

  delay(100);

  }
}
