/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>

Servo myservo1;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;
Servo myservo4;
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int i=0;
int j=0;

void setup() {
  myservo4.attach(A4);  // attaches the servo on pin 9 to the servo object
  myservo3.attach(A3);
  myservo2.attach(A2);
  myservo1.attach(A1);
}

void loop() {

//  while(i<2){
//  greeting();
//  i+=1;
//  }
//
//  
//  while(j<1){
//  up();
//  j+=1;
//  }

while(i<=1){
  original();
  i+=1;
}
delay(1000);
//while(j<1){
//sad();
//j+=1;
//}

while(j<4){
  crying();
  j+=1;
}
}

void greeting() {
    for (pos = 30; pos <= 150; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo4.write(pos);              // tell servo to go to position in variable 'pos'
    myservo3.write(pos);
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 150; pos >= 30; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo4.write(pos);              // tell servo to go to position in variable 'pos'
    myservo3.write(pos);
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
}

void up(){
  myservo1.write(30);
  myservo2.write(30);
  myservo3.write(170);
  myservo4.write(170);
}

void sad(){
  myservo3.write(100);
  myservo4.write(100);
}

void original(){
  myservo1.write(170);
  myservo2.write(170);
  myservo3.write(30);
  myservo4.write(30);
}

void crying(){
  for (pos = 50; pos <= 120; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    myservo2.write(pos);
    myservo3.write(170-pos);              // tell servo to go to position in variable 'pos'
    myservo4.write(170-pos);
    delay(15);
  }
  for (pos = 120; pos >= 50; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    myservo2.write(pos);
    myservo3.write(170-pos);              // tell servo to go to position in variable 'pos'
    myservo4.write(170-pos);
    delay(15);                       // waits 15 ms for the servo to reach the position
  }  
}
