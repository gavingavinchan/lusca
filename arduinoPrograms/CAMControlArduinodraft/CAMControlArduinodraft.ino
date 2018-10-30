#define ledPin 13

#define CH1pin 2
#define CH2pin 3
#define CH3pin 6
#define CH4pin 9

#define numOfCH 4
int ArrMicros[numOfCH] = {1500,1100,1500,1900};
int ArrCHpin[numOfCH] = {CH1pin,CH2pin,CH3pin,CH4pin};
unsigned long startOfInterval = 0;
int arrIndex = 0; 


void setup() {
  /*
  for(int i=0; i<numOfCH; i++) {
    pinMode(ArrCHpin[i], OUTPUT);
  }*/

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  

  Serial.begin(9600);
  Serial.println("Start");

  Serial.print("ArrMicros: ");
  printArr(ArrMicros,numOfCH);

  Serial.print("ArrCHpin: ");
  printArr(ArrCHpin,numOfCH);

  arrInsert(1600, 1);

  Serial.print("ArrMicros: ");
  printArr(ArrMicros,numOfCH);

  Serial.print("ArrCHpin: ");
  printArr(ArrCHpin,numOfCH);

  pinMode(ledPin, OUTPUT);
  Blink(2); 
}

void loop() {
  const long interval = 20000;

  if((micros()-startOfInterval) >= interval) {
    for(int i=0; i<numOfCH; i++) {
      digitalWrite(ArrCHpin[i], HIGH);
    }
    startOfInterval = micros();

    delayMicroseconds(ArrMicros[0]);
    digitalWrite(ArrCHpin[0], LOW);
   
    delayMicroseconds(ArrMicros[1] - ArrMicros[0]);
    digitalWrite(ArrCHpin[1], LOW);

    delayMicroseconds(ArrMicros[2] - ArrMicros[1]);
    digitalWrite(ArrCHpin[2], LOW);

    delayMicroseconds(ArrMicros[3] - ArrMicros[2]);
    digitalWrite(ArrCHpin[3], LOW);
  }

  
  //PWMwrite(ArrMicros, ArrCHpin, numOfCH, currentMicros);
  //dualPWMarr(ArrMicros, ArrCHpin);
  //dualPWMsimple(1100,2,1500,3);
}


void arrInsert(int micros, int CHpin) {
   for(int i=0;i<numOfCH;i++) {                     //replace old micros with new micros
    if(ArrCHpin[i] == CHpin || ArrCHpin[i] == 0) {
      ArrMicros[i] = micros;
    }
  }
  dualBubbleSort(ArrMicros, numOfCH, ArrCHpin);
}

void dualBubbleSort(int arBased[], int arBasedLength, int ar2[]) {        //sorting base on arBased, ar2 will be arranged how the arBased is arranged
  for (int i = (arBasedLength - 1); i >= 0; i--) {
    for (int j = 1; j <= i; j++) {
      if (arBased[j-1] > arBased[j]) {
        int temp1 = arBased[j-1];
        arBased[j-1] = arBased[j];
        arBased[j] = temp1;

        int temp2 = ar2[j-1];
        ar2[j-1] = ar2[j];
        ar2[j] = temp2;
      } 
    } 
  } 
}

void printArr(int arr[], int arrLength) {
  for(int i=0; i<arrLength; i++) {
    Serial.print(arr[i]);
    Serial.print("\t");
  }
  Serial.print('\n'); 
}


void PWMwrite(int _ArrMicros[], int _ArrCHpin[], int _numOfCH, unsigned long _currentMicros) {
  /*Serial.print("_ArrMicros[0] \t");
  Serial.println(_ArrMicros[0]);
  */

  
  const long interval = 20000;

  if((_currentMicros-startOfInterval) >= interval) {
    for(int i=0; i<_numOfCH; i++) {
      digitalWrite(_ArrCHpin[i], HIGH);
      /*
      Serial.print(_ArrCHpin[i]);
      Serial.print("\t");
      Serial.print("HIGH");
      Serial.print('\n'); 
      */
    }
    startOfInterval = _currentMicros;
  }

  if((_currentMicros-startOfInterval) >= _ArrMicros[arrIndex]) {
    digitalWrite(_ArrCHpin[arrIndex], LOW);
    if(arrIndex == (numOfCH-1)) {
      arrIndex = 0;
    } else {
      arrIndex++;
    }
  }
}

void dualPWMarr(int _ArrMicros[], int _ArrCHpin[]) {
  digitalWrite(_ArrCHpin[0], HIGH);
  digitalWrite(_ArrCHpin[1], HIGH);
  if(_ArrMicros[0] > _ArrMicros[1]) {
    delayMicroseconds(_ArrMicros[1]);
    digitalWrite(_ArrCHpin[1], LOW);
    delayMicroseconds(_ArrMicros[0] - _ArrMicros[1]);
    digitalWrite(_ArrCHpin[0], LOW);
  } else {
    delayMicroseconds(_ArrMicros[0]);
    digitalWrite(_ArrCHpin[0], LOW);
    delayMicroseconds(_ArrMicros[1] - _ArrMicros[0]);
    digitalWrite(_ArrCHpin[1], LOW);
  }
  delayMicroseconds(20000 - _ArrMicros[0] - _ArrMicros[1]);
}


void dualPWMsimple(unsigned int micros1, int _CH1pin, unsigned int micros2, int _CH2pin) {
  digitalWrite(_CH1pin, HIGH);
  digitalWrite(_CH2pin, HIGH);
  /*
  Serial.print("ALL HIGH \t");
  Serial.println(micros());
  */
  if(micros1 > micros2) {
    delayMicroseconds(micros2);
    digitalWrite(_CH2pin, LOW);
    /*
    Serial.print("ch2 Low \t");
    Serial.println(micros());
    */
    delayMicroseconds(micros1 - micros2);
    digitalWrite(_CH1pin, LOW);
    /*
    Serial.print("ch1 Low \t");
    Serial.println(micros());
    */
  } else {
    delayMicroseconds(micros1);
    digitalWrite(_CH1pin, LOW);
    /*
    Serial.print("ch1 Low \t");
    Serial.println(micros());
    */
    delayMicroseconds(micros2 - micros1);
    digitalWrite(_CH2pin, LOW);
    /*
    Serial.print("ch2 Low \t");
    Serial.println(micros());
    */
  }

  delay(17);
  unsigned int intervalLength = 3000;
  delayMicroseconds(intervalLength - micros1 - micros2);
  //Serial.println(20000 - micros1 - micros2);
  //delay(20);
}



void Blink(byte times){ 
  for (byte i=0; i< times; i++){
    digitalWrite(ledPin,HIGH);
    delay (175);
    digitalWrite(ledPin,LOW);
    delay (175);
  }
}
