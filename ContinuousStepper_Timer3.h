#pragma once

#include <TimerThree.h> // https://github.com/PaulStoffregen/TimerThree

#include "ContinuousStepperBase.h"
#include "TimerOneAdapter.hpp"

namespace ArduinoContinuousStepper {

struct ContinuousStepper_Timer3 : ContinuousStepperBase<ArduinoContinuousStepper::TimerOneAdapter<TimerThree>> {
  ContinuousStepper_Timer3() : ContinuousStepperBase(ArduinoContinuousStepper::TimerOneAdapter<TimerThree>()) {}
};

} // namespace ArduinoContinuousStepper

using ArduinoContinuousStepper::ContinuousStepper_Timer3;