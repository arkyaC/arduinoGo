#include <Stepper.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int last_pos = 165;    // variable to store the servo position
int pos;


const int stepsPerRevolution =200;// change this to fit the number of steps per revolution
// for your motor
const int numberOfRev =20;// this is as per the experiment

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(60);
  // initialize the serial port:
  Serial.begin(9600); 
  // step one revolution  in one direction:`
  Serial.println("clockwise");

 // myStepper.step(stepsPerRevolution);
  for (int i=0; i<numberOfRev; i++){
    myStepper.step(-200);
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
  void loop(){
  
}
