#pragma once

#include <TimerThree.h> // https://github.com/PaulStoffregen/TimerThree

#include "ContinuousStepperBase.h"
#include "TimerOneAdapter.hpp"

struct ContinuousStepper_Timer3 : ContinuousStepperBase<TimerOneAdapter<TimerThree>> {
  ContinuousStepper_Timer3(pin_t stepPin, pin_t dirPin, pin_t enablePin = ContinuousStepper::NULL_PIN)
      : ContinuousStepperBase(TimerOneAdapter<TimerThree>(), stepPin, dirPin, enablePin) {}
};