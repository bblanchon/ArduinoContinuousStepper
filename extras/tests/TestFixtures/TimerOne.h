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
    callback_ = cb;
  }

  void setPeriod(unsigned long period) {
    logEvent("TimerOne::setPeriod(%lu)", period);
    period_ = period;
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