#pragma once

#include <ContinuousStepper/Tickers/OscillatorTicker.hpp>

namespace ArduinoContinuousStepper {

class AwfOscillator {
public:
  void init(pin_t pin) {
    pinMode(pin, OUTPUT);
    _pin = pin;
  }

  void start(unsigned int frequency) {
    analogWriteFrequency(_pin, frequency);
    if (!_active) {
      analogWrite(_pin, 128);
      _active = true;
    }
  }

  void stop() {
    analogWrite(_pin, 0);
    _active = false;
  }

private:
  bool _active = false;
  pin_t _pin = NULL_PIN;
};

using AwfTicker = OscillatorTicker<AwfOscillator>;

} // namespace ArduinoContinuousStepper
