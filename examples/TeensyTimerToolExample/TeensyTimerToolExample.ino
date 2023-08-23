// This example requires the TeensyTimerTool library.
// https://github.com/luni64/TeensyTimerTool
//
// Tested with Teensy 4.1 and TeensyTimerTool 1.3.1
// ⚠️ Doesn't work on Teensy 3.1 (most likely due to a bug in PeriodicTimer::setPeriod())

#include <ContinuousStepper.h>
#include <ContinuousStepper/Tickers/TeensyTimerTool.hpp>

TeensyTimerTool::PeriodicTimer timer;

// If using a stepper driver, with STEP and DIR pins:
ContinuousStepper<StepperDriver, TeensyTimerToolTicker> stepper(timer);

// If using a four-wire stepper:
// ContinuousStepper<FourWireStepper, TeensyTimerToolTicker> stepper(timer);

void setup() {
  // If using a stepper driver, with STEP and DIR pins
  stepper.begin(/*step=*/2, /*dir=*/3);

  // If using a four-wire stepper:
  // stepper.begin(8, 10, 9, 11);

  stepper.spin(200);
}

void loop() {
  // no need to call stepper.loop()
  // it's called by the timer interrupt handler
}