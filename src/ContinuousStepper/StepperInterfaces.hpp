#pragma once

#include <Arduino.h>

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
  StepperDriver(pin_t stepPin, pin_t dirPin) : _stepPin(stepPin), _dirPin(dirPin) {
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
  }

  void setDirection(bool reversed) override {
    setDirPinLevel(reversed ? LOW : HIGH);
  }

  void step() override {
    toggleStepPinLevel();
  }

  bool needsDoubleSpeed() const override {
    // step() must be called twice per cycle:
    // - once to set the step pin high
    // - once to set it low
    return true;
  }

private:
  void toggleStepPinLevel() {
    _stepLevel = !_stepLevel;
    digitalWrite(_stepPin, _stepLevel);
  }

  void setDirPinLevel(bool level) {
    if (level == _dirLevel)
      return;
    digitalWrite(_dirPin, level);
    _dirLevel = level;
  }

  pin_t _stepPin, _dirPin;
  bool _stepLevel = LOW;
  bool _dirLevel = LOW;
};

} // namespace ArduinoContinuousStepper