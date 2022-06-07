#pragma once

namespace ArduinoContinuousStepper {
template <typename TTimer>
class TimerOneAdapter {
public:
  TimerOneAdapter() {
    _timer.attachInterrupt(interruptHandler);
  }

  void begin(TimerClient *client) {
    _client = client;
  }

  void setPeriod(unsigned long interval) {
    _timer.stop();
    if (interval) {
      _timer.setPeriod(interval);
      _timer.start();
    }
  }

private:
  static void interruptHandler() {
    if (_client)
      _client->tick();
  }

  static TTimer _timer;
  static TimerClient *_client;
};

template <typename TTimer>
TTimer TimerOneAdapter<TTimer>::_timer;

template <typename TTimer>
TimerClient *TimerOneAdapter<TTimer>::_client;

} // namespace ArduinoContinuousStepper