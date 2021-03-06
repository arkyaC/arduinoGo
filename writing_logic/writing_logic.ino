#include <Stepper.h>
#include <Servo.h>
#include <EEPROM.h>

Servo myservo;  // create servo object to control a servo

const int stepsPerRevolution =200;// DON'T CHANGE
// initialize the stepper library on pins 8 through 11:
Stepper myStepper_y(stepsPerRevolution, 8, 9, 10, 11);
Stepper myStepper_x(stepsPerRevolution,4,5,6,7);

int nSteps;//to contain number of steps per iteration for the stepper
int penDown = 160, penUp = 180; //pen down and up positions for the servo
int servoPos;
int segLength = 5;//length of each segment of the 7-segment
int flag = 0;// 1 when there's meaningful input from user
int servoPin = 3;

int addr = 0;
int command;
int addr_input;
int data_input;
int value_output;
byte value[8];

//int numberOfRev;// this is where USER INPUT goes (for now)
//byte value[] = {1,1,1,1,0,1,1,0};//will contain a byte length command for one character

//--------------------------------------------------------------------------

void setup() {
 Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
  pinMode(13, OUTPUT);    // TO check when the EEPROM is cleared
   
  // set the speed at 60 rpm:
  myStepper_y.setSpeed(60);
  myStepper_x.setSpeed(60);
  // initialize the serial port:
  Serial.begin(9600); 
  //myservo.attach(3);
  //flag = 1;
       
  // turn the LED on when we're done
  digitalWrite(13, HIGH);
}
//--------------------------------------------------------------------------
  void loop(){
          if (Serial.available() > 0) {
          command= Serial.read();// read the incoming data as a character
Serial.write(command);
Serial.println();
if(command==119){
                Serial.println("Writing to memory:");
                // read the incoming byte:
               
                while(!Serial.available());
                addr=Serial.read() ;
                Serial.println(addr);
                while(!Serial.available());
                data_input=Serial.parseInt();
                data_input=data_input+128;
                
  Serial.println(data_input, BIN);
                EEPROM.write(addr, data_input);
                // say what you got:
                 Serial.println("Write Complete" );
               
}
else if (command ==114){
  Serial.println("Reading from memory:");
  while(!Serial.available());
  addr_input= Serial.read();
  value_output = EEPROM.read(addr_input);
  flag=1;
  for (byte i=0; i<8; i++) {
    value[7-i] = bitRead(value_output, i);
  }
   for (byte j=0; j<8; j++) {
    Serial.print(value[j]);
  }
    Serial.println();
    if(flag==1&&value[0]==1){ //this must be set whenever there is meaningful input from user
      // Serial.println("Writing now");
      
      for(byte i=1;i<=7;i++){
        if(value[i]==1){
          servoPos = penDown;
        }
        else if(value[i]==0){
          servoPos = penUp;
        }
        myservo.attach(servoPin);
        myservo.write(servoPos);
        // Serial.println(value[i]);
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
                  // Serial.print("steps_x:");
                  // Serial.println(j+1);
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
                  // Serial.print("steps_y:");
                  // Serial.println(j+1);
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
      //Serial.println(value[i]);
      delay(100);
      //move to next position
      nSteps = 200;
      for (int j=0; j<2; j++){
        myStepper_x.step(nSteps);
        // Serial.print("steps_x:");
        // Serial.println(j+1);
        delay(10);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        delay(250);
      }
      flag = 0; //unflagging
    }
    else if(flag==1&&value[0]==0){
      Serial.println("INVALID CHARACTER, try again");
    }
  }
   else if( command == 67){
  Serial.println("Flushing memory:");
   for (int i = 0 ; i < EEPROM.length() ; i++) {//EEPROM cleared after each run, remove from final code
    EEPROM.write(i, 0);
   
  }
  Serial.println("Memory cleared"); 
}
        delay(100);
}
}
