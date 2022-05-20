#include "ContinuousStepper_Timer1.h"

#include <TimerOne.h> // https://github.com/PaulStoffregen/TimerOne

ContinuousStepper *ContinuousStepper_Timer1::_stepper = 0;
ContinuousStepper::time_t ContinuousStepper_Timer1::_timerPeriod = 0;

ContinuousStepper_Timer1::ContinuousStepper_Timer1(pin_t stepPin, pin_t dirPin, pin_t enablePin) {
  _stepper = new ContinuousStepper(stepPin, dirPin, enablePin);
  Timer1.attachInterrupt(interruptHandler);
  _timerPeriod = _stepper->interval();
  Timer1.initialize(_timerPeriod);
}

void ContinuousStepper_Timer1::configureTimer() {
  if (_timerPeriod == _stepper->interval())
    return;

  Timer1.stop();
  _timerPeriod = _stepper->interval();
  if (_timerPeriod) {
    Timer1.setPeriod(_timerPeriod);
    Timer1.start();
  }
}

void ContinuousStepper_Timer1::interruptHandler() {
  _stepper->loop();
  configureTimer();
}
