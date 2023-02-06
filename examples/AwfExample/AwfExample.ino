// This example requires a core that implements analogWriteFrequency()
// such as Teensy 3 and 4

#include <ContinuousStepper_AWF.h>

const uint8_t stepPin = 2;
const uint8_t dirPin = 3;

ContinuousStepper_AWF stepper;

void setup() {
  stepper.begin(stepPin, dirPin);
  stepper.spin(200);
}

void loop() {
  stepper.loop();
}