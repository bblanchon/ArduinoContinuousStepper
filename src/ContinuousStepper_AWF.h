#pragma once

#include "ContinuousStepperWithOscillator.hpp"

namespace ArduinoContinuousStepper {

// AWF = analogWriteFrequency(), a function that changes the PWM frequency on Teensy 3 and 4
class ContinuousStepper_AWF : public ContinuousStepperWithOscillator {
  void startOscillator(unsigned int frequency) override {
    analogWriteFrequency(stepPin(), frequency);
    if (!_active) {
      analogWrite(stepPin(), 128);
      _active = true;
    }
  }

  void stopOscillator() override {
    analogWrite(stepPin(), 0);
    _active = false;
  }

  bool _active = false;
};
} // namespace ArduinoContinuousStepper

using ArduinoContinuousStepper::ContinuousStepper_AWF;