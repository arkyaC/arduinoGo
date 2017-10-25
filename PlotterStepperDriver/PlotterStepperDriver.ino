/*
 * For the basic stepper motor test
 */
#include <Arduino.h>
#include "PlotterStepperDriver.h"

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200

// All the wires needed for full functionality
#define DIR 22
#define STEP 26

// Since microstepping is set externally, make sure this matches the selected mode
// 1=full step, 2=half step etc.
#define MICROSTEPS 1

// 2-wire basic config, microstepping is hardwired on the driver
PlotterStepperDriver stepper(MOTOR_STEPS, DIR, STEP);

void setup() {
    /*
     * Set target motor RPM.
     * These motors can do up to about 200rpm.
     * Too high will result in a high pitched whine and the motor does not move.
     */
    stepper.setRPM(200);
}

void loop() {
    /*
     * Tell the driver the microstep level we selected.
     * If mismatched, the motor will move at a different RPM than chosen.
     */
    stepper.setMicrostep(MICROSTEPS);

    /*
     * Moving motor one full revolution using the degree notation
     */
    stepper.rotate(360);
    delay(2000);
    /*
     * Moving motor to original position using steps
     */
    //stepper.move(-200*MICROSTEPS);
    
    stepper.rotate(-360);

    delay(2000);
}
