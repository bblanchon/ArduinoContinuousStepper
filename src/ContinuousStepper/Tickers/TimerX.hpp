#pragma once

namespace ArduinoContinuousStepper {

template <class TTimer>
class TimerXTicker : StepperTicker {
protected:
  using StepperTicker::StepperTicker;

  ~TimerXTicker() {
    timer_.stop();
  }

  void init() {
    instance_ = this;
    timer_.initialize();
    timer_.attachInterrupt(interruptHandler);
  }

  void setPeriod(unsigned long period) {
    timer_.stop();
    if (period) {
      timer_.setPeriod(period);
      timer_.start();
    }
  }

private:
  static void interruptHandler() {
    instance_->tick();
  }

  static TTimer timer_;
  static TimerXTicker *instance_;
};

template <class TTimer>
TTimer TimerXTicker<TTimer>::timer_;

template <class TTimer>
TimerXTicker<TTimer> *TimerXTicker<TTimer>::instance_;

} // namespace ArduinoContinuousStepper