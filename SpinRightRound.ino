#include <Servo.h>

Servo myservo;

int pos = 0;    // variable to store the servo position

void setup() {
  Serial.begin(9600);
  Serial.println("Servo Fun");
  
  myservo.attach(6);  // attaches the servo on pin x to the servo object
}

//void loop() {
//  Serial.println(pos);
//  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
//    // in steps of 1 degree
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    Serial.println(pos);
//    delay(150);                       // waits 15ms for the servo to reach the position
//  }
//  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    Serial.println(pos);
//    delay(150);                       // waits 15ms for the servo to reach the position
//  }
//}

void loop() {

  static int v = 0;
  //Serial.println("1. # to set");
  //Serial.println("2. w to write");
  if ( Serial.available() > 0) {
    char ch = Serial.read();

    Serial.print("I received: ");
    Serial.println(ch);

    switch(ch) {
      case '0'...'9':
        v = v * 10 + ch - '0';
        break;
      case 's':
        Serial.print("Moving to: ");
        Serial.println(v);
        myservo.write(v);
        v = 0;
        break;
      case 'w':
        //servo2.write(v);
        v = 0;
        break;
      case 'd':
        //servo2.detach();
        break;
      case 'a':
        //servo2.attach(15);
        break;
    }
  }


} 
