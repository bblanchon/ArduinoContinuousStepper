#pragma once

#include <ContinuousStepper/Tickers/OscillatorTicker.hpp>

namespace ArduinoContinuousStepper {

class AwfOscillator {
public:
  void init(uint8_t pin) {
    pinMode(pin, OUTPUT);
    pin_ = pin;
  }

  void start(unsigned int frequency) {
    analogWriteFrequency(pin_, frequency);
    if (!active_) {
      analogWrite(pin_, 128);
      active_ = true;
    }
  }

  void stop() {
    analogWrite(pin_, 0);
    active_ = false;
  }

private:
  bool active_ = false;
  uint8_t pin_ = nullPin;
};

using AwfTicker = OscillatorTicker<AwfOscillator>;

} // namespace ArduinoContinuousStepper
