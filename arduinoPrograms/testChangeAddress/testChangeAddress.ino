#include <Wire.h>


void setup() {
  Wire.begin();

  Wire.beginTransmission(0x14);
  Wire.write(0xce);
  Wire.write(0xff);
  Wire.endTransmission();
}

void loop() {
  // put your main code here, to run repeatedly:

}
