#pragma once

#include <TeensyTimerTool.h> // https://github.com/luni64/TeensyTimerTool

#include <ContinuousStepper.hpp>

namespace ArduinoContinuousStepper {

class TeensyTimerToolTicker : StepperTicker {
protected:
  TeensyTimerToolTicker(TickListener *listener, TeensyTimerTool::PeriodicTimer *timer)
      : StepperTicker(listener), _timer(timer) {}

  TeensyTimerToolTicker(const TeensyTimerToolTicker &) = delete;

  ~TeensyTimerToolTicker() {
    _timer->stop();
  }

  void begin() {
    _timer->begin([this]() { tick(); }, 1000, false);
  }

  void setPeriod(unsigned long period) {
    _timer->stop();
    if (period) {
      _timer->setPeriod(period);
      _timer->start();
    }
  }

private:
  TeensyTimerTool::PeriodicTimer *_timer;
};

template <class TStepper>
class ContinuousStepper<TStepper, TeensyTimerToolTicker>
    : public ContinuousStepperImpl<TStepper, TeensyTimerToolTicker> {

public:
  using TTicker = TeensyTimerToolTicker;
  using TBase = ContinuousStepperImpl<TStepper, TTicker>;

  ContinuousStepper(TeensyTimerTool::PeriodicTimer &timer) : TBase(&timer) {}
};
}; // namespace ArduinoContinuousStepper
