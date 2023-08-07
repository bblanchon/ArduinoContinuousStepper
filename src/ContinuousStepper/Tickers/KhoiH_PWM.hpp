#pragma once

#include <ContinuousStepper/Tickers/OscillatorTicker.hpp>

namespace ArduinoContinuousStepper {

template <class KhoiH_PWM>
class KhoihOscillator {
public:
  ~KhoihOscillator() {
    delete _pwm;
  }

  void init(uint8_t pin) {
    _pin = pin;
    _pwm = new KhoiH_PWM(pin, 500, 0);
  }

  void start(unsigned int frequency) {
    _pwm->setPWM(_pin, frequency, 50);
  }

  void stop() {
    _pwm->setPWM(_pin, 500, 0);
  }

private:
  uint8_t _pin = NULL_PIN;
  KhoiH_PWM *_pwm = nullptr;
};

template <class KhoiH_PWM>
using KhoihTicker = OscillatorTicker<KhoihOscillator<KhoiH_PWM>>;

} // namespace ArduinoContinuousStepper
