//Standard PWM DC control
int E1 = 5;     //M1 Speed Control
int E2 = 6;     //M2 Speed Control
int M1 = 4;    //M1 Direction Control
int M2 = 7;    //M1 Direction Control

int ledPin = 13;

void off(void)                    //Stop
{
  digitalWrite(E1,LOW);   
  digitalWrite(E2,LOW);      
}   

void on2(boolean dir, char str) {
  analogWrite (E2,str);    //strength
  digitalWrite(M2,dir);
}

void Blink(byte times){ 
  for (byte i=0; i< times; i++){
    digitalWrite(ledPin,HIGH);
    delay (175);
    digitalWrite(ledPin,LOW);
    delay (175);
  }
}

void setup() {
  int i;
  for(i=4;i<=7;i++)
    pinMode(i, OUTPUT);  
  Serial.begin(9600);      //Set Baud Rate
  Blink(1);
  on2(HIGH, 255);
  delay(2000);
  Blink(1);
  on2(LOW,255);
  delay(100);
  on2(HIGH,255);
  delay(100);
  on2(LOW,255);
  delay(100);
  off();
  Blink(1);
}

void loop() {
  // put your main code here, to run repeatedly:

}
