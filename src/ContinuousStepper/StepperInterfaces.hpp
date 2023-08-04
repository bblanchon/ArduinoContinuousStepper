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

  virtual void powerOn(){};
  virtual void powerOff(){};
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
    return _stepPin != NULL_PIN;
  }

private:
  OutputPin _stepPin, _dirPin;
};

class FourWireStepper : public StepperInterface {
public:
  FourWireStepper(pin_t pin1, pin_t pin2, pin_t pin3, pin_t pin4) : _pins{pin1, pin2, pin3, pin4} {}

  void setDirection(bool reversed) override {
    _increment = reversed ? 3 : 1;
  }

  void step() override {
    _position = (_position + _increment) % 4;
    setPins(_flags[_position]);
  }

  void powerOn() override {
    setPins(_flags[_position]);
  }

  void powerOff() override {
    setPins(0);
  }

private:
  void setPins(uint8_t flags) {
    for (auto &pin : _pins) {
      pin.set(flags & 1);
      flags >>= 1;
    }
  }

  OutputPin _pins[4];
  uint8_t _position = 0, _increment = 1;
  uint8_t _flags[4] = {0b0101, 0b0110, 0b1010, 0b1001};
};

} // namespace ArduinoContinuousStepper
