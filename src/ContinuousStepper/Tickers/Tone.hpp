#pragma once

#include <ContinuousStepper/Tickers/OscillatorTicker.hpp>

namespace ArduinoContinuousStepper {

class ToneOscillator {
public:
  void init(uint8_t pin) {
    pinMode(pin, OUTPUT);
    _pin = pin;
  }

  void start(unsigned int frequency) {
    tone(_pin, frequency);
  }

  void stop() {
    noTone(_pin);
  }

private:
  uint8_t _pin = NULL_PIN;
};

using ToneTicker = OscillatorTicker<ToneOscillator>;

} // namespace ArduinoContinuousStepper