// This example requires a core that implements analogWriteFrequency()
// such as Teensy 3 and 4
//
// Tested on Teensy 3.1 and Teensy 4.0
// ⚠️ speed is quite limited on Teensy 3.1

#include <ContinuousStepper.h>
#include <ContinuousStepper/Tickers/AnalogWriteFrequency.hpp>

// AwfTicker can only work with StepperDriver
ContinuousStepper<StepperDriver, AwfTicker> stepper;

void setup() {
  stepper.begin(/*step=*/2, /*dir=*/3); // ⚠️ step pin must support PWM

  stepper.spin(200);
}

void loop() {
  stepper.loop();
}