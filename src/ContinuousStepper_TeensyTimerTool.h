#pragma once

#include <TeensyTimerTool.h> // https://github.com/luni64/TeensyTimerTool

#include "ContinuousStepperBase.h"

namespace ArduinoContinuousStepper {

class ContinuousStepper_TeensyTimerTool : public ContinuousStepperBase {

public:
  ContinuousStepper_TeensyTimerTool(TeensyTimerTool::PeriodicTimer &timer) : _timer(&timer) {}

protected:
  void initialize() override {
    _timer->begin([this]() { tick(); }, 1000, false);
  }

  void setPeriod(unsigned long period) override {
    _timer->stop();
    if (period) {
      _timer->setPeriod(period / 2);
      _timer->start();
    }
  }

private:
  TeensyTimerTool::PeriodicTimer *_timer;
};

}; // namespace ArduinoContinuousStepper

using ArduinoContinuousStepper::ContinuousStepper_TeensyTimerTool;