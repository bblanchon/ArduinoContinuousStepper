#pragma once

#include "ContinuousStepperBase.h"

namespace ArduinoContinuousStepper {
struct NullTimer {
  void begin(TimerClient *) {}
  void setPeriod(unsigned long) {}
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