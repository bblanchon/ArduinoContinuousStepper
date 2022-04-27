#include <ContinuousStepper.h>

const uint8_t stepPin = 2;
const uint8_t dirPin = 3;

ContinuousStepper stepper(stepPin, dirPin);

void setup() {
  stepper.spin(200);
}

void loop() {
  stepper.loop();
}