#include <SoftSerial.h>
#include <TinyPinChange.h>

/*
  Software serial multple serial test

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.

 The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)

 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 Not all pins on the Leonardo and Micro support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example

 This example code is in the public domain.

 */

SoftSerial mySerial(1, 3); // RX, TX

void writeSound(byte sound){
  mySerial.write(0x7E);
  mySerial.write(0xFF);
  mySerial.write(0x06);
  mySerial.write(0x03);
  mySerial.write((byte)0x00);
  mySerial.write((byte)0x00);
  mySerial.write(sound);
  int checksum = 0 - (int)(0xFF+0x06+0x03+sound);
  mySerial.write(highByte(checksum));
  mySerial.write(lowByte(checksum));
  mySerial.write(0xEF);
}

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);



  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  //mySerial.println("Hello, world?");
}

int toneNum = 1;

void loop() { // run over and over
  writeSound(toneNum);
  toneNum += 1;

  delay(2000);
}


