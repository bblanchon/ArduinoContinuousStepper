#pragma once

#include "ContinuousStepper.h"

class ContinuousStepper_Timer1 {
public:
  using float_t = ContinuousStepper::float_t;
  using time_t = ContinuousStepper::time_t;
  using pin_t = ContinuousStepper::pin_t;

  ContinuousStepper_Timer1(pin_t stepPin, pin_t dirPin, pin_t enablePin = ContinuousStepper::NULL_PIN);

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
  static void configureTimer();
  static void interruptHandler();

  static ContinuousStepper *_stepper;
  static time_t _timerPeriod;
};