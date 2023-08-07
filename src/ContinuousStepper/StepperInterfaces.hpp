#pragma once

#include <Arduino.h>

#include <ContinuousStepper/ContinuousStepperImpl.hpp>
#include <ContinuousStepper/OutputPin.hpp>

namespace ArduinoContinuousStepper {

class StepperBase {
protected:
  StepperBase(StepperListener *listener) : listener_(listener) {}

  void stepperInitialized() {
    listener_->stepperInitialized();
  }

private:
  StepperListener *listener_;
};

class StepperDriver : StepperBase {
public:
  void begin(uint8_t stepPin, uint8_t dirPin) {
    stepPin_ = stepPin;
    dirPin_ = dirPin;
    stepperInitialized();
  }

  void setEnablePin(uint8_t pin, bool activeLevel = HIGH) {
    enablePin_ = pin;
    enablePinActiveLevel_ = activeLevel;
    enablePin_.set(!isPowered_ ^ activeLevel);
  }

protected:
  using StepperBase::StepperBase;

  void setDirection(bool reversed) {
    dirPin_.set(reversed ? LOW : HIGH);
  }

  void step() {
    stepPin_.toggle();
  }

  bool needsDoubleSpeed() const {
    // step() must be called twice per cycle:
    // - once to set the step pin high
    // - once to set it low
    return stepPin_ != nullPin;
  }

  void powerOn() {
    enablePin_.set(enablePinActiveLevel_);
    isPowered_ = true;
  };

  void powerOff() {
    enablePin_.set(!enablePinActiveLevel_);
    isPowered_ = false;
  };

private:
  OutputPin stepPin_, dirPin_, enablePin_;
  bool enablePinActiveLevel_ = HIGH;
  bool isPowered_ = true;
};

class FourWireStepper : StepperBase {
public:
  void begin(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4) {
    pins_[0] = pin1;
    pins_[1] = pin2;
    pins_[2] = pin3;
    pins_[3] = pin4;
    stepperInitialized();
  }

protected:
  using StepperBase::StepperBase;

  void setDirection(bool reversed) {
    increment_ = reversed ? 3 : 1;
  }

  void step() {
    position_ = (position_ + increment_) % 4;
    setPins(flags_[position_]);
  }

  void powerOn() {
    setPins(flags_[position_]);
  }

  void powerOff() {
    setPins(0);
  }

  bool needsDoubleSpeed() const {
    return false;
  }

private:
  void setPins(uint8_t flags) {
    for (auto &pin : pins_) {
      pin.set(flags & 1);
      flags >>= 1;
    }
  }

  OutputPin pins_[4];
  uint8_t position_ = 0, increment_ = 1;
  uint8_t flags_[4] = {0b0101, 0b0110, 0b1010, 0b1001};
};

} // namespace ArduinoContinuousStepper
