#pragma once

#include <Arduino.h>

#include <ContinuousStepper/OutputPin.hpp>
#include <ContinuousStepperImpl.hpp>

namespace ArduinoContinuousStepper {

class StepperBase {
protected:
  StepperBase(StepperListener *listener) : _listener(listener) {}

  void stepperInitialized() {
    _listener->stepperInitialized();
  }

private:
  StepperListener *_listener;
};

class StepperDriver : StepperBase {
public:
  void begin(uint8_t stepPin, uint8_t dirPin) {
    _stepPin = stepPin;
    _dirPin = dirPin;
    stepperInitialized();
  }

protected:
  using StepperBase::StepperBase;

  void setDirection(bool reversed) {
    _dirPin.set(reversed ? LOW : HIGH);
  }

  void step() {
    _stepPin.toggle();
  }

  bool needsDoubleSpeed() const {
    // step() must be called twice per cycle:
    // - once to set the step pin high
    // - once to set it low
    return _stepPin != NULL_PIN;
  }

  void powerOn(){};
  void powerOff(){};

private:
  OutputPin _stepPin, _dirPin;
};

class FourWireStepper : StepperBase {
public:
  void begin(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4) {
    _pins[0] = pin1;
    _pins[1] = pin2;
    _pins[2] = pin3;
    _pins[3] = pin4;
    stepperInitialized();
  }

protected:
  using StepperBase::StepperBase;

  void setDirection(bool reversed) {
    _increment = reversed ? 3 : 1;
  }

  void step() {
    _position = (_position + _increment) % 4;
    setPins(_flags[_position]);
  }

  void powerOn() {
    setPins(_flags[_position]);
  }

  void powerOff() {
    setPins(0);
  }

  bool needsDoubleSpeed() const {
    return false;
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
