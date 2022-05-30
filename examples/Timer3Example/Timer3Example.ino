// This example requires the TimerOne library.
// https://github.com/PaulStoffregen/TimerThree

#include <ContinuousStepper_Timer3.h>

const uint8_t stepPin = 2;
const uint8_t dirPin = 3;

ContinuousStepper_Timer3 stepper(stepPin, dirPin);

void setup() {
  stepper.spin(200);
}

void loop() {
  // no need to call stepper.loop()
  // it's called by the timer interrupt handler
}