#pragma once

#include <TimerOne.h> // https://github.com/PaulStoffregen/TimerOne

#include "ContinuousStepper_Timer.h"
#include "TimerOneAdapter.hpp"

struct ContinuousStepper_Timer1 : ContinuousStepper_Timer<TimerOneAdapter<TimerOne>> {
  ContinuousStepper_Timer1(pin_t stepPin, pin_t dirPin, pin_t enablePin = ContinuousStepper::NULL_PIN)
      : ContinuousStepper_Timer(TimerOneAdapter<TimerOne>(), stepPin, dirPin, enablePin) {}
};