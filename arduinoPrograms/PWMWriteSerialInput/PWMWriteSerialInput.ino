#define PWMPin 3
int incomingByte = 0;  // for incoming serial data

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  pinMode(PWMPin, OUTPUT);
}

void loop() {

  if(Serial.available()){
    analogWrite(PWMPin, Serial.parseInt());
  }
/*  
  if (Serial.available() > 0) {
    incomingByte = Serial.read()-48;
    Serial.print("recieved ");
    Serial.println(incomingByte);
  }
  analogWrite(PWMPin, incomingByte);
  Serial.print("PWM write: ");
  Serial.println(incomingByte);
  delay(100);
  */
}
