#pragma once

#include <TimerOne.h> // https://github.com/PaulStoffregen/TimerOne

#include "ContinuousStepperBase.h"
#include "TimerOneAdapter.hpp"

namespace ArduinoContinuousStepper {

struct ContinuousStepper_Timer1 : ContinuousStepperBase<TimerOneAdapter<TimerOne>> {
  ContinuousStepper_Timer1(pin_t stepPin, pin_t dirPin, pin_t enablePin = NULL_PIN)
      : ContinuousStepperBase(TimerOneAdapter<TimerOne>(), stepPin, dirPin, enablePin) {}
};

}; // namespace ArduinoContinuousStepper

using ArduinoContinuousStepper::ContinuousStepper_Timer1;