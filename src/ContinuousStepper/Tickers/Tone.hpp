#pragma once

#include <ContinuousStepper/Tickers/OscillatorTicker.hpp>

namespace ArduinoContinuousStepper {

class ToneOscillator {
public:
  void begin(pin_t pin) {
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
  pin_t _pin = NULL_PIN;
};

using ToneTicker = OscillatorTicker<ToneOscillator>;

} // namespace ArduinoContinuousStepper