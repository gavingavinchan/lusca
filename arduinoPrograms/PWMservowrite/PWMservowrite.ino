/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
String a;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
  Serial.println("Start");
  myservo.write(75); //75 as neutral point for ESC, >78 is turning

}

void loop() {
    if (Serial.available() > 0) {
      a = Serial.readString();

      // say what you got:
      Serial.print("received: ");
      Serial.println(a.toInt());
  }
  myservo.write(a.toInt());              // tell servo to go to position in variable 'pos'
  delay(15);                       // waits 15ms for the servo to reach the position
}
