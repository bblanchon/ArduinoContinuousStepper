#pragma once

#include "ContinuousStepperBase.h"

namespace ArduinoContinuousStepper {
class ContinuousStepper : public ContinuousStepperBase {
public:
  void loop() {
    tick();
  }

protected:
  void setPeriod(unsigned long) override {}
};
} // namespace ArduinoContinuousStepper

using ArduinoContinuousStepper::ContinuousStepper;