#include <ContinuousStepper.h>

const uint8_t stepPin = 2;
const uint8_t dirPin = 3;

ContinuousStepper stepper;

void setup() {
  stepper.begin(stepPin, dirPin);
  stepper.spin(200);
}

void loop() {
  stepper.loop();
}