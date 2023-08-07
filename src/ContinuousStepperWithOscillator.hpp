#pragma once

#include "ContinuousStepperBase.h"

namespace ArduinoContinuousStepper {
class ContinuousStepperWithOscillator : public ContinuousStepperBase {
  class DirOnlyDriver : public StepperInterface {
  public:
    DirOnlyDriver(pin_t dirPin) : _dirPin(dirPin) {}

    void step() override {}

    void setDirection(bool reversed) {
      _dirPin.set(reversed ? LOW : HIGH);
    }

  private:
    OutputPin _dirPin;
  };

public:
  void begin(pin_t stepPin, pin_t dirPin) {
    ContinuousStepperBase::begin(new DirOnlyDriver(dirPin));
    _stepPin = stepPin;
    pinMode(stepPin, OUTPUT);
  }

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

protected:
  pin_t stepPin() const {
    return _stepPin;
  }

private:
  virtual void startOscillator(unsigned int frequency) = 0;
  virtual void stopOscillator() = 0;

  void setPeriod(unsigned long period) override {
    if (period) {
      startOscillator(1e6 / period);
    } else {
      stopOscillator();
    }
    _period = period;
  }

  time_t _period, _periodStart = 0;
  pin_t _stepPin;
};
} // namespace ArduinoContinuousStepper
