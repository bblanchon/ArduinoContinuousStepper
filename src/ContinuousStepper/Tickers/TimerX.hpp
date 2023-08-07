#pragma once

namespace ArduinoContinuousStepper {

template <class TTimer>
class TimerXTicker : StepperTicker {
protected:
  using StepperTicker::StepperTicker;

  ~TimerXTicker() {
    _timer.stop();
  }

  void init() {
    _instance = this;
    _timer.initialize();
    _timer.attachInterrupt(interruptHandler);
  }

  void setPeriod(unsigned long period) {
    _timer.stop();
    if (period) {
      _timer.setPeriod(period);
      _timer.start();
    }
  }

private:
  static void interruptHandler() {
    _instance->tick();
  }

  static TTimer _timer;
  static TimerXTicker *_instance;
};

template <class TTimer>
TTimer TimerXTicker<TTimer>::_timer;

template <class TTimer>
TimerXTicker<TTimer> *TimerXTicker<TTimer>::_instance;

} // namespace ArduinoContinuousStepper