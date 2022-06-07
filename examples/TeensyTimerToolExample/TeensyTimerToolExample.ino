// This example requires the TeensyTimerTool library.
// https://github.com/luni64/TeensyTimerTool

#include <ContinuousStepper_TeensyTimerTool.h>

const uint8_t stepPin = 2;
const uint8_t dirPin = 3;

TeensyTimerTool::PeriodicTimer timer;
ContinuousStepper_TeensyTimerTool stepper(timer);

void setup() {
  stepper.begin(stepPin, dirPin);
  stepper.spin(200);
}

void loop() {
  // no need to call stepper.loop()
  // it's called by the timer interrupt handler
}