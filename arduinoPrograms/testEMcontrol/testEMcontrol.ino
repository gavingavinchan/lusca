// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
#define ledPin 13

#define slaveAddr 0x15

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  pinMode(ledPin, OUTPUT);
  Serial.begin(57600);
/*
  Wire.beginTransmission(slaveAddr);
  Wire.write(0x10);
  Wire.write(3);
  Wire.endTransmission();
  delay(10);
*/
  Wire.beginTransmission(slaveAddr);
  Wire.write(0x99);
  Wire.endTransmission();
  delay(10);

  Wire.requestFrom(slaveAddr,1);
  delay(500);

  while(Wire.available()) {
    byte hb = Wire.read();
    Serial.println(hb);
  }

  Blink(2);
  delay(3000);
  
  Wire.beginTransmission(slaveAddr);
  Wire.write(0x9A);
  Wire.endTransmission();
  delay(10);
  Wire.requestFrom(slaveAddr,1);
  delay(500);

  while(Wire.available()) {
    byte lb = Wire.read();
    Serial.println(lb);
  }
}

byte x = 0;

void loop() {
  
  Blink(1);                // Arduino Master Blink
  Wire.beginTransmission(slaveAddr); // transmit to device
  Wire.write(0x99);        // Slave blink command
  //Wire.write(255);        // blink for how much times
  Wire.endTransmission();    // stop transmitting
  delay(1000);

  Wire.requestFrom(slaveAddr,1);
  delay(500);

  while(Wire.available()) {
    byte hb = Wire.read();
    Serial.println(hb);
  }

  Wire.requestFrom(slaveAddr,1);
  delay(500);

  while(Wire.available()) {
    byte hb = Wire.read();
    Serial.println(hb);
  }



  Blink(2);                // Arduino Master Blink
  Wire.beginTransmission(slaveAddr); // transmit to device
  Wire.write(0x21);        // Slave blink command
  Wire.write(0);        // blink for how much times
  Wire.endTransmission();    // stop transmitting
  delay(1000);
  
  Wire.beginTransmission(slaveAddr); // transmit to device
  Wire.write(0x21);        // Slave blink command
  Wire.write(255);        // blink for how much times
  Wire.endTransmission();    // stop transmitting
  Serial.println("0x21,255 sent");
  delay(1000);



  Blink(2);                // Arduino Master Blink
  Wire.beginTransmission(slaveAddr); // transmit to device
  Wire.write(0x22);        // Slave blink command
  Wire.write(0);        // blink for how much times
  Wire.endTransmission();    // stop transmitting
  delay(1000);
  
}

void Blink(byte times){ 
  for (byte i=0; i< times; i++){
    digitalWrite(ledPin,HIGH);
    delay (250);
    digitalWrite(ledPin,LOW);
    delay (175);
  }
}
