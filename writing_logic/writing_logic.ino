#include <Stepper.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo

const int stepsPerRevolution =200;// DON'T CHANGE
// initialize the stepper library on pins 8 through 11:
Stepper myStepper_y(stepsPerRevolution, 8, 9, 10, 11);
Stepper myStepper_x(stepsPerRevolution,4,5,6,7);

int nSteps;//to contain number of steps per iteration for the stepper
int penDown = 165, penUp = 180; //pen down and up positions for the servo
int servoPos;
int segLength = 5;//length of each segment of the 7-segment
int flag = 0;// 1 when there's meaningful input from user
int servoPin = 3;


//int numberOfRev;// this is where USER INPUT goes (for now)
byte toWrite[] = {1,1,1,1,0,1,1,0};//will contain a byte length command for one character

//--------------------------------------------------------------------------

void setup() {
  // set the speed at 60 rpm:
  myStepper_y.setSpeed(60);
  myStepper_x.setSpeed(60);
  // initialize the serial port:
  Serial.begin(9600); 
  //myservo.attach(3);
  flag = 1;
  
}
//--------------------------------------------------------------------------
  void loop(){
    
    if(flag==1&&toWrite[0]==1){ //this must be set whenever there is meaningful input from user
      Serial.println("Writing now");
      
      for(byte i=1;i<=7;i++){
        if(toWrite[i]==1){
          servoPos = penDown;
        }
        else if(toWrite[i]==0){
          servoPos = penUp;
        }
        myservo.attach(servoPin);
        myservo.write(servoPos);
        Serial.println(toWrite[i]);
        delay(200);
        switch(i){
          case 1:
          case 3:
          case 6://x axis
                nSteps = 200 * (1+(i-1)*(i-6)/3);// will be -ve for i=3, +ve for i=1,6
                /*if(i==1||i==6){
                  nSteps=200;
                }
                else if(i==3){
                  nSteps=-200;
                }*/
                for (int j=0; j<segLength; j++){
                  myStepper_x.step(nSteps);
                  Serial.print("steps_x:");
                  Serial.println(j+1);
                  delay(10);
                  digitalWrite(4, LOW);
                  digitalWrite(5, LOW);
                  digitalWrite(6, LOW);
                  digitalWrite(7, LOW);
                  delay(250);
                }
                break;
          case 2:
          case 4:
          case 5:
          case 7://y axis
                nSteps = 200 * (1 + (4-i)*(i-5)/3);// will be -ve for i=2 and 7, +ve for i=4,5
                for (int j=0; j<segLength; j++){
                  myStepper_y.step(nSteps);//DIRECTION INFORMATION goes here
                  Serial.print("steps_y:");
                  Serial.println(j+1);
                  delay(10);
                  digitalWrite(8, LOW);
                  digitalWrite(9, LOW);
                  digitalWrite(10, LOW);
                  digitalWrite(11, LOW);
                  delay(250);
                }
        }// end of switch case        
        myservo.detach();
      }
      myservo.attach(servoPin);
      myservo.write(penUp);
      //Serial.println(toWrite[i]);
      delay(100);
      //move to next position
      nSteps = 200;
      for (int j=0; j<2; j++){
        myStepper_x.step(nSteps);
        Serial.print("steps_x:");
        Serial.println(j+1);
        delay(10);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        delay(250);
      }
      flag = 0; //unflagging
    }
    else if(flag==1&&toWrite[0]==0){
      Serial.println("INVALID CHARACTER, try again");
    }
}
