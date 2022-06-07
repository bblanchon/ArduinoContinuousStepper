// This example requires the TimerOne library.
// https://github.com/PaulStoffregen/TimerOne

#include <ContinuousStepper_Timer1.h>

const uint8_t stepPin = 2;
const uint8_t dirPin = 3;

ContinuousStepper_Timer1 stepper;

void setup() {
  stepper.begin(stepPin, dirPin);
  stepper.spin(200);
}

void loop() {
  // no need to call stepper.loop()
  // it's called by the timer interrupt handler
}