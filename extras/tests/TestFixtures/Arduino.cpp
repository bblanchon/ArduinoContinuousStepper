#include <Arduino.h>

#include <cstdio>
#include <string>
#include <vector>

static unsigned long _micros = 0;
EventLog arduino_log;

void set_micros(unsigned long t) {
  _micros = t;
}

unsigned long micros() {
  return _micros;
}

void pinMode(uint8_t pin, uint8_t mode) {
  arduino_log.add(_micros, "pinMode(%d, %s)", pin, mode ? "OUTPUT" : "INPUT");
}

void digitalWrite(uint8_t pin, uint8_t val) {
  arduino_log.add(_micros, "digitalWrite(%d, %s)", pin, val ? "HIGH" : "LOW");
}
