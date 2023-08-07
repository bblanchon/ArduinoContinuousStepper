#pragma once

#include <TeensyTimerTool.h> // https://github.com/luni64/TeensyTimerTool

#include <ContinuousStepper.hpp>

namespace ArduinoContinuousStepper {

class TeensyTimerToolTicker : StepperTicker {
protected:
  TeensyTimerToolTicker(TickListener *listener, TeensyTimerTool::PeriodicTimer *timer)
      : StepperTicker(listener), timer_(timer) {}

  TeensyTimerToolTicker(const TeensyTimerToolTicker &) = delete;

  ~TeensyTimerToolTicker() {
    timer_->stop();
  }

  void init() {
    timer_->begin([this]() { tick(); }, 1000, false);
  }

  void setPeriod(unsigned long period) {
    timer_->stop();
    if (period) {
      timer_->setPeriod(period);
      timer_->start();
    }
  }

private:
  TeensyTimerTool::PeriodicTimer *timer_;
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
