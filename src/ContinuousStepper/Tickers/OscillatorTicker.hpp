#pragma once

#include <ContinuousStepper.hpp>

namespace ArduinoContinuousStepper {

template <class TOscillator>
class OscillatorTicker : StepperTicker {
  using time_t = unsigned long;

public:
  void loop() {
    if (!period_)
      return;

    time_t now = micros();
    time_t elapsed = now - periodStart_;

    if (elapsed >= period_) {
      tick();
      periodStart_ = now;
    }
  }

protected:
  using StepperTicker::StepperTicker;

  void init() {}

  void setPin(uint8_t pin) {
    pinMode(pin, OUTPUT);
    oscillator_.init(pin);
  }

  void setPeriod(unsigned long period) {
    if (period) {
      oscillator_.start(1e6 / period);
    } else {
      oscillator_.stop();
    }
    period_ = period;
  }

private:
  TOscillator oscillator_;
  time_t period_ = 0, periodStart_ = 0;
};

template <class TStepper, class TOscillator>
class ContinuousStepper<TStepper, OscillatorTicker<TOscillator>> {
  ContinuousStepper() = delete; // This ticker only supports StepperDriver
};

template <class TOscillator>
class ContinuousStepper<StepperDriver, OscillatorTicker<TOscillator>>
    : public ContinuousStepperImpl<StepperDriver, OscillatorTicker<TOscillator>> {
  using TTicker = OscillatorTicker<TOscillator>;
  using TBase = ContinuousStepperImpl<StepperDriver, TTicker>;

public:
  void begin(uint8_t stepPin, uint8_t dirPin) {
    TTicker::setPin(stepPin);
    TBase::begin(nullPin, dirPin);
  }
};

} // namespace ArduinoContinuousStepper
