// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
#define ledPin 13

#define slaveAddr 0x17

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  pinMode(ledPin, OUTPUT);
}

byte x = 0;

void loop() {
  
  Blink(1);                // Arduino Master Blink
  Wire.beginTransmission(0x13); // transmit to device
  Wire.write(0x05);        // Slave blink command
  Wire.write(255);        // blink for how much times
  Wire.endTransmission();    // stop transmitting
  delay(3000);



  Blink(2);                // Arduino Master Blink
  Wire.beginTransmission(0x13); // transmit to device
  Wire.write(0x05);        // Slave blink command
  Wire.write(0);        // blink for how much times
  Wire.endTransmission();    // stop transmitting
  delay(3000);
  
  
}

void Blink(byte times){ 
  for (byte i=0; i< times; i++){
    digitalWrite(ledPin,HIGH);
    delay (250);
    digitalWrite(ledPin,LOW);
    delay (175);
  }
}
