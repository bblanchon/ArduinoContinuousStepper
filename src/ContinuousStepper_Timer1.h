#pragma once

#include <TimerOne.h> // https://github.com/PaulStoffregen/TimerOne

#include "ContinuousStepperBase.h"
#include "ContinuousStepper_TimerX.hpp"

namespace ArduinoContinuousStepper {

using ContinuousStepper_Timer1 = ContinuousStepper_TimerX<TimerOne>;

}; // namespace ArduinoContinuousStepper

using ArduinoContinuousStepper::ContinuousStepper_Timer1;