#pragma once

#include <Arduino.h>

namespace ArduinoContinuousStepper {

struct TimerClient {
  virtual void tick() = 0;
};

template <typename TTimer>
class ContinuousStepperBase : TimerClient {
public:
  typedef unsigned long time_t;
  typedef float float_t;
  typedef uint8_t pin_t;

  static const pin_t NULL_PIN = 255;
  static constexpr float_t MIN_SPEED = 0.001;

  ContinuousStepperBase(const TTimer &timer, pin_t stepPin, pin_t dirPin, pin_t enablePin = NULL_PIN)
      : _timer(timer), _stepPin(stepPin), _dirPin(dirPin), _enablePin(enablePin) {
    _timer.setClient(this);
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    if (enablePin != NULL_PIN)
      pinMode(enablePin, OUTPUT);
    powerOn();
  }

  void powerOn() {
    if (_status != OFF)
      return;

    if (_enablePin != NULL_PIN)
      digitalWrite(_enablePin, HIGH);

    if (abs(_targetSpeed) > MIN_SPEED)
      startMoving();
    else
      _status = WAIT;
  }

  void powerOff() {
    if (_enablePin != NULL_PIN)
      digitalWrite(_enablePin, LOW);

    _status = OFF;
    _currentSpeed = 0;
    _interval = 0;
  }

  void spin(float_t speed) {
    _targetSpeed = speed;

    if (_status == WAIT)
      startMoving();
  }

  void stop() {
    _targetSpeed = 0;
  }

  float_t speed() const {
    return _currentSpeed;
  }

  time_t interval() const {
    return _interval;
  }

  void setAcceleration(float_t acceleration) {
    _acceleration = acceleration;
  }

  bool isSpinning() const {
    return _status == STEP || _status == SKIP;
  }

protected:
  void tick() override {
    if (_status == WAIT || _status == OFF)
      return;

    time_t t = now();
    time_t elapsed = t - _lastTick;

    if (elapsed >= _interval) {
      if (_stepLevel == HIGH) {
        writeStep(LOW);
      } else {

        if (_status == STEP) {
          writeDir(_currentSpeed >= 0 ? HIGH : LOW);
          writeStep(HIGH);
        }

        updateSpeed();
      }

      _lastTick = t;
    }
  }

private:
  void writeStep(bool level) {
    digitalWrite(_stepPin, level);
    _stepLevel = level;
  }

  void writeDir(bool level) {
    digitalWrite(_dirPin, level);
  }

  void startMoving() {
    incrementSpeed(sqrt(_acceleration));
    _lastTick = now();
  }

  void updateSpeed() {
    incrementSpeed(_acceleration * _interval * 2 / oneSecond);
  }

  void incrementSpeed(float_t speedIncrement) {
    if (_targetSpeed > _currentSpeed) {
      _currentSpeed = min(_currentSpeed + speedIncrement, _targetSpeed);
    }

    if (_targetSpeed < _currentSpeed) {
      _currentSpeed = max(_currentSpeed - speedIncrement, _targetSpeed);
    }

    if (abs(_currentSpeed) > MIN_SPEED) {
      setInterval(oneSecond / abs(_currentSpeed) / 2);
      _status = STEP;
    } else if (abs(_targetSpeed) > MIN_SPEED) {
      // crossing the zero on the speed graph
      _status = SKIP;
    } else {
      // stop moving
      _status = WAIT;
      setInterval(0);
    }
  }

  void setInterval(time_t interval) {
    if (interval != _interval) {
      _interval = interval;
      _timer.setPeriod(interval);
    }
  }

  static time_t now() {
    return micros();
  }

  static const time_t oneSecond = 1e6;

  TTimer _timer;
  pin_t _stepPin, _dirPin, _enablePin;
  time_t _lastTick = 0, _interval = 0;
  float_t _targetSpeed = 0, _currentSpeed = 0, _acceleration = 1000;
  bool _stepLevel = false;

  enum Status {
    OFF,
    WAIT,
    STEP,
    SKIP,
  };

  Status _status = OFF;
};

} // namespace ArduinoContinuousStepper
