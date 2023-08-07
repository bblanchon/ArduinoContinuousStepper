#pragma once

#include <TimerOne.h> // https://github.com/PaulStoffregen/TimerOne

#include <ContinuousStepper/Tickers/TimerX.hpp>

namespace ArduinoContinuousStepper {

using TimerOneTicker = TimerXTicker<TimerOne>;

}; // namespace ArduinoContinuousStepper
