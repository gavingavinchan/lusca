int PosPin = 6; //digital pin
int NegPin = 9;
int halfPeriod = 5;
#define ledPin 13

bool currentDir = true;
int currentStrength = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(ledPin,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  EMon(true,255);
  Blink(1);
  delay(3000);
  Blink(2);
  //EMoff();
  //EMon(false,0);
  EMon(false,50);
  delay(10+0);
  EMon(true,0);
  delay(3000);
}

void EMon(bool dir, int strength) {
 if(dir) {
  currentDir = true;
  digitalWrite(PosPin, HIGH);
  analogWrite(NegPin, 255-strength);
 } else {
  currentDir = false;
  digitalWrite(PosPin, LOW);
  analogWrite(NegPin, strength);
 }
  currentStrength = strength;
}

void EMoff() {
  while(currentStrength > 5) {
    currentStrength = currentStrength/2;
    if(currentDir) {
      EMon(false, currentStrength);
    } else {
      EMon(true, currentStrength);
    }
    delay(halfPeriod);
  }
  EMon(false,0);
}


void Blink(byte times){ 
  for (byte i=0; i< times; i++){
    digitalWrite(ledPin,HIGH);
    delay(175);
    digitalWrite(ledPin,LOW);
    delay(175);
  }
}
