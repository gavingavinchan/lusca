#include <Wire.h>


void setup() {
  Serial.begin(9600);
  Wire.begin();
  Serial.println("Wire Begin");
  delay(2000);
  
  Wire.beginTransmission(0x50);
  
  Wire.write(0xCE);
  Wire.write(0x50);
  Wire.endTransmission();

  Serial.println("Change address");
}

void loop() {
  // put your main code here, to run repeatedly:

}
