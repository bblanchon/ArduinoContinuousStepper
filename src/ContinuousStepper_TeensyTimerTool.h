#pragma once

#include <TeensyTimerTool.h> // https://github.com/luni64/TeensyTimerTool

#include "ContinuousStepperBase.h"
#include "TimerOneAdapter.hpp"

namespace ArduinoContinuousStepper {

class TeensyTimerToolAdapter {
public:
  TeensyTimerToolAdapter(TeensyTimerTool::PeriodicTimer &timer) : _timer(&timer) {}

  void begin(TimerClient *client) {

    _timer->begin([client]() { client->tick(); }, 1000, false);
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

struct ContinuousStepper_TeensyTimerTool : ContinuousStepperBase<TeensyTimerToolAdapter> {
  ContinuousStepper_TeensyTimerTool(TeensyTimerTool::PeriodicTimer &timer)
      : ContinuousStepperBase(TeensyTimerToolAdapter(timer)) {}
};

}; // namespace ArduinoContinuousStepper

using ArduinoContinuousStepper::ContinuousStepper_TeensyTimerTool;