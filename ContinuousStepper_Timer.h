#pragma once

#include "ContinuousStepper.h"

struct TimerClient {
  virtual void tick() = 0;
};

template <typename TTimer>
class ContinuousStepper_Timer : public ContinuousStepperBase, TimerClient {
public:
  ContinuousStepper_Timer(TTimer timer, pin_t stepPin, pin_t dirPin, pin_t enablePin = ContinuousStepper::NULL_PIN)
      : ContinuousStepperBase(stepPin, dirPin, enablePin), _timer(timer) {
    _timer.setClient(this);
  }

private:
  void configureTimer(time_t interval) override {
    _timer.setPeriod(interval);
  }

  void tick() override {
    loop();
  }

  TTimer _timer;
};
