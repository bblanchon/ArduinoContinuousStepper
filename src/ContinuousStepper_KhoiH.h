#pragma once

#include "ContinuousStepperWithOscillator.hpp"

namespace ArduinoContinuousStepper {

// khoih = Khoi Hoang, the author of all the Xxx_PWM libraries
template <typename XXX_PWM>
class ContinuousStepper_KhoiH : public ContinuousStepperWithOscillator {
private:
  void initialize() override {
    _pwm = new XXX_PWM(stepPin(), 500, 0);
  }

  void startOscillator(unsigned int frequency) override {
    _pwm->setPWM(stepPin(), frequency, 50);
  }

  void stopOscillator() override {
    _pwm->setPWM(stepPin(), 500, 0);
  }

  XXX_PWM *_pwm = nullptr;
};
} // namespace ArduinoContinuousStepper

using ArduinoContinuousStepper::ContinuousStepper_KhoiH;