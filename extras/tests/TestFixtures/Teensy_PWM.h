#pragma once

#include "EventLog.hpp"

// https://github.com/khoih-prog/Teensy_PWM

class Teensy_PWM {
public:
  Teensy_PWM(uint8_t pin, float frequency, float dutycycle) {
    logEvent("Teensy_PWM::Teensy_PWM(%d, %d, %d)", pin, static_cast<int>(frequency), static_cast<int>(dutycycle));
  }

  void setPWM(uint8_t pin, float frequency, float dutycycle) {
    logEvent("Teensy_PWM::setPWM(%d, %d, %d)", pin, static_cast<int>(frequency), static_cast<int>(dutycycle));
  }
};