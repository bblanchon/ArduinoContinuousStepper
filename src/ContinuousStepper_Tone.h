#pragma once

#include "ContinuousStepperBase.h"

namespace ArduinoContinuousStepper {
class ContinuousStepper_Tone : public ContinuousStepperBase {
public:
  void loop() {
    if (!_period)
      return;

    time_t now = micros();
    time_t elapsed = now - _periodStart;

    if (elapsed >= _period) {
      updateSpeedIfNeeded();
      _periodStart = now;
    }
  }

private:
  void setPeriod(unsigned long period) override {
    if (period) {
      writeDir();
      tone(stepPin(), 1e6 / period);
    } else {
      noTone(stepPin());
    }
    _period = period;
  }

  void writeStep(bool) override {}

  time_t _period, _periodStart = 0;
};
} // namespace ArduinoContinuousStepper

using ArduinoContinuousStepper::ContinuousStepper_Tone;