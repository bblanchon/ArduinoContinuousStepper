#pragma once

#include <ContinuousStepper/Tickers/OscillatorTicker.hpp>

namespace ArduinoContinuousStepper {

class AwfOscillator {
public:
  void init(uint8_t pin) {
    pinMode(pin, OUTPUT);
    pin_ = pin;
  }

  void start(frequency_t frequency) {
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

  frequency_t minFrequency() const {
    // The analogWriteFrequency function has a lower limit of a few Hz.
    // https://www.pjrc.com/teensy/td_pulse.html#frequency
    return 5;
  }

private:
  bool active_ = false;
  uint8_t pin_ = nullPin;
};

using AwfTicker = OscillatorTicker<AwfOscillator>;

} // namespace ArduinoContinuousStepper
