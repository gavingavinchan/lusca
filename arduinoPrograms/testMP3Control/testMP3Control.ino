#include <Wire.h>
#include <SoftwareSerial.h>
#define ledPin 13

SoftwareSerial mySerial(10, 11);

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);

  mySerial.begin(9600);
  Serial.println("Start");
}


void loop() {
  //int sound = 0x01;
  //if( millis() % 5000 == 0){
  if(Serial.available() > 0) {
    Wire.beginTransmission(0x17);

    int input = Serial.read();
    if(input != 115) {
      
    Wire.write(byte(0x06));        // command
    byte sound = input - 48;
    Wire.write(byte(sound));

    } else {
      Wire.write(byte(0x07));
    } 
    
   /*
    Wire.write(byte(0x04));
    
    Wire.write(byte(0x7E));
    Wire.write(byte(0xFF));
    
    Wire.write(byte(0x08));
    
    Wire.write(0x03);
    Wire.write(0x00);
    Wire.write(0x00);
    
    Wire.write(sound);
    int checksum = 0 - (int)(0xFF+0x06+0x03+sound);
    Wire.write(highByte(checksum));
    Wire.write(lowByte(checksum));
    Wire.write(0xEF);
  */
    Wire.endTransmission();    // stop transmitting
  
    //Blink(sound);
    Serial.println(byte(input));
  }
 if (mySerial.available()) {
    Serial.write((byte)mySerial.read());
    Serial.flush();
  }
}

void Blink(byte times){ 
  for (byte i=0; i< times; i++){
    digitalWrite(ledPin,HIGH);
    delay (175);
    digitalWrite(ledPin,LOW);
    delay (175);
  }
}
