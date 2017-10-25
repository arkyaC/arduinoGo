
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int last_pos = 165;    // variable to store the servo position
int pos;

void setup() {
  //myservo.attach(3);  // attaches the servo on pin 3 to the servo object
  Serial.begin(9600);
}

void loop() {
  //RANGE is 155 (pen down) to 170 (pen up)
  if(Serial.available()>0){
    pos=Serial.parseInt();
  }
  if(pos<155)
    pos=last_pos;
  myservo.attach(3);
  myservo.write(pos);
  Serial.println(pos);
  last_pos=pos;
  delay(50);
  myservo.detach();
}

