#pragma once

#include <Arduino.h>
#include <catch2/catch_test_macros.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>

#define CLEAR_ARDUINO_LOG() arduino_log.clear()

#define CHECK_ARDUINO_LOG(...)                                                                                         \
  {                                                                                                                    \
    EventLog _expected_log(__VA_ARGS__);                                                                               \
    if (arduino_log != _expected_log)                                                                                  \
      FAIL_CHECK(arduino_log.diff(_expected_log));                                                                     \
    else                                                                                                               \
      SUCCEED();                                                                                                       \
  }

template <typename TContinuousStepper>
inline void loop_till(TContinuousStepper &stepper, unsigned long end_time, unsigned long step = 1) {
  for (unsigned long t = micros(); t <= end_time; t += step) {
    set_micros(t);
    stepper.loop();
  }
}

template <typename TContinuousStepper>
inline void loop_for(TContinuousStepper &stepper, unsigned long duration, unsigned long step = 1) {
  loop_till(stepper, micros() + duration, step);
}
