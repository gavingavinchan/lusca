// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
#define ledPin 13

#define addr 0x17

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  pinMode(ledPin, OUTPUT);
}

byte x = 0;

void loop() {
  
  Blink(1);
  Wire.beginTransmission(addr); // transmit to device #8
  Wire.write(0x11);        // sends five bytes
  Wire.write(1100 >> 8);              // sends one byte
  Wire.write(1100%255);
  
  Wire.write(0x12);        // sends five bytes
  Wire.write(1100 >> 8);              // sends one byte
  Wire.write(1100%255);
  delay(3000);

  Wire.write(0x13);        // sends five bytes
  Wire.write(1100 >> 8);              // sends one byte
  Wire.write(1100%255);
  delay(3000);

  Wire.write(0x14);        // sends five bytes
  Wire.write(1100 >> 8);              // sends one byte
  Wire.write(1100%255);
  
  Wire.endTransmission();    // stop transmitting
  delay(3000);
  
  
  Blink(2);
  Wire.beginTransmission(addr); // transmit to device #8
  Wire.write(0x11);        // sends five bytes
  Wire.write(1500 >> 8);              // sends one byte
  Wire.write(1500%255);

  
  Wire.write(0x12);        // sends five bytes
  Wire.write(1500 >> 8);              // sends one byte
  Wire.write(1500%255);
  delay(3000);

  Wire.write(0x13);        // sends five bytes
  Wire.write(1500 >> 8);              // sends one byte
  Wire.write(1500%255);
  delay(3000);

  Wire.write(0x14);        // sends five bytes
  Wire.write(1500 >> 8);              // sends one byte
  Wire.write(1500%255);
  
  Wire.endTransmission();    // stop transmitting
  delay(3000);
  
  Blink(3);
  Wire.beginTransmission(addr); // transmit to device #8
  Wire.write(0x11);        // sends five bytes
  Wire.write(1500 >> 8);              // sends one byte
  Wire.write(1500%255);

  Wire.write(0x12);        // sends five bytes
  Wire.write(1500 >> 8);              // sends one byte
  Wire.write(1500%255);
  delay(1000);

  Wire.write(0x13);        // sends five bytes
  Wire.write(1500 >> 8);              // sends one byte
  Wire.write(1500%255);
  delay(3000);

  Wire.write(0x14);        // sends five bytes
  Wire.write(1500 >> 8);              // sends one byte
  Wire.write(1500%255);
  
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
