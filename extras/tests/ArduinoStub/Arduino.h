#pragma once

#include <math.h>
#include <stdint.h>

enum { LOW, HIGH };
enum { INPUT, OUTPUT };

void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t val);

unsigned long micros();

template <typename T>
T abs(T a) {
  return a > 0 ? a : -a;
}

template <typename T>
T max(T a, T b) {
  return a > b ? a : b;
}

template <typename T>
T min(T a, T b) {
  return a < b ? a : b;
}

// ---------------------- TEST STUFF BELOW ----------------------

#include "EventLog.hpp"

extern EventLog arduino_log;

void set_micros(unsigned long);
