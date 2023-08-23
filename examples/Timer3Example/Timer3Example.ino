// This example requires the TimerThree library.
// https://github.com/PaulStoffregen/TimerThree
//
// Tested on Teensy 3.1
// ⚠️ Doesn't work on Teensy 4.1
// ⚠️ Works poorly on AVR boards (UNO, Leonardo, Mega, etc.)

#include <ContinuousStepper.h>
#include <ContinuousStepper/Tickers/TimerThree.hpp>

// If using a stepper driver, with STEP and DIR pins:
ContinuousStepper<StepperDriver, TimerThreeTicker> stepper;

// If using a four-wire stepper:
// ContinuousStepper<FourWireStepper, TimerThreeTicker> stepper;

void setup() {
  // If using a stepper driver, with STEP and DIR pins:
  stepper.begin(/*step=*/2, /*dir=*/3);

  // If using a four-wire stepper:
  // stepper.begin(8, 10, 9, 11);

  stepper.spin(200);
}

void loop() {
  // no need to call stepper.loop()
  // it's called by the timer interrupt handler
}