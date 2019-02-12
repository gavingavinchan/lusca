// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
#define ledPin 13

#define slaveAddr 0x14

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  pinMode(ledPin, OUTPUT);
  Serial.begin(57600);

  Serial.println("blink 5 times");
  Wire.beginTransmission(slaveAddr);
  Wire.write(0x10);
  Wire.write(5);
  Wire.endTransmission();
  delay(10);
}

byte hb =0;
byte lb =0;
bool hbReceive = false;
bool lbReceive = false;

void loop() {

  for(int i=0;i<10;i++) {
    Wire.beginTransmission(slaveAddr); // transmit to device
    Wire.write(0x99);        // Slave blink command
    Wire.endTransmission();    // stop transmitting
  
    Wire.requestFrom(slaveAddr,1);
  
    while(Wire.available()) {
      hb = Wire.read();
      //Serial.print(hb);
      hbReceive = true;
    }
  
    Wire.requestFrom(slaveAddr,1);
  
    while(Wire.available()) {
      lb = Wire.read();
      //Serial.print(lb);
      lbReceive = true;
    }
  

  }

  if(hbReceive == true && lbReceive == true) { //
    Serial.print("pinger Voltage: ");
    Serial.println((hb <<8) + lb);
    hbReceive = false;
    lbReceive = false;
  } else {
    Serial.println("cannot Ping");
  }


  Blink(2);                // Arduino Master Blink
  Wire.beginTransmission(slaveAddr); // transmit to device
  Wire.write(0x21);        // Slave blink command
  Wire.write(255);        // blink for how much times
  Wire.endTransmission();    // stop transmitting
  delay(1000);
  
  Wire.beginTransmission(slaveAddr); // transmit to device
  Wire.write(0x21);        // Slave blink command
  Wire.write(0);        // blink for how much times
  Wire.endTransmission();    // stop transmitting
  Serial.println("0x21,255 sent");
  delay(1000);



  Blink(2);                // Arduino Master Blink
  Wire.beginTransmission(slaveAddr); // transmit to device
  Wire.write(0x22);        // Slave blink command
  Wire.write(255);        // blink for how much times
  Wire.endTransmission();    // stop transmitting
  delay(1000);

  Wire.beginTransmission(slaveAddr); // transmit to device
  Wire.write(0x22);        // Slave blink command
  Wire.write(0);        // blink for how much times
  Wire.endTransmission();    // stop transmitting
  Serial.println("0x22,255 sent");
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
