// This example uses the tone() function, some restrictions apply.
// https://www.arduino.cc/reference/en/language/functions/advanced-io/tone/

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