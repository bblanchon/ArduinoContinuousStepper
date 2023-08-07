#pragma once

#include <TimerThree.h> // https://github.com/PaulStoffregen/TimerThree

#include <ContinuousStepper.h>
#include <ContinuousStepper/Tickers/TimerX.hpp>

namespace ArduinoContinuousStepper {

using TimerThreeTicker = TimerXTicker<TimerThree>;

} // namespace ArduinoContinuousStepper

using ArduinoContinuousStepper::TimerThreeTicker;
