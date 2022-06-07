#pragma once

#include <TimerThree.h> // https://github.com/PaulStoffregen/TimerThree

#include "ContinuousStepper_Timer.h"
#include "TimerOneAdapter.hpp"

struct ContinuousStepper_Timer3 : ContinuousStepper_Timer<TimerOneAdapter<TimerThree>> {
  ContinuousStepper_Timer3(pin_t stepPin, pin_t dirPin, pin_t enablePin = ContinuousStepper::NULL_PIN)
      : ContinuousStepper_Timer(TimerOneAdapter<TimerThree>(), stepPin, dirPin, enablePin) {}
};