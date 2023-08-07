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
    callback_ = callback;
    period_ = period;
    if (start)
      theClock.addWatcher(this);
  }

  void attachInterrupt(callback_t cb) {
    logEvent("PeriodicTimer::attachInterrupt()");
    callback_ = cb;
  }

  void setPeriod(unsigned long period) {
    logEvent("PeriodicTimer::setPeriod(%lu)", period);
    period_ = period;
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
    if (time - lastTime_ >= period_) {
      lastTime_ = time;
      if (callback_)
        callback_();
    }
  }

  unsigned long period_ = 0;
  unsigned long lastTime_ = 0;
  callback_t callback_ = nullptr;
};

} // namespace TeensyTimerTool