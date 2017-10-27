#include <Stepper.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int last_pos = 165;    // variable to store the servo position
int pos;
int nSteps;


const int stepsPerRevolution =200;// DON'T CHANGE
int numberOfRev;// this is where USER INPUT goes (for now)

// initialize the stepper library on pins 8 through 11:
Stepper myStepper_y(stepsPerRevolution, 8, 9, 10, 11);
Stepper myStepper_x(stepsPerRevolution,4,5,6,7);

void setup() {
  // set the speed at 60 rpm:
  myStepper_y.setSpeed(60);
  myStepper_x.setSpeed(60);
  // initialize the serial port:
  Serial.begin(9600); 
  //myservo.attach(3);
  // step one revolution  in one direction:`
  //Serial.println("clockwise");

 // myStepper_y.step(stepsPerRevolution);
  
}
  void loop(){
    if(Serial.available()>0){
      pos=Serial.parseInt();
    }
    if(pos>=150){//servo is activated here
      myservo.attach(3);
      myservo.write(pos);
      Serial.println(pos);
      last_pos=pos;
      delay(200);
      myservo.detach();
    }
    else if(abs(pos)<30&&abs(pos)>0){ //stepper_y is activated here
      numberOfRev=abs(pos);
      if(pos>0)
        nSteps = 200;
      else if(pos<0)
        nSteps = -200;
      for (int i=0; i<numberOfRev; i++){
        myStepper_y.step(nSteps);//DIRECTION INFORMATION goes here
        Serial.print("steps_y:");
        Serial.println(i+1);
        delay(10);
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
        digitalWrite(10, LOW);
        digitalWrite(11, LOW);
        delay(250);
      }
    }
    else if(abs(pos)>30&&abs(pos)<60){ //stepper_x is activated here
      numberOfRev=abs(pos)-30;
      if(pos>0)
        nSteps = 200;
      else if(pos<0)
        nSteps = -200;
      for (int i=0; i<numberOfRev; i++){
        myStepper_x.step(nSteps);//DIRECTION INFORMATION goes here
        Serial.print("steps_x:");
        Serial.println(i+1);
        delay(10);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        delay(250);
      }
    }
}
