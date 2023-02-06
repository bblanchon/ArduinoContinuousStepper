// This example requires the Teensy_PWM library.
// https://github.com/khoih-prog/Teensy_PWM

#include <ContinuousStepper_KhoiH.h>
#include <Teensy_PWM.h>

const uint8_t stepPin = 2;
const uint8_t dirPin = 3;

ContinuousStepper_KhoiH<Teensy_PWM> stepper;

void setup() {
  stepper.begin(stepPin, dirPin);
  stepper.spin(200);
}

void loop() {
  stepper.loop();
}