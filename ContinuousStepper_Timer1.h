#pragma once

#include <TimerOne.h> // https://github.com/PaulStoffregen/TimerOne

#include "ContinuousStepper.h"

template <typename TTimer>
class ContinuousStepper_Timer {
public:
  using float_t = ContinuousStepper::float_t;
  using time_t = ContinuousStepper::time_t;
  using pin_t = ContinuousStepper::pin_t;

  ContinuousStepper_Timer(pin_t stepPin, pin_t dirPin, pin_t enablePin = ContinuousStepper::NULL_PIN) {
    _stepper = new ContinuousStepper(stepPin, dirPin, enablePin);
    _timer.attachInterrupt(interruptHandler);
    _timerPeriod = _stepper->interval();
    _timer.initialize(_timerPeriod);
  }

  void powerOn() {
    _stepper->powerOn();
    configureTimer();
  }

  void powerOff() {
    _stepper->powerOff();
    configureTimer();
  }

  void spin(float_t speed) {
    _stepper->spin(speed);
    configureTimer();
  }

  void stop() {
    _stepper->stop();
    configureTimer();
  }

  float_t speed() const {
    return _stepper->speed();
  }

  time_t interval() const {
    return _stepper->interval();
  }

  void setAcceleration(float_t acceleration) {
    _stepper->setAcceleration(acceleration);
  }

  void setPulseWidth(time_t t) {
    _stepper->setPulseWidth(t);
  }

  bool isSpinning() const {
    return _stepper->isSpinning();
  }

private:
  static void configureTimer() {
    if (_timerPeriod == _stepper->interval())
      return;

    _timer.stop();
    _timerPeriod = _stepper->interval();
    if (_timerPeriod) {
      _timer.setPeriod(_timerPeriod);
      _timer.start();
    }
  }

  static void interruptHandler() {
    _stepper->loop();
    configureTimer();
  }

  static ContinuousStepper *_stepper;
  static time_t _timerPeriod;
  static TTimer _timer;
};

template <typename TTimer>
ContinuousStepper *ContinuousStepper_Timer<TTimer>::_stepper;

template <typename TTimer>
ContinuousStepper::time_t ContinuousStepper_Timer<TTimer>::_timerPeriod;

template <typename TTimer>
TTimer ContinuousStepper_Timer<TTimer>::_timer;

typedef ContinuousStepper_Timer<TimerOne> ContinuousStepper_Timer1;