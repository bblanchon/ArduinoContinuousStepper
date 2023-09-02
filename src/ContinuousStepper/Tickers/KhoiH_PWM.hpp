#pragma once

#include <ContinuousStepper/Tickers/OscillatorTicker.hpp>

namespace ArduinoContinuousStepper {

template <class KhoiH_PWM>
class KhoihOscillator {
public:
  ~KhoihOscillator() {
    delete pwm_;
  }

  void init(uint8_t pin) {
    pin_ = pin;
    pwm_ = new KhoiH_PWM(pin, 500, 0);
  }

  void start(frequency_t frequency) {
    pwm_->setPWM(pin_, frequency, 50);
  }

  void stop() {
    pwm_->setPWM(pin_, 500, 0);
  }

  frequency_t minFrequency() const {
    return 1;
  }

private:
  uint8_t pin_ = nullPin;
  KhoiH_PWM *pwm_ = nullptr;
};

template <class KhoiH_PWM>
using KhoihTicker = OscillatorTicker<KhoihOscillator<KhoiH_PWM>>;

} // namespace ArduinoContinuousStepper
