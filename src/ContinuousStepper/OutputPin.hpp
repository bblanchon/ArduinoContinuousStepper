#pragma once

#include <Arduino.h>

namespace ArduinoContinuousStepper {

typedef uint8_t pin_t;
constexpr pin_t NULL_PIN = 255;

class OutputPin {
public:
  OutputPin() : _pin(NULL_PIN) {}

  OutputPin(pin_t pin) : _pin(pin) {
    pinMode(pin, OUTPUT);
  }

  operator pin_t() const {
    return _pin;
  }

  void set(bool level) {
    if (_level == uint8_t(level) || _pin == NULL_PIN)
      return;
    digitalWrite(_pin, level);
    _level = level;
  }

  void toggle() {
    set(_level != HIGH);
  }

private:
  pin_t _pin;
  uint8_t _level = 2; // i.e. neither HIGH nor LOW
};

} // namespace ArduinoContinuousStepper