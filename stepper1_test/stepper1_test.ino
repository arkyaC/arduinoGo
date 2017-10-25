#include <Stepper.h>


const int stepsPerRevolution =200;// change this to fit the number of steps per revolution
// for your motor
const int stepsPerRevolution2 =15;// this is as per the experiment

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(100);
  // initialize the serial port:
  Serial.begin(9600); 
  // step one revolution  in one direction:`
  Serial.println("clockwise");

 // myStepper.step(stepsPerRevolution);
  for (int i=0; i<stepsPerRevolution2; i++){
     myStepper.step(1);
  Serial.print("steps:");
  Serial.println(i+1);
  delay(10);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  delay(250);
}
  delay(2000);
  // step one revolution in the other direction:
  Serial.println("counterclockwise");
  //myStepper.step(-stepsPerRevolution);
  for (int i=0; i<stepsPerRevolution2; i++){
     myStepper.step(-1);
  Serial.print("steps:");
  Serial.println(i+1);
  delay(10);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  delay(1000);
  }
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  }
  void loop(){
  
}
