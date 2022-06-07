// This example requires the TimerThree library.
// https://github.com/PaulStoffregen/TimerThree

#include <ContinuousStepper_Timer3.h>

const uint8_t stepPin = 2;
const uint8_t dirPin = 3;

ContinuousStepper_Timer3 stepper;

void setup() {
  stepper.begin(stepPin, dirPin);
  stepper.spin(200);
}

void loop() {
  // no need to call stepper.loop()
  // it's called by the timer interrupt handler
}