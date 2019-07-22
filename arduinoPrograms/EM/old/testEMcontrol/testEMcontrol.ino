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
/*
  Serial.println("blink 5 times");
  Wire.beginTransmission(slaveAddr);
  Wire.write(slaveAddr);
  Wire.write(5);
  Wire.endTransmission();
  delay(10);
  */
}

byte hb =0;
byte lb =0;
bool hbReceive = false;
bool lbReceive = false;

void loop() {
/*
  for(int i=0;i<10;i++) {
    Wire.beginTransmission(slaveAddr); // transmit to device
    Wire.write(0x99);        // Slave blink command
    Wire.endTransmission();    // stop transmitting

    //delay(10);

    //CHANGE TO REQUEST 2 BYTES!!!!
    Wire.requestFrom(slaveAddr,1);
  
    while(Wire.available()) {
      hb = Wire.read();
      Serial.print(hb);
      hbReceive = true;
    }
  
    Wire.requestFrom(slaveAddr,1);
  
    while(Wire.available()) {
      lb = Wire.read();
      Serial.print(lb);
      lbReceive = true;
    }

    //delay(10);
  }

  if(hbReceive == true && lbReceive == true) { //
    Serial.print("pinger Voltage: ");
    Serial.println((hb <<8) + lb);
    hbReceive = false;
    lbReceive = false;
  } else {
    Serial.println("cannot Ping");
  }

*/
/*
  byte echoHB = 0;
  byte echoLB = 0;
  bool echoHBReceive = false;
  for(int i=0;i<10;i++) {
    Wire.beginTransmission(slaveAddr); // transmit to device
    Wire.write(0x90);        // Slave blink command
    Wire.write(0x05);
    Wire.write(0x03);
    Wire.endTransmission();    // stop transmitting

    //delay(50);
    Wire.requestFrom(slaveAddr,2);
    while(Wire.available()) {
      echoHB = Wire.read();
      echoLB = Wire.read();
      echoHBReceive = true;
      
    }
  }
  
  if(echoHBReceive == true) { //
    Serial.print("echo results: ");
    Serial.print(echoHB);
    Serial.println(echoLB);
    echoHBReceive = false;
  } else {
    Serial.println("cannot Echo");
  }
 
*/
/*
  Wire.beginTransmission(slaveAddr); // transmit to device
  Wire.write(0x90);        // Slave blink command
  Wire.write(0x05);
  Wire.write(0x03);
  Wire.endTransmission();    // stop transmitting
*/
  Wire.beginTransmission(slaveAddr); // transmit to device
  Wire.write(0x21);        // Slave blink command
  Wire.write(255);        // blink for how much times
  Wire.endTransmission();    // stop transmitting
  Serial.println("0x21,127 sent");
  delay(1000);
  
/*
  Blink(2);                // Arduino Master Blink
  Wire.beginTransmission(slaveAddr); // transmit to device
  Wire.write(0x21);        // Slave blink command
  Wire.write(255);        // blink for how much times
  Wire.endTransmission();    // stop transmitting
  Serial.println("0x21,255 sent");
  delay(3000);
  
  Wire.beginTransmission(slaveAddr); // transmit to device
  Wire.write(0x21);        // Slave blink command
  Wire.write(102);        // blink for how much times
  Wire.endTransmission();    // stop transmitting
  Serial.println("0x21,102 sent");
  delay(10);
  
  Wire.beginTransmission(slaveAddr); // transmit to device
  Wire.write(0x21);        // Slave blink command
  Wire.write(127);        // blink for how much times
  Wire.endTransmission();    // stop transmitting
  Serial.println("0x21,127 sent");
  delay(3000);



  Blink(2);                // Arduino Master Blink
  Wire.beginTransmission(slaveAddr); // transmit to device
  Wire.write(0x22);        // Slave blink command
  Wire.write(255);        // blink for how much times
  Wire.endTransmission();    // stop transmitting
  Serial.println("0x22,255 sent");
  delay(3000);
  
  Wire.beginTransmission(slaveAddr); // transmit to device
  Wire.write(0x22);        // Slave blink command
  Wire.write(102);        // blink for how much times
  Wire.endTransmission();    // stop transmitting
  Serial.println("0x22,102 sent");
  delay(10);
  
  Wire.beginTransmission(slaveAddr); // transmit to device
  Wire.write(0x22);        // Slave blink command
  Wire.write(127);        // blink for how much times
  Wire.endTransmission();    // stop transmitting
  Serial.println("0x22,127 sent");
  delay(3000);
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
