#pragma once

#include <TimerThree.h> // https://github.com/PaulStoffregen/TimerThree

#include "ContinuousStepperBase.h"
#include "ContinuousStepper_TimerX.hpp"

namespace ArduinoContinuousStepper {

using ContinuousStepper_Timer3 = ContinuousStepper_TimerX<TimerThree>;

} // namespace ArduinoContinuousStepper

using ArduinoContinuousStepper::ContinuousStepper_Timer3;