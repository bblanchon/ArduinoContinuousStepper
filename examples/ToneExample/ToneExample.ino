// This example uses the tone() function, some restrictions apply.
// https://www.arduino.cc/reference/en/language/functions/advanced-io/tone/
//
// Tested on AVR, Teensy 3.1 and Teensy 4.1

#include <ContinuousStepper.h>
#include <ContinuousStepper/Tickers/Tone.hpp>

// ToneTicker can only work with StepperDriver
ContinuousStepper<StepperDriver, ToneTicker> stepper;

void setup() {
  stepper.begin(/*step=*/2, /*dir=*/3);

  stepper.spin(200);
}

void loop() {
  stepper.loop();
}