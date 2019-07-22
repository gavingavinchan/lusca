#include <Wire.h>

#define SLAVE_ADDR 0x14

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  Serial.println("start of setup:");
  delay(1000);
}

void testMotorControl(byte pwr){
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(0x22);
  Wire.write(pwr);
  Wire.endTransmission();

  Wire.requestFrom(SLAVE_ADDR, 1);
  while(Wire.available()){
    Serial.println( (int) Wire.read() );
  }
}

void loop()
{
  Serial.println("Send 0");

  testMotorControl(255);
  delay(3000);

  testMotorControl(100);
  delay(3000);

  testMotorControl(0);
  delay(3000);

  testMotorControl(170);
  delay(3000);


  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(0x90);
  Wire.write(45);
  Wire.write(89);
  Wire.endTransmission();

  Wire.requestFrom(SLAVE_ADDR, 2);
  while(Wire.available()){
    Serial.println( (int) Wire.read() );
    Serial.println( (int) Wire.read() );
  }

//  delay(3000);
//  Wire.beginTransmission(SLAVE_ADDR);
//  //command = 0x21;
//  Wire.write(command);
//  Wire.write(127);
//  Wire.endTransmission();
//  delay(3000);
}
