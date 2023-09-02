#pragma once

#include <ContinuousStepper/Tickers/OscillatorTicker.hpp>

namespace ArduinoContinuousStepper {

class ToneOscillator {
public:
  void init(uint8_t pin) {
    pinMode(pin, OUTPUT);
    pin_ = pin;
  }

  void start(frequency_t frequency) {
    tone(pin_, frequency);
  }

  void stop() {
    noTone(pin_);
  }

  frequency_t minFrequency() const {
#if defined(ARDUINO_ARCH_AVR)
    // It is not possible to generate tones lower than 31Hz
    // https://www.arduino.cc/reference/en/language/functions/advanced-io/tone/
    return 31;
#elif defined(ARDUINO_ARCH_NRF52)
    // For the nRF52, the allowed range for parameter `frequency` is `[20..25000]`.
    // https://github.com/adafruit/Adafruit_nRF52_Arduino/blob/1.5.0/cores/nRF5/Tone.h#L54
    return 20;
#else
    return 1;
#endif
  }

private:
  uint8_t pin_ = nullPin;
};

using ToneTicker = OscillatorTicker<ToneOscillator>;

} // namespace ArduinoContinuousStepper