#pragma once

#include "Clock.hpp"
#include "EventLog.hpp"

class TimerOne : ClockWatcher {
public:
  using callback_t = void (*)();

  void initialize() {
    logEvent("TimerOne::initialize()");
  }

  void attachInterrupt(callback_t cb) {
    logEvent("TimerOne::attachInterrupt()");
    _callback = cb;
  }

  void setPeriod(unsigned long period) {
    logEvent("TimerOne::setPeriod(%lu)", period);
    _period = period;
  }

  void start() {
    logEvent("TimerOne::start()");
    theClock.addWatcher(this);
  }

  void stop() {
    logEvent("TimerOne::stop()");
    theClock.removeWatcher(this);
  }

private:
  void timeChanged(unsigned long time) override {
    if (time - _lastTime >= _period) {
      _lastTime = time;
      if (_callback)
        _callback();
    }
  }

  unsigned long _period = 0;
  unsigned long _lastTime = 0;
  callback_t _callback = nullptr;
};