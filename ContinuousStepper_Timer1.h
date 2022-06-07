#pragma once

#include <TimerOne.h> // https://github.com/PaulStoffregen/TimerOne

#include "ContinuousStepperBase.h"
#include "TimerOneAdapter.hpp"

namespace ArduinoContinuousStepper {

struct ContinuousStepper_Timer1 : ContinuousStepperBase<TimerOneAdapter<TimerOne>> {
  ContinuousStepper_Timer1() : ContinuousStepperBase(TimerOneAdapter<TimerOne>()) {}
};

}; // namespace ArduinoContinuousStepper

using ArduinoContinuousStepper::ContinuousStepper_Timer1;