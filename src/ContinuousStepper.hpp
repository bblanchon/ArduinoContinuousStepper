#pragma once

#include "ContinuousStepperImpl.hpp"

namespace ArduinoContinuousStepper {

class StepperTicker {
public:
  StepperTicker(TickListener *listener) : _listener(listener) {}

  void tick() {
    _listener->tick();
  }

  void begin() {}

private:
  TickListener *_listener;
};

class LoopTicker : public StepperTicker {
public:
  using time_t = unsigned long;

  LoopTicker(TickListener *listener) : StepperTicker(listener) {}

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

template <class TStepper>
class ContinuousStepper<TStepper, LoopTicker> : public ContinuousStepperImpl<TStepper, LoopTicker> {
  using TBase = ContinuousStepperImpl<TStepper, LoopTicker>;

public:
  void loop() {
    TBase::_ticker.loop();
  }
};

} // namespace ArduinoContinuousStepper
