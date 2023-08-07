#pragma once

#include <ContinuousStepper.hpp>

namespace ArduinoContinuousStepper {

template <class TOscillator>
class OscillatorTicker : public StepperTicker {
public:
  using time_t = unsigned long;
  using StepperTicker::StepperTicker;

  void setPin(pin_t pin) {
    pinMode(pin, OUTPUT);
    _oscillator.begin(pin);
  }

  void setPeriod(unsigned long period) {
    if (period) {
      _oscillator.start(1e6 / period);
    } else {
      _oscillator.stop();
    }
    _period = period;
  }

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
  void begin(pin_t stepPin, pin_t dirPin) {
    TBase::_ticker.setPin(stepPin);
    TBase::begin(NULL_PIN, dirPin);
  }

  void loop() {
    TBase::_ticker.loop();
  }

private:
  time_t _periodStart = 0;
};

} // namespace ArduinoContinuousStepper
