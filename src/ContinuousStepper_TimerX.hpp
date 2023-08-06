#pragma once

namespace ArduinoContinuousStepper {
template <typename TTimer>
class ContinuousStepper_TimerX : public ContinuousStepperBase {
public:
  ~ContinuousStepper_TimerX() {
    _timer.stop();
  }

protected:
  void initialize() override {
    _instance = this;
    _timer.initialize();
    _timer.attachInterrupt(interruptHandler);
  }

  void setPeriod(unsigned long period) override {
    _timer.stop();
    if (period) {
      _timer.setPeriod(period);
      _timer.start();
    }
  }

  bool needsDoubleSpeed() const override {
    return true;
  }

private:
  static void interruptHandler() {
    _instance->tick();
  }

  static TTimer _timer;
  static ContinuousStepper_TimerX *_instance;
};

template <typename TTimer>
TTimer ContinuousStepper_TimerX<TTimer>::_timer;

template <typename TTimer>
ContinuousStepper_TimerX<TTimer> *ContinuousStepper_TimerX<TTimer>::_instance;

} // namespace ArduinoContinuousStepper