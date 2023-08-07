#pragma once

#include "ContinuousStepperImpl.hpp"

namespace ArduinoContinuousStepper {

class StepperTicker {
protected:
  StepperTicker(TickListener *listener) : _listener(listener) {}

  void tick() {
    _listener->tick();
  }

private:
  TickListener *_listener;
};

class LoopTicker : StepperTicker {
public:
  void loop() {
    if (!_tickPeriod)
      return;

    time_t now = micros();
    time_t elapsed = now - _lastTick;

    if (elapsed >= _tickPeriod) {
      tick();
      _lastTick = now;
    }
  }

protected:
  using time_t = unsigned long;

  LoopTicker(TickListener *listener) : StepperTicker(listener) {}

  void begin() {}

  void setPeriod(unsigned long period) {
    _tickPeriod = period;
  }

private:
  static time_t now() {
    return micros();
  }

  time_t _tickPeriod, _lastTick = 0;
};

template <class TStepper, class TTicker = LoopTicker>
class ContinuousStepper : public ContinuousStepperImpl<TStepper, TTicker> {};

} // namespace ArduinoContinuousStepper
