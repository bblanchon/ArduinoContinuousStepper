#pragma once

#include "ContinuousStepperBase.h"

struct NullTimer {
  void setPeriod(unsigned long) {}
  void setClient(TimerClient *) {}
};

class ContinuousStepper : public ContinuousStepperBase<NullTimer> {
public:
  ContinuousStepper(pin_t stepPin, pin_t dirPin, pin_t enablePin = NULL_PIN)
      : ContinuousStepperBase(NullTimer(), stepPin, dirPin, enablePin) {}

  void loop() {
    tick();
  }
};