void setup() {
  Serial.begin(9600);
  pinMode(8, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
}

void loop() {
  uint8_t number;
  bool signal ;  
  signal = digitalRead(8);
  if(signal == HIGH)  /* If new pin pressed */
   {
    delay(250);
    number = ( 0x00 | (digitalRead(13)<<0) | (digitalRead(12)<<1) | (digitalRead(11)<<2) | (digitalRead(10)<<3) );
      switch (number)
      {
        case 0x01:
        Serial.println("Pin Pressed : 1");
        break;
        case 0x02:
        Serial.println("Pin Pressed : 2");
        break;
        case 0x03:
        Serial.println("Pin Pressed : 3");
        break;
        case 0x04:
        Serial.println("Pin Pressed : 4");
        break;
        case 0x05:
        Serial.println("Pin Pressed : 5");
        break;
        case 0x06:
        Serial.println("Pin Pressed : 6");
        break;
        case 0x07:
        Serial.println("Pin Pressed : 7");
        break;
        case 0x08:
        Serial.println("Pin Pressed : 8");
        break;
        case 0x09:
        Serial.println("Pin Pressed : 9");
        break;
        case 0x0A:
        Serial.println("Pin Pressed : 0");
        break;
        case 0x0B:
        Serial.println("Pin Pressed : *");
        break;
        case 0x0C:
        Serial.println("Pin Pressed : #");
        break;    
      }
  }
}
