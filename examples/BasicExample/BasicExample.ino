#include <ContinuousStepper.h>

// If using a stepper driver, with STEP and DIR pins:
ContinuousStepper<StepperDriver> stepper;

// If using a four-wire stepper:
// ContinuousStepper<FourWireStepper> stepper;

void setup() {
  // If using a stepper driver, with STEP and DIR pins
  stepper.begin(/*step=*/2, /*dir=*/3);

  // If using a four-wire stepper:
  // stepper.begin(8, 10, 9, 11);

  stepper.spin(200);
}

void loop() {
  stepper.loop();
}