#pragma once

#include <TimerThree.h> // https://github.com/PaulStoffregen/TimerThree

#include "ContinuousStepperBase.h"
#include "TimerOneAdapter.hpp"

namespace ArduinoContinuousStepper {

struct ContinuousStepper_Timer3 : ContinuousStepperBase<ArduinoContinuousStepper::TimerOneAdapter<TimerThree>> {
  ContinuousStepper_Timer3(pin_t stepPin, pin_t dirPin, pin_t enablePin = NULL_PIN)
      : ContinuousStepperBase(ArduinoContinuousStepper::TimerOneAdapter<TimerThree>(), stepPin, dirPin, enablePin) {}
};

} // namespace ArduinoContinuousStepper

using ArduinoContinuousStepper::ContinuousStepper_Timer3;