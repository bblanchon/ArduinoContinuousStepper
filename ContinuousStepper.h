#pragma once

#include <Arduino.h>

class ContinuousStepper {
public:
  typedef unsigned long time_t;
  typedef float float_t;
  typedef uint8_t pin_t;

  static const pin_t NULL_PIN = 255;
  static constexpr float_t MIN_SPEED = 0.001;

  ContinuousStepper(pin_t stepPin, pin_t dirPin, pin_t enablePin = NULL_PIN)
      : _stepPin(stepPin), _dirPin(dirPin), _enablePin(enablePin), _lastTick(0), _interval(0), _targetSpeed(0),
        _currentSpeed(0), _acceleration(1000), _status(OFF), _stepLevel(false) {
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    if (enablePin != NULL_PIN)
      pinMode(enablePin, OUTPUT);
    powerOn();
  }

  void loop() {
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
      _interval = oneSecond / abs(_currentSpeed) / 2;
      _status = STEP;
    } else if (abs(_targetSpeed) > MIN_SPEED) {
      // crossing the zero on the speed graph
      _status = SKIP;
    } else {
      // stop moving
      _status = WAIT;
      _interval = 0;
    }
  }

  static time_t now() {
    return micros();
  }

  static const time_t oneSecond = 1e6;

  pin_t _stepPin, _dirPin, _enablePin;
  time_t _lastTick, _interval;
  float_t _targetSpeed, _currentSpeed, _acceleration;
  bool _stepLevel;

  enum Status {
    OFF,
    WAIT,
    STEP,
    SKIP,
  };

  Status _status;
};
