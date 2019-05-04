void setup() {
  // put your setup code here, to run once:
  pinMode(1,OUTPUT);
  pinMode(5,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(1,HIGH);
  digitalWrite(5,HIGH);
  delay(2000);
  digitalWrite(1,LOW);
  digitalWrite(5,LOW);
  delay(2000);
}
