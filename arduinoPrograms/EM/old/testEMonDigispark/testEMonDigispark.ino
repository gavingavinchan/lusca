#define channelA_D 3
#define channelA_A 1
#define channelB_D 5
#define channelB_A 4

void EMon(bool _channel, int _value){
  int valueOnOrigin = (_value-127)*2;
  if(valueOnOrigin>255) {valueOnOrigin = 255;}
  if(_channel) {
    if(valueOnOrigin>0) {
     digitalWrite(channelA_D, HIGH);
     analogWrite(channelA_A, 255-valueOnOrigin);
    } else {
     digitalWrite(channelA_D, LOW);
     analogWrite(channelA_A, -valueOnOrigin);
    }
  } else {
    if(valueOnOrigin>0) {
     digitalWrite(channelB_D, HIGH);
     analogWrite(channelB_A, 255-valueOnOrigin);
    } else {
     digitalWrite(channelB_D, LOW);
     analogWrite(channelB_A, -valueOnOrigin);
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(channelA_D,OUTPUT);
  pinMode(channelA_A,OUTPUT);
  pinMode(channelB_D,OUTPUT);
  pinMode(channelB_A,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  EMon(true, 0);
  delay(3000);
  EMon(true,165);
  delay(500);
  EMon(true,137);
  delay(1500);

//  digitalWrite(3, LOW);
//  analogWrite(1, 255);
//
//  delay(3000);
//  digitalWrite(3, HIGH);
//  analogWrite(1, 180);
//
//  delay(2000);
}
