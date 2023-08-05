#pragma once

#include "Clock.hpp"
#include "EventLog.hpp"

#include <functional>

namespace TeensyTimerTool {

class PeriodicTimer : ClockWatcher {
public:
  using callback_t = std::function<void()>;

  void begin(callback_t callback, unsigned long period, bool start = true) {
    logEvent("PeriodicTimer::begin(%lu, %s)", period, start ? "true" : "false");
    _callback = callback;
    _period = period;
    if (start)
      theClock.addWatcher(this);
  }

  void attachInterrupt(callback_t cb) {
    logEvent("PeriodicTimer::attachInterrupt()");
    _callback = cb;
  }

  void setPeriod(unsigned long period) {
    logEvent("PeriodicTimer::setPeriod(%lu)", period);
    _period = period;
  }

  void start() {
    logEvent("PeriodicTimer::start()");
    theClock.addWatcher(this);
  }

  void stop() {
    logEvent("PeriodicTimer::stop()");
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

} // namespace TeensyTimerTool