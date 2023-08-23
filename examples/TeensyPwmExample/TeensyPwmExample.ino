// This example requires the Teensy_PWM library.
// https://github.com/khoih-prog/Teensy_PWM
//
// Tested on Teensy 4.1
// ⛔ Doesn't work on Teensy 3.1 (most likely due to a bug in Teensy_PWM)

#include <ContinuousStepper.h>
#include <ContinuousStepper/Tickers/KhoiH_PWM.hpp>
#include <Teensy_PWM.h>

// KhoihTicker can only work with StepperDriver
ContinuousStepper<StepperDriver, KhoihTicker<Teensy_PWM>> stepper;

void setup() {
  stepper.begin(/*step=*/2, /*dir=*/3); // ⚠️ step pin must support PWM

  stepper.spin(200);
}

void loop() {
  stepper.loop();
}