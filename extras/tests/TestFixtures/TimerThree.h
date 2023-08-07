#pragma once

#include "Clock.hpp"
#include "EventLog.hpp"

class TimerThree : ClockWatcher {
public:
  using callback_t = void (*)();

  void initialize() {
    logEvent("TimerThree::initialize()");
  }

  void attachInterrupt(callback_t cb) {
    logEvent("TimerThree::attachInterrupt()");
    callback_ = cb;
  }

  void setPeriod(unsigned long period) {
    logEvent("TimerThree::setPeriod(%lu)", period);
    period_ = period;
  }

  void start() {
    logEvent("TimerThree::start()");
    theClock.addWatcher(this);
  }

  void stop() {
    logEvent("TimerThree::stop()");
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