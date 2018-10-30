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
  Wire.beginTransmission(0x16); // transmit to device
  Wire.write(0x10);        // Slave blink command
  Wire.write(1);        // blink for how much times
  Wire.endTransmission();    // stop transmitting

  Wire.beginTransmission(0x17); // transmit to device
  Wire.write(0x10);        // Slave blink command
  Wire.write(1);        // blink for how much times
  Wire.endTransmission();    // stop transmitting
  delay(1000);
  /*
  Blink(2);                // Arduino Master Blink
  Wire.beginTransmission(slaveAddr); // transmit to device
  Wire.write(0x10);        // Slave blink command
  Wire.write(2);        // blink for how much times
  Wire.endTransmission();    // stop transmitting
  delay(1000);

  Blink(3);                // Arduino Master Blink
  Wire.beginTransmission(slaveAddr); // transmit to device
  Wire.write(0x10);        // Slave blink command
  Wire.write(3);        // blink for how much times
  Wire.endTransmission();    // stop transmitting
  delay(1000);
  */
  
}

void Blink(byte times){ 
  for (byte i=0; i< times; i++){
    digitalWrite(ledPin,HIGH);
    delay (250);
    digitalWrite(ledPin,LOW);
    delay (175);
  }
}
