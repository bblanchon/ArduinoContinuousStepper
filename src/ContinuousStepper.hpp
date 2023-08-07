#pragma once

#include <ContinuousStepper/ContinuousStepperImpl.hpp>
#include <ContinuousStepper/StepperInterfaces.hpp>

namespace ArduinoContinuousStepper {

class StepperTicker {
protected:
  StepperTicker(TickListener *listener) : listener_(listener) {}

  void tick() {
    listener_->tick();
  }

private:
  TickListener *listener_;
};

class LoopTicker : StepperTicker {
public:
  void loop() {
    if (!tickPeriod_)
      return;

    time_t now = micros();
    time_t elapsed = now - lastTick_;

    if (elapsed >= tickPeriod_) {
      tick();
      lastTick_ = now;
    }
  }

protected:
  using time_t = unsigned long;

  LoopTicker(TickListener *listener) : StepperTicker(listener) {}

  void init() {}

  void setPeriod(unsigned long period) {
    tickPeriod_ = period;
  }

private:
  static time_t now() {
    return micros();
  }

  time_t tickPeriod_, lastTick_ = 0;
};

template <class TStepper, class TTicker = LoopTicker>
class ContinuousStepper : public ContinuousStepperImpl<TStepper, TTicker> {};

} // namespace ArduinoContinuousStepper
