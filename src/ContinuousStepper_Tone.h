#pragma once

#include "ContinuousStepperWithOscillator.hpp"

namespace ArduinoContinuousStepper {
class ContinuousStepper_Tone : public ContinuousStepperWithOscillator {
  void startOscillator(unsigned int frequency) override {
    tone(stepPin(), frequency);
  }

  void stopOscillator() override {
    noTone(stepPin());
  }
};
} // namespace ArduinoContinuousStepper

using ArduinoContinuousStepper::ContinuousStepper_Tone;