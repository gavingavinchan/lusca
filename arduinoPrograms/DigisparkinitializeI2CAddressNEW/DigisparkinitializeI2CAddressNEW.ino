#include <EEPROM.h>
void setup(){
  pinMode(13, OUTPUT); //LED on Model A  or Pro
  Blink(4);
  delay(1000);
}

void loop(){

  //Write value
  EEPROM.put(0, 0x14); //wirte I2C address

  Blink(1);

  delay(1000);

  byte readValue = 0;
  //Read value
  EEPROM.get(0, readValue);

  Blink(readValue);
  delay(1000);
}

void Blink(byte times){ // poor man's display
  for (byte i=0; i< times; i++){
    digitalWrite(13,HIGH);
    delay (250);
    digitalWrite(13,LOW);
    delay (175);
  }
}
