#pragma once

#include "ContinuousStepperBase.h"

namespace ArduinoContinuousStepper {
class ContinuousStepper : public ContinuousStepperBase {
public:
  void loop() {
    if (!_tickPeriod)
      return;

    time_t now = micros();
    time_t elapsed = now - _lastTick;

    if (elapsed >= _tickPeriod) {
      tick();
      _lastTick = now;
    }
  }

protected:
  void setPeriod(unsigned long period) override {
    _tickPeriod = period / 2;
  }

private:
  static time_t now() {
    return micros();
  }

  time_t _tickPeriod, _lastTick = 0;
};
} // namespace ArduinoContinuousStepper

using ArduinoContinuousStepper::ContinuousStepper;