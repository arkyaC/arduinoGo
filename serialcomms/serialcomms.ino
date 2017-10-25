int incomingByte = 0;   // for incoming serial data
#include <EEPROM.h>
int addr = 0;
int command;
int addr_input;
int value_output;
void setup() {
        Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
        pinMode(13, OUTPUT);    // TO check when the EEPROM is cleared
         for (int i = 0 ; i < EEPROM.length() ; i++) {//EEPROM cleared after each run, remove from final code
    EEPROM.write(i, 0);
  }

  // turn the LED on when we're done
  digitalWrite(13, HIGH);
}

void loop() {

        // send data only when you receive data:
        if (Serial.available() > 0) {
          command= Serial.read();// read the incoming data as a character
Serial.write(command);
Serial.println();
if(command==119){
                Serial.println("Writing to memory:");
                // read the incoming byte:
                while(!Serial.available());
                incomingByte = Serial.read();
                Serial.println(char(incomingByte));
                while(!Serial.available());
                addr= Serial.read();
                Serial.println(addr);
                EEPROM.write(addr, incomingByte);
                // say what you got:
                 Serial.println("Write Complete" );
               
}else if (command ==114){
  Serial.println("Reading from memory:");
  while(!Serial.available());
  addr_input= Serial.read();
  value_output = EEPROM.read(addr_input);

  Serial.print(char(value_output));
  Serial.print("\t");
  Serial.println(value_output, BIN);
}
        delay(100);
}
}
 








 

