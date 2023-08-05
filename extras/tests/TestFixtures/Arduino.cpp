#include "Arduino.h"
#include "Clock.hpp"
#include "EventLog.hpp"

unsigned long micros() {
  return theClock.get();
}

void pinMode(uint8_t pin, uint8_t mode) {
  logEvent("pinMode(%d, %s)", pin, mode ? "OUTPUT" : "INPUT");
}

void digitalWrite(uint8_t pin, uint8_t val) {
  logEvent("digitalWrite(%d, %s)", pin, val ? "HIGH" : "LOW");
}

void tone(uint8_t pin, unsigned int frequency) {
  logEvent("tone(%d, %u)", pin, frequency);
}

void noTone(uint8_t pin) {
  logEvent("noTone(%d)");
}

void analogWrite(uint8_t pin, uint8_t val) {
  logEvent("analogWrite(%d, %d)", pin, val);
}

void analogWriteFrequency(uint8_t pin, float frequency) {
  logEvent("analogWriteFrequency(%d, %g)", pin, frequency);
}
