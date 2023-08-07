#pragma once

#include <ContinuousStepper/Tickers/OscillatorTicker.hpp>

namespace ArduinoContinuousStepper {

class ToneOscillator {
public:
  void init(uint8_t pin) {
    pinMode(pin, OUTPUT);
    pin_ = pin;
  }

  void start(unsigned int frequency) {
    tone(pin_, frequency);
  }

  void stop() {
    noTone(pin_);
  }

private:
  uint8_t pin_ = nullPin;
};

using ToneTicker = OscillatorTicker<ToneOscillator>;

} // namespace ArduinoContinuousStepper