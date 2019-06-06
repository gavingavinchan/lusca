#define channelA_D 2
#define channelA_A 3
#define channelB_D 4
#define channelB_A 5

void EMon(bool _channel, int _value){
  int valueOnOrigin = (_value-127)*2;
  if(valueOnOrigin>255) {valueOnOrigin = 255;}
  if(_channel) {
    if(_value == 0) {          //for backwards compatibility
      digitalWrite(channelA_D, LOW);
      analogWrite(channelA_A, 0);
    } else if(valueOnOrigin>0) {
     digitalWrite(channelA_D, HIGH);
     analogWrite(channelA_A, 255-valueOnOrigin);
    } else {
     digitalWrite(channelA_D, LOW);
     analogWrite(channelA_A, -valueOnOrigin);
    }
  } else {
    if(_value == 0) {          //for backwards compatibility
      digitalWrite(channelB_D, LOW);
      analogWrite(channelB_A, 0);
    } else if(valueOnOrigin>0) {
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
  Serial.begin(57600);
  delay(500);
  Serial.println("start");
}

int i=127;
int j=0;
void loop() {
  // put your main code here, to run repeatedly: 
  EMon(true, i);
  EMon(false,j);
  Serial.print("EMon_left: ");
  Serial.println(i);
  Serial.print("EMon_right: ");
  Serial.println(j);
  delay(500);
  i += 10;
  j += 10;
  
  if(i>255) {
    i=0;
  }
  
  if(j>255) {
    j=0;
  }
  
}
