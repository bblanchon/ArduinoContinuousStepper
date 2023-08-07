#pragma once

#include <Arduino.h>

#include <ContinuousStepper/OutputPin.hpp>

namespace ArduinoContinuousStepper {

typedef unsigned long time_t;
typedef double float_t;
typedef uint8_t pin_t;

class StepperInterface {
public:
  virtual ~StepperInterface() = default;

  virtual void step() = 0;
  virtual void setDirection(bool reversed) = 0;

  // tells if drivers needs to be called twice per step
  virtual bool needsDoubleSpeed() const {
    return false;
  }
};

class StepperDriver : public StepperInterface {
public:
  StepperDriver(pin_t stepPin, pin_t dirPin) : _stepPin(stepPin), _dirPin(dirPin) {}

  void setDirection(bool reversed) override {
    _dirPin.set(reversed ? LOW : HIGH);
  }

  void step() override {
    _stepPin.toggle();
  }

  bool needsDoubleSpeed() const override {
    // step() must be called twice per cycle:
    // - once to set the step pin high
    // - once to set it low
    return true;
  }

private:
  OutputPin _stepPin, _dirPin;
};

} // namespace ArduinoContinuousStepper
