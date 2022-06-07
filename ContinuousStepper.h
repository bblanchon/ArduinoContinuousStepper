#pragma once

#include "ContinuousStepperBase.h"

namespace ArduinoContinuousStepper {
struct NullTimer {
  void setPeriod(unsigned long) {}
  void setClient(TimerClient *) {}
};

class ContinuousStepper : public ContinuousStepperBase<NullTimer> {
public:
  ContinuousStepper() : ContinuousStepperBase(NullTimer()) {}

  void loop() {
    tick();
  }
};
} // namespace ArduinoContinuousStepper

using ArduinoContinuousStepper::ContinuousStepper;