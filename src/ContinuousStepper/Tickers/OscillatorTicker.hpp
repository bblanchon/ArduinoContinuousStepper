#pragma once

#include <ContinuousStepper.hpp>

namespace ArduinoContinuousStepper {

template <class TOscillator>
class OscillatorTicker : StepperTicker {
  using time_t = unsigned long;

public:
  void loop() {
    if (!_period)
      return;

    time_t now = micros();
    time_t elapsed = now - _periodStart;

    if (elapsed >= _period) {
      tick();
      _periodStart = now;
    }
  }

protected:
  using StepperTicker::StepperTicker;

  void init() {}

  void setPin(uint8_t pin) {
    pinMode(pin, OUTPUT);
    _oscillator.init(pin);
  }

  void setPeriod(unsigned long period) {
    if (period) {
      _oscillator.start(1e6 / period);
    } else {
      _oscillator.stop();
    }
    _period = period;
  }

private:
  TOscillator _oscillator;
  time_t _period = 0, _periodStart = 0;
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
    TBase::begin(NULL_PIN, dirPin);
  }
};

} // namespace ArduinoContinuousStepper
