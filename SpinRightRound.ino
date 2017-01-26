#include <Servo.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306();
#if defined(ESP8266)
  #define BUTTON_A 0
  #define BUTTON_B 16
  #define BUTTON_C 2
  #define LED      0
#elif defined(ARDUINO_STM32F2_FEATHER)
  #define BUTTON_A PA15
  #define BUTTON_B PC7
  #define BUTTON_C PC5
  #define LED PB5
#elif defined(TEENSYDUINO)
  #define BUTTON_A 4
  #define BUTTON_B 3
  #define BUTTON_C 8
  #define LED 13
#else 
//  #define BUTTON_A 9
  #define BUTTON_B 6
  #define BUTTON_C 5
  #define LED      13
#endif

Servo myservo;

int pos = 0;    // variable to store the servo position
//int val;
int pin = 9;
//int v = 0;
//String str;

void setup() {
  Serial.begin(9600);
  //Serial.println("Servo Fun");

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.display();
  delay(500);
  
  myservo.attach(pin);  // attaches the servo on pin x to the servo object

  // Clear the buffer.
  display.clearDisplay();
  display.display();
  
  //disabling lcd buttons for this project
  //  pinMode(BUTTON_A, INPUT_PULLUP);
  //  pinMode(BUTTON_B, INPUT_PULLUP);
  //  pinMode(BUTTON_C, INPUT_PULLUP);

}

void loop() {

  if ( Serial.available() > 0) {
    char ch = Serial.read();
    
    Serial.print("I received: ");
    Serial.println(ch);
  
    if(ch=1){
    
      Serial.println(pos);
      for (pos = 0; pos <= 180; pos += 10) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        Serial.println(pos);
        sendToDisplay(String(pos), 0, true);
        delay(150);                       // waits 15ms for the servo to reach the position
      }
      for (pos = 180; pos >= 0; pos -= 10) { // goes from 180 degrees to 0 degrees
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        Serial.println(pos);
        sendToDisplay(String(pos), 0, true);
        delay(150);                       // waits 15ms for the servo to reach the position
      }
  
    }
  }
}

void sendToDisplay(String message, int delayTime, bool clearDisplay){
  if(clearDisplay)display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  if(clearDisplay)display.setCursor(0,0);
  display.print(message);
  display.display(); // actually display all of the above
  delay(delayTime);
}

//void loop() {
//
//  if(!myservo.attached()){
//    Serial.print("Not attached, ending program");
//    return;
//  }
//
//  //Serial.println("1. # to set");
//  //Serial.println("2. w to write");
//  if ( Serial.available() > 0) {
//    char ch = Serial.read();
//
//    Serial.print("I received: ");
//    Serial.println(ch);
//
//    switch(ch) {
//      case 'a':
//        Serial.println("Enter angle:");
//        while (Serial.available()==0) {             //Wait for user input
//        }
//        str = Serial.readString();
//        v = str.toInt();
//        Serial.print("Set to: ");
//        Serial.println(v);
//        Serial.println(str);
//        break;
//      case 's':
//        Serial.print("Moving to: ");
//        Serial.println(v);
//        myservo.write(v);
//        v = 0;
//        break;

//    }
//    delay(150); 
//  }
//
//
//} 


