#pragma once

#include <Arduino.h>

#include "attributes.h"

namespace ArduinoContinuousStepper {

class ContinuousStepperBase {
public:
  typedef unsigned long time_t;
  typedef double float_t;
  typedef uint8_t pin_t;

  void begin(pin_t stepPin, pin_t dirPin) {
    _stepPin = stepPin;
    _dirPin = dirPin;
    _status = WAIT;

    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);

    initialize();
  }

  CONTINUOUSSTEPPER_DEPRECATED("use setEnablePin() instead")
  void begin(pin_t stepPin, pin_t dirPin, pin_t enablePin) {
    begin(stepPin, dirPin);
    setEnablePin(enablePin);
  }

  void setEnablePin(pin_t enablePin, bool activeLevel = HIGH) {
    pinMode(enablePin, OUTPUT);
    digitalWrite(enablePin, (_status == OFF) ^ activeLevel);
    _enablePin = enablePin;
    _enablePinActiveLevel = activeLevel;
  }

  void powerOn() {
    if (_status != OFF)
      return;

    if (_enablePin != NULL_PIN)
      digitalWrite(_enablePin, _enablePinActiveLevel);

    updateSpeed();
  }

  void powerOff() {
    if (_enablePin != NULL_PIN)
      digitalWrite(_enablePin, !_enablePinActiveLevel);

    _status = OFF;
    _currentSpeed = 0;
    setPeriodIfChanged(0);
  }

  void spin(float_t speed) {
    _targetSpeed = speed;
    if (_status != OFF)
      updateSpeed();
  }

  void stop() {
    _targetSpeed = 0;
  }

  float_t speed() const {
    return _currentSpeed;
  }

  time_t period() const {
    return _period;
  }

  void setAcceleration(float_t acceleration) {
    _acceleration = acceleration;
    _minSpeedForAcceleration = sqrt(_acceleration);
  }

  bool isSpinning() const {
    return _status == STEP || _status == SKIP;
  }

protected:
  void tick() {
    if (_status == WAIT || _status == OFF)
      return;

    time_t t = now();
    time_t elapsed = t - _lastTick;

    if (elapsed >= _period / 2) {
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
    if (level == _dirLevel)
      return;
    digitalWrite(_dirPin, level);
    _dirLevel = level;
  }

  void updateSpeed() {
    float_t speedIncrement = _period ? _acceleration * _period / oneSecond : _minSpeedForAcceleration;

    if (_targetSpeed > _currentSpeed) {
      _currentSpeed = min(_currentSpeed + speedIncrement, _targetSpeed);
    }

    if (_targetSpeed < _currentSpeed) {
      _currentSpeed = max(_currentSpeed - speedIncrement, _targetSpeed);
    }

    if (abs(_currentSpeed) >= _minSpeedForAcceleration) {
      setPeriodIfChanged(oneSecond / abs(_currentSpeed));
      _status = STEP;
    } else if (abs(_targetSpeed) >= _minSpeedForAcceleration) {
      // crossing the zero on the speed graph
      setPeriodIfChanged(oneSecond / _minSpeedForAcceleration);
      _status = SKIP;
    } else if (_targetSpeed) {
      // target speed is not null but too low to allow a smooth acceleration
      setPeriodIfChanged(oneSecond / _targetSpeed);
      _status = STEP;
    } else {
      // target speed is null
      _status = WAIT;
      _currentSpeed = 0;
      setPeriodIfChanged(0);
    }
  }

  void setPeriodIfChanged(time_t period) {
    if (period != _period) {
      _period = period;
      setPeriod(period); // delegate to derived class
    }
  }

  virtual void initialize(){};
  virtual void setPeriod(time_t period) = 0;

  static time_t now() {
    return micros();
  }

  static const pin_t NULL_PIN = 255;
  static const time_t oneSecond = 1e6;

  pin_t _stepPin = 0, _dirPin = 0, _enablePin = NULL_PIN;
  time_t _lastTick = 0, _period = 0;
  float_t _targetSpeed = 0, _currentSpeed = 0, _acceleration = 1000, _minSpeedForAcceleration = sqrt(1000);
  bool _stepLevel = LOW, _dirLevel = LOW, _enablePinActiveLevel = HIGH;

  enum Status {
    OFF,
    WAIT,
    STEP,
    SKIP,
  };

  Status _status = OFF;
};

} // namespace ArduinoContinuousStepper
