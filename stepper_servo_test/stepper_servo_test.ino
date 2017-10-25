#include <Stepper.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int last_pos = 165;    // variable to store the servo position
int pos;


const int stepsPerRevolution =200;// DON'T CHANGE
int numberOfRev;// this is where USER INPUT goes (for now)

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(60);
  // initialize the serial port:
  Serial.begin(9600); 
  //myservo.attach(3);
  // step one revolution  in one direction:`
  //Serial.println("clockwise");

 // myStepper.step(stepsPerRevolution);
  
}
  void loop(){
    if(Serial.available()>0){
      pos=Serial.parseInt();
    }
    if(pos>=155){
      myservo.attach(3);
      myservo.write(pos);
      Serial.println(pos);
      last_pos=pos;
      delay(200);
      myservo.detach();
    }
    else if(pos<30){
      numberOfRev=pos;
      for (int i=0; i<numberOfRev; i++){
        myStepper.step(200);//DIRECTION INFORMATION goes here
        Serial.print("steps:");
        Serial.println(i+1);
        delay(10);
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
        digitalWrite(10, LOW);
        digitalWrite(11, LOW);
        delay(250);
      }
    }
}
