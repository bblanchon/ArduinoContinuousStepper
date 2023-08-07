#pragma once

#include <Arduino.h>

namespace ArduinoContinuousStepper {

constexpr uint8_t nullPin = 255;

class OutputPin {
public:
  OutputPin() : pin_(nullPin) {}

  OutputPin(uint8_t pin) : pin_(pin) {
    pinMode(pin, OUTPUT);
  }

  operator uint8_t() const {
    return pin_;
  }

  void set(bool level) {
    if (level_ == uint8_t(level) || pin_ == nullPin)
      return;
    digitalWrite(pin_, level);
    level_ = level;
  }

  void toggle() {
    set(level_ != HIGH);
  }

private:
  uint8_t pin_;
  uint8_t level_ = 2; // i.e. neither HIGH nor LOW
};

} // namespace ArduinoContinuousStepper