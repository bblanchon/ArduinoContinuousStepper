#pragma once

#include "ContinuousStepperBase.h"

namespace ArduinoContinuousStepper {
class ContinuousStepperWithOscillator : public ContinuousStepperBase {
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
  virtual void startOscillator(unsigned int frequency) = 0;
  virtual void stopOscillator() = 0;

  void setPeriod(unsigned long period) override {
    if (period) {
      writeDir();
      startOscillator(1e6 / period);
    } else {
      stopOscillator();
    }
    _period = period;
  }

  void writeStep(bool) override {}

  time_t _period, _periodStart = 0;
};
} // namespace ArduinoContinuousStepper
